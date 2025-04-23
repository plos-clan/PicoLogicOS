#pragma once

#pragma GCC system_header

#include "type.hpp"

constexpr auto operator""_B(unsigned long long x) -> usize {
  return x;
}

constexpr auto operator""_KiB(unsigned long long x) -> usize {
  return x * 1024;
}

constexpr auto operator""_MiB(unsigned long long x) -> usize {
  return x * 1024 * 1024;
}

constexpr auto operator""_GiB(unsigned long long x) -> usize {
  return x * 1024 * 1024 * 1024;
}

constexpr auto operator""_TiB(unsigned long long x) -> usize {
  return x * 1024 * 1024 * 1024 * 1024;
}

constexpr auto operator""_i8(unsigned long long x) -> i8 {
  return x;
}

constexpr auto operator""_u8(unsigned long long x) -> u8 {
  return x;
}

constexpr auto operator""_i16(unsigned long long x) -> i16 {
  return x;
}

constexpr auto operator""_u16(unsigned long long x) -> u16 {
  return x;
}

constexpr auto operator""_i32(unsigned long long x) -> i32 {
  return x;
}

constexpr auto operator""_u32(unsigned long long x) -> u32 {
  return x;
}

constexpr auto operator""_i64(unsigned long long x) -> i64 {
  return x;
}

constexpr auto operator""_u64(unsigned long long x) -> u64 {
  return x;
}

constexpr auto operator""_f32(long double x) -> f32 {
  return x;
}

constexpr auto operator""_f64(long double x) -> f64 {
  return x;
}

#if defined(__x86_64__)
constexpr auto operator""_i128(unsigned long long x) -> i128 {
  return x;
}

constexpr auto operator""_u128(unsigned long long x) -> u128 {
  return x;
}

#  if !NO_EXTFLOAT
constexpr auto operator""_f16(long double x) -> f16 {
  return x;
}

constexpr auto operator""_f128(long double x) -> f128 {
  return x;
}
#  endif
#endif
