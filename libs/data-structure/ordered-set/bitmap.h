#pragma once
#include "../base.h"

#if !__plos_definitions__
#  error "You need to include <define.h> of PLOS to use this library"
#endif

#if !PLOS_LIBDATASTRUCTURE_SHOW_WARNING
#  pragma GCC system_header
#endif

#ifdef ALL_IMPLEMENTATION
#  define BITMAP_IMPLEMENTATION
#endif

// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$
// $$$$$                                       Declaration                                       $$$$$
// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$

#if !defined(COMPILE_DATA_STRUCTURE_LIBRARY) && defined(BITMAP_IMPLEMENTATION)
#  define API static
#else
#  define API dlimport
#endif

#define BITMAP(_name_, _nbits_)                                                                    \
  struct {                                                                                         \
    const u32 length;                                                                              \
    const u32 nbits;                                                                               \
    u32       bits[(_nbits_ + 31) / 32];                                                           \
  } _name_ = {.length = (_nbits_ + 31) / 32, .nbits = _nbits_};

// 获取 bitmap 指定的位
API bool bitmap_get(u32 *map, i32 index) __THROW __nnull(1);
// 设置 bitmap 指定的位
API void bitmap_set(u32 *map, i32 index) __THROW __nnull(1);
// 清除 bitmap 指定的位
API void bitmap_clear(u32 *map, i32 index) __THROW __nnull(1);
// 将 bitmap 全部置零
API void bitmap_fillzero(u32 *map) __THROW __nnull(1);
// 将 bitmap 全部置一
API void bitmap_fillone(u32 *map) __THROW __nnull(1);
// 将 bitmap 指定范围置零
API void bitmap_fillzero_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);
// 将 bitmap 指定范围置一
API void bitmap_fillone_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);
// 查找 bitmap 中第一个为零的位
API i32  bitmap_first_zero(u32 *map) __THROW __nnull(1);
// 查找 bitmap 中第一个为一的位
API i32  bitmap_first_one(u32 *map) __THROW __nnull(1);
// 查找 bitmap 中连续 count 个为零的位
API i32  bitmap_find_zeros(u32 *map, i32 count) __THROW __nnull(1);
// 查找 bitmap 中连续 count 个为一的位
API i32  bitmap_find_ones(u32 *map, i32 count) __THROW __nnull(1);
// 判断 bitmap 的指定范围是否全为零
API bool bitmap_is_zero_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);
// 判断 bitmap 的指定范围是否全为一
API bool bitmap_is_one_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);
// 判断 bitmap 的指定范围是否有零
API bool bitmap_has_zero_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);
// 判断 bitmap 的指定范围是否有一
API bool bitmap_has_one_range(u32 *map, i32 start, i32 end) __THROW __nnull(1);

#undef API

// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$
// $$$$$                                     Implementation                                      $$$$$
// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$

#ifdef COMPILE_DATA_STRUCTURE_LIBRARY
#  define API dlexport
#else
#  define API static
#endif

#if defined(COMPILE_DATA_STRUCTURE_LIBRARY) || defined(BITMAP_IMPLEMENTATION)

API bool bitmap_get(u32 *map, i32 index) {
  u32 *bits = map + 2;
  return bits[index / 32] & ((u32)1 << (index % 32));
}

API void bitmap_set(u32 *map, i32 index) {
  u32 *bits         = map + 2;
  bits[index / 32] |= ((u32)1 << (index % 32));
}

API void bitmap_clear(u32 *map, i32 index) {
  u32 *bits         = map + 2;
  bits[index / 32] &= ~((u32)1 << (index % 32));
}

API void bitmap_fillzero(u32 *map) {
  const u32 length = map[0];
  u32      *bits   = map + 2;
  vectorize for (i32 i = 0; i < length; i++) {
    bits[i] = 0;
  }
}

API void bitmap_fillone(u32 *map) {
  const u32 length = map[0];
  u32      *bits   = map + 2;
  vectorize for (i32 i = 0; i < length; i++) {
    bits[i] = U32_MAX;
  }
}

API void bitmap_fillzero_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  vectorize for (i32 i = start; i < end; i++) {
    bits[i / 32] &= ~((u32)1 << (i % 32));
  }
}

API void bitmap_fillone_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  vectorize for (i32 i = start; i < end; i++) {
    bits[i / 32] |= ((u32)1 << (i % 32));
  }
}

API i32 bitmap_first_zero(u32 *map) {
  const u32 length = map[0];
  const u32 nbits  = map[1];
  u32      *bits   = map + 2;
  for (i32 i = 0; i < length; i++) {
    if (!~bits[i]) continue;
    const i32 n = i * 32 + __builtin_ffs(~bits[i]) - 1;
    return n < nbits ? n : -1;
  }
  return -1;
}

API i32 bitmap_first_one(u32 *map) {
  const u32 length = map[0];
  const u32 nbits  = map[1];
  u32      *bits   = map + 2;
  for (i32 i = 0; i < length; i++) {
    if (!bits[i]) continue;
    const i32 n = i * 32 + __builtin_ffs(bits[i]) - 1;
    return n < nbits ? n : -1;
  }
  return -1;
}

API i32 bitmap_find_zeros(u32 *map, i32 count) {
  const u32 length = map[0];
  const u32 nbits  = map[1];
  u32      *bits   = map + 2;
  i32       start, zeros = 0;
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

API i32 bitmap_find_ones(u32 *map, i32 count) {
  const u32 length = map[0];
  const u32 nbits  = map[1];
  u32      *bits   = map + 2;
  i32       start, ones = 0;
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

API bool bitmap_is_zero_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  for (i32 i = start; i < end; i++) {
    if (bits[i / 32] & (1 << (i % 32))) return false;
  }
  return true;
}

API bool bitmap_is_one_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  for (i32 i = start; i < end; i++) {
    if (!(bits[i / 32] & (1 << (i % 32)))) return false;
  }
  return true;
}

API bool bitmap_has_zero_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  for (i32 i = start; i < end; i++) {
    if (!(bits[i / 32] & (1 << (i % 32)))) return true;
  }
  return false;
}

API bool bitmap_has_one_range(u32 *map, i32 start, i32 end) {
  u32 *bits = map + 2;
  for (i32 i = start; i < end; i++) {
    if (bits[i / 32] & (1 << (i % 32))) return true;
  }
  return false;
}

#endif

#undef API

// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$
// $$$$$                                     Macro Functions                                     $$$$$
// $$$$$ ========== ========== ========== ========== ========== ========== ========== ========== $$$$$

#define bitmap_get(map, index)                 bitmap_get((u32 *)&(map), index)
#define bitmap_set(map, index)                 bitmap_set((u32 *)&(map), index)
#define bitmap_clear(map, index)               bitmap_clear((u32 *)&(map), index)
#define bitmap_fillzero(map)                   bitmap_fillzero((u32 *)&(map))
#define bitmap_fillone(map)                    bitmap_fillone((u32 *)&(map))
#define bitmap_fillzero_range(map, start, end) bitmap_fillzero_range((u32 *)&(map), start, end)
#define bitmap_fillone_range(map, start, end)  bitmap_fillone_range((u32 *)&(map), start, end)
#define bitmap_first_zero(map)                 bitmap_first_zero((u32 *)&(map))
#define bitmap_first_one(map)                  bitmap_first_one((u32 *)&(map))
#define bitmap_find_zeros(map, count)          bitmap_first_one((u32 *)&(map), count)
#define bitmap_find_ones(map, count)           bitmap_first_one((u32 *)&(map), count)
#define bitmap_is_zero_range(map, start, end)  bitmap_is_zero_range((u32 *)&(map), start, end)
#define bitmap_is_one_range(map, start, end)   bitmap_is_one_range((u32 *)&(map), start, end)
#define bitmap_has_zero_range(map, start, end) bitmap_has_zero_range((u32 *)&(map), start, end)
#define bitmap_has_one_range(map, start, end)  bitmap_has_one_range((u32 *)&(map), start, end)
