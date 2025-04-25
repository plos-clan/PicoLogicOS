#pragma once

static const char _plos_lut_alnum_lower[62] =
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const char _plos_lut_alnum_upper[62] =
    "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

#define __tostr_begin                                                                              \
  char *s = buf + len;                                                                             \
  *--s    = '\0';
#define __tostr_begin_nlt                                                                          \
  cstr nlt = _plos_lut_alnum_upper;                                                                \
  if (b < 0) (b = -b, nlt = _plos_lut_alnum_lower);                                                \
  __tostr_begin

#define __tostrb2(t, type, utype)                                                                  \
  static char *t##tostrb2(char *buf, size_t len, type _n) {                                        \
    __tostr_begin;                                                                                 \
    if (_n == 0) return (*--s = '0', s);                                                           \
    bool  neg = _n < 0;                                                                            \
    utype n   = neg ? -(utype)_n : _n;                                                             \
    for (; n; n >>= 1)                                                                             \
      *--s = (n & 1) + '0';                                                                        \
    if (neg) *--s = '-';                                                                           \
    return s;                                                                                      \
  }
#define __utostrb2(t, type)                                                                        \
  static char *t##tostrb2(char *buf, size_t len, type n) {                                         \
    __tostr_begin;                                                                                 \
    if (n == 0) return (*--s = '0', s);                                                            \
    for (; n; n >>= 1)                                                                             \
      *--s = (n & 1) + '0';                                                                        \
    return s;                                                                                      \
  }

#define __tostrb8(t, type, utype)                                                                  \
  static char *t##tostrb8(char *buf, size_t len, type _n) {                                        \
    __tostr_begin;                                                                                 \
    if (_n == 0) return (*--s = '0', s);                                                           \
    bool  neg = _n < 0;                                                                            \
    utype n   = neg ? -(utype)_n : _n;                                                             \
    for (; n; n >>= 3)                                                                             \
      *--s = (n & 7) + '0';                                                                        \
    if (neg) *--s = '-';                                                                           \
    return s;                                                                                      \
  }
#define __utostrb8(t, type)                                                                        \
  static char *t##tostrb8(char *buf, size_t len, type n) {                                         \
    __tostr_begin;                                                                                 \
    if (n == 0) return (*--s = '0', s);                                                            \
    for (; n; n >>= 3)                                                                             \
      *--s = (n & 7) + '0';                                                                        \
    return s;                                                                                      \
  }

#define __tostrb10(t, type, utype)                                                                 \
  static char *t##tostrb10(char *buf, size_t len, type _n) {                                       \
    __tostr_begin;                                                                                 \
    if (_n == 0) return (*--s = '0', s);                                                           \
    bool  neg = _n < 0;                                                                            \
    utype n   = neg ? -(utype)_n : _n;                                                             \
    for (; n; n /= 10)                                                                             \
      *--s = n % 10 + '0';                                                                         \
    if (neg) *--s = '-';                                                                           \
    return s;                                                                                      \
  }
#define __utostrb10(t, type)                                                                       \
  static char *t##tostrb10(char *buf, size_t len, type n) {                                        \
    __tostr_begin;                                                                                 \
    if (n == 0) return (*--s = '0', s);                                                            \
    for (; n; n /= 10)                                                                             \
      *--s = n % 10 + '0';                                                                         \
    return s;                                                                                      \
  }

#define __tostrb16(t, type, utype)                                                                 \
  static char *t##tostrb16(char *buf, size_t len, type _n) {                                       \
    __tostr_begin;                                                                                 \
    if (_n == 0) return (*--s = '0', s);                                                           \
    bool  neg = _n < 0;                                                                            \
    utype n   = neg ? -(utype)_n : _n;                                                             \
    for (; n; n >>= 4)                                                                             \
      *--s = _plos_lut_alnum_lower[n & 15];                                                        \
    if (neg) *--s = '-';                                                                           \
    return s;                                                                                      \
  }
#define __utostrb16(t, type)                                                                       \
  static char *t##tostrb16(char *buf, size_t len, type n) {                                        \
    __tostr_begin;                                                                                 \
    if (n == 0) return (*--s = '0', s);                                                            \
    for (; n; n >>= 4)                                                                             \
      *--s = _plos_lut_alnum_lower[n & 15];                                                        \
    return s;                                                                                      \
  }

#define __tostrB16(t, type, utype)                                                                 \
  static char *t##tostrB16(char *buf, size_t len, type _n) {                                       \
    __tostr_begin;                                                                                 \
    if (_n == 0) return (*--s = '0', s);                                                           \
    bool  neg = _n < 0;                                                                            \
    utype n   = neg ? -(utype)_n : _n;                                                             \
    for (; n; n >>= 4)                                                                             \
      *--s = _plos_lut_alnum_upper[n & 15];                                                        \
    if (neg) *--s = '-';                                                                           \
    return s;                                                                                      \
  }
#define __utostrB16(t, type)                                                                       \
  static char *t##tostrB16(char *buf, size_t len, type n) {                                        \
    __tostr_begin;                                                                                 \
    if (n == 0) return (*--s = '0', s);                                                            \
    for (; n; n >>= 4)                                                                             \
      *--s = _plos_lut_alnum_upper[n & 15];                                                        \
    return s;                                                                                      \
  }

#define _tostrb2(t, u)  __tostrb2(t, t, u)
#define _utostrb2(t)    __utostrb2(t, t)
#define _tostrb8(t, u)  __tostrb8(t, t, u)
#define _utostrb8(t)    __utostrb8(t, t)
#define _tostrb10(t, u) __tostrb10(t, t, u)
#define _utostrb10(t)   __utostrb10(t, t)
#define _tostrb16(t, u) __tostrb16(t, t, u)
#define _utostrb16(t)   __utostrb16(t, t)
#define _tostrB16(t, u) __tostrB16(t, t, u)
#define _utostrB16(t)   __utostrB16(t, t)

#define __(name)                                                                                   \
  __##name(hh, char, uchar);                                                                       \
  __u##name(uhh, uchar);                                                                           \
  __##name(h, short, ushort);                                                                      \
  __u##name(uh, ushort);                                                                           \
  __##name(i, int, uint);                                                                          \
  __u##name(ui, uint);                                                                             \
  __##name(l, long, ulong);                                                                        \
  __u##name(ul, ulong);                                                                            \
  __##name(ll, llong, ullong);                                                                     \
  __u##name(ull, ullong);                                                                          \
  _##name(i8, u8);                                                                                 \
  _u##name(u8);                                                                                    \
  _##name(i16, u16);                                                                               \
  _u##name(u16);                                                                                   \
  _##name(i32, u32);                                                                               \
  _u##name(u32);                                                                                   \
  _##name(i64, u64);                                                                               \
  _u##name(u64);

__(tostrb2);
__(tostrb8);
__(tostrb10);
__(tostrb16);
__(tostrB16);
