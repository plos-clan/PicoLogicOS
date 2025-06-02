#pragma once

#pragma GCC system_header

#include "00-include.h"

#if !DO_NOT_OVERRIDE_COMMON_NAMES
#  define fn auto
#endif

// 获取数组的长度
#ifndef lengthof
#  define lengthof(arr) (sizeof(arr) / sizeof(*(arr)))
#endif

// 获取表达式的类型，类似于 auto
#ifndef typeof
#  define typeof(arg) __typeof__((void)0, arg)
#endif

// 获取结构体成员的偏移量
#ifndef offsetof
#  define offsetof(t, d) __builtin_offsetof(t, d)
#endif

#ifndef alloca
#  define alloca(size) __builtin_alloca(size)
#endif

// 获取是否有指定内置函数
#if NO_BUILTIN
#  define __has(name) (0)
#else
#  define __has(name) (__has_builtin(__builtin_##name))
#endif

#define CONCAT_(a, b) a##b
#define CONCAT(a, b)  CONCAT_(a, b)

#if !DO_NOT_OVERRIDE_COMMON_NAMES
#  if defined(__clang__)
#    define assume(...) (__builtin_assume(__VA_ARGS__))
#  elif defined(__GNUC__)
#    define assume(...) (__attribute__((__assume__(__VA_ARGS__))))
#  elif defined(_MSC_VER)
#    define assume(...) (__assume(__VA_ARGS__))
#  else
#    define assume(...) ((void)0)
#  endif
#endif

#if !DO_NOT_OVERRIDE_COMMON_NAMES
#  define where(...) __attr(__assume__(__VA_ARGS__))
#endif

// likely 和 unlikely 用于分支预测
#define likely(expr)   (__builtin_expect(!!(expr), 1))
#define unlikely(expr) (__builtin_expect(!!(expr), 0))

// TODO 历史遗留问题
#if STD_SAFE_API
#  define __std_safe__(...) ((void)({__VA_ARGS__}))
#else
#  define __std_safe__(...) ((void)(0))
#endif

// TODO 历史遗留问题
#if SAFE_API
#  define __safe__(...) ((void)({__VA_ARGS__}))
#else
#  define __safe__(...) ((void)(0))
#endif

#define __ARGN_PRIVATE__(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15,     \
                         _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29,     \
                         _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43,     \
                         _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57,     \
                         _58, _59, _60, _61, _62, _63, _64, n, ...)                                \
  n
#define __ARGN__(...)                                                                              \
  __ARGN_PRIVATE__(0, ##__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50,   \
                   49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, \
                   29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, \
                   9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define COUNT_ARGS(...) __ARGN__(__VA_ARGS__)

#define PADDING_DOWN(size, to)                                                                     \
  ({                                                                                               \
    size_t _size_ = (size_t)(size);                                                                \
    size_t _to_   = (to);                                                                          \
    _size_        = _size_ / _to_ * _to_;                                                          \
    (typeof(size))_size_;                                                                          \
  })
#define PADDING_UP(size, to)                                                                       \
  ({                                                                                               \
    size_t _size_ = (size_t)(size);                                                                \
    size_t _to_   = (to);                                                                          \
    _size_        = (_size_ + _to_ - 1) / _to_ * _to_;                                             \
    (typeof(size))_size_;                                                                          \
  })

#if !DO_NOT_OVERRIDE_COMMON_NAMES
// 如果循环不会被打断，则使用 infinite_loop
#  define infinite_loop while (true)
// 如果循环会被打断，则使用 loop
#  define loop          while (true)
// 反正都是 while (true)
#endif

#if !DO_NOT_OVERRIDE_COMMON_NAMES
// waitif:    如果满足条件，则等待直到条件不满足
// waituntil: 如果不满足条件，则等待直到条件满足
#  if __i386__ || __x86_64__
#    define waitif(cond)                                                                           \
      ((void)({                                                                                    \
        while (cond) {                                                                             \
          asm volatile("pause\n\t" ::: "memory");                                                  \
        }                                                                                          \
      }))
#    define waituntil(cond)                                                                        \
      ((void)({                                                                                    \
        while (!(cond)) {                                                                          \
          asm volatile("pause\n\t" ::: "memory");                                                  \
        }                                                                                          \
      }))
#  elif __arm__ || __aarch64__
#    define waitif(cond)                                                                           \
      ((void)({                                                                                    \
        while (cond) {                                                                             \
          asm volatile("yield\n\t" ::: "memory");                                                  \
        }                                                                                          \
      }))
#    define waituntil(cond)                                                                        \
      ((void)({                                                                                    \
        while (!(cond)) {                                                                          \
          asm volatile("yield\n\t" ::: "memory");                                                  \
        }                                                                                          \
      }))
#  elif __riscv
#    define waitif(cond)                                                                           \
      ((void)({                                                                                    \
        while (cond) {                                                                             \
          asm volatile("nop\n\t" ::: "memory");                                                    \
        }                                                                                          \
      }))
#    define waituntil(cond)                                                                        \
      ((void)({                                                                                    \
        while (!(cond)) {                                                                          \
          asm volatile("nop\n\t" ::: "memory");                                                    \
        }                                                                                          \
      }))
#  endif
#endif
