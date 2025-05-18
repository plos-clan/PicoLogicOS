#pragma once
#include <define.h>

// 定义信号量结构体（根据具体实现需要调整）
typedef struct {
  int count; // 信号量计数
} sem_t;

// 初始化信号量
int sem_init(sem_t *sem, int pshared, unsigned int value);

// 销毁信号量
int sem_destroy(sem_t *sem);

// 等待信号量
int sem_wait(sem_t *sem);

// 尝试等待信号量
int sem_trywait(sem_t *sem);

// 释放信号量
int sem_post(sem_t *sem);

// 获取信号量当前值
int sem_getvalue(sem_t *sem, int *sval);
