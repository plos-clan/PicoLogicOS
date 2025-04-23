from typing import Callable
from .helper import randomize_color

DEBUG = True
LOG_COLOR_RANDOMIZE = False
LOGGING_DEPTH = 0


def debug_only(func: Callable) -> Callable:

  def wrapper(*args, **kwargs):
    if DEBUG:
      func(*args, **kwargs)

  return wrapper


def colored(text, fr=None, fg=None, fb=None, br=None, bg=None, bb=None, end=True):
  if fr is None:
    return f'\033[0m{text}\033[0m'
  elif br is None:
    if LOG_COLOR_RANDOMIZE:
      fr, fg, fb = randomize_color(fr, fg, fb)
    if end:
      return f'\033[38;2;{fr};{fg};{fb}m{text}\033[0m'
    else:
      return f'\033[38;2;{fr};{fg};{fb}m{text}'
  else:
    if LOG_COLOR_RANDOMIZE:
      fr, fg, fb = randomize_color(fr, fg, fb)
      br, bg, bb = randomize_color(br, bg, bb)
    if end:
      return f'\033[38;2;{fr};{fg};{fb};48;2;{br};{bg};{bb}m{text}\033[0m'
    else:
      return f'\033[38;2;{fr};{fg};{fb};48;2;{br};{bg};{bb}m{text}'


def fatal(message: str, rets=1, e: Exception = None):
  print('- ' * LOGGING_DEPTH + colored(message, 255, 64, 64))
  if e is not None: print(colored(str(e), 255, 64, 64))
  exit(rets)


def error(message: str, rets=None, e: Exception = None):
  print('- ' * LOGGING_DEPTH + colored(message, 255, 128, 64))
  if e is not None: print(colored(str(e), 255, 128, 64))


def warn(message: str, e: Exception = None):
  print('- ' * LOGGING_DEPTH + colored(message, 255, 192, 0))
  if e is not None: print(colored(str(e), 255, 192, 0))


def info(message: str):
  print('- ' * LOGGING_DEPTH + colored(message, 64, 192, 128))


@debug_only
def debug(message: str):
  print('- ' * LOGGING_DEPTH + colored(message, 128, 192, 255))
