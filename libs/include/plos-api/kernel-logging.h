#pragma once
#include <base.h>

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

dlimport void klog_raw(cstr s) __THROW __nnull(1);

// 请勿直接调用此函数
dlimport void klog(cstr _rest fmt, ...) __THROWNL __nnull(1) __attr(format(printf, 1, 2));

// 请勿直接调用此函数
dlimport void kprintf(cstr _rest fmt1, cstr _rest fmt2, ...) __THROWNL __nnull(1, 2)
    __attr(format(printf, 1, 3), format(printf, 2, 3));

#define __LOG(type, fmt, ...)                                                                      \
  klog(CONCAT(STR, type) STR_LOGINFO CONCAT(COLOR, type) fmt CEND "\n", ARG_LOGINFO, ##__VA_ARGS__)

#define klogd(fmt, ...) __LOG(_DEBUG, fmt, ##__VA_ARGS__)
#define klogi(fmt, ...) __LOG(_INFO, fmt, ##__VA_ARGS__)
#define klogw(fmt, ...) __LOG(_WARN, fmt, ##__VA_ARGS__)
#define kloge(fmt, ...) __LOG(_ERROR, fmt, ##__VA_ARGS__)
#define klogf(fmt, ...) __LOG(_FATAL, fmt, ##__VA_ARGS__)

#define _COLOR_DEBUG "\033[1;36m"
#define _COLOR_INFO  "\033[1;32m"
#define _COLOR_WARN  "\033[1;33m"
#define _COLOR_ERROR "\033[1;31m"
#define _COLOR_FATAL "\033[1;31m"

#define _STR_DEBUG "[" _COLOR_DEBUG "Debug" CEND "] "
#define _STR_INFO  "[" _COLOR_INFO "Info " CEND "] "
#define _STR_WARN  "[" _COLOR_WARN "Warn " CEND "] "
#define _STR_ERROR "[" _COLOR_ERROR "Error" CEND "] "
#define _STR_FATAL "[" _COLOR_FATAL "Fatal" CEND "] "

#define _STR_LOGINFO_FILE "[\033[1;35m%-12s" CEND "] "
#define _STR_LOGINFO_FUNC "[\033[1;36m%-20s" CEND ":\033[1;35m%4d" CEND "] "
#define _STR_LOGINFO      _STR_LOGINFO_FILE _STR_LOGINFO_FUNC

#undef _LOG
#define _LOG(type, fmt, ...)                                                                       \
  kprintf(CONCAT(STR, type) STR_LOGINFO   CONCAT(COLOR, type) fmt CEND "\n",                       \
          CONCAT(_STR, type) _STR_LOGINFO CONCAT(_COLOR, type) fmt CEND "\n", ARG_LOGINFO,         \
          ##__VA_ARGS__)

#undef fatal
#define fatal(fmt, ...)                                                                            \
  ({                                                                                               \
    _LOG(_INFO, "): Oops! Something is wrong with your Computer:");                                \
    _LOG(_FATAL, fmt, ##__VA_ARGS__);                                                              \
    abort();                                                                                       \
    __builtin_unreachable();                                                                       \
  })
