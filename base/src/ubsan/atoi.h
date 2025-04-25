#pragma once

#define isdigit(c) ('0' <= (c) && (c) <= '9')

static int strb10toi(cstr _rest s, char **_rest e) {
  cstr __s = s;
  bool neg = *s == '-';
  if (neg || *s == '+') s++;
  cstr _s = s;
  int  n  = 0;
  for (; isdigit(*s); s++)
    n = n * 10 + (*s - '0');
  if (e) *e = (char *)(_s == s ? __s : s);
  return neg ? -n : n;
}
