if 'target' not in globals(): from build_api import *

include_dir('include')
include_dir('stdinc')
include_dir('stdinc/' + CC_TYPE)

add_compile_flags('-ffreestanding')


@target('base', type='static-lib', platforms=['ia32', 'amd64'])
def main():
  add_compile_flags('-DPLOS_BASE=1')
  include('define.h')
  src_dir('src/base')


@target('pico-alloc', type='lib', platforms=['ia32', 'amd64'])
def main():
  add_compile_flags('-DPLOS_BASE=1')
  include('define.h')
  src_dir('src/pico-alloc')


@target('ubscan', type='static-lib', platforms=['ia32', 'amd64'])
def main():
  add_compile_flags('-DPLOS_BASE=1')
  include('define.h')
  compile('src/ubscan.c')
