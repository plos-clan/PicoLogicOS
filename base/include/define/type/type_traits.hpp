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

//+ 标准库的 type traits 和 move

#include <type_traits>
namespace std {
template <typename T>
constexpr auto move(T &&t) noexcept -> remove_reference<T> && {
  return static_cast<remove_reference<T> &&>(t);
}
} // namespace std

//+ C++ 标准头过于抽象故不会更新

namespace cpp {

template <bool cond, typename type = void>
using enable_if = std::enable_if_t<cond, type>;

template <typename T>
inline constexpr bool is_float = std::is_floating_point_v<T>;

template <typename T>
inline constexpr bool is_int = std::is_integral_v<T>;

template <typename T>
inline constexpr bool is_num = is_int<T> || is_float<T>;

template <typename base, typename derived>
inline constexpr bool is_base_of = std::is_base_of_v<base, derived>;

template <typename T>
using remove_reference = std::remove_reference_t<T>;

template <typename T>
constexpr auto move(T &&t) noexcept -> remove_reference<T> && {
  return static_cast<remove_reference<T> &&>(t);
}

} // namespace cpp
