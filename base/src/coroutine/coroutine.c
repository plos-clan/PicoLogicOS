#include <coroutine.h>

usize coroutine_stack_size = 8192;

#if COROUTINE_MULTITHREAD
__thread coroutine_t coroutine_this = null;
#else
coroutine_t coroutine_this = null;
#endif

#if COROUTINE_MULTITHREAD
spin_t coroutine_lock = SPIN_INIT;
#endif

coroutine_t coroutine_waiting = null;

coroutine_t coroutine_task(coroutine_func_t func, void *userdata) {
  if (func == null) return null;
  coroutine_t coroutine = malloc(sizeof(struct coroutine));
  if (!coroutine) return NULL;

  val stack_size = coroutine_stack_size;

  coroutine->func  = func;
  coroutine->stack = malloc(stack_size);
  if (!coroutine->stack) {
    free(coroutine);
    return NULL;
  }
  coroutine->stack_size = stack_size;
  coroutine->retval     = null;
  coroutine->userdata   = userdata;

  return coroutine;
}

int coroutine_yield() {
  if (coroutine_waiting == null) return COROUTINE_NOTASK;
  struct timespec ts;
  if (__plos_coroutine_gettime(&ts) == 0) {
    val delta = (ts.tv_sec - coroutine_this->ts.tv_sec) * 1000000000 +
                (ts.tv_nsec - coroutine_this->ts.tv_nsec);
    if (delta < COROUTINE_TIMESLICE) return COROUTINE_SUCCESS;
  }
#if COROUTINE_MULTITHREAD
  spin_lock(coroutine_lock);
#endif
  coroutine_switch(&coroutine_this->regs, &coroutine_waiting->regs);
  coroutine_waiting_tail->next = coroutine_this;
  coroutine_waiting_tail       = coroutine_this;
  coroutine_this               = coroutine_waiting;
  coroutine_waiting            = coroutine_this->next;
  coroutine_this->next         = null;
#if COROUTINE_MULTITHREAD
  spin_unlock(coroutine_lock);
#endif
  return COROUTINE_SUCCESS;
}

int coroutine_resume(coroutine_t coroutine) {
  if (coroutine == null) return COROUTINE_NULARG;
#if COROUTINE_MULTITHREAD
  spin_lock(coroutine_lock);
#endif
  coroutine_switch(&coroutine_this->regs, &coroutine->regs);
  coroutine_waiting_tail->next = coroutine_this;
  coroutine_waiting_tail       = coroutine_this;
  coroutine_this               = coroutine_waiting;
  coroutine_waiting            = coroutine_this->next;
  coroutine_this->next         = null;
#if COROUTINE_MULTITHREAD
  spin_unlock(coroutine_lock);
#endif
  return COROUTINE_SUCCESS;
}

void coroutine_set_stack_size(usize size) {
  coroutine_stack_size = size;
}
