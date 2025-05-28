load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    # WIP
    name = "highlight",
    srcs = glob([
        "highlight/**/*.c",
    ]),
    copts = ["-std=gnu2x"],
    cxxopts = ["-std=gnu++2b"],
    visibility = ["//visibility:public"],
)

cc_binary(
    name = "util-calc",
    srcs = glob([
        "calc/**/*.c",
        "calc/**/*.cpp",
    ]),
    copts = ["-std=gnu2x"],
    cxxopts = ["-std=gnu++2b"],
    visibility = ["//visibility:public"],
    deps = [
        "//base:headers",
        "//libs:headers",
    ],
)
