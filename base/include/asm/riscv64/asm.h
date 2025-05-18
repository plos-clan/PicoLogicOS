#pragma once

#define asm_nop   ({ asm volatile("nop\n\t" ::: "memory"); })
#define asm_pause ({ asm volatile("nop\n\t" ::: "memory"); })
#define asm_yield ({ asm volatile("nop\n\t" ::: "memory"); })

#define asm_wfi ({ asm volatile("wfi\n\t" ::: "memory"); })

#define disable_interrupts ({ asm volatile("csrci mstatus, 0x8" ::: "memory"); })

#define enable_interrupts ({ asm volatile("csrsi mstatus, 0x8" ::: "memory"); })

#define asm_getreg(reg)                                                                            \
  ({                                                                                               \
    size_t _var;                                                                                   \
    asm volatile("mv %0, " #reg "\n\t" : "=r"(_var));                                              \
    _var;                                                                                          \
  })

#define asm_setreg(reg, value) ({ asm volatile("mv " #reg ", %0\n\t" ::"r"((size_t)(value))); })

#define RV_READ_CSR(reg)                                                                           \
  ({                                                                                               \
    unsigned long __tmp;                                                                           \
    asm volatile("csrr %0, " #reg : "=r"(__tmp));                                                  \
    __tmp;                                                                                         \
  })

#define RV_WRITE_CSR(reg, val) ({ asm volatile("csrw " #reg ", %0" ::"rK"(val)); })

#define RV_SWAP_CSR(reg, val)                                                                      \
  ({                                                                                               \
    unsigned long __tmp;                                                                           \
    asm volatile("csrrw %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val));                              \
    __tmp;                                                                                         \
  })

#define RV_SET_CSR(reg, val)                                                                       \
  ({                                                                                               \
    unsigned long __tmp;                                                                           \
    asm volatile("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val));                              \
    __tmp;                                                                                         \
  })

#define RV_CLEAR_CSR(reg, val)                                                                     \
  ({                                                                                               \
    unsigned long __tmp;                                                                           \
    asm volatile("csrrc %0, " #reg ", %1" : "=r"(__tmp) : "rK"(val));                              \
    __tmp;                                                                                         \
  })
