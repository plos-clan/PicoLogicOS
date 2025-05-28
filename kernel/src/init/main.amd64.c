#include <base.h>
#include <kernel.h>
#include <limine.h>

//| ============================================================================================================== |
//| Copyright (c) 2025 plos-clan                                                                                   |
//|                                                                                                                |
//| This file is part of the Pico Logic OS.                                                                        |
//|                                                                                                                |
//| Licensed under either of:                                                                                      |
//| - Apache License, Version 2.0 (see LICENSE-APACHE or http://www.apache.org/licenses/LICENSE-2.0)               |
//| - MIT License (see LICENSE-MIT or https://opensource.org/licenses/MIT)                                         |
//| at your option.                                                                                                |
//|                                                                                                                |
//| Unless required by applicable law or agreed to in writing, software distributed                                |
//| under these licenses is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES                                    |
//| OR CONDITIONS OF ANY KIND, either express or implied. See the licenses for details.                            |
//| ============================================================================================================== |

static void kernel_main();

#define PLOS_LIMINE_REVISION 3

LIMINE_REQUEST_MARKERS;

LIMINE_REQUEST LIMINE_BASE_REVISION(PLOS_LIMINE_REVISION);

LIMINE_REQUEST struct limine_framebuffer_request fb = {
    .id       = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
};

LIMINE_REQUEST struct limine_mp_request mp = {
    .id       = LIMINE_MP_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
    .flags    = MASK(0),
};

LIMINE_REQUEST struct limine_memmap_request mmap = {
    .id       = LIMINE_MEMMAP_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
};

LIMINE_REQUEST struct limine_paging_mode_request pgmode = {
    .id       = LIMINE_PAGING_MODE_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
    .mode     = LIMINE_PAGING_MODE_DEFAULT,
    .max_mode = LIMINE_PAGING_MODE_X86_64_5LVL,
    .min_mode = LIMINE_PAGING_MODE_X86_64_4LVL,
};

LIMINE_REQUEST struct limine_hhdm_request hhdm = {
    .id       = LIMINE_HHDM_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
};

LIMINE_REQUEST struct limine_stack_size_request ss = {
    .id         = LIMINE_STACK_SIZE_REQUEST,
    .revision   = PLOS_LIMINE_REVISION,
    .stack_size = 65536,
};

LIMINE_REQUEST struct limine_entry_point_request entry = {
    .id       = LIMINE_ENTRY_POINT_REQUEST,
    .revision = PLOS_LIMINE_REVISION,
    .entry    = &kernel_main,
};

void percpu_main(struct limine_mp_info *core) {
  asm_cli;

  asm_wrmsr(IA32_FS_BASE, 0);
  asm_wrmsr(IA32_GS_BASE, core->extra_argument);
  asm_wrmsr(IA32_KERNEL_GS_BASE, core->extra_argument);

  if (fb.response == null || fb.response->framebuffer_count < 1) infinite_loop asm_hlt;

  val framebuffer = fb.response->framebuffers[0];

  u32 *fb_ptr = framebuffer->address;
  vectorize for (usize i = 0; i < 100; i++) {
    fb_ptr[i * (framebuffer->pitch / 4) + i + core->processor_id * 16] = 0xffffff;
  }

  infinite_loop asm_hlt;
}

USED SECTION(".plos_loader_info") static const volatile struct {
  u8 signature[4];
} info;

void klog_raw(cstr s);

void klog_number(u64 n) {
  char  buf[32];
  char *p = buf + sizeof(buf);
  *--p    = '\0';
  *--p    = '\n';
  do {
    *--p  = '0' + (n % 10);
    n    /= 10;
  } while (n != 0);
  klog_raw(p);
}

void klog_number16(u64 n) {
  char  buf[32];
  char *p = buf + sizeof(buf);
  *--p    = '\0';
  *--p    = '\n';
  do {
    u64 r = n % 16;
    if (r < 10) {
      *--p = '0' + r;
    } else {
      *--p = 'a' + (r - 10);
    }
    n /= 16;
  } while (n != 0);
  klog_raw(p);
}

void print_pt() {
  val pml4 = (PML4E *)(asm_get_cr3() + hhdm.response->offset);
  klog_number16((usize)pml4);
  for (usize i = 0; i < 512; i++) {
    klog_number16(pml4[i].addr);
  }
}

/* >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>> >>>>>

 +      内存布局      +

 | 0xffffffffffffffff |
 |                    |
 |                    |
 |                    |  <=  内核其它映射
 |                    |
 | 0xffffc00000000000 |
 | 0xffffbfffffffffff |
 |                    |  <=  物理内存直接映射 (读写)
 | 0xffffa00000000000 |
 | 0xffff9fffffffffff |
 |                    |  <=  物理内存直接映射 (只读)
 | 0xffff800000000000 |
 | 0x00007fffffffffff |
 |                    |
 |                    |
 |                    |
 |                    |
 |                    |  <=  用户空间
 |                    |
 |                    |
 |                    |
 |                    |
 |                    |
 | 0x0000000000000000 |

<<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< <<<<< */

static void memory_init() {
  usize max_usable_addr = 0;
  usize max_usable_size = 0;

  usize mem_total_size  = 0;
  usize mem_usable_size = 0;
  for (usize i = 0; i < mmap.response->entry_count; i++) {
    val entry       = mmap.response->entries[i];
    mem_total_size += entry->length;
    if (entry->type == LIMINE_MEMMAP_USABLE) {
      if (entry->length > max_usable_size) {
        max_usable_addr = entry->base;
        max_usable_size = entry->length;
      }
    } else if (entry->type == LIMINE_MEMMAP_RESERVED) {
    } else if (entry->type == LIMINE_MEMMAP_ACPI_RECLAIMABLE) {
    } else if (entry->type == LIMINE_MEMMAP_ACPI_NVS) {
    } else if (entry->type == LIMINE_MEMMAP_BAD_MEMORY) {
    } else if (entry->type == LIMINE_MEMMAP_BOOTLOADER_RECLAIMABLE) {
    } else if (entry->type == LIMINE_MEMMAP_EXECUTABLE_AND_MODULES) {
    } else if (entry->type == LIMINE_MEMMAP_FRAMEBUFFER) {
    } else {
      infinite_loop asm_hlt;
    }
  }
}

#define NORETURN    __attr(noreturn)
#define RETURNTWICE __attr(return_twice)

__attr(returns_nonnull) __attr(nonnull(1)) void *func(void *a) {
  return null;
}

static void kernel_main() {
  asm_cli;

  if (!LIMINE_BASE_REVISION_SUPPORTED) infinite_loop asm_hlt;

  if (mp.response == null) infinite_loop asm_hlt;

  for (usize i = 0; i < mp.response->cpu_count; i++) {
    val core             = mp.response->cpus[i];
    core->goto_address   = &percpu_main;
    core->extra_argument = 0;
  }

  asm_wrmsr(IA32_FS_BASE, 0);
  asm_wrmsr(IA32_GS_BASE, 0);
  asm_wrmsr(IA32_KERNEL_GS_BASE, 0);

  memory_init();

  if (fb.response == null || fb.response->framebuffer_count < 1) infinite_loop asm_hlt;

  val framebuffer = fb.response->framebuffers[0];

  volatile u32 *fb_ptr = framebuffer->address;
  vectorize for (usize i = 0; i < 100; i++) {
    fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xff00ff;
  }

  klog_number16(hhdm.response->offset);

  print_pt();

  klog_number(pgmode.response->mode);

  klog_number(INT_MAX + 2);
  klog_number(INT_MIN - 2);
  klog_number(INT_MAX * 2);

  func(null);

  __builtin_clz(0);

  char aaa[1];
  aaa[-1] = '\0';

  klog_number(-INT_MIN);

  int  n = -2;
  char a[n];

  infinite_loop asm_hlt;
}

// void _start() { // 如果在 linux 下被执行
//   __syscall(1, 1, "Hello World!\n", 13);
//   __syscall(60, 0);
//   infinite_loop asm_hlt;
// }

#define vaddrof(paddr) ((usize)(paddr) + hhdm.response->offset)
