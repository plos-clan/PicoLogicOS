if 'target' not in globals(): from build_api import *

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/kernel/include')

add_link_flags('-nostdlib', '-T lds/amd64.ld', '-pie')

add_compile_flags('-DRING0=1')
add_compile_flags('-fPIE', '-mcmodel=kernel')

add_compile_flags('-fvisibility=hidden')

add_compile_flags('-fsanitize=undefined')
add_link_flags('-fno-sanitize=undefined')
add_compile_flags('-fsanitize=pointer-overflow')
add_link_flags('-fno-sanitize=pointer-overflow')


@target('kernel', type='exec', platforms=['ia32', 'amd64'])
def _(platform: str):
  include('define.h')
  depedency('base')
  depedency('ubsan')
  src_dir('src')


@target('kernel', type='exec', platforms=['riscv64'])
def _(platform: str):
  include('define.h')
  include_dir(f'{PROJECT_PATH}/kernel/riscv-uboot/include')
  depedency('base')
  src_dir('riscv-uboot')


# @target('kernel', type='exec', platforms=['arm64'])
# def _(platform: str):
#   pass


@target('img', type='customize', platforms=['ia32', 'amd64'])
def _():
  pass
