#pragma once

typedef struct pcb *pcb_t;
typedef struct tcb *tcb_t;

typedef struct cpu *cpu_t;

// 中断处理程序的寄存器
typedef struct regs16 regs16, *regs16_t;
typedef struct regs32 regs32, *regs32_t;
typedef struct regs64 regs64, *regs64_t;

typedef struct syscall_regs32 syscall_regs32, *syscall_regs32_t;
typedef struct syscall_regs64 syscall_regs64, *syscall_regs64_t;
