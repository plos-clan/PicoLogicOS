#pragma once
#include "../base.h"

#if !PLOS_LIBDATASTRUCTURE_SHOW_WARNING
#  pragma GCC system_header
#endif

#ifdef ALL_IMPLEMENTATION
#  define CIRCQUEUE_IMPLEMENTATION
#endif

// 环形队列
typedef struct cirqueue {
  byte  *buf;
  size_t tail;
  size_t head;
  size_t free;
  size_t len;
  size_t flags;
} *cirqueue_t;

#define FLAGS_OVERRUN 0x0001

#ifdef CIRCQUEUE_IMPLEMENTATION
#  define extern static
#endif

extern void cirqueue_init(cirqueue_t queue, size_t size, byte *buf);
extern int  cirqueue_put(cirqueue_t queue, byte data);
extern int  cirqueue_get(cirqueue_t queue);
extern int  cirqueue_len(cirqueue_t queue);

#ifdef CIRCQUEUE_IMPLEMENTATION
#  undef extern
#endif

#ifdef CIRCQUEUE_IMPLEMENTATION

static void cirqueue_init(cirqueue_t queue, size_t size, byte *buf) {
  queue->len   = size;
  queue->buf   = buf;
  queue->free  = size;
  queue->flags = 0;
  queue->tail  = 0;
  queue->head  = 0;
}

static int cirqueue_put(cirqueue_t queue, byte data) {
  if (queue->free == 0) {
    queue->flags |= FLAGS_OVERRUN;
    return -1;
  }
  queue->buf[queue->tail] = data;
  queue->tail++;
  if (queue->tail == queue->len) { queue->tail = 0; }
  queue->free--;
  return 0;
}

static int cirqueue_get(cirqueue_t queue) {
  int data;
  if (queue->free == queue->len) return -1; // 如果缓冲区为空则返回
  data = queue->buf[queue->head];
  queue->head++;
  if (queue->head == queue->len) { queue->head = 0; }
  queue->free++;
  return data;
}

static int cirqueue_len(cirqueue_t queue) {
  if (queue == null) return 0;
  return queue->len - queue->free;
}

static void cirqueue_copyto(cirqueue_t src, cirqueue_t dst) {
  if (dst->len != src->len) return;
  dst->free  = src->free;
  dst->flags = src->flags;
  dst->tail  = src->tail;
  dst->head  = src->head;
  memcpy(dst->buf, src->buf, src->len);
}

#  undef CIRCQUEUE_IMPLEMENTATION
#endif
