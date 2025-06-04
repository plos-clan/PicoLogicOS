#!/usr/bin/env bash

if [[ -n "$STRIP" ]]; then
  exec "$STRIP" $*
else
  exec llvm-strip $*
fi
