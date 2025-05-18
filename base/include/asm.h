#pragma once

#include <asm/general.h>

#if __i386__
#  include <asm/amd64.h>
#elif __x86_64__
#  include <asm/amd64.h>
#elif __arm__
#  include <asm/arm64.h>
#elif __aarch64__
#  include <asm/arm64.h>
#elif __riscv__
#  include <asm/riscv64.h>
#endif
