#pragma once
#include <define.h>

namespace cpp {

class Spin {
  atomic volatile bool spin = false;

public:
  Spin()                         = default;
  Spin(Spin &)                   = delete;
  Spin(const Spin &)             = delete;
  Spin(Spin &&)                  = delete;
  Spin(const Spin &&)            = delete;
  Spin &operator=(Spin &)        = delete;
  Spin &operator=(const Spin &)  = delete;
  Spin &operator=(Spin &&)       = delete;
  Spin &operator=(const Spin &&) = delete;
  ~Spin()                        = default;

  // 尝试获取锁，成功返回 true，失败返回 false
  bool try_lock() {
    return !atom_tas(&spin);
  }

  // 阻塞直到获取锁
  void lock() {
    while (atom_tas(&spin)) {}
  }

  // 释放锁
  void unlock() {
    atom_clr(&spin);
  }

  // // 尝试锁定多个 Spin 对象
  // static void lock_all(std::initializer_list<Spin *> spins) {
  //   while (true) {
  //     size_t i = 0;
  //     for (; i < spins.size(); ++i) {
  //       if (!spins.begin()[i]->try_lock()) { break; }
  //     }
  //     if (i == spins.size()) {
  //       break; // 全部锁定成功
  //     }
  //     // 解锁已锁定的锁
  //     for (size_t j = 0; j < i; ++j) {
  //       spins.begin()[j]->unlock();
  //     }
  //   }
  // }

  // // 解锁多个 Spin 对象
  // static void unlock_all(std::initializer_list<Spin *> spins) {
  //   for (auto it = spins.end(); it != spins.begin();) {
  //     (--it)->unlock();
  //   }
  // }
};

} // namespace cpp
