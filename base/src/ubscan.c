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

#include <base.h>

#define PORT 0x3f8 // COM1

static void log_outs(cstr s) {
  for (size_t i = 0; s[i] != '\0'; i++) {
    waituntil(asm_in8(PORT + 5) & 0x20);
    asm_out8(PORT, s[i]);
  }
}

static void klog(cstr _rest fmt, ...) {
  var flag = asm_get_flags();
  asm_cli;
  static char buf[4096];
  va_list     va;
  va_start(va, fmt);
  vsprintf(buf, fmt, va);
  va_end(va);
  log_outs(buf);
  asm_set_flags(flag);
}

#define _log_func_ klog
#include <ubscan.h>
