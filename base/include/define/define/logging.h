//| ============================================================================================================== |
//| Copyright (c) 2025 plos-clan                                                                                   |
//|                                                                                                                |
//| This file is part of the Pico Logic OS.                                                                        |
//|                                                                                                                |
//| Licensed under either of:                                                                                      |
//| - Apache License, Version 2.0 (see LICENSE-APACHE or http://www.apache.org/licenses/LICENSE-2.0)               |
//| - MIT License (see LICENSE-MIT or https://opensource.org/licenses/MIT)                                         |
//| at your option.                                                                                                |
//|                                                                                                                |
//| Unless required by applicable law or agreed to in writing, software distributed                                |
//| under these licenses is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES                                    |
//| OR CONDITIONS OF ANY KIND, either express or implied. See the licenses for details.                            |
//| ============================================================================================================== |

#pragma once

#pragma GCC system_header

#include "00-include.h"

#if LOG_RGB_SUPPORTED
// 设置终端颜色的转义序列
#  define CRGB(r, g, b)  "\033[38;2;" #r ";" #g ";" #b "m"
#  define CBRGB(r, g, b) "\033[48;2;" #r ";" #g ";" #b "m"
#  define CEND           "\033[0m"
#endif

#if LOG_RGB_SUPPORTED
#  define COLOR_DEBUG CRGB(128, 192, 255)
#  define COLOR_INFO  CRGB(64, 192, 128)
#  define COLOR_WARN  CRGB(255, 192, 0)
#  define COLOR_ERROR CRGB(255, 128, 64)
#  define COLOR_FATAL CRGB(255, 64, 64)
#else
#  define COLOR_DEBUG "\033[1;36m"
#  define COLOR_INFO  "\033[1;32m"
#  define COLOR_WARN  "\033[1;33m"
#  define COLOR_ERROR "\033[1;31m"
#  define COLOR_FATAL "\033[1;31m"
#endif

#define STR_DEBUG "[" COLOR_DEBUG "Debug" CEND "] "
#define STR_INFO  "[" COLOR_INFO "Info " CEND "] "
#define STR_WARN  "[" COLOR_WARN "Warn " CEND "] "
#define STR_ERROR "[" COLOR_ERROR "Error" CEND "] "
#define STR_FATAL "[" COLOR_FATAL "Fatal" CEND "] "

// 这是屎山，不用看 (其实就是给 memcmp() == 0 展开了)

static inline
    __attribute__((always_inline, nonnull(1, 2), access(read_only, 1, 3), access(read_only, 2, 3)))
#if !defined(__cplusplus) && __STDC_VERSION__ < 202311L
    _Bool
#else
    bool
#endif
    _log_memeq_(const void *a, const void *b, __UINTPTR_TYPE__ size) {
  const __UINT8_TYPE__ *p = (const __UINT8_TYPE__ *)a;
  const __UINT8_TYPE__ *q = (const __UINT8_TYPE__ *)b;
  for (__UINTPTR_TYPE__ i = 0; i < size; i++) {
#if !defined(__cplusplus) && __STDC_VERSION__ < 202311L
    if (p[i] != q[i]) return (_Bool)0;
#else
    if (p[i] != q[i]) return false;
#endif
  }
#if !defined(__cplusplus) && __STDC_VERSION__ < 202311L
  return (_Bool)1;
#else
  return true;
#endif
}

static __attribute__((nonnull(1))) const char *_log_basename_(const char *path) {
  __INTPTR_TYPE__ i = 0;
  while (path[i] != '\0')
    i++;
  for (i--; i >= 0; i--) {
    if (path[i] == '/' || path[i] == '\\') break;
  }
  return path + i + 1;
}

static __attribute__((nonnull(1))) const char *_log_relative_path_(const char *path) {
  __INTPTR_TYPE__ i = 0;
  while (path[i] != '\0')
    i++;
  for (__INTPTR_TYPE__ j = i - 3; j >= 0; j--) {
    if (_log_memeq_(path + j, "OS/", 3)) return path + j + 3;
  }
  return path;
}

#define ARG_LOGINFO_FILE _log_basename_(__FILE__)
#define STR_LOGINFO_FILE "[" CRGB(192, 128, 255) "%-12s" CEND "] "
#define ARG_LOGINFO_FUNC __func__, __LINE__
#define STR_LOGINFO_FUNC "[" CRGB(0, 255, 255) "%-20s" CEND ":" CRGB(255, 128, 192) "%4d" CEND "] "

#define ARG_LOGINFO ARG_LOGINFO_FILE, ARG_LOGINFO_FUNC
#define STR_LOGINFO STR_LOGINFO_FILE STR_LOGINFO_FUNC

#if !LOG_RGB_SUPPORTED
#  undef STR_LOGINFO_FILE
#  undef STR_LOGINFO_FUNC
#  define STR_LOGINFO_FILE "[\033[1;35m%-12s" CEND "] "
#  define STR_LOGINFO_FUNC "[\033[1;36m%-20s" CEND ":\033[1;35m%4d" CEND "] "
#endif

#define _LOG(type, fmt, ...)                                                                       \
  printf(CONCAT(STR, type) STR_LOGINFO CONCAT(COLOR, type) fmt CEND "\n", ARG_LOGINFO,             \
         ##__VA_ARGS__)

#ifdef DEBUG
#  define printd(fmt, ...) _LOG(_DEBUG, fmt, ##__VA_ARGS__)
#else
#  define printd(fmt, ...) _LOG(_DEBUG, fmt, ##__VA_ARGS__)
#endif

#define printi(fmt, ...) _LOG(_INFO, fmt, ##__VA_ARGS__)
#define printw(fmt, ...) _LOG(_WARN, fmt, ##__VA_ARGS__)
#define printe(fmt, ...) _LOG(_ERROR, fmt, ##__VA_ARGS__)

#define info(fmt, ...)  printi(fmt, ##__VA_ARGS__)
#define warn(fmt, ...)  printw(fmt, ##__VA_ARGS__)
#define error(fmt, ...) printe(fmt, ##__VA_ARGS__)
#define fatal(fmt, ...)                                                                            \
  ({                                                                                               \
    _LOG(_FATAL, fmt, ##__VA_ARGS__);                                                              \
    abort();                                                                                       \
    __builtin_unreachable();                                                                       \
  })

#if defined(DEBUG) && !defined(NO_MALLOC_MESSAGE)
#  define malloc(size)                                                                             \
    ({                                                                                             \
      size_t __size = (size);                                                                      \
      void  *__ptr  = malloc(__size);                                                              \
      printd("分配对象 %p 大小 %ld", __ptr, __size);                                               \
      __ptr;                                                                                       \
    })
#  define free(ptr)                                                                                \
    ({                                                                                             \
      void *__ptr = (void *)(ptr);                                                                 \
      printd("释放对象 %p", __ptr);                                                                \
      free(__ptr);                                                                                 \
    })
#endif
