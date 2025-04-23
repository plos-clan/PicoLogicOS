#pragma once

#define ADDRESS_SPACE(x) __attr(address_space(x))

typedef struct pcb *pcb_t;
typedef struct tcb *tcb_t;

struct pcb {
  i32   pid;      // 进程 ID
  tcb_t tcb;      // 线程控制块
  usize nthreads; // 线程数量
};

struct tcb {
  i32   tid;   // 线程 ID
  pcb_t pcb;   // 进程控制块
  usize stack; // 栈指针
};

static ADDRESS_SPACE(257) struct tcb *const tcb = (ADDRESS_SPACE(257) void *)0;
