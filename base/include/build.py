if 'target' not in globals(): from build_api import *

mkheader('base', flag='h-only', recurse=True)
mkheader('base', flag='hpp-only', recurse=True)

mkheader('define', flag='h-only', recurse=True)
mkheader('define', flag='hpp', recurse=True)
