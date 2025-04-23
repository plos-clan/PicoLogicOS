import os
import json
import shlex
import shutil
import inspect
from ..logging import *
from ..env import *
from ..helper import md5, file_basename_c_style, flags_join
from .. import logging
from .callbacks import TargetCallbacks


class Target:  # interface
  id: int = 0
  dir: str = ''
  name: str = ''
  type: str = 'exec'
  func: Callable = None
  platform: str = 'none'
  archiver: str = ''
  linker: str = ''
  linker_flags: str = ''
  include_files: list[str]
  include_dirs: list[str]
  depedency: list[str]
  output: str = ''
  version: list[int]
  copy_to: str = ''
  callbacks: TargetCallbacks


hash_cache: dict[int, dict[int, str]] = {}


def load_hash_cache():
  global hash_cache
  if os.path.exists(os.path.join(BUILD_PATH, 'hash_cache.json')):
    with open(os.path.join(BUILD_PATH, 'hash_cache.json'), 'r') as f:
      hash_cache = {int(k): {int(vk): vv for vk, vv in v.items()} for k, v in json.load(f).items()}
  else:
    hash_cache = {}


def save_hash_cache():
  with open(os.path.join(BUILD_PATH, 'hash_cache.json'), 'w') as f:
    json.dump(hash_cache, f, ensure_ascii=False, indent=2)


def clear_hash_cache():
  global hash_cache
  hash_cache = {}
  save_hash_cache()


def save_targets():
  targets_json = {}
  for target in targets.values():
    targets_json[target.id] = target.fullname
  with open(os.path.join(BUILD_PATH, 'targets.json'), 'w') as f:
    json.dump(targets_json, f, ensure_ascii=False, indent=2)


class CompileCommand:
  output_preprocess: str = ''
  output_compile: str = ''
  preprocess: str = ''
  compile: str = ''

  def __init__(self, output_preprocess: str, output_compile: str, preprocess: str, compile: str):
    self.output_preprocess = output_preprocess
    self.output_compile = output_compile
    self.preprocess = preprocess
    self.compile = compile


class CompileObject:
  id: int = 0
  type: str = 'c'
  dir: str = ''
  compiler: str = ''
  files: list[str]
  flags: str = ''

  def __init__(self, id: int, type: str):
    self.id = id
    self.type = type
    self.files = []

  def compile_command(self, target: Target) -> CompileCommand:
    if len(self.compiler) == 0: fatal('Compiler not set')
    if len(self.files) == 0: warn('Files not set')

    compiler = shlex.quote(self.compiler)
    prefix = ''
    files = ' '.join([shlex.quote(f) for f in self.files])
    include_dirs = ' '.join([f'-I{shlex.quote(d)}' for d in target.include_dirs])
    include_files = ' '.join([f'-include {shlex.quote(f)}' for f in target.include_files])
    flags = self.flags
    postfix = ''

    define_filenames = ' '.join([f'-D_{file_basename_c_style(f)}_=1' for f in self.files])

    output_preprocess = os.path.join(BUILD_PATH, 'sources', f'{target.id}-{self.id}.i')
    output_compile = os.path.join(BUILD_PATH, 'objects', f'{target.id}-{self.id}.o')
    if self.type == 'nasm':
      return CompileCommand(
          output_preprocess=output_preprocess,
          output_compile=output_compile,
          preprocess=f'{compiler} {prefix} -E {files} -o {shlex.quote(output_preprocess)} {define_filenames} {flags} {postfix}',
          compile=f'{compiler} {prefix} {files} -o {shlex.quote(output_compile)} {define_filenames} {flags} {postfix}',
      )
    else:
      return CompileCommand(
          output_preprocess=output_preprocess,
          output_compile=output_compile,
          preprocess=f'{compiler} {prefix} -E -P {files} -o {shlex.quote(output_preprocess)} {define_filenames} {include_dirs} {include_files} {flags} {postfix}',
          compile=f'{compiler} {prefix} -c {files} -o {shlex.quote(output_compile)} {define_filenames} {include_dirs} {include_files} {flags} {postfix}',
      )

  def run(self, target: Target) -> tuple[str, bool]:
    if len(self.compiler) == 0: fatal('Compiler not set')
    if len(self.files) == 0: warn('Files not set')

    os.chdir(self.dir)

    command = self.compile_command(target)

    output = command.output_preprocess
    if os.path.exists(output): os.remove(output)
    ret = os.system(command.preprocess)
    if ret != 0: fatal('Failed to preprocess')
    hash = md5(output)

    changed = False
    output = command.output_compile
    if self.id not in hash_cache[target.id] or hash_cache[target.id][self.id] != hash:
      changed = True
      hash_cache[target.id][self.id] = hash
      if os.path.exists(output): os.remove(output)
      ret = os.system(command.compile)
      if ret != 0: fatal('Failed to compile')
    else:
      info('No changes')

    return output, changed


class Target:
  id: int = 0
  dir: str = ''
  name: str = ''
  type: str = 'exec'
  func: Callable = None
  platform: str = 'default'
  archiver: str = ''
  linker: str = ''
  linker_flags: str = ''
  include_files: list[str]
  include_dirs: list[str]
  depedency: list[str]
  output: str = ''
  version: list[int]
  copy_to: str = ''
  callbacks: TargetCallbacks
  compile_objects: list[CompileObject]

  @property
  def fullname(self) -> str:
    return f'{self.name}#{self.platform}'

  @fullname.setter
  def fullname(self, value: str):
    self.name, self.platform = value.split('#')

  def __init__(self, id: int, dir: str, name: str, platform: str = 'default'):
    self.id = id
    self.dir = dir
    self.name = name
    self.platform = platform
    self.include_files = []
    self.include_dirs = []
    self.depedency = []
    self.version = [0, 0, 0, 0]
    self.callbacks = TargetCallbacks()
    self.compile_objects = []

  def flush(self):
    if not self.linker: globals()['linker']()

  def add_compile_object(self, type: str, compiler: str, files: list[str], flags: str):
    obj = CompileObject(len(self.compile_objects), type)
    obj.dir = self.dir
    obj.compiler = compiler
    obj.files = files
    obj.flags = flags
    self.compile_objects.append(obj)

  def compile_commands(self):
    commands = []
    for obj in self.compile_objects:
      command = obj.compile_command(self)
      commands += [{'directory': obj.dir, 'command': command.compile, 'file': file} for file in obj.files]
    return commands

  def setcompile(self, *files: str, build_scope, flags_overwrite: str | list[str] = None) -> str:
    if isinstance(flags_overwrite, list): flags_overwrite = flags_join(flags_overwrite)

    BS = build_scope
    CC = BS['CC']
    CPP = BS['CXX']
    AS = BS['AS']
    NASM = BS['NASM']
    FLAGS_C = flags_join(BS['COMPILE_FLAGS'] if not BS['FLAGS_OVERWRITE_C'] else '', BS['COMPILE_FLAGS_C'])
    FLAGS_CPP = flags_join(BS['COMPILE_FLAGS'] if not BS['FLAGS_OVERWRITE_CPP'] else '', BS['COMPILE_FLAGS_CPP'])
    FLAGS_ASM = flags_join(BS['COMPILE_FLAGS'] if not BS['FLAGS_OVERWRITE_ASM'] else '', BS['COMPILE_FLAGS_ASM'])
    FLAGS_NASM = flags_join(BS['COMPILE_FLAGS'] if not BS['FLAGS_OVERWRITE_NASM'] else '', BS['COMPILE_FLAGS_NASM'])
    FLAGS_C = flags_overwrite if flags_overwrite is not None else FLAGS_C
    FLAGS_CPP = flags_overwrite if flags_overwrite is not None else FLAGS_CPP
    FLAGS_ASM = flags_overwrite if flags_overwrite is not None else FLAGS_ASM
    FLAGS_NASM = flags_overwrite if flags_overwrite is not None else FLAGS_NASM

    INCLUDE_FILES = flags_join([f'-include {shlex.quote(file)}' for file in BS['INCLUDE_FILES']])
    INCLUDE_FILES_C = flags_join([f'-include {shlex.quote(file)}' for file in BS['INCLUDE_FILES_C']])
    INCLUDE_FILES_CPP = flags_join([f'-include {shlex.quote(file)}' for file in BS['INCLUDE_FILES_CPP']])

    INCLUDE_DIRS = flags_join([f'-I{shlex.quote(dir)}' for dir in BS['INCLUDE_DIRS']])
    INCLUDE_DIRS_C = flags_join([f'-I{shlex.quote(dir)}' for dir in BS['INCLUDE_DIRS_C']])
    INCLUDE_DIRS_CPP = flags_join([f'-I{shlex.quote(dir)}' for dir in BS['INCLUDE_DIRS_CPP']])

    FLAGS_C = flags_join(INCLUDE_DIRS, INCLUDE_DIRS_C, INCLUDE_FILES, INCLUDE_FILES_C, FLAGS_C)
    FLAGS_CPP = flags_join(INCLUDE_DIRS, INCLUDE_DIRS_CPP, INCLUDE_FILES, INCLUDE_FILES_CPP, FLAGS_CPP)

    for file in files:
      if file.lower().endswith('.c'):
        self.add_compile_object('c', CC, [file], FLAGS_C)
      elif file.lower().endswith('.cpp'):
        self.add_compile_object('cpp', CPP, [file], FLAGS_CPP)
      elif file.lower().endswith('.s'):
        self.add_compile_object('asm', AS, [file], FLAGS_ASM)
      elif file.lower().endswith('.asm'):
        self.add_compile_object('nasm', NASM, [file], FLAGS_NASM)
      else:
        fatal(f'Unsupported file type: {file}')

  def setlink(self, build_scope, flags_overwrite: str | list[str] = None):
    if isinstance(flags_overwrite, list): flags_overwrite = ' '.join(flags_overwrite)

    cpp_file_count = sum(1 for obj in self.compile_objects if obj.type == 'cpp')

    BS = build_scope

    FLAGS_C = BS['COMPILE_FLAGS'] + ' ' + BS['COMPILE_FLAGS_C']
    FLAGS_CPP = BS['COMPILE_FLAGS'] + ' ' + BS['COMPILE_FLAGS_CPP']

    LINKER = BS['LINKER']
    LINKER = LINKER if LINKER else CXX if cpp_file_count > 0 else CC
    LINKER_FLAGS = (FLAGS_C if cpp_file_count > 0 else FLAGS_CPP) + ' ' + BS['LINK_FLAGS']
    LINKER_FLAGS = flags_overwrite if flags_overwrite is not None else LINKER_FLAGS

    LINKER_FLAGS = ' '.join([f'-L{shlex.quote(dir)}' for dir in BS['LIB_DIRS']]) + ' ' + LINKER_FLAGS

    self.linker = LINKER
    self.linker_flags = LINKER_FLAGS

    self.archiver = BS['AR']

  def fix(self, build_scope):
    if not self.linker: self.setlink(build_scope=build_scope)
    if not self.archiver: self.setlink(build_scope=build_scope)

  def _get_depedency_args(self) -> tuple[list[str], list[Target]]:
    depedency: list[str] = []
    depedency_targets: list[Target] = []
    for name in self.depedency:
      if '#' in name:
        if name not in targets:
          error(f'Target {name} not found')
          continue
        target = targets[name]
        depedency_targets.append(target)
        if target.type == 'static-lib':
          depedency.append(shlex.quote(target.output))
        else:
          depedency.append(f'-l{shlex.quote(target.name)}')
      if f'{name}#{self.platform}' in targets:
        target = targets[f'{name}#{self.platform}']
        depedency_targets.append(target)
        if target.type == 'static-lib':
          depedency.append(shlex.quote(target.output))
        else:
          depedency.append(f'-l{shlex.quote(target.name)}')
      elif name in targets:
        target = targets[name]
        depedency_targets.append(target)
        if target.type == 'static-lib':
          depedency.append(shlex.quote(target.output))
        else:
          depedency.append(f'-l{shlex.quote(target.name)}')
      else:
        depedency.append(f'-l{shlex.quote(name)}')
    if any([dep.fullname == self.fullname for dep in depedency_targets]):
      fatal(f'Target {self.fullname} depends on itself')
    return depedency, depedency_targets

  def _run_link(self, outputs: list[str], need_link: bool):
    if need_link or ALWAYS_RELINK:
      archiver = shlex.quote(self.archiver)
      linker = shlex.quote(self.linker)
      prefix = ''
      files = ' '.join([shlex.quote(f) for f in outputs])
      dependencies = ' '.join(self._get_depedency_args()[0])
      output = self.output
      flags = self.linker_flags
      postfix = ''
      if os.path.exists(output): os.remove(output)
      if not os.path.exists(os.path.dirname(output)): os.makedirs(os.path.dirname(output), exist_ok=True)
      if self.type == 'static-lib':
        ret = os.system(f'{archiver} rcs {shlex.quote(output)} {files}')
      elif self.type == 'static-exec':
        ret = os.system(f'{linker} {prefix} -static {files} {dependencies} -o {shlex.quote(output)} {flags} {postfix}')
      elif self.type == 'lib':
        ret = os.system(f'{linker} {prefix} -shared {files} {dependencies} -o {shlex.quote(output)} {flags} {postfix}')
      elif self.type == 'exec':
        ret = os.system(f'{linker} {prefix} {files} {dependencies} -o {shlex.quote(output)} {flags} {postfix}')
      else:
        fatal('Unknown target type')
      if ret != 0: fatal('Failed to link')
    else:
      info('No changes')

  def run(self, args: list[str] = None):
    if args is None: args = []
    if self.type == 'customize':
      func_signature = inspect.signature(self.func)
      if len(func_signature.parameters) > 1:
        error('Customize function should have no more than one parameter')
      elif len(func_signature.parameters) == 0:
        if len(args) > 0: warn('Customize function does not accept arguments, ignored')
        self.func()
      elif func_signature.parameters.values()[0].kind == inspect.Parameter.VAR_POSITIONAL:
        self.func(*args)
      else:
        error('Keyword argument not supported')
      return

    if len(args) > 0: warn('Target is not a customize target, arguments ignored')

    if len(self.output) == 0: fatal('Output not set')
    if len(self.compile_objects) == 0: warn('No compile objects')

    dependent_targets = self._get_depedency_args()[1]
    for target in dependent_targets:
      target.run()

    if self.id not in hash_cache:
      hash_cache[self.id] = {}

    info(f'Start building {self.name} ({self.platform})')

    os.chdir(self.dir)
    self.callbacks.before_build()

    outputs = []
    need_link = False
    for obj in self.compile_objects:
      info(f'Compiling {" ".join([os.path.relpath(file, PROJECT_PATH) for file in obj.files])}')
      logging.LOGGING_DEPTH += 1
      self.callbacks.before_compile()
      output, changed = obj.run(self)
      outputs.append(output)
      if changed: need_link = True
      self.callbacks.after_compile()
      logging.LOGGING_DEPTH -= 1

    info(f'Linking {os.path.relpath(self.output, PROJECT_PATH)}')
    logging.LOGGING_DEPTH += 1
    self.callbacks.before_link()
    self._run_link(outputs, need_link)
    self.callbacks.after_link()
    logging.LOGGING_DEPTH -= 1

    if self.copy_to:
      os.makedirs(os.path.dirname(self.copy_to), exist_ok=True)
      shutil.copy(self.output, self.copy_to)

    self.callbacks.after_build()
    os.chdir(PROJECT_PATH)

    save_hash_cache()


targets: dict[str, Target] = {}
now_target: Target = None


def open_target(dir: str, name: str, platform: str = 'default') -> Target:
  fullname = f'{name}#{platform}'
  global now_target
  now_target = targets[fullname] if fullname in targets else Target(len(targets), dir, name, platform)
  targets[fullname] = now_target
  return now_target


def close_target():
  global now_target
  now_target = None


def has_target(name: str) -> bool:
  return name in targets


def get_target(name: str) -> Target:
  if name not in targets:
    raise ValueError(f"Target {name} not found.")
  return targets[name]


def get_now_target() -> Target:
  return now_target


def run(target: str, args: list[str] = None):
  if target not in targets:
    fatal(f'Target {target} not found')
  if args is None: args = []
  targets[target].run(args)


def run_all():
  for target in targets:
    run(target)


def print_targets():
  info('Targets:')
  for name, target in targets.items():
    if target.type == 'customize':
      info(f'  {name}: {target.type}')
    else:
      info(f'  {name}: {target.type} -> {os.path.relpath(target.copy_to if target.copy_to else target.output, PROJECT_PATH)}')


def export_compile_commands(path: str = None):
  if path is None: path = os.path.join(BUILD_PATH, 'compile_commands.json')
  compile_commands = []
  for target in targets:
    compile_commands += targets[target].compile_commands()
  with open(path, 'w') as f:
    json.dump(compile_commands, f, ensure_ascii=False, indent=2)
  debug('Exported compile_commands.json')
