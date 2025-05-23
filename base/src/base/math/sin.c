#include <base.h>

// --------------------------------------------------
//; 三角函数

#if PLOS_FAST_MATH

dlimport const f32 _plos_lut_sin[128];

dlexport constfn f32 sinf(f32 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_sin[idx];
}
dlexport constfn f64 sin(f64 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_sin[idx];
}

#else

dlexport constfn f32 sinf(f32 x) {
  x         = fmodf(x, (f32)(2 * PI));
  f32  sum  = x;
  f32  term = x;
  int  n    = 1;
  bool sign = true;
  while (term > F32_EPSILON || term < -F32_EPSILON) {
    n    += 2;
    term *= x * x / (n * (n - 1));
    sum  += sign ? -term : term;
    sign  = !sign;
  }
  return sum;
}
dlexport constfn f64 sin(f64 x) {
  x         = fmod(x, 2 * PI);
  f64  sum  = x;
  f64  term = x;
  int  n    = 1;
  bool sign = true;
  while (term > F64_EPSILON || term < -F64_EPSILON) {
    n    += 2;
    term *= x * x / (n * (n - 1));
    sum  += sign ? -term : term;
    sign  = !sign;
  }
  return sum;
}

#endif

#if PLOS_FAST_MATH

dlimport const f32 _plos_lut_cos[128];

dlexport constfn f32 cosf(f32 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_cos[idx];
}
dlexport constfn f64 cos(f64 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_cos[idx];
}

#else

dlexport constfn f32 cosf(f32 x) {
  x         = fmodf(x, (f32)(2 * PI));
  f32  sum  = 1;
  f32  term = 1;
  int  n    = 0;
  bool sign = true;
  while (term > F32_EPSILON || term < -F32_EPSILON) {
    n    += 2;
    term *= x * x / (n * (n - 1));
    sum  += sign ? -term : term;
    sign  = !sign;
  }
  return sum;
}
dlexport constfn f64 cos(f64 x) {
  x         = fmod(x, 2 * PI);
  f64  sum  = 1;
  f64  term = 1;
  int  n    = 0;
  bool sign = true;
  while (term > F64_EPSILON || term < -F64_EPSILON) {
    n    += 2;
    term *= x * x / (n * (n - 1));
    sum  += sign ? -term : term;
    sign  = !sign;
  }
  return sum;
}

#endif

dlexport void sincosf(f32 x, f32 *s, f32 *c) {
  *s = sinf(x);
  *c = cosf(x);
}
dlexport void sincos(f64 x, f64 *s, f64 *c) {
  *s = sin(x);
  *c = cos(x);
}

#if PLOS_FAST_MATH

dlimport const f32 _plos_lut_tan[128];

dlexport constfn f32 tanf(f32 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_tan[idx];
}
dlexport constfn f64 tan(f64 x) {
  isize idx = (isize)(x * 20.371832715762604f);
  idx       = idx % 128;
  idx       = idx < 0 ? idx + 128 : idx;
  return _plos_lut_tan[idx];
}

#else

dlexport constfn f32 tanf(f32 x) {
  return sinf(x) / cosf(x);
}
dlexport constfn f64 tan(f64 x) {
  return sin(x) / cos(x);
}

#endif

dlexport constfn f32 asinf(f32 x) {
  f32 sum  = x;
  f32 term = x;
  int n    = 1;
  while (term > F32_EPSILON || term < -F32_EPSILON) {
    term *= (x * x * (2 * n - 1) * (2 * n - 1)) / (2 * n * (2 * n + 1));
    sum  += term;
    n++;
  }
  return sum;
}
dlexport constfn f64 asin(f64 x) {
  f64 sum  = x;
  f64 term = x;
  int n    = 1;
  while (term > F64_EPSILON || term < -F64_EPSILON) {
    term *= (x * x * (2 * n - 1) * (2 * n - 1)) / (2 * n * (2 * n + 1));
    sum  += term;
    n++;
  }
  return sum;
}

dlexport constfn f32 acosf(f32 x) {
  return (f32)(PI / 2) - asinf(x);
}
dlexport constfn f64 acos(f64 x) {
  return PI / 2 - asin(x);
}

dlexport constfn f32 atanf(f32 x) {
  f32  sum  = x;
  f32  term = x;
  int  n    = 1;
  bool sign = true;
  while (term > F32_EPSILON || term < -F32_EPSILON) {
    term *= x * x * (2 * n - 1) / (2 * n + 1);
    sum  += sign ? -term : term;
    sign  = !sign;
    n++;
  }
  return sum;
}
dlexport constfn f64 atan(f64 x) {
  f64  sum  = x;
  f64  term = x;
  int  n    = 1;
  bool sign = true;
  while (term > F64_EPSILON || term < -F64_EPSILON) {
    term *= x * x * (2 * n - 1) / (2 * n + 1);
    sum  += sign ? -term : term;
    sign  = !sign;
    n++;
  }
  return sum;
}

dlexport constfn f32 atan2f(f32 y, f32 x) {
  if (x > 0) return atanf(y / x);
  if (x < 0 && y >= 0) return atanf(y / x) + (f32)PI;
  if (x < 0 && y < 0) return atanf(y / x) - (f32)PI;
  if (x == 0 && y > 0) return (f32)(PI / 2);
  if (x == 0 && y < 0) return -(f32)(PI / 2);
  return 0;
}
dlexport constfn f64 atan2(f64 y, f64 x) {
  if (x > 0) return atan(y / x);
  if (x < 0 && y >= 0) return atan(y / x) + PI;
  if (x < 0 && y < 0) return atan(y / x) - PI;
  if (x == 0 && y > 0) return PI / 2;
  if (x == 0 && y < 0) return -PI / 2;
  return 0;
}
