#include <base.hpp>

namespace cpp {

__attr(const) auto exp2(f32 x) noexcept -> f32 {
  f32 y;
  i32 e;
  e   = (i32)(x + 127);
  x  += 127 - e;
  e <<= 23;
  y   = *(f32 *)&e;
  x  *= x * .339766027f + .660233972f;
  return (x + 1) * y;
}
__attr(const) auto exp2(f64 x) noexcept -> f64 {
  f64 y;
  i64 e;
  e   = (i64)(x + 1023);
  x  += 1023 - e;
  e <<= 52;
  y   = *(f64 *)&e;
  x  *= x * .339766027 + .660233972;
  return (x + 1) * y;
}

constfn exp(f32 x) noexcept -> f32 {
  f32 sum  = 1;
  f32 term = 1;
  int n    = 1;
  while (term > F32_EPSILON || term < -F32_EPSILON) {
    term *= x / n;
    sum  += term;
    n++;
  }
  return sum;
}
constfn exp(f64 x) noexcept -> f64 {
  f64 sum  = 1;
  f64 term = 1;
  int n    = 1;
  while (term > F64_EPSILON || term < -F64_EPSILON) {
    term *= x / n;
    sum  += term;
    n++;
  }
  return sum;
}

__attr(const) auto log2(f32 x) noexcept -> f32 {
  i32 y;
  f32 r;
  y   = *(i32 *)&x;
  y >>= 23;
  r   = (f32)y;
  y   = *(i32 *)&x;
  y   = (y & 0x007fffff) | 0x3f800000;
  x   = *(f32 *)&y;
  r  += -128 + x * (x * -0.333333333f + 2) - 0.666666666f;
  return r;
}
__attr(const) auto log2(f64 x) noexcept -> f64 {
  i64 y;
  f64 r;
  y   = *(i64 *)&x;
  y >>= 52;
  r   = (f64)y;
  y   = *(i64 *)&x;
  y   = (y & 0x000fffffffffffff) | 0x3ff0000000000000;
  x   = *(f64 *)&y;
  r  += -1024 + x * (x * -0.3333333333333333 + 2) - 0.6666666666666666;
  return r;
}

constfn pow(f32 a, u32 b) noexcept -> f32 {
  f32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

constfn pow(f32 a, i32 b) noexcept -> f32 {
  return b < 0 ? 1 / pow(a, (u32)-b) : pow(a, (u32)b);
}

constfn pow(i32 a, u32 b) noexcept -> i32 {
  i32 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

constfn pow(f64 a, u64 b) noexcept -> f64 {
  f64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

constfn pow(f64 a, i64 b) noexcept -> f64 {
  return b < 0 ? 1 / pow(a, (u64)-b) : pow(a, (u64)b);
}

constfn pow(i64 a, u64 b) noexcept -> i64 {
  i64 r = 1;
  while (b > 0) {
    if (b & 1) r *= a;
    a  *= a;
    b >>= 1;
  }
  return r;
}

constfn pow(f32 a, f32 b) noexcept -> f32 {
  i32 c  = b;
  b     -= c;
  return exp2(b * log2(a)) * pow(a, c);
}
constfn pow(f64 a, f64 b) noexcept -> f64 {
  i64 c  = b;
  b     -= c;
  return exp2(b * log2(a)) * pow(a, c);
}

} // namespace cpp
