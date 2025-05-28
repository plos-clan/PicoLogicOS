load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:host_build.bzl", "host_binary", "host_library")
load("//tools/bazel:plos_build.bzl", "plos_binary", "plos_library")
load("//tools/bazel:plos_flags.bzl", "get_default_flags")

include_files = ["-include " + name for name in [
    "define.h",
]]

cflags = get_default_flags("plos")["cflags"] + include_files

cxxflags = get_default_flags("plos")["cxxflags"] + include_files

linkflags = get_default_flags("plos")["linkflags"]

cc_library(
    name = "asm",
    hdrs = glob(["include/asm/**/*"]) + ["include/asm.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "platform",
    hdrs = glob(["include/platform/**/*"]) + ["include/platform.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "define",
    hdrs = glob(["include/define/**/*"]) + ["include/define.h"],
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = ["//base:asm"],
)

cc_library(
    name = "stdinc",
    hdrs = glob(["stdinc/**/*"]),
    includes = [
        "stdinc",
        "stdinc/clang",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = ["//base:stdinc"],
)

plos_library(
    name = "base",
    srcdir = "src/base",
    copts = cflags + ["-ffreestanding"],
    cxxopts = cxxflags + ["-ffreestanding"],
    linkopts = linkflags + ["-ffreestanding"],
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)

# host_library(
#     name = "base",
#     srcdir = "src/base",
#     copts = cflags + ["-ffreestanding"],
#     cxxopts = cxxflags + ["-ffreestanding"],
#     linkopts = linkflags + ["-ffreestanding"],
#     visibility = ["//visibility:public"],
#     deps = ["//base:headers"],
# )

plos_library(
    name = "pico-alloc",
    srcdir = "src/pico-alloc",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)

plos_library(
    name = "ubsan",
    srcdir = "src/ubsan",
    copts = cflags + ["-ffreestanding"],
    cxxopts = cxxflags + ["-ffreestanding"],
    linkopts = linkflags + ["-ffreestanding"],
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)

plos_library(
    name = "coroutine",
    srcdir = "src/coroutine",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)

plos_library(
    name = "ainit",
    srcdir = "src/ainit",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)

plos_library(
    name = "textdraw",
    srcdir = "src/textdraw",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = ["//base:headers"],
)
