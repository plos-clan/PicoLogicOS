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

#define PICO_PAGE_SIZE 4096

#if PICO_PAGE_SIZE == 4096
#  define PICO_BLOCK_SIZE 32
#else
#  error "Unsupported page size"
#endif

#ifndef panic
#  define panic() ({ asm volatile("ud2"); })
#endif

typedef struct SmallAllocArea SmallAllocArea;
struct SmallAllocArea {
  SmallAllocArea *next;
  usize           free;
  i128            bitmap;
};

typedef struct PicoAlloc {
  usize size;
  void *(*reqmem)(usize size); // Request memory
  void (*relmem)(void *ptr);   // Release memory
  SmallAllocArea *small_alloc_areas;
} PicoAlloc;

static void *pico_alloc_small(usize size) {
  val delta = size;
  assume(delta != 0);
  assume(delta % PICO_BLOCK_SIZE == 0);
  assume((delta & (delta - 1)) == 0);
  for (usize i = 1, off = delta; off < PICO_PAGE_SIZE; i++, off += delta) {}
}

static void *pico_alloc_large(usize size) {}

void *pico_malloc(usize size) {
  if (likely(size <= PICO_PAGE_SIZE / 4)) {
    return pico_alloc_small(size);
  } else {
    return pico_alloc_large(size);
  }
}

static void pico_free_small(void *ptr) {
  val p = (usize)ptr;
}

static void pico_free_large(void *ptr) {
  val p = (usize)ptr;
}

void pico_free(void *ptr) {
  if (likely((usize)ptr & (PICO_PAGE_SIZE - 1))) {
    pico_free_small(ptr);
  } else {
    pico_free_large(ptr);
  }
}
