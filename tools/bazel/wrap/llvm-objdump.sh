#!/usr/bin/env bash

if [[ -n "$OBJDUMP" ]]; then
  exec "$OBJDUMP" $*
else
  exec llvm-objdump $*
fi
