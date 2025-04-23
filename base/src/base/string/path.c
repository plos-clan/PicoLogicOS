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

dlexport char *pathcat(char *p1, cstr p2) {
  val len = strlen(p1);
  if (p1[len - 1] == '/') {
    strcpy(p1 + len, p2);
  } else {
    p1[len] = '/';
    strcpy(p1 + len + 1, p2);
  }
  return p1;
}

dlexport char *pathncat(char *p1, cstr p2, usize n) {
  val len = strlen(p1);
  if (p1[len - 1] == '/') {
    strncpy(p1 + len, p2, n);
  } else {
    p1[len] = '/';
    strncpy(p1 + len + 1, p2, n);
  }
  return p1;
}
