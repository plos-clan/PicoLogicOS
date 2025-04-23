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
#include "00-include.hpp"

// 与 include/define/define/rc.h 行为相同

namespace cpp::rc {

template <typename T>
finline auto alloc(size_t size) -> T * {
  var *ptr = (size_t *)::malloc(size * sizeof(T) + sizeof(size_t));
  if (ptr != null) {
    ptr[0]  = 1;
    ptr    += 1;
  }
  return (T *)ptr;
}

template <typename T>
finline auto free(T *ptr) -> void {
  var *p = (size_t *)ptr;
  if (p != null) ::free(p - 1);
}

template <typename T>
finline auto refcnt(T *ptr) -> size_t {
  size_t rc = 0;
  var   *p  = (size_t *)ptr;
  if (p != null) rc = p[-1];
  return rc;
}

template <typename T>
finline auto ref(T *ptr) -> size_t {
  size_t rc = 0;
  var   *p  = (size_t *)ptr;
  if (p != null) rc = ++p[-1];
  return rc;
}

template <typename T>
finline auto unref(T *ptr) -> size_t {
  size_t rc = 0;
  var   *p  = (size_t *)ptr;
  if (p != null) {
    rc = --p[-1];
    if (rc == 0) ::free(p - 1);
  }
  return rc;
}

} // namespace cpp::rc
