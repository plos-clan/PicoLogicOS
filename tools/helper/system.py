import os
import shlex


def system(*cmd: str, cwd: str = None, env: dict[str, str] = None) -> bool:
  if env is None: env = os.environ
  if cwd is None: cwd = os.getcwd()
  sh = env.get('SHELL', '/bin/sh')
  try:
    ret = os.execvpe(sh, [sh, '-c', '\n'.join([f'cd {shlex.quote(cwd)}'] + cmd)], env)
  except FileNotFoundError:
    return False
  return ret == 0
