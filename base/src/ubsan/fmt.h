#pragma once
#include "atoi.h"
#include "itoa.h"
#include "serial.h"
#include "strlen.h"

#define format_bufsize 64
static char format_buf[format_bufsize];

enum fmtalign {
  align_left,
  align_middle,
  align_right,
};

typedef struct fmtarg {
  int  align;     // 对齐方式
  bool fill_zero; // 是否用 0 填充

  bool print_ptr;

  ssize_t padding; // 输出字符串的对齐长度
  ssize_t maxlen;  // 输出字符串的最大长度
  ssize_t minlen;  // 输出字符串的最小长度

  // 格式化时的缓冲区
  char  *buf;
  size_t bufsize;

  // 原数据直接转换成的字符串
  // 包括结尾的 '\0'
  // 不包括用于对齐的空格
  // 指向 buf 中的内容
  char *text;
} fmtarg;

static void fmtarg_clear(fmtarg *arg) {
  arg->align     = align_right;
  arg->fill_zero = false;
  arg->print_ptr = false;
  arg->padding   = 0;
  arg->maxlen    = 0;
  arg->minlen    = 0;
  arg->text      = null;
}

static bool format_parse(fmtarg *arg, cstr _rest *_fmt, va_list *_va) {
#define va (*_va)
  fmtarg_clear(arg);
  cstr fmt = *_fmt + 1;

  if (*fmt == '%') {
    arg->text    = arg->buf;
    arg->text[0] = '%';
    arg->text[1] = '\0';
    *_fmt        = fmt + 1;
    return true;
  }

  if (*fmt == '0') {
    arg->fill_zero = true;
    fmt++;
  }

  if (*fmt == '!') { // 解析自定义 padding 语法，如 !8d !-8d
    fmt++;
    char *f;
    arg->padding = strb10toi(fmt, &f);
    if (fmt == f && *f == '*') {
      arg->padding = va_arg(va, int);
      f++;
    }
    if (arg->padding < 0) {
      arg->padding = -arg->padding;
      arg->align   = align_left;
    }
    fmt = f;
  } else { // 解析标准的写法
    char *f;
    arg->minlen = strb10toi(fmt, &f); // 解析 %15d 这样的写法
    if (fmt == f && *f == '*') {      // 解析 %*d 这样的写法
      arg->minlen = va_arg(va, int);
      f++;
    }
    if (arg->minlen < 0) { // 小于 0 的靠右对齐
      arg->minlen = -arg->minlen;
      arg->align  = align_left;
    }
    fmt = f;
  }

  if (arg->fill_zero && arg->align != align_right) goto err;

  // 1 | char      | error
  // 2 | short     | error
  // 3 | int       | float
  // 4 | long      | double
  // 5 | long long | long double
  int _size = 3;

next_char:
  switch (*fmt++) {

  case 'h':
    if (_size <= 0 || _size > 3) goto err;
    _size--;
    goto next_char;

  case 'l':
    if (_size < 3 || _size >= 6) goto err;
    _size++;
    goto next_char;

  case 'c':
  case 'C':
    if (_size != 3) goto err;
    arg->text      = arg->buf;
    arg->text[0]   = va_arg(va, int);
    arg->text[1]   = '\0';
    arg->fill_zero = false; // 字符不应该使用 0 填充
    goto end;

#define tostr_arg(type)     arg->buf, arg->bufsize, va_arg(va, type)
#define tostr_arg2(t, type) arg->buf, arg->bufsize, (t)va_arg(va, type)

#define format_in_bn(_n_, _u_)                                                                     \
  switch (_size) {                                                                                 \
  case 1: arg->text = _u_##hhtostr##_n_(tostr_arg2(_u_##char, _u_##int)); break;                   \
  case 2: arg->text = _u_##htostr##_n_(tostr_arg2(_u_##short, _u_##int)); break;                   \
  case 3: arg->text = _u_##itostr##_n_(tostr_arg(_u_##int)); break;                                \
  case 4: arg->text = _u_##ltostr##_n_(tostr_arg(_u_##long)); break;                               \
  case 5: arg->text = _u_##lltostr##_n_(tostr_arg(_u_##llong)); break;                             \
  }                                                                                                \
  goto end;

  case 'b':
  case 'B': format_in_bn(b2, u);

  case 'o':
  case 'O': format_in_bn(b8, u);

  case 'i':
  case 'I':
  case 'd':
  case 'D': format_in_bn(b10, );

  case 'u':
  case 'U': format_in_bn(b10, u);

  case 'x': format_in_bn(b16, u);
  case 'X': format_in_bn(B16, u);

#undef format_in_bn

  case 'p':
    if (_size != 3) goto err;
    arg->print_ptr = true;
#ifdef __x86_64__
    arg->text = u64tostrb16(tostr_arg(u64));
#else
    arg->text = u32tostrb16(tostr_arg(u32));
#endif
    goto end;
  case 'P':
    if (_size != 3) goto err;
    arg->print_ptr = true;
#ifdef __x86_64__
    arg->text = u64tostrB16(tostr_arg(u64));
#else
    arg->text = u32tostrB16(tostr_arg(u32));
#endif
    goto end;

#undef tostr_arg
#undef tostr_arg2

  case 's': // 字符串
  case 'S':
    if (_size != 3) goto err;
    arg->text = va_arg(va, char *);
    if (!arg->text) {
      arg->text      = arg->buf;
      arg->text[0]   = '\0';
      arg->fill_zero = false; // 字符串不应该使用 0 填充
    }
    goto end;

  default: goto err;
  }

end:
  *_fmt = fmt;
  return true;

err:
  return false;
#undef va
}

static void format_print(fmtarg *arg) {
  if (!arg->text) return; // 无输出
  ssize_t _arg_len = strlen(arg->text);
  ssize_t arg_len  = arg->print_ptr ? 2 + 2 * sizeof(void *) : _arg_len;

  if (arg->maxlen > 0 && arg_len > arg->maxlen) { // 放不下就进行截断 假如 maxlen 为 25
    if (arg->maxlen <= 3) {                       // This is a long long long long line.
      for (size_t i = 0; i < arg->maxlen; i++)    // This is a long long lo...
        klogc('.');
    } else {
      for (size_t i = 0; i < arg->maxlen - 3; i++)
        klogc(arg->text[i]);
      for (size_t i = 0; i < 3; i++)
        klogc('.');
    }
    return;
  }

  if (arg->padding) arg->minlen = (arg_len + arg->padding - 1) / arg->padding * arg->padding;

  ssize_t blank      = arg->minlen - arg_len;
  size_t  blank_left = 0, blank_right = 0;

  if (blank > 0) {
    if (arg->align == align_left) {
      blank_right = blank;
    } else if (arg->align == align_middle) {
      blank_left  = blank / 2;
      blank_right = blank - blank_left;
    } else if (arg->align == align_right) {
      blank_left = blank;
    } else {
      blank_right = blank; // 异常值当作左对齐
    }
  }

  if (blank_left > 0 && arg->fill_zero && *arg->text == '-') {
    klogc('-');
    arg->text++;
  }
  for (size_t i = 0; i < blank_left; i++)
    klogc(arg->fill_zero ? '0' : ' ');
  if (arg->print_ptr) {
    klogc('0');
    klogc('x');
    for (size_t i = _arg_len; i < 2 * sizeof(void *); i++)
      klogc('0');
  }
  while (*arg->text != '\0')
    klogc(*arg->text++);
  for (size_t i = 0; i < blank_right; i++)
    klogc(' ');
}

static bool try_format_and_print(cstr _rest *fmt, fmtarg *arg, va_list *va) {
  if (**fmt != '%') return false;
  if (!format_parse(arg, fmt, va)) return false;
  format_print(arg);
  return true;
}

static void klog(cstr _rest fmt, ...) {
  if (fmt == null) return;

  static fmtarg arg = {.buf = format_buf, .bufsize = format_bufsize};

  va_list va;
  va_start(va, fmt);

  while (*fmt != '\0') {
    if (try_format_and_print(&fmt, &arg, &va)) continue;
    klogc(*fmt++);
  }

  va_end(va);
}

#define P(_type_)                                                                                  \
  static void p##_type_(_type_ n) {                                                                \
    klogs(_type_##tostrb10(format_buf, format_bufsize, n));                                        \
  }

P(i8);
P(u8);
P(i16);
P(u16);
P(i32);
P(u32);
P(i64);
P(u64);
