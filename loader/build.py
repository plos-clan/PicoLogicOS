if 'target' not in globals(): from build_api import *

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/loader/include')

add_link_flags('-nostdlib', '-T lds/amd64.ld')

add_compile_flags('-DRING0=1')
add_compile_flags('-fPIE', '-fPIC')


@target('loader', type='static-exec', platforms=['ia32', 'amd64'])
def _(platform: str):
  include('define.h')
  depedency('base')
  src_dir('src')


@target('img', type='customize')
def _():
  pass
