#!/usr/bin/env python3
if 'target' not in globals():
  from tools import main
  main()
  from build_api import *

COMPILE_FLAGS_C = '-std=gnu2x'
COMPILE_FLAGS_CPP = '-std=gnu++2b'

if CC_TYPE == 'clang': add_link_flags('-fuse-ld=lld')

add_compile_flags(
    '-O3' if BUILD_TYPE == 'release' else '-O2',
    '-fno-delete-null-pointer-checks',  # 不删除程序员进行的额外空指针检查 (gcc 默认删除)
    '-fno-strict-aliasing',  # 禁用严格别名规则 (gcc 默认开启)
    '-finput-charset=UTF-8 -fexec-charset=UTF-8',  # 使用 utf-8 (默认)
    '-fno-stack-protector',  # 不使用栈保护 (默认使用)
    '-fno-asynchronous-unwind-tables',  # 禁用异步取消表 (默认启用)
    '-fno-exceptions',  # 禁用异常处理 (默认启用)
)

if CC_TYPE == 'clang': add_compile_flags(
    '-Wno-compound-token-split-by-macro',  #
)

add_compile_flags('-ffunction-sections', '-fdata-sections')
add_link_flags('-Wl,--gc-sections')

add_link_flags(
    '-flto=thin' if CC_TYPE == 'clang' else '-flto=16',
    '-Wl,-O3' if BUILD_TYPE == 'release' else '-Wl,-O2',
)

#$$ a $$#


@platform('ia32-unknown-none')
def _():
  add_compile_flags(
      '-nostdlib',
      '-nostdinc',
      '-ffreestanding',
  )


@platform('amd64-unknown-none')
def _():
  add_compile_flags(
      '-nostdlib',
      '-nostdinc',
      '-ffreestanding',
  )


@platform('arm64-unknown-none')
def _():
  add_compile_flags(
      '--target=aarch64-unknown-elf',
      '-march=armv8-a',
      '-mabi=lp64',
      '-nostdlib',
      '-nostdinc',
      '-ffreestanding',
  )


@platform('riscv64-unknown-none')
def _():
  add_compile_flags(
      '--target=riscv64-unknown-elf',
      '-march=rv64imac',
      '-mabi=lp64',
      '-nostdlib',
      '-nostdinc',
      '-ffreestanding',
  )


@platform('ia32-plos-plibc')
def _():
  add_compile_flags(
      '-nostdlib',
      '-nostdinc',
      '-include libc.h',
  )


@platform('amd64-plos-plibc')
def _():
  add_compile_flags(
      '-nostdlib',
      '-nostdinc',
      '-include libc.h',
  )


@platform('arm64-plos-plibc')
def _():
  add_compile_flags(
      '--target=aarch64-unknown-elf',
      '-march=armv8-a',
      '-mabi=lp64',
      '-nostdlib',
      '-nostdinc',
      '-include libc.h',
  )


@platform('riscv64-plos-plibc')
def _():
  add_compile_flags(
      '--target=riscv64-unknown-elf',
      '-march=rv64imac',
      '-mabi=lp64',
      '-nostdlib',
      '-nostdinc',
      '-include libc.h',
  )
