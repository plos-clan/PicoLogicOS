import re
import os
import fnmatch


def TODO(*args) -> None:
  raise NotImplementedError(f' '.join([str(arg) for arg in args]))


def flatten(lst: list[list]) -> list:
  return [item for sublist in lst for item in sublist]


def flatten_reserve(lst: list) -> list:
  ret = []
  for item in lst:
    if isinstance(item, list):
      ret.extend(flatten_reserve(item))
    else:
      ret.append(item)
  return ret


def parse_target(target: str) -> list[str] | None:
  if re.match(r'^[a-zA-Z0-9_\-]+$', target) is None: return None
  target = target.split('-')
  return None if len(target) != 3 else target


def scan_files(dirname: str) -> str:
  ret = []
  for root, dirs, files in os.walk(dirname):
    for file in files:
      ret.append(f'{root}/{file}')
  return ret


def match_files(pattern: str, base: str) -> str:
  matches = []
  for root, dirs, files in os.walk(base):
    for filename in fnmatch.filter(files, pattern):
      matches.append(os.path.join(root, filename))
  return matches


def flags_join(*flags: str) -> str:
  return ' '.join([flag.strip() for flag in flatten_reserve(flags) if flag])
