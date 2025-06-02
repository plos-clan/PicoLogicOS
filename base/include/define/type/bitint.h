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

#if PLOS_BITINT

#  define B(N)                                                                                     \
    typedef _BitInt(N) int##N##_t, i##N;                                                           \
    typedef unsigned _BitInt(N) uint##N##_t, u##N;
#  define BB(N) B(N##0) B(N##1) B(N##2) B(N##3) B(N##4) B(N##5) B(N##6) B(N##7) B(N##8) B(N##9)

B(2) B(3) B(4) B(5) B(6) B(7) B(9);
B(10) B(11) B(12) B(13) B(14) B(15) B(17) B(18) B(19);
BB(2);
B(30) B(31) B(33) B(34) B(35) B(36) B(37) B(38) B(39);
BB(4);
BB(5);
B(60) B(61) B(62) B(63);

#  undef BB
#  undef B

#  define B(N)                                                                                     \
    typedef _BitInt(N) bi##N;                                                                      \
    typedef unsigned _BitInt(N) bu##N;
#  define BB(N) B(N##0) B(N##1) B(N##2) B(N##3) B(N##4) B(N##5) B(N##6) B(N##7) B(N##8) B(N##9)

B(2) B(3) B(4) B(5) B(6) B(7) B(8) B(9);
BB(1) BB(2) BB(3) BB(4) BB(5);
B(60) B(61) B(62) B(63) B(64);

#  undef BB
#  undef B

#endif
