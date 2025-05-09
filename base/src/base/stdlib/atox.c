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

#include <base.h>

#define isdigit2(c)  ((c) == '0' || (c) == '1')
#define isdigit8(c)  ('0' <= (c) && (c) <= '7')
#define isdigit(c)   ('0' <= (c) && (c) <= '9')
#define isdigit16(c) (isdigit(c) || ('a' <= (c) && (c) <= 'f') || ('A' <= (c) && (c) <= 'F'))

#define __atof(_t_, _type_)                                                                        \
  dlexport _type_ ato##_t_(cstr s) {                                                               \
    bool neg = *s == '-';                                                                          \
    if (neg || *s == '+') s++;                                                                     \
                                                                                                   \
    if (*s == 'n' || *s == 'N') {                                                                  \
      if (s++, *s == 'a' || *s == 'A')                                                             \
        if (s++, *s == 'n' || *s == 'N') return NAN;                                               \
      return 0;                                                                                    \
    }                                                                                              \
                                                                                                   \
    if (*s == 'i' || *s == 'I') {                                                                  \
      if (s++, *s == 'n' || *s == 'N') {                                                           \
        if (s++, *s == 'f' || *s == 'F') {                                                         \
          if (neg)                                                                                 \
            return -INFINITY;                                                                      \
          else                                                                                     \
            return INFINITY;                                                                       \
        }                                                                                          \
      }                                                                                            \
      return 0;                                                                                    \
    }                                                                                              \
                                                                                                   \
    if (!isdigit(*s) && (*s != '.' || !isdigit(*(s + 1)))) return 0;                               \
                                                                                                   \
    _type_ f = 0;                                                                                  \
                                                                                                   \
    for (; isdigit(*s); s++)                                                                       \
      f = f * 10 + (*s - '0');                                                                     \
                                                                                                   \
    if (!__builtin_isfinite(f)) return neg ? -f : f;                                               \
                                                                                                   \
    if (*s == '.') {                                                                               \
      s++;                                                                                         \
      _type_ n = 1;                                                                                \
      for (; isdigit(*s); s++)                                                                     \
        f += (*s - '0') * (n *= (_type_).1);                                                       \
    }                                                                                              \
                                                                                                   \
    if (*s == 'e' || *s == 'E') {                                                                  \
      s++;                                                                                         \
      bool nneg = *s == '-';                                                                       \
      if (nneg || *s == '+') s++;                                                                  \
      u32 n = 0;                                                                                   \
      if (!isdigit(*s)) return 0;                                                                  \
      for (; isdigit(*s); s++)                                                                     \
        n = n * 10 + (*s - '0');                                                                   \
      if (nneg) {                                                                                  \
        _type_ a = .1;                                                                             \
        for (; n; n >>= 1, a *= a)                                                                 \
          if (n & 1) f *= a;                                                                       \
      } else {                                                                                     \
        _type_ a = 10;                                                                             \
        for (; n; n >>= 1, a *= a)                                                                 \
          if (n & 1) f *= a;                                                                       \
      }                                                                                            \
    }                                                                                              \
                                                                                                   \
    return neg ? -f : f;                                                                           \
  }

#if NO_STD
__atof(ff, float);
__atof(f, double);
__atof(fl, long double);
#endif

#define _atof(t) __atof(t, t)

_atof(f32);
_atof(f64);
#if defined(__x86_64__) && !NO_EXTFLOAT
_atof(f16);
_atof(f128);
#endif

#undef _atof

#undef __atof

#define __stof(_t_, _type_)                                                                        \
  dlexport _type_ strto##_t_(cstr _rest s, char **_rest e) noexcept {                              \
    if (e) *e = (char *)s;                                                                         \
                                                                                                   \
    bool neg = *s == '-';                                                                          \
    if (neg || *s == '+') s++;                                                                     \
                                                                                                   \
    if (*s == 'n' || *s == 'N') {                                                                  \
      if (s++, *s == 'a' || *s == 'A')                                                             \
        if (s++, *s == 'n' || *s == 'N') {                                                         \
          if (e) *e = (char *)s;                                                                   \
          return NAN;                                                                              \
        }                                                                                          \
      return 0;                                                                                    \
    }                                                                                              \
                                                                                                   \
    if (*s == 'i' || *s == 'I') {                                                                  \
      if (s++, *s == 'n' || *s == 'N') {                                                           \
        if (s++, *s == 'f' || *s == 'F') {                                                         \
          if (e) *e = (char *)s;                                                                   \
          if (neg)                                                                                 \
            return -INFINITY;                                                                      \
          else                                                                                     \
            return INFINITY;                                                                       \
        }                                                                                          \
      }                                                                                            \
      return 0;                                                                                    \
    }                                                                                              \
                                                                                                   \
    if (!isdigit(*s) && (*s != '.' || !isdigit(*(s + 1)))) return 0;                               \
                                                                                                   \
    _type_ f = 0;                                                                                  \
                                                                                                   \
    for (; isdigit(*s); s++)                                                                       \
      f = f * 10 + (*s - '0');                                                                     \
                                                                                                   \
    if (*s == '.') {                                                                               \
      s++;                                                                                         \
      _type_ n = 1;                                                                                \
      for (; isdigit(*s); s++)                                                                     \
        f += (*s - '0') * (n *= (_type_).1);                                                       \
    }                                                                                              \
                                                                                                   \
    if (*s == 'e' || *s == 'E') {                                                                  \
      s++;                                                                                         \
      bool nneg = *s == '-';                                                                       \
      if (nneg || *s == '+') s++;                                                                  \
      u32 n = 0;                                                                                   \
      if (!isdigit(*s)) return 0;                                                                  \
      for (; isdigit(*s); s++)                                                                     \
        n = n * 10 + (*s - '0');                                                                   \
      if (nneg) {                                                                                  \
        _type_ a = .1;                                                                             \
        for (; n; n >>= 1, a *= a)                                                                 \
          if (n & 1) f *= a;                                                                       \
      } else {                                                                                     \
        _type_ a = 10;                                                                             \
        for (; n; n >>= 1, a *= a)                                                                 \
          if (n & 1) f *= a;                                                                       \
      }                                                                                            \
    }                                                                                              \
                                                                                                   \
    if (e) *e = (char *)s;                                                                         \
    return neg ? -f : f;                                                                           \
  }

__stof(f, float);
__stof(d, double);

#define _stof(t) __stof(t, t)

_stof(f32);
_stof(f64);
#if defined(__x86_64__) && !NO_EXTFLOAT
_stof(f16);
_stof(f128);
#endif

#undef _stof

#undef __stof

#undef isdigit
