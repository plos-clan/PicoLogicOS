#!/usr/bin/env bash

if [[ -n "$NM" ]]; then
  exec "$NM" $*
else
  exec llvm-nm $*
fi
