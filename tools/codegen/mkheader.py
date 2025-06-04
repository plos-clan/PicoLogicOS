import os
from ..logging import *
from ..helper import *
from .filegen import CFileGenerator
from .fileread import CCommentReader, c_file_has_flag


def mkheader(name: str, srcdir: str = None, workdir: str = None, recurse: bool = False, flag: str = 'h') -> int:
  if len(name) == 0: raise ValueError("Invalid value for 'name': it should not be empty.")
  if name == '.' or name == '..': raise ValueError("Invalid value for 'name': it should not be '.' or '..'.")
  if ' ' in name: raise ValueError("Invalid value for 'name': it should not contain spaces.")
  if name[-1] == '/': raise ValueError("Invalid value for 'name': it should not end with '/'.")
  if flag not in ['h', 'hpp', 'h-only', 'hpp-only']: raise ValueError("Invalid value for 'flag'.")

  workdir = given_path_or_workdir(workdir)
  srcdir = given_path_or_default(srcdir, os.path.join(workdir, name), isdir=True)
  outdir = os.path.dirname(os.path.join(workdir, name))

  h_files = get_files_with_extensions(srcdir, 'h', recurse)
  hpp_files = get_files_with_extensions(srcdir, 'hpp', recurse)
  h_files = sorted(h_files, key=lambda f: (f.count(os.sep), f))
  hpp_files = sorted(hpp_files, key=lambda f: (f.count(os.sep), f))

  if recurse:
    h_files = [f for f in h_files if not c_file_has_flag('include-generated', f)]
    hpp_files = [f for f in hpp_files if not c_file_has_flag('include-generated', f)]

  if flag == 'h-only': hpp_files = []
  if flag == 'hpp-only': h_files = []

  debug(f'Generating header: {name} with {len(h_files)} .h files and {len(hpp_files)} .hpp files')

  with CFileGenerator(f'{name}.hpp' if flag == 'hpp' or flag == 'hpp-only' else f'{name}.h', workdir) as w:
    w.flag('include-generated')
    w.once()

    if len(h_files) > 0:
      with w.if_cpp():
        w.line('extern "C" {')
      for header in h_files:
        w.include(os.path.relpath(header, outdir))
      with w.if_cpp():
        w.line('}')

    if len(hpp_files) > 0:
      with w.if_cpp():
        for header in hpp_files:
          w.include(os.path.relpath(header, outdir))

  return len(h_files) + len(hpp_files)
