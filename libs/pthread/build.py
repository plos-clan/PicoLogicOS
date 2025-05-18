if 'target' not in globals(): from build_api import *

mkheader('include/pthread')

add_compile_flags('-nostdlib', '-nostdinc')

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/libs/pthread/include')
include('define.h')


@target('pthread', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('src')
