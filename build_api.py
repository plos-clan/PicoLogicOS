from typing import Callable
from packaging.version import Version

# 项目常量
PROJECT_PATH = ''
BUILD_DIR = ''
GITHUB_ACTIONS = False
BUILD_TYPE = 'release'

CC = ''
CXX = ''
CC_TYPE = 'unknown'
CC_VERSION = Version('0.0.0')
CXX_TYPE = 'unknown'
CXX_VERSION = Version('0.0.0')

AS = ''  # 汇编器
NASM = ''
AR = ''  # 打包器
LINKER = ''  # 链接器

# 编译参数
INCLUDE_FILES: list[str] = []
INCLUDE_FILES_C: list[str] = []
INCLUDE_FILES_CPP: list[str] = []

INCLUDE_DIRS: list[str] = []
INCLUDE_DIRS_C: list[str] = []
INCLUDE_DIRS_CPP: list[str] = []

LIB_DIRS: list[str] = []

COMPILE_FLAGS_POSTFIX = ''
LINK_FLAGS_POSTFIX = ''

COMPILE_FLAGS = ''
COMPILE_FLAGS_C = ''
COMPILE_FLAGS_CPP = ''
COMPILE_FLAGS_ASM = ''
COMPILE_FLAGS_NASM = ''

FLAGS_OVERWRITE_C = False
FLAGS_OVERWRITE_CPP = False
FLAGS_OVERWRITE_ASM = False
FLAGS_OVERWRITE_NASM = True

LINK_FLAGS = ''

# 每个文件不同的常量
DIR = ''
FILE = ''

if True:

  # 日志
  def fatal(message: str, rets=1, e: Exception = None):
    '''
      message: 日志信息
      rets: 返回值
      e: 异常
    '''

  def error(message: str, rets=None, e: Exception = None):
    '''
      message: 日志信息
      rets: 返回值
      e: 异常
    '''

  def warn(message: str, e: Exception = None):
    '''
      message: 日志信息
      e: 异常
    '''

  def info(message: str):
    '''
      message: 日志信息
    '''

  def debug(message: str):
    '''
      message: 日志信息
    '''

  def find_files(dir: str, pattern: str) -> list[str]:
    ...

  def abspath(path: str) -> str:
    ...

  def relpath(path: str, start: str = None) -> str:
    ...

  # 生成一个头文件
  def mkheader(name: str, srcdir: str = None, workdir: str = None, recurse: bool = False, flag: str = 'h') -> int:
    """
      flag:
        h: 生成一个 .h 文件
        hpp: 生成一个 .hpp 文件
        h-only: 生成一个 .h 文件，但不包含 .hpp 文件
        hpp-only: 生成一个 .hpp 文件，但不包含 .h 文件
    """
    return 0

  # 源代码目录
  def src_dir(*dirs: str, hidden_file: bool = False):
    ...

  # 编译一个源代码文件
  def compile(*files: str, exclude: list[str] | str = None, flags_overwrite: str | list[str] = None) -> str:
    '''
      编译源代码并链接
      files: 源代码文件
      flags_overwrite: 覆盖编译参数
        -> 输出文件路径
    '''

  def link(*, flags_overwrite: str | list[str] = None) -> str:
    '''
      链接目标
      flags_overwrite: 覆盖链接参数
        -> 输出文件路径
    '''

  def include(*files: str, lang: str = 'all', abslute: bool = False):
    '''
      files: 头文件
      lang: 语言类型 ['all', 'c', 'cpp', 'asm']
      abslute: 是否使用绝对路径
    '''

  def include_dir(*dir: str, lang: str = 'all'):
    ...

  def depedency(*targets: str):
    ...

  def lib_dir(*dir: str):
    ...

  def clear_compile_flags(lang: str = 'all') -> None:
    ...

  def add_compile_flags(*flags: str, lang: str = 'all') -> None:
    ...

  def remove_compile_flags(*flags: str, lang: str = 'all') -> None:
    ...

  def clear_link_flags() -> None:
    ...

  def add_link_flags(*flags: str) -> None:
    ...

  def remove_link_flags(*flags: str) -> None:
    ...

  def target(name: str, type: str = 'exec', platforms: list[str] | str = None) -> Callable[[Callable], Callable]:
    '''
      name: 目标名称
      type: 目标类型 ['exec', 'static-exec', 'lib', 'static-lib', 'dynamic-lib', 'customize']
    '''

  def platform(name: str) -> Callable[[Callable], Callable]:
    '''
      name: 平台名称
    '''

  # 编译过程
  def before_build(target: str) -> Callable[[Callable], Callable]:
    '''
      在构建目标之前执行
      target: 目标名称
    '''

  def before_compile(target: str) -> Callable[[Callable], Callable]:
    '''
      在每个源文件编译之前执行
      target: 目标名称
    '''

  def after_compile(target: str) -> Callable[[Callable], Callable]:
    '''
      在每个源文件编译之后执行
      target: 目标名称
    '''

  def before_link(target: str) -> Callable[[Callable], Callable]:
    '''
      在链接目标之前执行
      target
    '''

  def after_link(target: str) -> Callable[[Callable], Callable]:
    '''
      在链接目标之后执行
      target
    '''

  def after_build(target: str) -> Callable[[Callable], Callable]:
    '''
      在构建目标之后执行
      target
    '''

  def dump_flags():
    ...

  def system(*cmd: str, cwd: str = None, env: dict[str, str] = None) -> bool:
    ...


class CCommentReader:
  ...


class CFileFlagReader:
  ...


class CFileGenerator:
  ...
