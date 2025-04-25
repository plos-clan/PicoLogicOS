import os
import inspect
from typing import Callable
from functools import partial
from ..logging import *
from ..env import *
from .. import logging
from ..target import open_target, close_target, has_target, get_target
from ..platform import open_platform, close_platform, get_platform
from . import buildtree

VAILD_NAME = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-+'


def get_function_params(func):
  return [param.name for param in inspect.signature(func).parameters.values()]


def create_target(
    *,
    name: str,
    type: str,
    platform: str,
    output: str,
    func: Callable,
) -> bool:
  if has_target(name):
    warn(f'Target {name} already exists.')
    return False
  if type not in ['exec', 'static-exec', 'lib', 'dynamic-lib', 'static-lib']: raise ValueError("Invalid value for 'type'.")
  fullname = f'{name}#{platform}'

  info(f'Creating target {fullname}')

  target = open_target(buildtree.build_scope['DIR'], name, platform)
  target.type = type
  if type == 'static-lib':
    target.output = os.path.join(BUILD_PATH, 'libraries', f'lib{output}.a') if platform is None else os.path.join(BUILD_PATH, 'libraries', platform, f'lib{output}.a')
  elif type == 'dynamic-lib':
    target.output = os.path.join(BUILD_PATH, 'libraries', f'lib{output}.so') if platform is None else os.path.join(BUILD_PATH, 'libraries', platform, f'lib{output}.so')
  else:
    target.output = os.path.join(BUILD_PATH, 'binaries', output) if platform is None else os.path.join(BUILD_PATH, 'binaries', platform, output)

  params = get_function_params(func)
  logging.LOGGING_DEPTH += 1
  func(*{
      k: v
      for k, v in {
          'name': name,
          'type': type,
          'platform': platform,
          'fullname': fullname,
          'target': target,
          'output': target.output,
      }.items() if k in params
  })
  logging.LOGGING_DEPTH -= 1

  target.fix(build_scope=buildtree.build_scope)
  close_target()

  return True


def target(name: str, type: str = 'exec', platforms: list[str] | str = 'default', output: str = None) -> Callable[[Callable], Callable]:
  if any([c not in VAILD_NAME for c in name]): raise ValueError("Invalid character in 'name'.")
  if output is None: output = name
  if type not in ['exec', 'static-exec', 'lib', 'dynamic-lib', 'static-lib', 'customize']: raise ValueError("Invalid value for 'type'.")
  if platforms is not None and any([any([c not in VAILD_NAME for c in platform]) for platform in platforms]): raise ValueError("Invalid character in 'platforms'.")
  if isinstance(platforms, str): platforms = [platforms]

  def decorator(func: Callable) -> Callable:
    for platform in platforms:
      if type == 'customize':
        info(f'Creating customize target {name}#{platform}')
        target = open_target(buildtree.build_scope['DIR'], name, platform)
        target.type = type
        target.func = func
        close_target()
      else:
        create_target(name=name, type=type, platform=platform, output=output, func=func)
    return func

  return decorator


def platform(name: str) -> Callable[[Callable], Callable]:
  if any([c not in VAILD_NAME for c in name]): raise ValueError("Invalid character in 'name'.")

  def decorator(func: Callable) -> Callable:
    info(f'Creating platform {name}')
    platform = open_platform(name)
    func()
    close_platform()
    return func

  return decorator


def before_build(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.before_build_list.append(func)
    return func

  return decorator


def before_compile(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.before_compile_list.append(func)
    return func

  return decorator


def after_compile(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.after_compile_list.append(func)
    return func

  return decorator


def before_link(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.before_link_list.append(func)
    return func

  return decorator


def after_link(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.after_link_list.append(func)
    return func

  return decorator


def after_build(target: str) -> Callable[[Callable], Callable]:

  def decorator(func: Callable) -> Callable:
    get_target(target).callbacks.after_build_list.append(func)
    return func

  return decorator
