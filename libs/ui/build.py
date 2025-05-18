if 'target' not in globals(): from build_api import *

mkheader('include/pl2d/points', flag='hpp-only')
mkheader('include/pl2d/pixel', flag='hpp-only')
mkheader('include/pl2d/texture', flag='hpp-only')
mkheader('include/pl2d', flag='hpp-only', recurse=True)
mkheader('include/plds/base', flag='hpp-only')
mkheader('include/plds/client', flag='hpp-only')
mkheader('include/plds/server', flag='hpp-only')
mkheader('include/plds', flag='hpp-only', recurse=True)
mkheader('include/plui', flag='hpp-only', recurse=True)

include_dir(f'{PROJECT_PATH}/base/include')
include_dir(f'{PROJECT_PATH}/libs/include')
include_dir(f'{PROJECT_PATH}/libs/misc/include')
include_dir(f'{PROJECT_PATH}/libs/ui/include')
include('define.h')


@target('pl2d', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('pl2d')


@target('plds', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('plds')


@target('plui', type='lib', platforms=['ia32', 'amd64'])
def _():
  src_dir('plui')
