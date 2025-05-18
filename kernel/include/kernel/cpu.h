#pragma once
#include "./typedefs.h"

struct cpu {
  i32   id;
  i32   apic_id;
  usize sp;
};

static ADDRESS_SPACE(256) struct cpu *const cpu = (ADDRESS_SPACE(256) void *)0;

struct regs16 {
  u16 di, si, bp, _, bx, dx, cx, ax;
  u16 gs, fs, es, ds;
};

// 可参考 https://www.felixcloutier.com/x86/iret:iretd:iretq

/**
 *\brief 32 位保护模式下中断处理程序的寄存器
 *
 */
struct regs32 {
  u32 edi, esi, ebp, _, ebx, edx, ecx, eax;
  u32 gs, fs, es, ds;
  u32 id, err; // err: 当中断具有错误码时为错误码，否则为中断号
  u32 eip, cs, flags, esp, ss;
};

struct regs64 {
  u64 rax;
  u64 rbx;
  u64 rcx;
  u64 rdx;
  u64 rsi;
  u64 rdi;
  u64 rbp;
  u64 rsp;
  u64 r8;
  u64 r9;
  u64 r10;
  u64 r11;
  u64 r12;
  u64 r13;
  u64 r14;
  u64 r15;
};

#ifdef __x86_64__
typedef regs64_t regs_t;
#else
typedef regs32_t regs_t;
#endif

typedef struct SegmentDescriptor {
  u16  limit_low;
  u16  base_low;
  byte base_mid;
  byte access_right;
  byte limit_high;
  byte base_high;
#ifdef __x86_64__
  u32 base_upper;
  u32 reserved;
#endif
} SegmentDescriptor;

typedef struct GateDescriptor {
  u16  offset_low;
  u16  selector;
  byte dw_count;
  byte access_right;
  u16  offset_high;
#ifdef __x86_64__
  u32 offset_upper;
  u32 reserved;
#endif
} GateDescriptor;
