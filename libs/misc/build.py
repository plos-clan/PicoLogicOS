if 'target' not in globals(): from build_api import *

mkheader('include/misc', recurse=True)

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/libs/misc/include')
include('define.h')


@target('misc', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('src')
