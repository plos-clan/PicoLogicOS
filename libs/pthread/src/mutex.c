#include <pthread.h>

int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
// int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abstime);

int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type) {
  *type = attr->type;
  return 0;
}
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type) {
  if (type != PTHREAD_MUTEX_NORMAL && type != PTHREAD_MUTEX_ERRORCHECK &&
      type != PTHREAD_MUTEX_RECURSIVE) {
    return EINVAL;
  }
  attr->type = type;
  return 0;
}
