#!/usr/bin/env bash

if [[ -n "$AR" ]]; then
  exec "$AR" $*
else
  exec llvm-ar $*
fi
