import os
import sys
import shlex
import atexit
import readline
from .logging import *
from .env import *
from .target import run as target_run, print_targets, clear_hash_cache, targets as all_targets
from . import logging


def run(args: list[str]):
  if args[0] == 'help':
    warn('No helps')
  elif args[0] == 'clean':
    if len(args) == 1:
      shutil.rmtree(os.path.join(BUILD_PATH, 'binaries'))
      shutil.rmtree(os.path.join(BUILD_PATH, 'libraries'))
      shutil.rmtree(os.path.join(BUILD_PATH, 'objects'))
      shutil.rmtree(os.path.join(BUILD_PATH, 'sources'))
      clear_hash_cache()
    elif args[1] == 'all':
      shutil.rmtree(BUILD_PATH)
      os.makedirs(BUILD_PATH, exist_ok=True)
      clear_hash_cache()
      exit(0)
    else:
      warn('Unknown command')
  elif args[0] == 'show':
    if len(args) == 1:
      warn('Show what?')
    elif args[1] == 'targets':
      print_targets()
    elif args[1] == 'history':
      info('Command history:')
      for i in range(readline.get_current_history_length()):
        info('  ' + readline.get_history_item(i + 1))
    else:
      warn(f'What is {args[1]}?')
  elif args[0] == 'clear':
    if args[1] == 'history':
      readline.clear_history()
      try:
        os.remove(os.path.join(BUILD_PATH, '.cli_history'))
      except FileNotFoundError:
        pass
      info('Command history cleared')
    else:
      warn('Unknown command')
  else:
    if '#' in args[0]:
      if args[0] in all_targets:
        target_run(args[0], args=args[1:])
      else:
        warn(f'Target {args[0]} not found')
    else:
      target_found = False
      for target in all_targets:
        if target.split('#')[0] == args[0]:
          target_found = True
          info(f'Running target {target}')
          target_run(target, args=args[1:])
      if not target_found:
        warn(f'Target {args[0]} not found')


def main():
  print_targets()
  CLIHISTORY_PATH = os.path.join(BUILD_PATH, '.cli_history')
  if len(sys.argv) > 1 and sys.argv[1] == 'once':
    run(sys.argv[2:])
  else:
    try:
      readline.read_history_file(CLIHISTORY_PATH)
    except FileNotFoundError:
      pass
    atexit.register(readline.write_history_file, CLIHISTORY_PATH)
    try:
      while True:
        text = input(colored('>>>', 192, 128, 255) + ' ' + colored('', 255, 128, 192, end=False)).strip()
        if len(text) == 0: continue
        if text == 'exit': break
        run(shlex.split(text))
    except (EOFError, KeyboardInterrupt):
      print()
  exit(0)
