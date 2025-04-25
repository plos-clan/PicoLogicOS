import os
from ..logging import *
from ..env import *
from ..codegen import *
from ..helper import flatten, find_files, check_and_mkdirs
from ..target import export_compile_commands, targets, load_hash_cache, save_targets
from .build_globals import init_build_globals
from . import buildtree
from .. import logging

build_tree: buildtree.BuildTree = None


def init_build_tree():
  global build_tree
  build_tree = buildtree.BuildTree(PROJECT_PATH)
  build_tree.run()


def print_build_tree():
  debug('Build tree:')
  logging.LOGGING_DEPTH += 1
  for name, target in targets.items():
    if target.type == 'customize':
      debug(f'Customize target: {name}')
      continue
    debug(f'Target: {name} with {len(target.compile_objects)} compile objects')
    logging.LOGGING_DEPTH += 1
    for obj in target.compile_objects:
      debug(' '.join([os.path.relpath(file, PROJECT_PATH) for file in obj.files]))
    logging.LOGGING_DEPTH -= 1
  logging.LOGGING_DEPTH -= 1


def init():
  debug(f'Project path: {PROJECT_PATH}')
  debug(f'Build path: {BUILD_PATH}')
  check_and_mkdirs('sources', 'objects', 'binaries', 'libraries', base=BUILD_PATH)

  load_hash_cache()

  if not os.path.exists(os.path.join(PROJECT_PATH, 'build.py')):
    fatal('There should be a build.py in the project root directory')

  init_build_globals()
  init_build_tree()
  save_targets()
  export_compile_commands()
  print_build_tree()
