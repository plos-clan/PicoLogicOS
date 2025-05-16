load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:plos_build.bzl", "plos_binary", "plos_library")
load("//tools/bazel:plos_flags.bzl", "get_default_flags")

include_files = ["-include " + name for name in [
    "define.h",
]]

cflags = get_default_flags("plos")["cflags"] + include_files

cxxflags = get_default_flags("plos")["cxxflags"] + include_files

linkflags = get_default_flags("plos")["linkflags"] + [
    "-T $(location :lds/amd64.ld)",
]

includes = [
    "include",
]

cc_library(
    name = "kernel_headers",
    hdrs = glob(["include/**/*"]),
    includes = includes,
    visibility = ["//visibility:public"],
)

plos_binary(
    name = "kernel",
    srcdir = "src",
    additional_linker_inputs = glob(["lds/*.ld"]),
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    type = "static",
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//kernel:kernel_headers",
        "//libs:lib_headers",
    ],
)
