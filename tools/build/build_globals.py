from ..logging import *
from ..env import *
from ..codegen import *
from ..helper import *
from ..target import *
from ..platform import *
from .constants import *
from .flags import *
from .decorator import *
from .commands import *
from . import buildtree


def init_build_globals():

  def build_warning(func: str, instead: str = None):
    msg = f'Do not use {func}' + (f', use {instead} instead' if instead is not None else '')
    buildtree.BUILD_GLOBALS[func] = \
      lambda *args, **kwargs: \
        warn(msg) or \
          globals()[func](*args, **kwargs)

  buildtree.BUILD_GLOBALS = {k: globals()[k] for k in buildtree.BUILD_GLOBALS}
  build_warning('print', 'logging functions')
  build_warning('exec')
