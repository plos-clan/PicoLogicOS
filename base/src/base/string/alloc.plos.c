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

#if NO_STD

dlexport char *strdup(cstr s) noexcept {
  size_t len = strlen(s);
  auto   ptr = (char *)malloc(len + 1);
  if (ptr == null) return null;
  memcpy(ptr, s, len + 1);
  return ptr;
}

dlexport char *strndup(cstr s, size_t n) noexcept {
  size_t len = strlen(s);
  if (n > len) n = len;
  auto ptr = (char *)malloc(n + 1);
  if (ptr == null) return null;
  memcpy(ptr, s, n);
  ptr[n] = '\0';
  return ptr;
}

#endif

dlexport void *memdup(const void *s, size_t n) noexcept {
  void *ptr = malloc(n);
  if (ptr == null) return null;
  memcpy(ptr, s, n);
  return ptr;
}

// 将 C 标准的字符串 转换为 xstr
dlexport xstr c2xstr(cstr s) noexcept {
  if (s == null) return null;
  size_t len = strlen(s);
  xstr   x   = (xstr)malloc(sizeof(struct _xstr) + len + 1);
  if (x == null) return null;
  x->len  = len;
  x->hash = memhash(s, len);
  memcpy(x->data, s, len + 1);
  return x;
}

// 将 xstr 转换为 C 标准的字符串，并删除 xstr
dlexport char *x2str(xstr s) noexcept {
  if (s == null) return null;
  auto ptr = strdup(s->data);
  free(s);
  return ptr;
}

dlexport xstr xstrdup(xstr s) noexcept {
  if (s == null) return null;
  xstr x = (xstr)malloc(sizeof(struct _xstr) + s->len + 1);
  if (x == null) return null;
  x->len  = s->len;
  x->hash = s->hash;
  memcpy(x->data, s->data, s->len + 1);
  return x;
}

dlexport char *pathacat(cstr p1, cstr p2) noexcept {
  char *p = (char *)malloc(strlen(p1) + strlen(p2) + 2);
  if (p == null) return null;
  if (p1[strlen(p1) - 1] == '/') {
    sprintf(p, "%s%s", p1, p2);
  } else {
    sprintf(p, "%s/%s", p1, p2);
  }
  return p;
}
