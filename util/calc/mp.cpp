#include <cstdio>
#include <cstdlib>
#include <cstring>

#define NO_STD 0
#include <define.hpp>

class Constant {
  usize *ptr sized_by(cap) = null;
  usize  cap               = 0;

public:
  Constant() = default;

  Constant(const Constant &other) {
    cap = other.cap;
    ptr = (usize *)malloc(cap * sizeof(usize));
    memcpy(ptr, other.ptr, cap * sizeof(usize));
  }

  Constant(Constant &&other) noexcept {
    ptr       = other.ptr;
    cap       = other.cap;
    other.ptr = null;
    other.cap = 0;
  }

  Constant(usize value) {
    cap    = 1;
    ptr    = (usize *)malloc(sizeof(usize));
    ptr[0] = value;
  }

  static auto with_cap(usize cap) -> Constant {
    Constant c;
    c.cap = cap;
    c.ptr = (usize *)malloc(cap * sizeof(usize));
    return c;
  }

  auto realloc(usize new_len) -> Constant & {

    return *this;
  }

  auto operator+(const Constant &rhs) const -> Constant {}
};

auto gcd(i64 a, i64 b) -> i64 {
  while (b != 0) {
    i64 t = b;
    b     = a % b;
    a     = t;
  }
  return a;
}

class Fraction {
  i64 num = 0;
  i64 den = 1;

public:
  Fraction() = default;

  Fraction(i64 num, i64 den) : num(num), den(den) {}

  auto is_nan() const -> bool {
    return num == 0 && den == 0;
  }

  auto is_inf() const -> bool {
    return num != 0 && den == 0;
  }

  auto operator+(const Fraction &rhs) const -> Fraction {
    return {
        num * rhs.den + rhs.num * den,
        den * rhs.den,
    };
  }

  auto operator-(const Fraction &rhs) const -> Fraction {
    return {
        num * rhs.den - rhs.num * den,
        den * rhs.den,
    };
  }

  auto operator*(const Fraction &rhs) const -> Fraction {
    return {
        num * rhs.num,
        den * rhs.den,
    };
  }

  auto operator/(const Fraction &rhs) const -> Fraction {
    return {
        num * rhs.den,
        den * rhs.num,
    };
  }

  auto operator==(const Fraction &rhs) const -> bool {
    return num * rhs.den == rhs.num * den;
  }

  auto operator!=(const Fraction &rhs) const -> bool {
    return !(*this == rhs);
  }

  auto operator<(const Fraction &rhs) const -> bool {
    return num * rhs.den < rhs.num * den;
  }

  auto operator>(const Fraction &rhs) const -> bool {
    return num * rhs.den > rhs.num * den;
  }

  auto operator<=(const Fraction &rhs) const -> bool {
    return num * rhs.den <= rhs.num * den;
  }

  auto operator>=(const Fraction &rhs) const -> bool {
    return num * rhs.den >= rhs.num * den;
  }
};
