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

cc_library(
    name = "headers",
    hdrs = ["include/kmman.h"] + glob(
        ["include/kmman/**/*"],
        allow_empty = True,
    ),
    includes = ["include"],
    visibility = ["//visibility:public"],
)

plos_library(
    name = "kmman",
    srcdir = "src",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//base:headers",
        "//libs:headers",
        "//libs/kmman:headers",
    ],
)
