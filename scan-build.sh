#!/usr/bin/sh

# scan-build --use-cc=clang --use-c++=clang++ -analyze-headers ./build.py

export CC=/usr/lib/llvm-19/bin/clang
export CXX=/usr/lib/llvm-19/bin/clang++

scan-build \
  --use-cc="$CC" \
  --use-c++="$CXX" \
  -analyze-headers \
  bazel build \
  --crosstool_top=@bazel_tools//tools/cpp:clang_x86_64 \
  --spawn_strategy=standalone \
  --strategy=CppCompile=standalone \
  --action_env=CC \
  --action_env=CXX \
  $*
