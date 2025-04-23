#pragma once
#include <define.hpp>

namespace cpp {

template <typename T>
inline_const auto min(T x) -> T {
  return x;
}
template <typename T, typename... Args>
inline_const auto min(T x, Args... args) -> T {
  T y = min(args...);
  return x < y ? x : y;
}

template <typename T>
inline_const auto max(T x) -> T {
  return x;
}
template <typename T, typename... Args>
inline_const auto max(T x, Args... args) -> T {
  T y = max(args...);
  return x > y ? x : y;
}

// 将 v 限制到 [min,max] 的范围内
#if __cplusplus >= 202002L
template <typename T>
requires(std::is_arithmetic_v<T>)
inline_const auto clamp(const T &v, const T &min, const T &max) -> const T & {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}
#else
template <typename T>
inline_const auto clamp(const T &v, const T &min, const T &max) ->
    typename std::enable_if_t<std::is_arithmetic_v<T>, const T &> {
  if (v < min) return min;
  if (v > max) return max;
  return v;
}
#endif

} // namespace cpp
