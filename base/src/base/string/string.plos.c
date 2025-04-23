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

// 未完成，不用

typedef struct str_builder {
  char  *str;
  size_t len;
  size_t cap;
} *str_builder_t;

str_builder_t str_builder_new(size_t cap) {
  str_builder_t sb = malloc(sizeof(struct str_builder));
  sb->str          = malloc(cap);
  sb->len          = 0;
  sb->cap          = cap;
  return sb;
}

void str_builder_free(str_builder_t sb) {
  free(sb->str);
  free(sb);
}

void str_builder_append(str_builder_t sb, char ch) {
  if (sb->len >= sb->cap) {
    sb->cap *= 2;
    sb->str  = realloc(sb->str, sb->cap);
  }
  sb->str[sb->len++] = ch;
}

void str_builder_insert(str_builder_t sb, int pos, char ch) {
  if (sb->len >= sb->cap) {
    sb->cap *= 2;
    sb->str  = realloc(sb->str, sb->cap);
  }
  sb->len++;
}

void str_builder_delete(str_builder_t sb, int pos) {
  sb->len--;
}

void str_builder_clear(str_builder_t sb) {
  sb->len = 0;
}

void str_builder_str(str_builder_t sb, char *str) {
  strcpy(str, sb->str);
}
