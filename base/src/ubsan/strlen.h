#pragma once

static size_t strlen(cstr s) {
  size_t len = 0;
  while (s[len] != '\0')
    len++;
  return len;
}
