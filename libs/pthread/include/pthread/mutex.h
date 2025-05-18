#pragma once
#include <define.h>

// 互斥锁类型
typedef struct pthread_mutex {
  // 实现定义的互斥锁数据结构
  i32 locked;
  i32 holder;
  // 其他需要的字段...
} pthread_mutex_t;

// 互斥锁属性
typedef struct pthread_mutexattr {
  int type;
} pthread_mutexattr_t;

enum {
  PTHREAD_MUTEX_NORMAL,
  PTHREAD_MUTEX_ERRORCHECK,
  PTHREAD_MUTEX_RECURSIVE,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
};

enum {
  PTHREAD_PROCESS_PRIVATE,
  PTHREAD_PROCESS_SHARED,
};

enum {
  PTHREAD_MUTEX_STALLED,
  PTHREAD_MUTEX_ROBUST,
};

enum {
  PTHREAD_PRIO_NONE,
  PTHREAD_PRIO_INHERIT,
  PTHREAD_PRIO_PROTECT,
};

// 互斥锁函数
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
// int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);

// 互斥锁属性函数
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
