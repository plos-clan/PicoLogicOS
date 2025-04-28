#!/bin/bash

clang -c 'ubsan.c' -o 'ubsan.amd64.o' \
  -D_UBSAN_C_=1 \
  -include define.h \
  -I'../../include' \
  -I'../../stdinc' \
  -I'../../stdinc/clang' \
  -O2 \
  -fno-delete-null-pointer-checks \
  -fno-strict-aliasing \
  -finput-charset=UTF-8 \
  -fexec-charset=UTF-8 \
  -fno-stack-protector \
  -fno-asynchronous-unwind-tables \
  -fno-exceptions \
  -Wno-compound-token-split-by-macro \
  -ffunction-sections \
  -fdata-sections \
  -DRING0=1 \
  -fPIE -fPIC \
  -fvisibility=hidden \
  -ffreestanding \
  -std=gnu2x \
  -mno-mmx -mno-sse

ar rcs libubsan.amd64.a ubsan.amd64.o

rm ./ubsan.amd64.o

clang -c ubsan.c -o ubsan.ia32.o \
  -D_UBSAN_C_=1 \
  -include define.h \
  -I'../../include' \
  -I'../../stdinc' \
  -I'../../stdinc/clang' \
  -m32 \
  -O2 \
  -fno-delete-null-pointer-checks \
  -fno-strict-aliasing \
  -finput-charset=UTF-8 \
  -fexec-charset=UTF-8 \
  -fno-stack-protector \
  -fno-asynchronous-unwind-tables \
  -fno-exceptions \
  -Wno-compound-token-split-by-macro \
  -ffunction-sections \
  -fdata-sections \
  -DRING0=1 \
  -fPIE -fPIC \
  -fvisibility=hidden \
  -ffreestanding \
  -std=gnu2x \
  -mno-mmx -mno-sse

ar rcs libubsan.ia32.a ubsan.ia32.o

rm ./ubsan.ia32.o
