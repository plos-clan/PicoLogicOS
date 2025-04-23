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

#if __INT_WIDTH__ != 32
#  error "int 必须为 int32"
#endif

#if __FLT_RADIX__ != 2
#  error "浮点数必须是二进制的"
#endif

#if __FLT_MANT_DIG__ != 24
#  error "float 必须为 32 位浮点数"
#endif

#if __DBL_MANT_DIG__ != 53
#  error "double 必须为 64 位浮点数"
#endif

typedef signed char        schar; // 在大多数环境下 schar 就是 char
typedef unsigned char      uchar;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long      ulong;
typedef long long          llong;
typedef unsigned long long ullong;

#if PLOS_USE_BITINT_FOR_INTN

typedef _BitInt(8) int8_t;
typedef _BitInt(16) int16_t;
typedef _BitInt(32) int32_t;
typedef _BitInt(64) int64_t;
typedef unsigned _BitInt(8) uint8_t;
typedef unsigned _BitInt(16) uint16_t;
typedef unsigned _BitInt(32) uint32_t;
typedef unsigned _BitInt(64) uint64_t;
#  ifdef __x86_64__
typedef _BitInt(128) int128_t;
typedef unsigned _BitInt(128) uint128_t;
#  endif

#else

typedef __INT8_TYPE__   int8_t;
typedef __INT16_TYPE__  int16_t;
typedef __INT32_TYPE__  int32_t;
typedef __INT64_TYPE__  int64_t;
typedef __UINT8_TYPE__  uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;
#  ifdef __x86_64__
typedef __int128          int128_t;
typedef unsigned __int128 uint128_t;
#  endif

#endif

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#ifdef __x86_64__
typedef int128_t  i128;
typedef uint128_t u128;
#endif

typedef __INTMAX_TYPE__  intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;
typedef intmax_t         imax;
typedef uintmax_t        umax;

#if PLOS_ABBR_FLOATN
typedef float  float32_t;
typedef double float64_t;
#  if defined(__x86_64__) && !NO_EXTFLOAT
typedef _Float16   float16_t; // 命名最不统一的一集
typedef __float128 float128_t;
#  endif
#endif

#if PLOS_ABBR_FN
typedef float32_t f32;
typedef float64_t f64;
#  if defined(__x86_64__) && !NO_EXTFLOAT
typedef float16_t  f16;
typedef float128_t f128;
#  endif
#endif
