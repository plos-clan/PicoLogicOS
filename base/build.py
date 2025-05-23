if 'target' not in globals(): from build_api import *

include_dir('include')
include_dir('stdinc')
include_dir('stdinc/' + CC_TYPE)

add_compile_flags('-ffreestanding')

add_compile_flags('-DPLOS_BASE=1')


@target('base', type='static-lib', platforms=['ia32', 'amd64'])
def main():
  include('define.h')
  src_dir('src/base')


@target('pico-alloc', type='static-lib', platforms=['ia32', 'amd64'])
def main():
  include('define.h')
  src_dir('src/pico-alloc')


@target('ubsan', type='static-lib', platforms=['ia32', 'amd64'])
def main(platform: str):
  include('define.h')
  src_dir('src/ubsan')


@target('coroutine', type='static-lib', platforms=['ia32', 'amd64'])
def _():
  include('define.h')
  src_dir('src/coroutine')


@target('ainit', type='static-lib', platforms=['ia32', 'amd64'])
def _():
  include('define.h')
  src_dir('src/ainit')


@target('textdraw', type='static-lib', platforms=['ia32', 'amd64'])
def _():
  include('define.h')
  src_dir('src/textdraw')
