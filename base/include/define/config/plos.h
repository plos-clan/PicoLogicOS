

#ifndef DO_NOT_OVERRIDE_COMMON_NAMES
#  define DO_NOT_OVERRIDE_COMMON_NAMES 0
#endif

// 是否使用中断来实现系统调用
// (仅在 x86 平台上使用)
#define SYSCALL_USE_INTERRPUT 0

#define PLOS_LOGGING 2

#define PLOS_LOGGING_PRINTS 0

#define USE_SSE 1 // 是否在代码中使用 SIMD 指令集

#define PLOS_USE_BITINT_FOR_INTN 0

#define PLOS_BITINT  1 // 定义 bitint 类型 (iN uN)
#define PLOS_COMPLEX 1 // 定义复数类型 (ciN cuN cN)

// 各种奇怪的简称（bushi）
#define PLOS_ABBR_FLOATN   1
#define PLOS_ABBR_FN       1
#define PLOS_ABBR_ATOM_XXX 1
#define PLOS_ABBR_AIN      1

// 目前无法修改
#define PLOS_SYSCALL_INTERRPUT_ID  0x36
#define LINUX_SYSCALL_INTERRPUT_ID 0x80

#define PLOS_LIBALGORITHM_SHOW_WARNING     1 // 是否显示在算法库中产生的编译警告
#define PLOS_LIBDATASTRUCTURE_SHOW_WARNING 1 // 是否显示在数据结构库中产生的编译警告

// 快速但丢失精度（真的快吗）
#define PLOS_FAST_MATH 1
