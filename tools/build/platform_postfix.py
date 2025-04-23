import os
from itertools import combinations
from ..helper import flatten


# 列表中内容的组合
def combinations_of(input_list: list):
  result = list(input_list)
  for r in range(2, len(input_list) + 1):
    result.extend(['-'.join(comb) for comb in combinations(input_list, r)])
  return result


def splitext(path: str) -> tuple[str, str]:
  base, ext = os.path.splitext(path)
  return base, ext[1:].lower() if ext else ''


def filter_file_by_postfix(
    files: str | list[str],
    postfix: str | list[str] = None,
    extname: str | list[str] = None,
    include_no_postfix: bool = False,
) -> list[str]:
  if isinstance(files, str): files = [files]
  if isinstance(postfix, str): postfix = [postfix]
  if isinstance(extname, str): extname = [extname]
  if include_no_postfix: postfix.append('')

  if extname:
    extname = set(extname)
    files = [file for file in files if splitext(file)[1] in extname]
  if postfix:
    postfix = set(postfix)
    files = [file for file in files if splitext(splitext(file)[0])[1] in postfix]

  return files


def filter_file_by_platform(
    files: str | list[str],
    *,
    platform: str | list[str],
    postfix: str | list[str] = None,
    extname: str | list[str] = None,
    include_no_postfix: bool = False,
) -> list[str]:
  if isinstance(files, str): files = [files]
  if isinstance(platform, str): platform = [platform]
  if isinstance(postfix, str): postfix = [postfix]
  if isinstance(extname, str): extname = [extname]
  postfix += flatten([combinations_of(p.split('-')) if p else [] for p in platform])
  return filter_file_by_postfix(files, postfix=postfix, extname=extname, include_no_postfix=include_no_postfix)
