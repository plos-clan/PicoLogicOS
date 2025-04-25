import os
from ..logging import *
from ..env import *
from ..codegen import *
from ..helper import flatten, find_files, filter_file_by_postfix, filter_file_by_platform
from ..target import get_now_target
from ..platform import get_now_platform
from .constants import *
from . import buildtree
from .. import logging


def src_dir(*dirs: str, hidden_file: bool = False, flags_overwrite: str | list[str] = None):
  if isinstance(dirs, str): dirs = [dirs]

  target = get_now_target()
  if target is None: fatal('No target specified')

  files = flatten([filter_file_by_platform(
      find_files(dir, hidden_file=hidden_file),
      platform=target.platform,
      postfix=[CC_TYPE, CXX_TYPE],
      extname=['c', 'cpp', 'a', 's', 'asm'],
      include_no_postfix=True,
  ) for dir in dirs])

  files = [os.path.abspath(os.path.join(buildtree.build_scope['DIR'], file)) for file in files]

  target.setcompile(*files, build_scope=buildtree.build_scope, flags_overwrite=flags_overwrite)


def compile(
    *files: str,
    exclude: list[str] | str = None,
    flags_overwrite: str | list[str] = None,
    files_pattern: bool = True,
    hidden_file: bool = False,
    exclude_pattern: bool = True,
) -> str:
  if isinstance(flags_overwrite, list): flags_overwrite = ' '.join(flags_overwrite)
  if isinstance(exclude, str): exclude = [exclude]
  files = [file for file in files if file]
  exclude = [file for file in exclude if file] if exclude else None

  target = get_now_target()
  if target is None: fatal('No target specified')

  DIR = buildtree.build_scope['DIR']

  if files_pattern:
    files = flatten([find_files(DIR, pattern=pattern, hidden_file=hidden_file) for pattern in files])
  if exclude:
    if exclude_pattern:
      exclude = flatten([find_files(DIR, pattern=pattern) for pattern in exclude])
    files = [file for file in files if file not in exclude]

  target.setcompile(*files, build_scope=buildtree.build_scope, flags_overwrite=flags_overwrite)

  return target.output


def link(*, flags_overwrite: str | list[str] = None) -> str:
  target = get_now_target()
  if target is None: fatal('No target specified')

  target.setlink(build_scope=buildtree.build_scope, flags_overwrite=flags_overwrite)

  return target.output


def include(*files: str, lang: str = 'all', abslute: bool = False):
  if abslute:
    DIR = buildtree.build_scope['DIR']
    files = [os.path.abspath(os.path.join(DIR, file)) for file in files]
  target = get_now_target()
  platform = get_now_platform()
  if target:
    target.include_files += files
  elif platform:
    platform.include_files += files
  else:
    buildtree.build_scope['INCLUDE_FILES'] += files


def depedency(*targets: str):
  target = get_now_target()
  if target is None: fatal('No target specified')
  target.depedency += targets


def include_dir(*dirs: str, lang: str = 'all'):
  dirs = [os.path.abspath(os.path.join(buildtree.build_scope['DIR'], dir)) for dir in dirs]
  target = get_now_target()
  if target is None:
    buildtree.build_scope['INCLUDE_DIRS'] += dirs
  else:
    target.include_dirs += dirs


def lib_dir(*dirs: str):
  dirs = [os.path.abspath(os.path.join(buildtree.build_scope['DIR'], dir)) for dir in dirs]
  target = get_now_target()
  if target is None:
    buildtree.build_scope['LIB_DIRS'] += dirs
  else:
    target.lib_dirs += dirs
