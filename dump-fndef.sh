#!/usr/bin/env bash

clang -E -dM "$1"

echo

clang -Xclang -ast-dump=json -fsyntax-only "$1" |
  jq -r --arg file "$1" '
    .. | objects
    | select(
        .kind=="FunctionDecl"
        and has("inner")
        and (.inner | any(.kind=="CompoundStmt"))
      )
    | "\(.loc.file // $file):\(.loc.line):\(.loc.col)\t\(.name)\t\(.type.qualType)\n\tfrom \(.range.begin.file // $file):\(.loc.line):\(.range.begin.col)\tto \(.range.end.file // $file):\(.range.end.line):\(.range.end.col)"
  '
