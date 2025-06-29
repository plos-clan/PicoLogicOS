#pragma once

#pragma GCC system_header

#include "00-include.h"

// gcc 扩展，让 C 中的 auto 具有和 C++ 类似的语义
// 神经你 C23 加这鬼玩意干嘛，没活可以咬个打火机
// keyword is hidden by macro definition 但我们不要管它
#if !defined(__cplusplus) && __STDC_VERSION__ < 202311L
#  define auto __auto_type
#endif

#if !DO_NOT_OVERRIDE_COMMON_NAMES
#  define var auto
#  define val const auto
#endif

#ifdef __cplusplus
static val null = nullptr;
#else
#  define null ((void *)0)
#endif

#define NULL 0

typedef __INT8_TYPE__  sbyte;
typedef __UINT8_TYPE__ byte;

typedef int errno_t;

typedef __INT64_TYPE__ time_t;

#ifdef __cplusplus
#  if !DO_NOT_OVERRIDE_COMMON_NAMES
#    define lit constexpr
#  endif
#endif
