#!/bin/bash

clang 'boxxy.c' -o 'boxxy' \
  -include define.h \
  -I'../../include' \
  -I'../../stdinc' \
  -I'../../stdinc/clang' \
  -O2 \
  -std=gnu2x

./boxxy
