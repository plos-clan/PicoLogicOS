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

#define UTF32_ERRCH 0xfffd

dlexport u32 utf8to32c(cstr8 *sp) {
  cstr8 s = *sp;
  u32   code;
  if (s[0] < 0x80) { // ASCII字符（单字节）
    code = *s++;
  } else if ((s[0] & 0xe0) == 0xc0) { // 2字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x1f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((s[0] & 0xf0) == 0xe0) { // 3字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x0F) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else if ((s[0] & 0xf8) == 0xf0) { // 4字节UTF-8字符
    if ((s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80 || (s[3] & 0xc0) != 0x80) goto err;
    code  = (*s++ & 0x07) << 18;
    code |= (*s++ & 0x3f) << 12;
    code |= (*s++ & 0x3f) << 6;
    code |= (*s++ & 0x3f);
  } else { // 非法的UTF-8序列
    goto err;
  }
  *sp = s;
  return code;

err:
  s++;
  *sp = s;
  return UTF32_ERRCH; // 跳过非法序列
}

dlexport usize utf8to32s(u32 *d, cstr8 s) {
  const u32 *_d = d;
  while (*s != '\0') {
    *d++ = utf8to32c(&s);
  }
  *d = '\0';
  return d - _d;
}

dlexport u32 *utf8to32a(cstr8 s) {
  u32 *r = malloc((strlen8(s) + 1) * 4);
  if (r == null) return null;
  usize n = utf8to32s(r, s);
  return realloc(r, (n + 1) * 4);
}

dlexport u32 utf16to32c(cstr16 *sp) {
  cstr16 s = *sp;
  u32    code;
  if (0xD800 <= s[0] && s[0] <= 0xDBFF) {   // 高代理项
    if (0xDC00 <= s[1] && s[1] <= 0xDFFF) { // 低代理项
      code  = ((s[0] - 0xD800) << 10) + (s[1] - 0xDC00) + 0x10000;
      s    += 2;
    } else {
      code = UTF32_ERRCH; // 非法的代理对
      s++;
    }
  } else {
    code = s[0];
    s++;
  }

  *sp = s;
  return code;
}

dlexport usize utf16to32s(u32 *d, cstr16 s) {
  const u32 *_d = d;
  while (*s != '\0') {
    *d++ = utf16to32c(&s);
  }
  *d = '\0';
  return d - _d;
}

dlexport u32 *utf16to32a(cstr16 s) {
  u32 *r = malloc((strlen16(s) + 1) * 4);
  if (r == null) return null;
  usize n = utf16to32s(r, s);
  return realloc(r, (n + 1) * 4);
}

dlexport isize utf32to8c(u32 c, u8 *s) {
  if (c <= 0x7f) {
    s[0] = c;
    return 1;
  } else if (c <= 0x7ff) {
    s[0] = 0xc0 | (c >> 6);
    s[1] = 0x80 | (c & 0x3f);
    return 2;
  } else if (c <= 0xffff) {
    s[0] = 0xe0 | (c >> 12);
    s[1] = 0x80 | ((c >> 6) & 0x3f);
    s[2] = 0x80 | (c & 0x3f);
    return 3;
  } else if (c <= 0x1fffff) {
    s[0] = 0xf0 | (c >> 18);
    s[1] = 0x80 | ((c >> 12) & 0x3f);
    s[2] = 0x80 | ((c >> 6) & 0x3f);
    s[3] = 0x80 | (c & 0x3f);
    return 4;
  } else {
    return -1;
  }
}

dlexport usize utf32to8s(u8 *d, cstr32 s) {
  const u8 *_d = d;
  while (*s != '\0') {
    isize n = utf32to8c(*s++, d);
    if (n < 0) {
      *d++ = 0xef;
      *d++ = 0xbf;
      *d++ = 0xbd;
    } else {
      d += n;
    }
  }
  *d = '\0';
  return d - _d;
}

dlexport u8 *utf32to8a(cstr32 s) {
  u8 *r = malloc(strlen32(s) * 4 + 1);
  if (r == null) return null;
  usize n = utf32to8s(r, s);
  return realloc(r, n + 1);
}

dlexport isize utf32to16c(u32 c, u16 *s) {
  if (c <= 0xffff) {
    s[0] = c;
    return 1;
  } else if (c <= 0x10ffff) {
    c    -= 0x10000;
    s[0]  = 0xd800 | (c >> 10);
    s[1]  = 0xdc00 | (c & 0x3ff);
    return 2;
  } else {
    return -1;
  }
}

dlexport usize utf32to16s(u16 *d, cstr32 s) {
  const u16 *_d = d;
  while (*s != '\0') {
    isize n = utf32to16c(*s++, d);
    if (n < 0) {
      *d++ = 0xfffd;
    } else {
      d += n;
    }
  }
  *d = '\0';
  return d - _d;
}

dlexport u16 *utf32to16a(cstr32 s) {
  u16 *r = malloc(strlen32(s) * 4 + 2);
  if (r == null) return null;
  usize n = utf32to16s(r, s);
  return realloc(r, (n + 1) * 2);
}

dlexport constfn bool is_vaild_utf32(u32 c) {
  return c <= 0x10ffff && (c < 0xd800 || c > 0xdfff);
}

dlexport bool is_vaild_utf32s(cstr32 s) {
  while (*s != '\0') {
    if (!is_vaild_utf32(*s++)) return false;
  }
  return true;
}

dlexport usize count_invalid_utf32s(cstr32 s) {
  usize n = 0;
  while (*s != '\0') {
    if (!is_vaild_utf32(*s++)) n++;
  }
  return n;
}

dlexport usize remove_invalid_utf32s(u32 *d, cstr32 s) {
  const u32 *_d = d;
  while (*s != '\0') {
    u32 c = *s++;
    if (is_vaild_utf32(c)) *d++ = c;
  }
  *d = '\0';
  return d - _d;
}

dlexport usize count_invalid_utf16s(cstr16 s) {
  usize n = 0;
  while (*s != '\0') {
    u32 c = utf16to32c(&s);
    if (!is_vaild_utf32(c)) n++;
  }
  return n;
}

dlexport usize remove_invalid_utf16s(u16 *d, cstr16 s) {
  const u16 *_d = d;
  while (*s != '\0') {
    u32 c = utf16to32c(&s);
    if (is_vaild_utf32(c)) {
      isize n = utf32to16c(c, d);
      if (n > 0) d += n;
    }
  }
  *d = '\0';
  return d - _d;
}

dlexport usize count_invalid_utf8s(cstr8 s) {
  usize n = 0;
  while (*s != '\0') {
    u32 c = utf8to32c(&s);
    if (!is_vaild_utf32(c)) n++;
  }
  return n;
}

dlexport usize remove_invalid_utf8s(u8 *d, cstr8 s) {
  const u8 *_d = d;
  while (*s != '\0') {
    u32 c = utf8to32c(&s);
    if (is_vaild_utf32(c)) {
      isize n = utf32to8c(c, d);
      if (n > 0) d += n;
    }
  }
  *d = '\0';
  return d - _d;
}

dlexport bool utf32_isprint(u32 c) {
  return (c >= 0x20 && c <= 0x7E) || (c >= 0xA0 && c <= 0x10FFFF && c != 0xAD);
}

dlexport bool utf32_isspace(u32 c) {
  return c == 0x20 || (c >= 0x09 && c <= 0x0D) || c == 0x85 || c == 0xA0;
}
