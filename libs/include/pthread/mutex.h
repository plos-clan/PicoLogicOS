#pragma once
#include <define.h>

// 互斥锁类型
typedef struct pthread_mutex {
  // 实现定义的互斥锁数据结构
  int locked;
  // 其他需要的字段...
} pthread_mutex_t;

// 互斥锁属性
typedef struct pthread_mutexattr {
  // 实现定义的互斥锁属性结构
  int type;
  // 其他需要的属性...
} pthread_mutexattr_t;

// 互斥锁函数
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);

// 互斥锁属性函数
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
