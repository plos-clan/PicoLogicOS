if 'target' not in globals(): from build_api import *

mkheader('amd64')
mkheader('arm64')
mkheader('riscv64')
