if 'target' not in globals(): from build_api import *

mkheader('include/efi')

mkheader('include/data-structure', srcdir='data-structure', flag='h-only', recurse=True)
mkheader('include/data-structure', srcdir='data-structure', flag='hpp-only', recurse=True)

mkheader('include/algorithm', srcdir='algorithm', flag='h-only', recurse=True)
mkheader('include/algorithm', srcdir='algorithm', flag='hpp-only', recurse=True)

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include('define.h')


@target('algorithm', type='static-lib', platforms=['ia32', 'amd64'])
def _():
  compile('algorithm/main.c', 'algorithm/main.cpp')


@target('data-structure', type='static-lib', platforms=['ia32', 'amd64'])
def _():
  compile('data-structure/main.c', 'data-structure/main.cpp')
