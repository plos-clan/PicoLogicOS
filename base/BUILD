load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:plos_build.bzl", "plos_binary", "plos_library")
load("//tools/bazel:plos_flags.bzl", "get_default_flags")

include_files = ["-include " + name for name in [
    "define.h",
]]

cflags = get_default_flags("plos")["cflags"] + include_files

cxxflags = get_default_flags("plos")["cxxflags"] + include_files

linkflags = get_default_flags("plos")["linkflags"]

includes = [
    "include",
    "stdinc",
    "stdinc/clang",
]

plos_library(
    name = "base",
    srcdir = "src/base",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)

plos_library(
    name = "pico-alloc",
    srcdir = "src/pico-alloc",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)

plos_library(
    name = "ubsan",
    srcdir = "src/ubsan",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)

plos_library(
    name = "coroutine",
    srcdir = "src/coroutine",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)

plos_library(
    name = "ainit",
    srcdir = "src/ainit",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)

plos_library(
    name = "textdraw",
    srcdir = "src/textdraw",
    hdrs = glob(["include/**/*"]),
    copts = cflags,
    cxxopts = cxxflags,
    includes = includes,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
)
