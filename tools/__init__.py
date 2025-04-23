from .helper import *
from .safe_globals import SAFE_GLOBALS
from .env import *
from .logging import *
from .codegen import *
from . import logging
from . import build
from . import cli


def main():
  build.init()
  cli.main()
