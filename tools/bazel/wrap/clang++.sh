#!/usr/bin/env bash

ARGS=()
for arg in "$@"; do
  if [[ $arg == -fuse-ld=* ]]; then
    ARGS+=("-fuse-ld=lld")
  else
    ARGS+=("$arg")
  fi
done

if [[ -n "$CXX" ]]; then
  exec "$CXX" "${ARGS[@]}"
else
  exec clang++ "${ARGS[@]}"
fi
