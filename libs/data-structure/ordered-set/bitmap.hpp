#pragma once
#include "../base.hpp"

#if !__plos_definitions__
#  error "You need to include <define.hpp> of PLOS to use this library"
#endif

#if !PLOS_LIBDATASTRUCTURE_SHOW_WARNING
#  pragma GCC system_header
#endif

namespace cpp {

template <u32 nbits>
struct Bitmap {
  static constexpr const u32 length = (nbits + 31) / 32;

  static_assert(nbits > 0, "Bitmap size must be greater than 0");
  static_assert(nbits <= I32_MAX, "Bitmap size must be less than 2^31");

  u32 bits[length];

  // 获取指定位
  __wur constexpr bool get(i32 index) const noexcept {
    return bits[index / 32] & ((u32)1 << (index % 32));
  }

  // 设置指定位
  constexpr void set(i32 index) noexcept {
    bits[index / 32] |= ((u32)1 << (index % 32));
  }

  // 清除指定位
  constexpr void clear(i32 index) noexcept {
    bits[index / 32] &= ~((u32)1 << (index % 32));
  }

  // 将 bitmap 全部置零
  constexpr void fill_zero() noexcept {
    vectorize for (i32 i = 0; i < length; i++) {
      bits[i] = 0;
    }
  }

  // 将 bitmap 全部置一
  constexpr void fill_one() noexcept {
    vectorize for (i32 i = 0; i < length; i++) {
      bits[i] = U32_MAX;
    }
  }

  // 将指定范围置零
  constexpr void fill_zero_range(i32 start, i32 end) noexcept {
    vectorize for (i32 i = start; i < end; i++) {
      bits[i / 32] &= ~((u32)1 << (i % 32));
    }
  }

  // 将指定范围置一
  constexpr void fill_one_range(i32 start, i32 end) noexcept {
    vectorize for (i32 i = start; i < end; i++) {
      bits[i / 32] |= ((u32)1 << (i % 32));
    }
  }

  // 查找第一个为零的位
  __wur constexpr i32 first_zero() const noexcept {
    for (i32 i = 0; i < length; i++) {
      if (!~bits[i]) continue;
      const i32 n = i * 32 + __builtin_ffs(~bits[i]) - 1;
      return n < nbits ? n : -1;
    }
    return -1;
  }

  // 查找第一个为一的位
  __wur constexpr i32 first_one() const noexcept {
    for (i32 i = 0; i < length; i++) {
      if (!bits[i]) continue;
      const i32 n = i * 32 + __builtin_ffs(bits[i]) - 1;
      return n < nbits ? n : -1;
    }
    return -1;
  }

  // 查找 bitmap 中连续 count 个为零的位
  __wur constexpr i32 bitmap_find_zeros(i32 count) const noexcept {
    i32 start, zeros = 0;
    for (i32 i = 0; i < length; i++) {
      if (!~bits[i]) continue;
      for (i32 j = 0; j < 32; j++) {
        if ((bits[i] & (1 << j)) != 0) {
          zeros = 0;
          continue;
        }
        if (zeros == 0) start = i * 32 + j;
        zeros++;
        if (zeros >= count) return start;
      }
    }
    return -1;
  }

  // 查找 bitmap 中连续 count 个为一的位
  __wur constexpr i32 bitmap_find_ones(i32 count) const noexcept {
    i32 start, ones = 0;
    for (i32 i = 0; i < length; i++) {
      if (!bits[i]) continue;
      for (i32 j = 0; j < 32; j++) {
        if ((bits[i] & (1 << j)) == 0) {
          ones = 0;
          continue;
        }
        if (ones == 0) start = i * 32 + j;
        ones++;
        if (ones >= count) return start;
      }
    }
    return -1;
  }

  // 判断指定范围是否全为零
  __wur constexpr bool is_zero_range(i32 start, i32 end) const noexcept {
    for (i32 i = start; i < end; i++) {
      if (bits[i / 32] & (1 << (i % 32))) return false;
    }
    return true;
  }

  // 判断指定范围是否全为一
  __wur constexpr bool is_one_range(i32 start, i32 end) const noexcept {
    for (i32 i = start; i < end; i++) {
      if (!(bits[i / 32] & (1 << (i % 32)))) return false;
    }
    return true;
  }

  // 判断指定范围是否有零
  __wur constexpr bool has_zero_range(i32 start, i32 end) const noexcept {
    for (i32 i = start; i < end; i++) {
      if (!(bits[i / 32] & (1 << (i % 32)))) return true;
    }
    return false;
  }

  // 判断指定范围是否有一
  __wur constexpr bool has_one_range(i32 start, i32 end) const noexcept {
    for (i32 i = start; i < end; i++) {
      if (bits[i / 32] & (1 << (i % 32))) return true;
    }
    return false;
  }
};

} // namespace cpp
