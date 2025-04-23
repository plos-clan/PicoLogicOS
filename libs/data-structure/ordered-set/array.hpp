#pragma once
#include "../base.hpp"

#if !__plos_definitions__
#  error "You need to include <define.hpp> of PLOS to use this library"
#endif

#if !PLOS_LIBDATASTRUCTURE_SHOW_WARNING
#  pragma GCC system_header
#endif

namespace cpp {

template <typename T, usize N>
struct SizedArray {
  T data[N]; // 固定大小的数组

  // 获取数组大小
  __wur constexpr usize length() const noexcept {
    return N;
  }

  // 获取数组大小 (字节数)
  __wur constexpr usize size() const noexcept {
    return N * sizeof(T);
  }

  // 获取数组容量
  __wur constexpr usize capacity() const noexcept {
    return N;
  }

  // 检查数组是否为空
  __wur constexpr bool empty() const noexcept {
    return N == 0;
  }

  // 访问元素（带边界检查）
  __wur constexpr T &at(usize index) {
    if (index >= N) fatal("Array index out of range");
    return data[index];
  }

  __wur constexpr const T &at(usize index) const {
    if (index >= N) fatal("Array index out of range");
    return data[index];
  }

  // 访问元素（不带边界检查）
  __wur constexpr T &operator[](usize index) noexcept {
    return data[index];
  }

  __wur constexpr const T &operator[](usize index) const noexcept {
    return data[index];
  }

  // 获取第一个元素
  __wur constexpr T &front() noexcept {
    return data[0];
  }

  __wur constexpr const T &front() const noexcept {
    return data[0];
  }

  // 获取最后一个元素
  __wur constexpr T &back() noexcept {
    return data[N - 1];
  }

  __wur constexpr const T &back() const noexcept {
    return data[N - 1];
  }

  // 获取底层数据指针
  __wur constexpr T *data_ptr() noexcept {
    return data;
  }

  __wur constexpr const T *data_ptr() const noexcept {
    return data;
  }

  // 填充整个数组
  constexpr void fill(const T &value) noexcept {
    for (usize i = 0; i < N; i++) {
      data[i] = value;
    }
  }
};

template <typename T, usize N>
struct SizedArrayMT {
  Spin lock;
  T    data[N]; // 固定大小的数组

  // 获取数组大小
  __wur constexpr usize length() const noexcept {
    return N;
  }

  // 获取数组大小 (字节数)
  __wur constexpr usize size() const noexcept {
    return N * sizeof(T);
  }

  // 获取数组容量
  __wur constexpr usize capacity() const noexcept {
    return N;
  }

  // 检查数组是否为空
  __wur constexpr bool empty() const noexcept {
    return N == 0;
  }

  // 访问元素（带边界检查）
  __wur constexpr T &at(usize index) {
    lock.lock();
    if (index >= N) {
      lock.unlock();
      fatal("Array index out of range");
    }
    var &value = data[index];
    lock.unlock();
    return value;
  }

  // 访问元素（不带边界检查）
  __wur constexpr T &operator[](usize index) noexcept {
    lock.lock();
    var &value = data[index];
    lock.unlock();
    return value;
  }

  // 获取第一个元素
  __wur constexpr T &front() noexcept {
    lock.lock();
    var &value = data[0];
    lock.unlock();
    return value;
  }

  // 获取最后一个元素
  __wur constexpr T &back() noexcept {
    lock.lock();
    var &value = data[N - 1];
    lock.unlock();
    return value;
  }

  // 获取底层数据指针
  __wur constexpr T *data_ptr() noexcept {
    return data;
  }

  __wur constexpr const T *data_ptr() const noexcept {
    return data;
  }

  // 填充整个数组
  constexpr void fill(const T &value) noexcept {
    lock.lock();
    for (usize i = 0; i < N; i++) {
      data[i] = value;
    }
    lock.unlock();
  }
};

template <typename T>
class Array {
private:
  T    *data;     // 动态分配的数组
  usize capacity; // 当前容量
  usize length;   // 当前元素数量

  // 扩容函数
  void resize(usize new_capacity) {
    T *new_data = new T[new_capacity];
    for (usize i = 0; i < length; i++) {
      new_data[i] = std::move(data[i]);
    }
    delete[] data;
    data     = new_data;
    capacity = new_capacity;
  }

public:
  // 构造函数
  Array() : data(null), capacity(0), length(0) {}

  explicit Array(usize initial_capacity)
      : data(new T[initial_capacity]), capacity(initial_capacity), length(0) {}

  // 析构函数
  ~Array() {
    delete[] data;
  }

  // 获取当前大小
  __wur usize size() const noexcept {
    return length;
  }

  // 获取容量
  __wur usize get_capacity() const noexcept {
    return capacity;
  }

  // 检查是否为空
  __wur bool empty() const noexcept {
    return length == 0;
  }

  // 添加元素到末尾
  void push_back(const T &value) {
    if (length == capacity) { resize(capacity == 0 ? 1 : capacity * 2); }
    data[length++] = value;
  }

  void push_back(T &&value) {
    if (length == capacity) { resize(capacity == 0 ? 1 : capacity * 2); }
    data[length++] = std::move(value);
  }

  // 删除末尾元素
  void pop_back() {
    if (length > 0) { length--; }
  }

  // 访问元素（带边界检查）
  __wur T &at(usize index) {
    if (index >= length) fatal("Array index out of range");
    return data[index];
  }

  __wur const T &at(usize index) const {
    if (index >= length) fatal("Array index out of range");
    return data[index];
  }

  // 访问元素（不带边界检查）
  __wur T &operator[](usize index) noexcept {
    return data[index];
  }

  __wur const T &operator[](usize index) const noexcept {
    return data[index];
  }

  // 清空数组
  void clear() noexcept {
    length = 0;
  }
};

} // namespace cpp
