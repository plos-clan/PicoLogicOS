#pragma once
#include <define.h>

typedef struct coroutine_regs {
#if __i686__
  // x86-32 被调用者保存寄存器
  usize ebx;
  usize esi;
  usize edi;
  usize ebp;
  usize esp;
#endif

#if __x86_64__
  // x86-64 被调用者保存寄存器
  usize rbx;
  usize rbp;
  usize rsp;
  usize r12;
  usize r13;
  usize r14;
  usize r15;
#endif

#if defined(__ARM_ARCH) || defined(__arm__) || defined(__aarch64__)
// ARM 被调用者保存寄存器
#  if defined(__aarch64__) // ARM64
  usize x19;
  usize x20;
  usize x21;
  usize x22;
  usize x23;
  usize x24;
  usize x25;
  usize x26;
  usize x27;
  usize x28;
  usize x29; // 帧指针 (FP)
  usize x30; // 链接寄存器 (LR)
  usize sp;  // 栈指针
#  else      // ARM32
  usize r4;
  usize r5;
  usize r6;
  usize r7;
  usize r8;
  usize r9;
  usize r10;
  usize r11; // 帧指针
  usize lr;  // 链接寄存器
  usize sp;  // 栈指针
#  endif
#endif

#if __RISCV
  // RISC-V 被调用者保存寄存器
  usize s0;  // 帧指针/x8
  usize s1;  // x9
  usize s2;  // x18
  usize s3;  // x19
  usize s4;  // x20
  usize s5;  // x21
  usize s6;  // x22
  usize s7;  // x23
  usize s8;  // x24
  usize s9;  // x25
  usize s10; // x26
  usize s11; // x27
  usize sp;  // 栈指针/x2
  usize ra;  // 返回地址/x1
#endif

#if defined(_WIN64)
// Windows x64 调用约定下，XMM6-XMM15 是被调用者保存
#  if __AVX512F__
  usize zmm6_15[10][8]; // ZMM6-ZMM15 (每个 512 位/64 字节)
#  elif __AVX__
  usize ymm6_15[10][4]; // YMM6-YMM15 (每个 256 位/32 字节)
#  elif __SSE__
  usize xmm6_15[10][2]; // XMM6-XMM15 (每个 128 位/16 字节)
#  endif
#endif

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
  // ARM NEON 寄存器 (对于 AArch64)
  usize v[32]; // v8-v15 是被调用者保存
#endif
} *coroutine_regs_t;

NAKED void coroutine_switch(coroutine_regs_t from, coroutine_regs_t to);
