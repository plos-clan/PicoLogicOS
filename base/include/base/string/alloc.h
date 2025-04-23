#pragma once
#include "str.h"

// 以下几个函数已在其它文件中声明
#if 0
char *strdup(cstr s);
char *strndup(cstr s, size_t n);
void *memdup(const void *s, size_t n);
#endif

dlimport xstr c2xstr(cstr s);

dlimport char *x2str(xstr s);

dlimport xstr xstrdup(xstr s);

dlimport char *pathacat(cstr p1, cstr p2) __THROW __nnull(1, 2) __attr_malloc
    __attr_dealloc(free, 1) ownership_returns(malloc);
