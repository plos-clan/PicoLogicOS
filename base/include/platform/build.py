if 'target' not in globals(): from build_api import *

mkheader('amd64', recurse=True)
mkheader('k1', recurse=True)
