class CCompileFlags:
  include_files = []  # -include xxx.h
  include_dirs = []
  optim = ''  # -O1
  defines = {}  # -Dname=value
  flags = []

  def include(self, file: str | list[str]):
    if isinstance(file, list):
      self.include_files.extend(file)
    else:
      self.include_files.append(file)

  def define(self, name: str | list[str], value: str = None):
    if isinstance(name, list):
      for n in name:
        self.define(n, value)
    else:
      self.defines[name] = value

  def __lshift__(self, other: str | list[str]):
    if isinstance(other, list):
      for flag in other:
        self << flag
      return self

    if not isinstance(other, str): raise TypeError("Unsupported type for << operation")

    if other.startswith('-O'): self.optim = other[2:]
    if other.startswith('-I'): self.include_dirs.append(other[2:])
    if other.startswith('-D'): self.define(*other[2:].split('=', 1))
    else: self.flags.append(other)

    return self

  def __repr__(self):
    cmd = []

    if self.optim:
      if self.optim not in ['0', '1', '2', '3', 'fast', 'g', 's', 'z']: raise ValueError(f"Invalid value for 'optim': {self.optim}")
      cmd.append(f'-O{self.optim}')

    for name, value in self.defines.items():
      if value is not None:
        cmd.append(f'-D{name}={value}')
      else:
        cmd.append(f'-D{name}')

    for dir in self.include_dirs:
      cmd.append(f'-I{dir}')

    for file in self.include_files:
      cmd.append(f'-include {file}')

    return ' '.join(cmd + self.flags)
