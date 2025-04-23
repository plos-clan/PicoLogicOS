if 'target' not in globals(): from build_api import *

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/kernel/include')

add_link_flags('-nostdlib', '-T lds/amd64.ld')

add_compile_flags('-DRING0=1')
add_compile_flags('-fPIE', '-fPIC')


@target('kernel', type='static-exec', platforms=['ia32', 'amd64'])
def _(platform: str):
  include('define.h')
  depedency('base')
  src_dir('src')


@target('kernel', type='static-exec', platforms=['riscv64'])
def _(platform: str):
  include('define.h')
  include_dir(f'{PROJECT_PATH}/kernel/riscv-uboot/include')
  depedency('base')
  src_dir('riscv-uboot')


@target('img', type='customize')
def _():
  pass
