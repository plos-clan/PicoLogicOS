#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_STD 0
#include <define.h>

enum {
  OP_CONST,
  OP_VAR,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_POW,
  OP_LOG
};

typedef struct Constant {
} Constant;

typedef struct Fraction {};

typedef struct Expr {
  i32          type;
  usize        value;
  struct Expr *lhs;
  struct Expr *rhs;
} Expr;

Expr *simplify(Expr *e) {
  if (!e) return NULL;
  e->left  = simplify(e->left);
  e->right = simplify(e->right);

  if (e->type == OP_ADD || e->type == OP_MUL || e->type == OP_SUB || e->type == OP_DIV ||
      e->type == OP_POW) {
    if (e->left && e->left->type == OP_CONST && e->right && e->right->type == OP_CONST) {
      double a      = e->left->value;
      double b      = e->right->value;
      double result = 0;
      switch (e->type) {
      case OP_ADD: result = a + b; break;
      case OP_SUB: result = a - b; break;
      case OP_MUL: result = a * b; break;
      case OP_DIV: result = a / b; break;
      case OP_POW: result = pow(a, b); break;
      default: break;
      }
      return make_const(result);
    }

    // 简化规则
    if (e->type == OP_MUL) {
      if ((e->left->type == OP_CONST && e->left->value == 0) ||
          (e->right->type == OP_CONST && e->right->value == 0))
        return make_const(0);
      if (e->left->type == OP_CONST && e->left->value == 1) return e->right;
      if (e->right->type == OP_CONST && e->right->value == 1) return e->left;
    }

    if (e->type == OP_ADD) {
      if (e->left->type == OP_CONST && e->left->value == 0) return e->right;
      if (e->right->type == OP_CONST && e->right->value == 0) return e->left;
    }

    if (e->type == OP_LOG && e->right && e->right->type == OP_POW &&
        e->right->left->type == OP_CONST && e->right->left->value == M_E) {
      return e->right->right; // log(e^x) = x
    }
  }
  return e;
}

// 打印表达式（中缀）
void print_expr(Expr *e) {
  if (!e) return;
  if (e->type == OP_CONST)
    printf("%.2f", e->value);
  else if (e->type == OP_VAR)
    printf("%s", e->var);
  else {
    printf("(");
    print_expr(e->left);
    switch (e->type) {
    case OP_ADD: printf(" + "); break;
    case OP_SUB: printf(" - "); break;
    case OP_MUL: printf(" * "); break;
    case OP_DIV: printf(" / "); break;
    case OP_POW: printf(" ^ "); break;
    case OP_LOG:
      printf("log(");
      print_expr(e->right);
      printf(")");
      return;
    default: break;
    }
    print_expr(e->right);
    printf(")");
  }
}

Expr *parse_num(cstr *_s) {
  cstr s = *_s;
  if (!isdigit(*s)) return null;

  while (isdigit(*s)) {
    s++;
  }

  return;
}

int main(int argc, char **argv) {}
