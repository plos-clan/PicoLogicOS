#pragma once

#define used_val1(value)      ({ asm volatile("" ::"r,m"(value)); })
#define used_val2(value, ...) ({ used_val1(value), used_val1(__VA_ARGS__); })
#define used_val3(value, ...) ({ used_val1(value), used_val2(__VA_ARGS__); })
#define used_val4(value, ...) ({ used_val1(value), used_val3(__VA_ARGS__); })
#define used_val5(value, ...) ({ used_val1(value), used_val4(__VA_ARGS__); })
#define used_val6(value, ...) ({ used_val1(value), used_val5(__VA_ARGS__); })
#define used_val7(value, ...) ({ used_val1(value), used_val6(__VA_ARGS__); })
#define used_val8(value, ...) ({ used_val1(value), used_val7(__VA_ARGS__); })
#define used_val9(value, ...) ({ used_val1(value), used_val8(__VA_ARGS__); })
#define used_val(...)         CONCAT(used_val, COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)
