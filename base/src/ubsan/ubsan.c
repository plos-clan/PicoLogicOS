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

#include <asm.h>

#include "serial.h"

#include "fmt.h"

#include "lock.h"

static void panic() {
  asm_cli;
  klogs(CRGB(255, 64, 64) "Panic!" CEND "\n");
  while (true) {
    asm_hlt;
  }
}

typedef const struct SourceLocation {
  cstr file; // 文件名
  u32  line; // 行号
  u32  col;  // 列号
} SourceLocation;

typedef const struct TypeDescriptor {
  u16  TypeKind;   // 类型种类
  u16  TypeInfo;   // 类型信息
  char TypeName[]; // 类型名称，以 null 结尾
} TypeDescriptor;

typedef const struct OutOfBoundsData {
  SourceLocation        Loc;
  const TypeDescriptor *ArrayType;
  const TypeDescriptor *IndexType;
} OutOfBoundsData;

typedef const struct ShiftOutOfBoundsData {
  SourceLocation  Loc;
  TypeDescriptor *LHSType;
  TypeDescriptor *RHSType;
} ShiftOutOfBoundsData;

// https://github.com/gcc-mirror/gcc/blob/2056d52d74070f50c5f8a22e4a600fcc3974fd88/libsanitizer/ubsan/ubsan_handlers.cpp#L43
/// 我们可能会为指针或左值的适用性发出检查的情况。
/// 需要与 clang 中的 CodeGenFunction.h 保持同步。
enum TypeCheckKind {
  /// 检查加载操作的操作数。必须具有适当的大小和对齐。
  TCK_Load,
  /// 检查存储目标。必须具有适当的大小和对齐。
  TCK_Store,
  /// 检查引用绑定中的绑定值。必须具有适当的大小和对齐，
  /// 但根据核心问题453，在引用被使用之前不需要引用一个对象。
  TCK_ReferenceBinding,
  /// 检查非静态数据成员访问中的对象表达式。
  /// 必须是在其生命周期内的对象。
  TCK_MemberAccess,
  /// 检查非静态成员函数调用的'this'指针。
  /// 必须是在其生命周期内的对象。
  TCK_MemberCall,
  /// 检查构造函数调用的'this'指针。
  TCK_ConstructorCall,
  /// 检查static_cast到派生指针类型的操作数。
  /// 必须是null或在其生命周期内的对象。
  TCK_DowncastPointer,
  /// 检查static_cast到派生引用类型的操作数。
  /// 必须是在其生命周期内的对象。
  TCK_DowncastReference,
  /// 检查转换为基类对象的操作数。必须具有适当的大小和对齐。
  TCK_Upcast,
  /// 检查转换为虚拟基类对象的操作数。必须是在其生命周期内的对象。
  TCK_UpcastToVirtualBase,
  /// 检查分配给_Nonnull指针的值。不能为null。
  TCK_NonnullAssign,
  /// 检查dynamic_cast或typeid表达式的操作数。
  /// 必须是null或在其生命周期内的对象。
  TCK_DynamicOperation
};

typedef const struct TypeMismatchData {
  SourceLocation  Loc;
  TypeDescriptor *Type;
  u8              LogAlignment;
  u8              TypeCheckKind;
} TypeMismatchData;

typedef const struct OverflowData {
  SourceLocation  Loc;
  TypeDescriptor *Type;
} OverflowData;

// https://github.com/gcc-mirror/gcc/blob/2056d52d74070f50c5f8a22e4a600fcc3974fd88/libsanitizer/ubsan/ubsan_handlers.h#L162
enum BuiltinCheckKind {
  BCK_CTZPassedZero,
  BCK_CLZPassedZero,
  BCK_AssumePassedFalse,
};

typedef const struct InvalidBuiltinData {
  SourceLocation Loc;
  u8             Kind;
} InvalidBuiltinData;

typedef const struct NonNullArgData {
  SourceLocation Loc;
  SourceLocation AttrLoc;
  int            ArgIndex;
} NonNullArgData;

typedef const struct VLABoundData {
  SourceLocation  Loc;
  TypeDescriptor *Type;
} VLABoundData;

enum ImplicitConversionCheckKind {
  ICCK_IntegerTruncation                   = 0, // Legacy, was only used by clang 7.
  ICCK_UnsignedIntegerTruncation           = 1,
  ICCK_SignedIntegerTruncation             = 2,
  ICCK_IntegerSignChange                   = 3,
  ICCK_SignedIntegerTruncationOrSignChange = 4,
};

typedef const struct ImplicitConversionData {
  SourceLocation  Loc;
  TypeDescriptor *FromType;
  TypeDescriptor *ToType;
  unsigned char   Kind;
  unsigned int    BitfieldBits;
} ImplicitConversionData;

#define UB   "[" CRGB(255, 128, 64) "UB" CEND "]"
#define AT   CRGB(253, 192, 160) "at" CEND
#define IN   CRGB(253, 192, 160) "in" CEND
#define TO   CRGB(253, 192, 160) "to" CEND
#define OF   CRGB(253, 192, 160) "of" CEND
#define IDX  CRGB(253, 192, 160) "idx" CEND
#define AKA  CRGB(253, 192, 160) "aka" CEND
#define TYPE CRGB(255, 192, 0) "%-20s" CEND
#define POS  "[" CRGB(0, 255, 255) "%-4u" CEND ":" CRGB(255, 128, 192) "%3u" CEND "]"
#define FILE "[" CRGB(192, 128, 255) "%-24s" CEND "]"

#define FMT UB " " TYPE " " AT " " POS " " IN " " FILE "\n"

#define ublog(type, pos)                                                                           \
  ({                                                                                               \
    asm volatile("xchg %%bx, %%bx\n\t" ::: "memory");                                              \
    klog(FMT, type, (pos)->line, (pos)->col, _log_relative_path_((pos)->file ?: "<unknown>"));     \
  })

#define UBSAN_FN(_type_, _version_) __nif void __ubsan_handle_##_type_##_version_
#define UBSAN_FX(_type_, _version_) __attr(noreturn) __nif void __ubsan_handle_##_type_##_version_

#define HANDLE(_name_, _type_, _version_, ...)                                                     \
  UBSAN_FN(_type_, _version_)(const void *pos, const usize v1, const usize v2) {                   \
    klock();                                                                                       \
    ublog(_name_, (SourceLocation *)pos);                                                          \
    (__VA_ARGS__);                                                                                 \
    kunlock();                                                                                     \
  }                                                                                                \
  UBSAN_FX(_type_, _version_##abort)(const void *pos, const usize v1, const usize v2) {            \
    klock();                                                                                       \
    ublog(_name_, (SourceLocation *)pos);                                                          \
    (__VA_ARGS__);                                                                                 \
    panic();                                                                                       \
    __builtin_unreachable();                                                                       \
  }
#define HANDLX(_name_, _type_, _version_, ...)                                                     \
  UBSAN_FX(_type_, _version_)(const void *pos, const usize v1, const usize v2) {                   \
    klock();                                                                                       \
    ublog(_name_, (SourceLocation *)pos);                                                          \
    (__VA_ARGS__);                                                                                 \
    panic();                                                                                       \
    __builtin_unreachable();                                                                       \
  }                                                                                                \
  UBSAN_FX(_type_, _version_##abort)(const void *pos, const usize v1, const usize v2) {            \
    klock();                                                                                       \
    ublog(_name_, (SourceLocation *)pos);                                                          \
    (__VA_ARGS__);                                                                                 \
    panic();                                                                                       \
    __builtin_unreachable();                                                                       \
  }

#define C1 CRGB(128, 192, 255)
#define C2 CRGB(64, 192, 128)
#define C3 CRGB(192, 255, 128)

static i32 typewidth(TypeDescriptor *type) {
  if (type->TypeKind == 0) { // int
    return 1 << (type->TypeInfo >> 1);
  } else if (type->TypeKind == 1) { // float
    return -1;
  } else if (type->TypeKind == 2) { // bitint
    return *(u32 *)&type->TypeName[strlen(type->TypeName) + 1];
  } else {
    return -1;
  }
}

static void ptype(TypeDescriptor *type, bool aka) {
  klog("(" C3);
  if (type->TypeKind == 0) { // int
    if (type->TypeInfo & 1) {
      klog("i%d", 1 << (type->TypeInfo >> 1));
    } else {
      klog("u%d", 1 << (type->TypeInfo >> 1));
    }
  } else if (type->TypeKind == 1) { // float
    klog("f%u", 1 << (type->TypeInfo >> 1));
  } else if (type->TypeKind == 2) { // bitint
    u32 width = *(u32 *)&type->TypeName[strlen(type->TypeName) + 1];
    if (type->TypeInfo & 1) {
      klog("bit i%u", width);
    } else {
      klog("bit u%u", width);
    }
  } else {
    for (u32 i = type->TypeName[0] == '\''; type->TypeName[i] && type->TypeName[i] != '\''; i++) {
      klog("%c", type->TypeName[i]);
    }
  }
  klog(CEND ")");
  if (aka && type->TypeKind == 0) {
    klog(" " AKA " " C3);
    for (u32 i = type->TypeName[0] == '\''; type->TypeName[i] && type->TypeName[i] != '\''; i++) {
      klog("%c", type->TypeName[i]);
    }
    klog(CEND);
  }
}

static void pvalue(TypeDescriptor *type, usize value) {
  if (type->TypeKind == 0) { // int
    if (type->TypeInfo & 1) {
      switch (type->TypeInfo >> 1) {
      case 3: pi8(value); break;
      case 4: pi16(value); break;
      case 5: pi32(value); break;
#ifdef __x86_64__
      case 6: pi64(value); break;
#else
      case 6: pi64(*(i64 *)value); break;
#endif
      default: klogs("<ukn>"); break;
      }
    } else {
      switch (type->TypeInfo >> 1) {
      case 3: pu8(value); break;
      case 4: pu16(value); break;
      case 5: pu32(value); break;
#ifdef __x86_64__
      case 6: pu64(value); break;
#else
      case 6: pu64(*(u64 *)value); break;
#endif
      default: klogs("<ukn>"); break;
      }
    }
  } else if (type->TypeKind == 1) { // float
    klogs("<flt>");
  } else if (type->TypeKind == 2) { // bitint
    u32 width = *(u32 *)&type->TypeName[strlen(type->TypeName) + 1];
    if (width <= sizeof(usize) * 8) {
      usize _val = value << (sizeof(usize) * 8 - width);
#ifdef __x86_64__
      if (type->TypeInfo & 1) {
        pi64((i64)_val >> (sizeof(usize) * 8 - width));
      } else {
        pu64((u64)_val >> (sizeof(usize) * 8 - width));
      }
#else
      if (type->TypeInfo & 1) {
        pi32((i32)_val >> (sizeof(usize) * 8 - width));
      } else {
        pu32((u32)_val >> (sizeof(usize) * 8 - width));
      }
#endif
    } else if (width <= 64) {
#ifdef __x86_64__
      klogs("<ukn>");
#else
      u64 _val = *(u64 *)value << (sizeof(u64) * 8 - width);
      if (type->TypeInfo & 1) {
        pi64((i64)_val >> (sizeof(i64) * 8 - width));
      } else {
        pu64((u64)_val >> (sizeof(u64) * 8 - width));
      }
#endif
    } else {
      klogs("<ukn>");
    }
  } else {
    klog("<%p>", value);
  }
}

enum {
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_NEG,
};

static void pcalc(TypeDescriptor *type, usize v1, usize v2, int op) {
  i32 width = typewidth(type);
  if (width < 0 || width > 64) {
    klog("<ukn>");
    return;
  }
#ifdef __x86_64__
  usize result = 0;
  if (op == OP_ADD) {
    result = v1 + v2;
  } else if (op == OP_SUB) {
    result = v1 - v2;
  } else if (op == OP_MUL) {
    result = v1 * v2;
  } else if (op == OP_NEG) {
    result = -v1;
  }
  pvalue(type, result);
#else
  if (width <= 32) {
    usize result = 0;
    if (op == OP_ADD) {
      result = v1 + v2;
    } else if (op == OP_SUB) {
      result = v1 - v2;
    } else if (op == OP_MUL) {
      result = v1 * v2;
    } else if (op == OP_NEG) {
      result = -v1;
    }
    pvalue(type, result);
  } else {
#  define v1 (*(u64 *)v1)
#  define v2 (*(u64 *)v2)
    u64 result = 0;
    if (op == OP_ADD) {
      result = v1 + v2;
    } else if (op == OP_SUB) {
      result = v1 - v2;
    } else if (op == OP_MUL) {
      result = v1 * v2;
    } else if (op == OP_NEG) {
      result = -v1;
    }
#  undef v1
#  undef v2
    pvalue(type, (usize)&result);
  }
#endif
}

HANDLE("add_overflow", add_overflow, , {
  OverflowData *data = pos;
  klog("\t" C1);
  pvalue(data->Type, v1);
  klog(CEND " + " C1);
  pvalue(data->Type, v2);
  klog(CEND " => " C2);
  pcalc(data->Type, v1, v2, OP_ADD);
  klog(CEND);
  klog("\t"), ptype(data->Type, true), klog("\n");
});
HANDLE("alignment_assumption", alignment_assumption, , {});
HANDLX("builtin_unreachable", builtin_unreachable, , {
  klog("\t" COLOR_FATAL "Control flow should not reach here." CEND "\n");
  klog(COLOR_FATAL "Terminating..." CEND "\n");
});
HANDLE("cfi_bad_type", cfi_bad_type, , {});
HANDLE("cfi_check_fail", cfi_check_fail, , {});
HANDLE("divrem_overflow", divrem_overflow, , {});
HANDLE("dynamic_type_cache_miss", dynamic_type_cache_miss, , {});
HANDLE("float_cast_overflow", float_cast_overflow, , {});
HANDLE("function_type_mismatch", function_type_mismatch, , {});
HANDLE("implicit_conversion", implicit_conversion, , {
  ImplicitConversionData *data = pos;
  klog("\t" C1), pvalue(data->FromType, v1), klog(CEND " "), ptype(data->FromType, true);
  klog(" " TO " " C1), pvalue(data->ToType, v2), klog(CEND " "), ptype(data->ToType, true);
  klog("\n");
});
HANDLE("invalid_builtin", invalid_builtin, , {
  InvalidBuiltinData *data = pos;
  if (data->Kind == BCK_CTZPassedZero) {
    klog("\t" C1 "__builtin_ctz" CEND "(" C2 "0" CEND ")\n");
  } else if (data->Kind == BCK_CLZPassedZero) {
    klog("\t" C1 "__builtin_clz" CEND "(" C2 "0" CEND ")\n");
  } else if (data->Kind == BCK_AssumePassedFalse) {
    klog("\t" C1 "__builtin_assume" CEND "(" C2 "false" CEND ")\n");
  }
});
HANDLE("invalid_objc_cast", invalid_objc_cast, , {});
HANDLE("load_invalid_value", load_invalid_value, , {});
HANDLX("missing_return", missing_return, , {
  klog("\t" COLOR_FATAL "The function returns nothing." CEND "\n");
  klog(COLOR_FATAL "Terminating..." CEND "\n");
});
HANDLE("mul_overflow", mul_overflow, , {
  OverflowData *data = pos;
  klog("\t" C1);
  pvalue(data->Type, v1);
  klog(CEND " * " C1);
  pvalue(data->Type, v2);
  klog(CEND " => " C2);
  pcalc(data->Type, v1, v2, OP_MUL);
  klog(CEND);
  klog("\t"), ptype(data->Type, true), klog("\n");
});
HANDLE("negate_overflow", negate_overflow, , {
  OverflowData *data = pos;
  klog("\t- " C1);
  pvalue(data->Type, v1);
  klog(CEND " => " C2);
  pcalc(data->Type, v1, 0, OP_NEG);
  klog(CEND);
  klog("\t"), ptype(data->Type, true), klog("\n");
});
HANDLE("nonnull_arg", nonnull_arg, , {
  NonNullArgData *data = pos;
  klog("\t" C3 "arg %-3d " CEND "\t" TO " " POS " " IN " " FILE "\n", data->ArgIndex,
       data->AttrLoc.line, data->AttrLoc.col,
       _log_relative_path_(data->AttrLoc.file ?: "<unknown>"));
});
HANDLE("nonnull_return", nonnull_return, _v1, {
  SourceLocation *loc = (SourceLocation *)v1;
  klog("\t" C3 "ret null" CEND "\t" AT " " POS " " IN " " FILE "\n", loc->line, loc->col,
       _log_relative_path_(loc->file ?: "<unknown>"));
});
HANDLE("nullability_arg", nullability_arg, , {
  NonNullArgData *data = pos;
  klog("\t" C3 "arg %-3d " CEND "\t" TO " " POS " " IN " " FILE "\n", data->ArgIndex,
       data->AttrLoc.line, data->AttrLoc.col,
       _log_relative_path_(data->AttrLoc.file ?: "<unknown>"));
});
HANDLE("nullability_return", nullability_return, _v1, {
  SourceLocation *loc = (SourceLocation *)v1;
  klog("\t" C3 "ret null" CEND "\t" AT " " POS " " IN " " FILE "\n", loc->line, loc->col,
       _log_relative_path_(loc->file ?: "<unknown>"));
});
HANDLE("out_of_bounds", out_of_bounds, , {
  OutOfBoundsData *data = pos;
  klog("\t" IDX " " C1 "%d" CEND " ", v1), ptype(data->IndexType, false);
  klog(" " OF " "), ptype(data->ArrayType, false), klog("\n");
});
HANDLE("pointer_overflow", pointer_overflow, , { klog("%p %p\n", v1, v2); });
HANDLE("shift_out_of_bounds", shift_out_of_bounds, , {
  ShiftOutOfBoundsData *data = pos;
  klog("\t" C1 "%d" CEND " ", v1), ptype(data->LHSType, false);
  klog(" " TO " "), ptype(data->RHSType, false), klog("\n");
});
HANDLE("sub_overflow", sub_overflow, , {
  OverflowData *data = pos;
  klog("\t" C1);
  pvalue(data->Type, v1);
  klog(CEND " - " C1);
  pvalue(data->Type, v2);
  klog(CEND " => " C2);
  pcalc(data->Type, v1, v2, OP_SUB);
  klog(CEND);
  klog("\t"), ptype(data->Type, true), klog("\n");
});
// HANDLE("type_mismatch", type_mismatch, _v1, {
//   TypeMismatchData *data = pos;
//   klog("\t" C1 "%d" CEND " ", 1 << data->LogAlignment);
//   ptype(data->Type, true), klog("\n");
// });
HANDLE("vla_bound_not_positive", vla_bound_not_positive, , {
  VLABoundData *data = pos;
  klog("\t[" C1), pvalue(data->Type, v1), klog(CEND "]");
  klog("\t"), ptype(data->Type, true), klog("\n");
});

UBSAN_FN(type_mismatch, _v1)(const void *pos, const usize v1, const usize v2) {}
UBSAN_FX(type_mismatch, _v1abort)(const void *pos, const usize v1, const usize v2) {}

__nif void __ubsan_default_options() {
  // 目前无用
}

__nif void __ubsan_on_report() {
  // 目前无用
}

__nif void __ubsan_get_current_report_data() {
  // 目前无用
}
