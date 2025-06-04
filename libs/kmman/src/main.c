#include <kernel.h>

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

void *kmalloc(usize size) {
  assert(size > 0, "kmalloc size must > 0");
  assert(size < SIZE_16k, "kmalloc size must < 16k, otherwise use kpalloc");
}

void kmfree(void *ptr) {}

void *kpalloc(usize size) {
  assert(size > 0, "kpalloc size must > 0");
}

void kpfree(void *ptr, usize size) {
  assert(((usize)ptr & PAGE_SIZE) == 0, "kpfree ptr must page aligned");
  val paddr = (usize)ptr & 0x00007fffffffffff;
  size      = PADDING_UP(size, PAGE_SIZE);
}
