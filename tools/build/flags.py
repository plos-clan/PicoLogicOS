import re
from ..logging import *
from ..env import *
from ..helper import TODO
from .. import logging
from ..target import get_now_target
from .platform import get_now_platform
from . import buildtree

DUMPED_FLAGS = [
    'CC',
    'CXX',
    'COMPILE_FLAGS',
    'LINK_FLAGS',
]


@debug_only
def dump_flags():
  if get_now_target() is not None:
    target = get_now_target()
  elif get_now_platform() is not None:
    platform = get_now_platform()
  else:
    info('Dump flags:')
    logging.LOGGING_DEPTH += 1
    for flag in DUMPED_FLAGS:
      info(f'{flag}: {buildtree.build_scope[flag]}')
    logging.LOGGING_DEPTH -= 1


def clear_compile_flags(lang: str = 'all') -> None:
  if get_now_target() is not None:
    target = get_now_target()
  elif get_now_platform() is not None:
    platform = get_now_platform()
  else:
    flag_name = f'COMPILE_FLAGS_{lang.upper()}' if lang.lower() != 'all' else 'COMPILE_FLAGS'
    buildtree.build_scope[flag_name] = ''


def add_compile_flags(*flags: str, lang: str = 'all') -> None:
  flags = [flag for flag in flags if flag != '']
  if get_now_target() is not None:
    target = get_now_target()
  elif get_now_platform() is not None:
    platform = get_now_platform()
  else:
    flag_name = f'COMPILE_FLAGS_{lang.upper()}' if lang.lower() != 'all' else 'COMPILE_FLAGS'
    compile_flags = buildtree.build_scope[flag_name]
    if len(compile_flags) > 0: compile_flags += ' '
    compile_flags += ' '.join(flags)
    buildtree.build_scope[flag_name] = compile_flags


def remove_compile_flags(*flags: str, lang: str = 'all') -> None:
  if get_now_target() is not None:
    target = get_now_target()
  elif get_now_platform() is not None:
    platform = get_now_platform()
  else:
    flag_name = f'COMPILE_FLAGS_{lang.upper()}' if lang.lower() != 'all' else 'COMPILE_FLAGS'
    compile_flags = buildtree.build_scope[flag_name]
    for flag in flags:
      compile_flags = re.sub(r'(^|\s)' + re.escape(flag) + r'(\s|$)', ' ', compile_flags)
    buildtree.build_scope[flag_name] = compile_flags


def clear_link_flags():
  if get_now_target() is not None:
    pass
  elif get_now_platform() is not None:
    pass
  else:
    buildtree.build_scope['LINK_FLAGS'] = ''


def add_link_flags(*flags: str):
  flags = [flag for flag in flags if flag != '']
  if get_now_target() is not None:
    pass
  elif get_now_platform() is not None:
    pass
  else:
    link_flags = buildtree.build_scope['LINK_FLAGS']
    if len(link_flags) > 0: link_flags += ' '
    link_flags += ' '.join(flags)
    buildtree.build_scope['LINK_FLAGS'] = link_flags


def remove_link_flags(*flags: str):
  if get_now_target() is not None:
    pass
  elif get_now_platform() is not None:
    pass
  else:
    link_flags = buildtree.build_scope['LINK_FLAGS']
    for flag in flags:
      link_flags = re.sub(r'(^|\s)' + re.escape(flag) + r'(\s|$)', ' ', link_flags)
    buildtree.build_scope['LINK_FLAGS'] = link_flags
