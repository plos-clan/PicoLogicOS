#pragma once
#include <define.h>

// 线程标识符
typedef usize pthread_t;

// 线程属性
typedef struct pthread_attr {
  // 实现定义的线程属性结构
  int    detachstate;
  size_t stacksize;
  void  *stackaddr;
  // 其他需要的属性...
} pthread_attr_t;

// 线程特定数据键
typedef unsigned int pthread_key_t;

// 一次性初始化控制
typedef int pthread_once_t;
#define PTHREAD_ONCE_INIT 0

// 互斥锁初始化宏
#define PTHREAD_MUTEX_INITIALIZER {0}

// 条件变量初始化宏
#define PTHREAD_COND_INITIALIZER {0}

// 互斥锁类型常量
#define PTHREAD_MUTEX_NORMAL     0
#define PTHREAD_MUTEX_RECURSIVE  1
#define PTHREAD_MUTEX_ERRORCHECK 2
#define PTHREAD_MUTEX_DEFAULT    PTHREAD_MUTEX_NORMAL

// 线程分离状态常量
#define PTHREAD_CREATE_JOINABLE 0
#define PTHREAD_CREATE_DETACHED 1

// 取消状态常量
#define PTHREAD_CANCEL_ENABLE  0
#define PTHREAD_CANCEL_DISABLE 1

// 取消类型常量
#define PTHREAD_CANCEL_DEFERRED     0
#define PTHREAD_CANCEL_ASYNCHRONOUS 1

// 取消返回值
#define PTHREAD_CANCELED ((void *)-1)

// 线程管理函数
int  pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *),
                    void *arg);
void pthread_exit(void *retval);
int  pthread_join(pthread_t thread, void **retval);
int  pthread_detach(pthread_t thread);
pthread_t pthread_self();
int       pthread_equal(pthread_t t1, pthread_t t2);
int       pthread_once(pthread_once_t *once_control, void (*init_routine)());
int       pthread_cancel(pthread_t thread);
int       pthread_setcancelstate(int state, int *oldstate);
int       pthread_setcanceltype(int type, int *oldtype);
void      pthread_testcancel();

// 线程特定数据函数
int   pthread_key_create(pthread_key_t *key, void (*destructor)(void *));
int   pthread_key_delete(pthread_key_t key);
int   pthread_setspecific(pthread_key_t key, const void *value);
void *pthread_getspecific(pthread_key_t key);

// 线程属性函数
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
int pthread_attr_getstacksize(const pthread_attr_t *attr, size_t *stacksize);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stacksize);
int pthread_attr_getstackaddr(const pthread_attr_t *attr, void **stackaddr);
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stackaddr);
