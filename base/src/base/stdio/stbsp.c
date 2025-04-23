// ^^^^^ ========== ========== ========== ========== ========== ========== ========== ========== ^^^^^
// ^^^^^             The functions in this file is just wrapper of the stb_sprintf.h             ^^^^^
// ^^^^^ ========== ========== ========== ========== ========== ========== ========== ========== ^^^^^

#include <base.h>

#pragma GCC optimize("O0")

#if NO_STD && !USE_SPRINTF

#  define STB_SPRINTF_IMPLEMENTATION
#  include "stb_sprintf.h"

dlexport int vsprintf(char *buf, const char *fmt, va_list args) {
  return stbsp_vsprintf(buf, fmt, args);
}

dlexport int sprintf(char *_rest s, cstr _rest fmt, ...) {
  if (fmt == null) return 0;
  va_list va;
  va_start(va, fmt);
  int rets = vsprintf(s, fmt, va);
  va_end(va);
  return rets;
}

#endif
