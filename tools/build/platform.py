import os
import json
import shlex
import shutil
from ..logging import *
from ..env import *
from .. import logging


class Platform:

  def __init__(self, name: str):
    self.name = name
    self.platform = None
    self.target = None
    self.output = None
    self.type = None
    self.func = None
    self.params = {}
    self.envs = {}
    self.command = []
    self.args = []
    self.prebuild = []
    self.postbuild = []
    self.build = []
    self.clean = []
    self.extra_envs = {}
    self.extra_args = {}
    self.extra_prebuild = {}
    self.extra_postbuild = {}
    self.extra_build = {}
    self.extra_clean = {}


platforms: dict[str, Platform] = {}
now_platform: Platform = None


def open_platform(name: str) -> Platform:
  global now_platform
  now_platform = platforms[name] if name in platforms else Platform(name)
  platforms[name] = now_platform
  return now_platform


def close_platform():
  global now_platform
  now_platform = None


def has_platform(name: str) -> bool:
  return name in platforms


def get_platform(name: str) -> Platform:
  if name not in platforms:
    raise ValueError(f"Platform {name} not found.")
  return platforms[name]


def get_now_platform() -> Platform:
  return now_platform
