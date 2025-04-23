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

// 你 builtin 一下这么难是吧

#if NO_STD

dlexport cf32 __mulsc3(f32 a, f32 b, f32 c, f32 d) {
  return (a * c - b * d) + (a * d + b * c) * 1.if;
}

dlexport cf64 __muldc3(f64 a, f64 b, f64 c, f64 d) {
  return (a * c - b * d) + (a * d + b * c) * 1.i;
}

dlexport cf32 __divsc3(f32 a, f32 b, f32 c, f32 d) {
  f32 e = c * c + d * d;
  return (a * c + b * d) / e + (b * c - a * d) / e * 1.if;
}

dlexport cf64 __divdc3(f64 a, f64 b, f64 c, f64 d) {
  f64 e = c * c + d * d;
  return (a * c + b * d) / e + (b * c - a * d) / e * 1.i;
}

#endif
