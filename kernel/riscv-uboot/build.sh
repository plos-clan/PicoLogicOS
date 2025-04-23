#!/usr/bin/sh

clang \
  -O2 -Wl,-O2 \
  --target=riscv64-unknown-elf \
  -march=rv64imac \
  -mabi=lp64 \
  -nostdlib \
  -ffreestanding \
  -fuse-ld=lld \
  -I./include \
  -I../../base/include \
  -include define.h \
  -T riscv-uboot.ld \
  -o kernel.elf \
  start.asm main.c

llvm-objcopy -O binary kernel.elf kernel.bin

mkimage -C none -A riscv -T script -d boot.cmd boot.scr

# screen /dev/ttyUSB0 115200,cs8,-cstopb,-parenb
