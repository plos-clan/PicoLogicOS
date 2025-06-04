load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:plos_build.bzl", "plos_library", "plos_rust_library")
load("//tools/bazel:plos_flags.bzl", "get_default_flags")

include_files = ["-include " + name for name in [
    "define.h",
]]

cflags = get_default_flags("plos")["cflags"] + include_files

cxxflags = get_default_flags("plos")["cxxflags"] + include_files

linkflags = get_default_flags("plos")["linkflags"]

cc_library(
    name = "headers",
    hdrs = glob(["include/**/*"]),
    includes = ["include"],
    visibility = ["//visibility:public"],
)

plos_library(
    name = "algorithm",
    srcdir = "src/algorithm",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//base:headers",
        "//libs:headers",
    ],
)

plos_rust_library(
    name = "algorithm.rs",
    srcdir = "src/algorithm",
    visibility = ["//visibility:public"],
)

plos_library(
    name = "data-structure",
    srcdir = "src/data-structure",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//base:headers",
        "//libs:headers",
    ],
)

plos_rust_library(
    name = "data-structure.rs",
    srcdir = "src/data-structure",
    visibility = ["//visibility:public"],
)

plos_library(
    name = "c",
    srcdir = "src/c",
    copts = cflags + ["-ffreestanding"],
    cxxopts = cxxflags + ["-ffreestanding"],
    linkopts = linkflags + ["-ffreestanding"],
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//base:headers",
        "//base:pico-alloc#",
        "//libs:headers",
    ],
)

plos_library(
    name = "c++",
    srcdir = "src/c++",
    copts = cflags + ["-ffreestanding"],
    cxxopts = cxxflags + ["-ffreestanding"],
    linkopts = linkflags + ["-ffreestanding"],
    visibility = ["//visibility:public"],
    deps = [
        "//libs:c#",
        "//libs:headers",
    ],
)

plos_library(
    name = "asio",
    srcdir = "src/asio",
    copts = cflags,
    cxxopts = cxxflags,
    linkopts = linkflags,
    visibility = ["//visibility:public"],
    deps = [
        "//base:base#",
        "//base:headers",
        "//libs:headers",
    ],
)
