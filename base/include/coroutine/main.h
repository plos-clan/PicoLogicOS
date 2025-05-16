#pragma once
#include "regs.h"
#include <base.h>

typedef struct coroutine *coroutine_t;

typedef void *(*coroutine_func_t)(void *userdata);
typedef bool (*coroutine_cond_t)(void *userdata);

struct coroutine {
  struct coroutine_regs regs;
  coroutine_func_t      func;
  void                 *stack;      // 栈顶
  usize                 stack_size; // 栈大小
  void                 *retval;
  void                 *userdata;
  struct timespec       ts; // 协程当前运行的时间
  coroutine_t           prev;
  coroutine_t           next;
};

#define COROUTINE_TIMESLICE 10000000 // 10ms

extern usize coroutine_stack_size; // 栈大小

#if COROUTINE_MULTITHREAD
extern __thread coroutine_t coroutine_this;
#else
extern coroutine_t coroutine_this;
#endif

#if COROUTINE_MULTITHREAD
extern spin_t coroutine_lock; // 多线程下的调度锁
#endif

extern coroutine_t coroutine_waiting; // 等待队列
extern coroutine_t coroutine_waiting_tail;

#define COROUTINE_SUCCESS (0)  // 成功
#define COROUTINE_ERROR   (-1) // 错误
#define COROUTINE_NOTASK  (-2) // 除正在运行的协程外没有可运行的协程
#define COROUTINE_NOMEM   (-3) // 内存不足
#define COROUTINE_NULARG  (-4) // 参数为空

/**
 *\brief 初始化协程全局上下文（如果为多个线程初始化则每个线程都要调用一次）
 *
 *\return 是否成功
 */
int         coroutine_init();
/**
 *\brief 销毁协程全局上下文（每个 init 都要有一个 deinit）
 *
 */
void        coroutine_deinit();
/**
 *\brief 创建一个协程
 *
 *\param func     协程函数
 *\param userdata 用户数据
 *\return 协程对象
 */
coroutine_t coroutine_task(coroutine_func_t func, void *userdata);
/**
 *\brief 切换协程
 *
 *\return 是否成功
 */
int         coroutine_yield();
/**
 *\brief 恢复协程
 *
 *\param coroutine 协程对象
 *\return 是否成功
 */
int         coroutine_resume(coroutine_t coroutine);
/**
 *\brief 等待协程结束
 *
 *\param coroutine 协程对象
 *\return 是否成功
 */
int         coroutine_wait(coroutine_t coroutine);
/**
 *\brief 等待协程结束（带超时）
 *
 *\param coroutine 协程对象
 *\param timeout   超时时间
 *\return 是否成功
 */
int         coroutine_wait_timeout(coroutine_t coroutine, const struct timespec *timeout);
/**
 *\brief 等待条件
 *
 *\param cond     条件
 *\param userdata 用户数据
 *\return 是否成功
 */
int         coroutine_waituntil(coroutine_cond_t cond, void *userdata);
int         coroutine_waituntil_timeout(coroutine_cond_t cond, void *userdata,
                                        const struct timespec *timeout);

void coroutine_free(coroutine_t coroutine);
void coroutine_exit(coroutine_t coroutine, void *retval);
void coroutine_set_stack_size(usize size);
void coroutine_set_retval(coroutine_t coroutine, void *retval);
void coroutine_set_regs(coroutine_t coroutine, struct coroutine_regs *regs);
void coroutine_get_regs(coroutine_t coroutine, struct coroutine_regs *regs);

void *__plos_coroutine_alloc_stack(usize size);
int   __plos_coroutine_gettime(struct timespec *ts);
