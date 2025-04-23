import os
import glob
from typing import Callable


def given_path_or_workdir(path: str | None) -> str:
  if path is None: path = os.getcwd()
  if not isinstance(path, str): raise TypeError(f"Invalid type for 'path': {type(path)}")
  if len(path) == 0: path = os.getcwd()
  path = os.path.abspath(path)
  if not os.path.isdir(path): raise FileNotFoundError(f"Directory '{path}' not found.")
  return path


def given_path_or_default(path: str | None, default: str, isdir: bool = False) -> str:
  if not isinstance(default, str): raise TypeError(f"Invalid type for 'default': {type(default)}")
  if len(default) == 0: raise ValueError("Invalid value for 'default': empty string.")
  if path is None: path = default
  if not isinstance(path, str): raise TypeError(f"Invalid type for 'path': {type(path)}")
  if len(path) == 0: path = default
  path = os.path.abspath(path)
  if isdir and not os.path.isdir(path): raise FileNotFoundError(f"Directory '{path}' not found.")
  return path


# path: 要搜索的路径或路径列表
#     如 'path/to/dir' 或 ['path/to/dir1', 'path/to/dir2']
# extensions: 要搜索的扩展名或扩展名列表
#     如 'txt' 或 ['txt', 'md']
# recurse: 是否递归搜索
def get_files_with_extensions(path: str | list[str], extensions: str | list[str], recurse: bool = False):
  if isinstance(path, list):
    for path in path:
      file_list += get_files_with_extensions(path, extensions)
    return file_list
  if isinstance(extensions, str): extensions = [extensions]
  extensions = [f'.{ext}' for ext in extensions]
  if not recurse: return [os.path.join(path, f) for f in os.listdir(path) if any([f.endswith(ext) for ext in extensions])]
  file_list = []
  for root, dirs, files in os.walk(path):
    file_list += [os.path.join(root, f) for f in files if any([f.endswith(ext) for ext in extensions])]
  return file_list


def readlink(path: str) -> str:
  path = os.path.abspath(path)
  while os.path.islink(path):
    path = os.path.abspath(os.path.join(os.path.dirname(path), os.readlink(path)))
  return path


def find_files(dir: str, pattern: str = None, function: Callable[[str], bool] = None, hidden_file: bool = False) -> list[str]:
  if pattern is not None:
    if function is not None:
      files = glob.glob(os.path.join(dir, pattern), recursive=True, include_hidden=hidden_file)
      files = [file for file in files if function(file)]
      return files
    else:
      return glob.glob(os.path.join(dir, pattern), recursive=True, include_hidden=hidden_file)
  else:
    if function is not None:
      rets = []
      for root, dirs, files in os.walk(dir):
        for file in files:
          if not hidden_file and file.startswith('.'): continue
          file = os.path.join(root, file)
          if function(file):
            rets.append(file)
      return rets
    else:
      rets = []
      for root, dirs, files in os.walk(dir):
        for file in files:
          if not hidden_file and file.startswith('.'): continue
          rets.append(os.path.join(root, file))
      return rets


def abspath(path: str) -> str:
  return os.path.abspath(path)


def relpath(path: str, start: str = None) -> str:
  return os.path.relpath(path, start)


def file_basename_c_style(file: str) -> str:
  return ''.join([c.upper() if c.isalnum() else '_' for c in os.path.basename(file)])


def check_and_mkdirs(*paths: str, base: str = None):
  for path in paths:
    path = os.path.abspath(os.path.join(base, path) if base else path)
    if os.path.exists(path):
      if not os.path.isdir(path):
        raise Exception(f'{path} is not a directory')
    else:
      try:
        os.makedirs(path)
      except Exception as e:
        raise Exception(f'Failed to create directory {path}: {e}')
