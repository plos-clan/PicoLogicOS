#pragma once

#define asm_nop   ({ asm volatile("nop\n\t" ::: "memory"); })
#define asm_pause ({ asm volatile("yield\n\t" ::: "memory"); })
#define asm_yield ({ asm volatile("yield\n\t" ::: "memory"); })
