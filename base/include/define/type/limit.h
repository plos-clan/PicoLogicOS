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

#define INT_MIN    (-__INT_MAX__ - 1)
#define INT_MAX    __INT_MAX__
#define UINT_MAX   ((unsigned int)-1)
#define LONG_MIN   (-__LONG_MAX__ - 1)
#define LONG_MAX   __LONG_MAX__
#define ULONG_MAX  ((unsigned long)-1)
#define LLONG_MIN  (-__LONG_LONG_MAX__ - 1)
#define LLONG_MAX  __LONG_LONG_MAX__
#define ULLONG_MAX ((unsigned long long)-1)

#define INT8_MIN   (-__INT8_MAX__ - 1)
#define INT8_MAX   __INT8_MAX__
#define UINT8_MAX  __UINT8_MAX__
#define INT16_MIN  (-__INT16_MAX__ - 1)
#define INT16_MAX  __INT16_MAX__
#define UINT16_MAX __UINT16_MAX__
#define INT32_MIN  (-__INT32_MAX__ - 1)
#define INT32_MAX  __INT32_MAX__
#define UINT32_MAX __UINT32_MAX__
#define INT64_MIN  (-__INT64_MAX__ - 1)
#define INT64_MAX  __INT64_MAX__
#define UINT64_MAX __UINT64_MAX__

#define INTMAX_MIN  (-__INTMAX_MAX__ - 1)
#define INTMAX_MAX  __INTMAX_MAX__
#define UINTMAX_MAX __UINTMAX_MAX__

#define SSIZE_MAX ((__INTPTR_TYPE__)(__SIZE_MAX__ >> 1))
#define SSIZE_MIN (-SSIZE_MAX - 1)
#define SIZE_MAX  __SIZE_MAX__

#define ISIZE_MAX SSIZE_MAX
#define ISIZE_MIN SSIZE_MIN
#define USIZE_MAX SIZE_MAX

#define I8_MIN  (-__INT8_MAX__ - 1)
#define I8_MAX  __INT8_MAX__
#define U8_MAX  __UINT8_MAX__
#define I16_MIN (-__INT16_MAX__ - 1)
#define I16_MAX __INT16_MAX__
#define U16_MAX __UINT16_MAX__
#define I32_MIN (-__INT32_MAX__ - 1)
#define I32_MAX __INT32_MAX__
#define U32_MAX __UINT32_MAX__
#define I64_MIN (-__INT64_MAX__ - 1)
#define I64_MAX __INT64_MAX__
#define U64_MAX __UINT64_MAX__

#define IMAX_MIN (-__INTMAX_MAX__ - 1)
#define IMAX_MAX __INTMAX_MAX__
#define UMAX_MAX __UINTMAX_MAX__

#define FLT_RADIX    __FLT_RADIX__
#define FLT_MANT_DIG __FLT_MANT_DIG__
