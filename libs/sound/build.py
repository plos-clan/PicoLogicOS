if 'target' not in globals(): from build_api import *

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/libs/sound/include')
include('define.h')


@target('sound-vsound', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('vsound')
