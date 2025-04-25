if 'target' not in globals(): from build_api import *

mkheader('asm')
mkheader('config')
mkheader('define')
mkheader('type', flag='h-only')
mkheader('type', flag='hpp-only')
