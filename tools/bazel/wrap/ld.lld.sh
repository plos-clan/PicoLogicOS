#!/usr/bin/env bash

ARGS=()
for arg in "$@"; do
  if [[ $arg == -fuse-ld=* ]]; then
    ARGS+=("-fuse-ld=lld")
  else
    ARGS+=("$arg")
  fi
done

if [[ -n "$LD" ]]; then
  exec "$LD" "${ARGS[@]}"
else
  exec ld.lld "${ARGS[@]}"
fi
