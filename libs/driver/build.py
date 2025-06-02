if 'target' not in globals(): from build_api import *

mkheader('include/driver/pci', recurse=True)
mkheader('include/driver')

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/libs/driver/include')
include('define.h')


@target('driver-pci', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('src/pci')
