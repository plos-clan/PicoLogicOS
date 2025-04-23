from typing import Callable


class TargetCallbacks:

  def __init__(self):
    self.before_build_list: list[Callable] = []
    self.before_compile_list: list[Callable] = []
    self.after_compile_list: list[Callable] = []
    self.before_link_list: list[Callable] = []
    self.after_link_list: list[Callable] = []
    self.after_build_list: list[Callable] = []

  def before_build(self):
    for callback in self.before_build_list:
      callback()

  def before_compile(self):
    for callback in self.before_compile_list:
      callback()

  def after_compile(self):
    for callback in self.after_compile_list:
      callback()

  def before_link(self):
    for callback in self.before_link_list:
      callback()

  def after_link(self):
    for callback in self.after_link_list:
      callback()

  def after_build(self):
    for callback in self.after_build_list:
      callback()
