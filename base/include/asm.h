#pragma once

#include "asm/general.h"

#if __i386__ || __x86_64__
#  include "asm/amd64.h"
#elif __arm__ || __aarch64__
#  include "asm/arm64.h"
#elif __riscv
#  include "asm/riscv64.h"
#endif
