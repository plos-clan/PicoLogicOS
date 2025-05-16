#pragma once
#include <coroutine.h>

NAKED void coroutine_switch(coroutine_regs_t from, coroutine_regs_t to) {
  asm volatile("mov %%rbx, 0(%%rdi)\n\t"
               "mov %%rbp, 8(%%rdi)\n\t"
               "mov %%rsp, 16(%%rdi)\n\t"
               "mov %%r12, 24(%%rdi)\n\t"
               "mov %%r13, 32(%%rdi)\n\t"
               "mov %%r14, 40(%%rdi)\n\t"
               "mov %%r15, 48(%%rdi)\n\t"

               "mov 0(%%rsi), %%rbx\n\t"
               "mov 8(%%rsi), %%rbp\n\t"
               "mov 16(%%rsi), %%rsp\n\t"
               "mov 24(%%rsi), %%r12\n\t"
               "mov 32(%%rsi), %%r13\n\t"
               "mov 40(%%rsi), %%r14\n\t"
               "mov 48(%%rsi), %%r15\n\t"

               :
               :
               : "memory");
}
