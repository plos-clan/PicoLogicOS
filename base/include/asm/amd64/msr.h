#pragma once

#define asm_rdmsr(msr, data)                                                                       \
  ({                                                                                               \
    const u64 _data_ = (data);                                                                     \
    const u32 _lo_   = (u32)(_data_);                                                              \
    const u32 _hi_   = (u32)(_data_ >> 32);                                                        \
    asm volatile("rdmsr\n\t" : "=a"(_lo_), "=d"(_hi_) : "c"(msr)::"memory");                       \
  })
#define asm_wrmsr(msr, data)                                                                       \
  ({                                                                                               \
    const u64 _data_ = (data);                                                                     \
    const u32 _lo_   = (u32)(_data_);                                                              \
    const u32 _hi_   = (u32)(_data_ >> 32);                                                        \
    asm volatile("wrmsr\n\t" ::"a"(_lo_), "d"(_hi_), "c"(msr) : "memory");                         \
  })

//+注意 IA32_SYSENTER_CS 的约定：
//   Ring 0 的代码段 CS0
//   Ring 0 的数据段 DS0 = CS0 + 8
//   Ring 3 的代码段 CS3 = CS0 + 16
//   Ring 3 的数据段 DS3 = CS0 + 24
//   如果有 REX.W 前缀则：
//     CS3 = CS0 + 32
//     DS3 = CS0 + 40
#define IA32_SYSENTER_CS  0x174
#define IA32_SYSENTER_ESP 0x175
#define IA32_SYSENTER_EIP 0x176

#define IA32_FS_BASE        0xC0000100
#define IA32_GS_BASE        0xC0000101
#define IA32_KERNEL_GS_BASE 0xC0000102
