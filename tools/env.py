import shutil
import os
import sys
from packaging.version import Version
from .logging import *
from .helper import readlink
from dotenv import load_dotenv

PROJECT_PATH = os.path.dirname(os.path.abspath(sys.argv[0]))
os.chdir(PROJECT_PATH)

ENV_PATH = os.path.join(PROJECT_PATH, '.env')
if os.path.exists(ENV_PATH):
  debug('Loading .env file')
  load_dotenv(ENV_PATH)

BUILD_DIR = os.environ.get('BUILD_DIR', 'build')
BUILD_PATH = os.path.join(PROJECT_PATH, BUILD_DIR)
GITHUB_ACTIONS = os.environ.get('GITHUB_ACTIONS', False) == 'true'
BUILD_TYPE = os.environ.get('BUILD_TYPE', 'release')

if os.path.relpath(BUILD_PATH, PROJECT_PATH).startswith('.'):
  fatal('BUILD_PATH should be in the project directory')

if GITHUB_ACTIONS:
  info('Running on GitHub Actions')

if BUILD_TYPE not in ['release', 'debug']:
  fatal('BUILD_TYPE must be release or debug')


def _helper():
  # 设置默认编译器
  if 'CC' not in os.environ:
    warn('CC is not set, try using cc as default')
    cc_path = shutil.which('cc')
    if cc_path is None:
      warn('cc is not found, try using clang or gcc as default')
      cc_path = shutil.which('clang')
      if cc_path is None:
        cc_path = shutil.which('gcc')
        if cc_path is None:
          fatal('cc is not found')
    os.environ['CC'] = cc_path
  if 'CXX' not in os.environ:
    warn('CXX is not set, try using c++ as default')
    cxx_path = shutil.which('c++')
    if cxx_path is None:
      warn('c++ is not found, try using clang++ or g++ as default')
      cxx_path = shutil.which('clang++')
      if cxx_path is None:
        cxx_path = shutil.which('g++')
        if cxx_path is None:
          fatal('c++ is not found')
    os.environ['CXX'] = cxx_path

  global CC, CXX
  CC = os.environ['CC']
  CXX = os.environ['CXX']

  if os.path.islink(CC):
    info(f'Using CC: {CC} -> {readlink(CC)}')
  else:
    info(f'Using CC: {CC}')
  if os.path.islink(CXX):
    info(f'Using CXX: {CXX} -> {readlink(CXX)}')
  else:
    info(f'Using CXX: {CXX}')

  # 设置默认汇编器
  if 'AS' not in os.environ:
    warn('AS is not set, try using as as default')
    as_path = shutil.which('as')
    if as_path is None:
      fatal('as is not found')
    os.environ['AS'] = as_path

  global AS
  AS = os.environ['AS']

  if os.path.islink(AS):
    info(f'Using AS: {AS} -> {readlink(AS)}')
  else:
    info(f'Using AS: {AS}')

  # 设置默认打包工具
  if 'AR' not in os.environ:
    warn('AR is not set, try using ar as default')
    ar_path = shutil.which('ar')
    if ar_path is None:
      fatal('ar is not found')
    os.environ['AR'] = ar_path

  global AR, LINKER
  AR = os.environ['AR']
  LINKER = ''

  if os.path.islink(AR):
    info(f'Using AR: {AR} -> {readlink(AR)}')
  else:
    info(f'Using AR: {AR}')

  # 设置默认NASM
  if 'NASM' not in os.environ:
    warn('NASM is not set, try using nasm as default')
    nasm_path = shutil.which('nasm')
    if nasm_path is None:
      fatal('nasm is not found')
    os.environ['NASM'] = nasm_path

  global NASM
  NASM = os.environ['NASM']

  if os.path.islink(NASM):
    info(f'Using NASM: {NASM} -> {readlink(NASM)}')
  else:
    info(f'Using NASM: {NASM}')

  # 检查编译器版本
  cc_version = os.popen(f'{CC} --version').read().strip()
  global CC_TYPE, CC_VERSION
  if 'Free Software Foundation' in cc_version:
    CC_TYPE = 'gcc'
    CC_VERSION = Version(cc_version.split('\n')[0].split(' ')[-1])
  elif 'clang' in cc_version:
    CC_TYPE = 'clang'
    CC_VERSION = Version(cc_version.split('\n')[0].split(' ')[-2])
  else:
    CC_TYPE = 'unknown'
    CC_VERSION = Version('0.0.0')

  info(f'CC_TYPE: {CC_TYPE}, CC_VERSION: {CC_VERSION}')

  cxx_version = os.popen(f'{CXX} --version').read().strip()
  global CXX_TYPE, CXX_VERSION
  if 'Free Software Foundation' in cxx_version:
    CXX_TYPE = 'gcc'
    CXX_VERSION = Version(cxx_version.split('\n')[0].split(' ')[-1])
  elif 'clang' in cxx_version:
    CXX_TYPE = 'clang'
    CXX_VERSION = Version(cxx_version.split('\n')[0].split(' ')[-2])
  else:
    CXX_TYPE = 'unknown'
    CXX_VERSION = Version('0.0.0')

  info(f'CXX_TYPE: {CXX_TYPE}, CXX_VERSION: {CXX_VERSION}')


_helper()

del _helper

ALWAYS_RELINK = True
