import hashlib


def md5(file: str) -> str:
  hash = hashlib.md5()
  with open(file, "rb") as f:
    for chunk in iter(lambda: f.read(4096), b""):
      hash.update(chunk)
  return hash.hexdigest()
