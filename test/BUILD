load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")

cc_binary(
    name = "bazel-test",
    srcs = ["bazel-test.c"],
    copts = ["-std=gnu2x"],
    cxxopts = ["-std=gnu++2b"],
    visibility = ["//visibility:public"],
)
