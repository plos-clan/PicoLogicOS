#ifndef _no_plos_header_
#  include <base.h>
#endif

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

// !!!!! ========== ========== ========== ========== ========== ========== ========== ========== !!!!!
// !!!!!                                       Deprecated                                        !!!!!
// !!!!! ========== ========== ========== ========== ========== ========== ========== ========== !!!!!

#warning "This file is deprecated, please use libubsan.a instead."

#ifndef _lock_
#  define _lock_ _ubsan_empty_func_
#  ifndef _ubsan_defined_empty_func_
#    define _ubsan_defined_empty_func_
static void _ubsan_empty_func_() {}
#  endif
#  warning "_lock_ is not defined, using empty function"
#endif

#ifndef _unlock_
#  define _unlock_ _ubsan_empty_func_
#  ifndef _ubsan_defined_empty_func_
#    define _ubsan_defined_empty_func_
static void _ubsan_empty_func_() {}
#  endif
#  warning "_unlock_ is not defined, using empty function"
#endif

#ifndef _log_func_
#  define _log_func_ printf
#  warning "_log_func_ is not defined, using printf"
#endif

#ifndef _panic_func_
#  define _panic_func_ abort
#  warning "_panic_func_ is not defined, using abort"
#endif

typedef const struct SourceLocation {
  cstr file; // 文件名
  u32  line; // 行号
  u32  col;  // 列号
} SourceLocation;

#define _format_(type)                                                                             \
  STR_ERROR CRGB(253, 133, 172) "at" CEND " [" CRGB(192, 128, 255) "%-24s" CEND "] [" CRGB(        \
      0, 255, 255) "%-4u" CEND ":" CRGB(255, 128, 192) "%3u" CEND "] " COLOR_ERROR                 \
                                                       "UB! " type CEND "\n"

#define ublog(type, file, line, col)                                                               \
  ({                                                                                               \
    asm volatile("xchg %%bx, %%bx\n\t" ::: "memory");                                              \
    _log_func_(_format_(type), _log_relative_path_((file) ?: "<unknown>"), line, col);             \
  })

#define UBSAN_FN(_type_, _version_) __nif void __ubsan_handle_##_type_##_version_

#define HANDLE(_type_, _version_)                                                                  \
  UBSAN_FN(_type_, _version_)(SourceLocation * pos) {                                              \
    ublog(#_type_, pos->file, pos->line, pos->col);                                                \
  }                                                                                                \
  __attr(noreturn) UBSAN_FN(_type_, _version_##abort)(SourceLocation * pos) {                      \
    ublog(#_type_, pos->file, pos->line, pos->col);                                                \
    _panic_func_();                                                                                \
    __builtin_unreachable();                                                                       \
  }
#define HANDLX(_type_, _version_)                                                                  \
  __attr(noreturn) UBSAN_FN(_type_, _version_)(SourceLocation * pos) {                             \
    ublog(#_type_, pos->file, pos->line, pos->col);                                                \
    _panic_func_();                                                                                \
    __builtin_unreachable();                                                                       \
  }                                                                                                \
  __attr(noreturn) UBSAN_FN(_type_, _version_##abort)(SourceLocation * pos) {                      \
    ublog(#_type_, pos->file, pos->line, pos->col);                                                \
    _panic_func_();                                                                                \
    __builtin_unreachable();                                                                       \
  }

HANDLE(add_overflow, );
HANDLE(alignment_assumption, );
HANDLX(builtin_unreachable, );
HANDLE(cfi_bad_type, );
HANDLE(cfi_check_fail, );
HANDLE(divrem_overflow, );
HANDLE(dynamic_type_cache_miss, );
HANDLE(float_cast_overflow, );
HANDLE(function_type_mismatch, );
HANDLE(implicit_conversion, );
HANDLE(invalid_builtin, );
HANDLE(invalid_objc_cast, );
HANDLE(load_invalid_value, );
HANDLX(missing_return, );
HANDLE(mul_overflow, );
HANDLE(negate_overflow, );
HANDLE(nonnull_arg, );
HANDLE(nonnull_return, _v1);
HANDLE(nullability_arg, );
HANDLE(nullability_return, _v1);
HANDLE(out_of_bounds, );
HANDLE(pointer_overflow, );
HANDLE(shift_out_of_bounds, );
HANDLE(sub_overflow, );
HANDLE(type_mismatch, _v1);
HANDLE(vla_bound_not_positive, );

#undef HANDLE
#undef HANDLX

#undef UBSAN_FN

#undef ublog

__nif void __ubsan_default_options() {
  // 目前无用
}

__nif void __ubsan_on_report() {
  // 目前无用
}

__nif void __ubsan_get_current_report_data() {
  // 目前无用
}
