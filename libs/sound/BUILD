load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:plos_build.bzl", "plos_binary", "plos_library")
load("//tools/bazel:plos_flags.bzl", "get_default_flags")

include_files = ["-include " + name for name in [
    "define.h",
    "asm.h",
    "base.h",
]]

cflags = get_default_flags("plos")["cflags"] + include_files

cxxflags = get_default_flags("plos")["cxxflags"] + include_files

linkflags = get_default_flags("plos")["linkflags"]

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
    deps = [
        "//base:headers",
    ],
)

plos_library(
    name = "vsound",
    srcdir = "vsound",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = [
        ":headers",
        "//base:headers",
    ],
)
