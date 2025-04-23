#pragma once
#include "base.hpp"
#include <define.hpp>

namespace cpp {

// --------------------------------------------------
//; 对数 指数 幂

#if __has(exp2) && !defined(_EXP_LOG_CPP_)
inline_const auto exp2(f32 x) -> f32 {
  return __builtin_exp2f(x);
}
inline_const auto exp2(f64 x) -> f64 {
  return __builtin_exp2(x);
}
#else
__attr(const) auto exp2(f32 x) noexcept -> f32;
__attr(const) auto exp2(f64 x) noexcept -> f64;
#endif

#if __has(exp) && !defined(_EXP_LOG_CPP_)
inline_const auto exp(f32 x) -> f32 {
  return __builtin_expf(x);
}
inline_const auto exp(f64 x) -> f64 {
  return __builtin_exp(x);
}
#else
constfn exp(f32 x) noexcept -> f32;
constfn exp(f64 x) noexcept -> f64;
#endif

#if __has(log2) && !defined(_EXP_LOG_CPP_)
inline_const auto log2(f32 x) -> f32 {
  return __builtin_log2f(x);
}
inline_const auto log2(f64 x) -> f64 {
  return __builtin_log2(x);
}
#else
__attr(const) auto log2(f32 x) noexcept -> f32;
__attr(const) auto log2(f64 x) noexcept -> f64;
#endif

#ifndef _EXP_LOG_CPP_

inline_const auto pow(f32 a, u32 b) -> f32 {
  f32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

inline_const auto pow(f32 a, i32 b) -> f32 {
  return b < 0 ? 1 / pow(a, (u32)-b) : pow(a, (u32)b);
}

inline_const auto pow(i32 a, u32 b) -> i32 {
  i32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

inline_const auto pow(f64 a, u64 b) -> f64 {
  f64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

inline_const auto pow(f64 a, i64 b) -> f64 {
  return b < 0 ? 1 / pow(a, (u64)-b) : pow(a, (u64)b);
}

inline_const auto pow(i64 a, u64 b) -> i64 {
  i64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

#else

constfn pow(f32 a, u32 b) noexcept -> f32;
constfn pow(f32 a, i32 b) noexcept -> f32;
constfn pow(i32 a, u32 b) noexcept -> i32;
constfn pow(f64 a, u64 b) noexcept -> f64;
constfn pow(f64 a, i64 b) noexcept -> f64;
constfn pow(i64 a, u64 b) noexcept -> i64;

#endif

#if __has(pow) && !defined(_EXP_LOG_CPP_)
inline_const auto pow(f32 a, f32 b) -> f32 {
  return __builtin_powf(a, b);
}
inline_const auto pow(f64 a, f64 b) -> f64 {
  return __builtin_pow(a, b);
}
#else
constfn pow(f32 a, f32 b) noexcept -> f32;
constfn pow(f64 a, f64 b) noexcept -> f64;
#endif

} // namespace cpp
