if 'target' not in globals(): from build_api import *

COMPILE_FLAGS = ''
COMPILE_FLAGS_C = ''
COMPILE_FLAGS_CPP = ''

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')


@target('util-calc', type='exec', platforms=['ia32', 'amd64'])
def _():
  src_dir('.')
