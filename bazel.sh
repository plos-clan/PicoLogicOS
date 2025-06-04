#!/usr/bin/env bash

ACTION_ENVS=()
if [ -f .env ]; then
  while IFS= read -r line || [ -n "$line" ]; do
    [[ -z "$line" || "$line" =~ ^[[:space:]]*# ]] && continue

    key="${line%%=*}"
    value="${line#*=}"

    value="${value%\"}"
    value="${value#\"}"

    ACTION_ENVS+=(--action_env="${key}=${value}")
  done <.env
fi

cmd="$1"
shift
bazel "$cmd" "${ACTION_ENVS[@]}" "$@"
