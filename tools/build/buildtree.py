import os
from typing import Callable
from types import ModuleType
from copy import deepcopy
from ..logging import *
from ..env import *
from .. import logging

BUILD_GLOBALS = {}
BUILTIN_GLOBALS = {}

# 加载 api 表
with open(os.path.join(PROJECT_PATH, 'build_api.py'), 'r') as f:
  exec(f.read(), BUILD_GLOBALS)
  exec('', BUILTIN_GLOBALS)
  BUILD_GLOBALS = {k: v for k, v in BUILD_GLOBALS.items() if k not in BUILTIN_GLOBALS and k != '__annotations__'}

build_scope = {}

# def readonly_property(name: str, value) -> property:
#   return property(
#       lambda self: value,
#       lambda self, value: fatal(f'{name} is read-only'),
#       lambda self: fatal(f'{name} is read-only'),
#   )


class BuildTree:

  def __init__(self, path: str):
    self.path: str = path
    self.file: str = os.path.join(path, 'build.py')
    self.sub: list[BuildTree] = []
    if not os.path.isdir(self.path): fatal(f'Internal error: path is not a directory. path: {self.path}')
    if not os.path.exists(self.file): fatal(f'Internal error: build.py not found. file: {self.file}')
    for entry in os.listdir(path):
      entry = os.path.join(path, entry)
      if os.path.isdir(entry) and not os.path.islink(entry):
        self.scan(entry)

  def scan(self, path: str):
    if not os.path.isdir(path): fatal(f'Internal error: path is not a directory. path: {path}')
    build_file = os.path.join(path, 'build.py')
    if os.path.exists(build_file) and os.path.isfile(build_file):
      self.sub.append(BuildTree(path))
      return
    for entry in os.listdir(path):
      entry = os.path.join(path, entry)
      if os.path.isdir(entry) and not os.path.islink(entry):
        self.scan(entry)

  def copy_scope_dict(scope: dict) -> dict:
    new_scope = {}
    for k, v in scope.items():
      if isinstance(v, dict):
        new_scope[k] = BuildTree.copy_scope_dict(v)
      elif isinstance(v, list):
        new_scope[k] = BuildTree.copy_scope_list(v)
      elif isinstance(v, tuple):
        new_scope[k] = BuildTree.copy_scope_tuple(v)
      elif isinstance(v, set):
        new_scope[k] = BuildTree.copy_scope_set(v)
      elif isinstance(v, type):
        new_scope[k] = v
      elif isinstance(v, Callable):
        new_scope[k] = v
      elif not isinstance(v, ModuleType):
        new_scope[k] = deepcopy(v)
    return new_scope

  def copy_scope_list(scope: list) -> list:
    new_scope = []
    for e in scope:
      if isinstance(e, dict):
        new_scope.append(BuildTree.copy_scope_dict(e))
      elif isinstance(e, list):
        new_scope.append(BuildTree.copy_scope_list(e))
      elif isinstance(e, tuple):
        new_scope.append(BuildTree.copy_scope_tuple(e))
      elif isinstance(e, set):
        new_scope.append(BuildTree.copy_scope_set(e))
      elif isinstance(e, type):
        new_scope.append(e)
      elif isinstance(e, Callable):
        new_scope.append(e)
      elif not isinstance(e, ModuleType):
        new_scope.append(deepcopy(e))
    return scope

  def copy_scope_tuple(scope: tuple) -> tuple:
    new_scope = []
    for e in scope:
      if isinstance(e, dict):
        new_scope.append(BuildTree.copy_scope_dict(e))
      elif isinstance(e, list):
        new_scope.append(BuildTree.copy_scope_list(e))
      elif isinstance(e, tuple):
        new_scope.append(BuildTree.copy_scope_tuple(e))
      elif isinstance(e, set):
        new_scope.append(BuildTree.copy_scope_set(e))
      elif isinstance(e, type):
        new_scope.append(e)
      elif isinstance(e, Callable):
        new_scope.append(e)
      elif not isinstance(e, ModuleType):
        new_scope.append(deepcopy(e))
    return tuple(new_scope)

  def copy_scope_set(scope: set) -> set:
    new_scope = set()
    for e in scope:
      if isinstance(e, dict):
        new_scope.add(BuildTree.copy_scope_dict(e))
      elif isinstance(e, list):
        new_scope.add(BuildTree.copy_scope_list(e))
      elif isinstance(e, tuple):
        new_scope.add(BuildTree.copy_scope_tuple(e))
      elif isinstance(e, set):
        new_scope.add(BuildTree.copy_scope_set(e))
      elif isinstance(e, type):
        new_scope.add(e)
      elif isinstance(e, Callable):
        new_scope.add(e)
      elif not isinstance(e, ModuleType):
        new_scope.add(deepcopy(e))
    return new_scope

  def copy_scope(scope: dict[str]) -> dict[str]:
    new_scope = {}
    for k, v in {k: v for k, v in scope.items() if k not in BUILTIN_GLOBALS}.items():
      if isinstance(v, dict):
        new_scope[k] = BuildTree.copy_scope_dict(v)
      elif isinstance(v, list):
        new_scope[k] = BuildTree.copy_scope_list(v)
      elif isinstance(v, tuple):
        new_scope[k] = BuildTree.copy_scope_tuple(v)
      elif isinstance(v, set):
        new_scope[k] = BuildTree.copy_scope_set(v)
      elif isinstance(v, type):
        new_scope[k] = v
      elif isinstance(v, Callable):
        new_scope[k] = v
      elif not isinstance(v, ModuleType):
        new_scope[k] = deepcopy(v)
    return scope

  def run(self, scope: dict[str] = None):
    if scope is None: scope = BuildTree.copy_scope(BUILD_GLOBALS)
    global build_scope
    build_scope = scope

    scope.update({
        'PROJECT_PATH': PROJECT_PATH,
        'ENV_PATH': ENV_PATH,
        'BUILD_DIR': BUILD_DIR,
        'BUILD_PATH': BUILD_PATH,
        'GITHUB_ACTIONS': GITHUB_ACTIONS,
        'BUILD_TYPE': BUILD_TYPE,
        'DIR': self.path,
        'FILE': self.file,
    })

    info(f'Running build.py in {os.path.relpath(self.path, PROJECT_PATH)}')

    os.chdir(self.path)
    logging.LOGGING_DEPTH += 1

    with open(self.file, 'r') as f:
      exec(f.read(), scope)

    for sub in self.sub:
      sub.run(BuildTree.copy_scope(scope))

    logging.LOGGING_DEPTH -= 1
    os.chdir(self.path)
