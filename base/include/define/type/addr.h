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

#if __INTPTR_WIDTH__ == 32
#elif __INTPTR_WIDTH__ == 64
#else
#  error "指针宽度必须为 32 或 64"
#endif

typedef __INTPTR_TYPE__  intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef intptr_t         iptr;
typedef uintptr_t        uptr;
typedef __INTPTR_TYPE__  ssize_t;
typedef __UINTPTR_TYPE__ size_t;
typedef __INTPTR_TYPE__  ptrdiff_t;
typedef ssize_t          isize;
typedef size_t           usize;

typedef union __attr(transparent_union) {
  isize       ivalue;
  usize       uvalue;
  usize       value;
  void       *ptr;
  const void *cptr;
  isize       i;
  usize       u;
  usize       v;
  void       *p;
  const void *c;
  int         _for_converting_from_int_literal;
  unsigned    _for_converting_from_unsigned_literal;
} VAddr;

typedef union __attr(transparent_union) {
  isize    ivalue;
  usize    uvalue;
  usize    value;
  isize    i;
  usize    u;
  usize    v;
  int      _for_converting_from_int_literal;
  unsigned _for_converting_from_unsigned_literal;
} PAddr;

typedef union __attr(transparent_union) {
  isize       iaddr;
  usize       uaddr;
  usize       addr;
  void       *ptr;
  const void *cptr;
  isize       i;
  usize       u;
  usize       a;
  void       *p;
  const void *c;
} Ptr;

typedef union __attr(transparent_union) {
  isize       iaddr;
  usize       uaddr;
  usize       addr;
  const void *cptr;
  isize       i;
  usize       u;
  usize       a;
  const void *c;
} ConstPtr;

#define VADDR(_addr_) ((VAddr)(_addr_))
#define PADDR(_addr_) ((PAddr)(_addr_))
