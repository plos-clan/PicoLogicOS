#!/usr/bin/env bash

ARGS=()
for arg in "$@"; do
  if [[ $arg == -fuse-ld=* ]]; then
    ARGS+=("-fuse-ld=lld")
  else
    ARGS+=("$arg")
  fi
done

if [[ -n "$CC" ]]; then
  exec "$CC" "${ARGS[@]}"
else
  exec clang "${ARGS[@]}"
fi
