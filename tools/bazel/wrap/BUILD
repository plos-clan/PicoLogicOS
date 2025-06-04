load("//tools/bazel/wrap:cc_toolchain_config.bzl", "cc_toolchain_config")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "files",
    srcs = glob(["**"]),
)

cc_toolchain_config(name = "clang-config")

cc_toolchain(
    name = "clang-wrap",
    all_files = ":files",
    ar_files = ":files",
    as_files = ":files",
    compiler_files = ":files",
    dwp_files = ":files",
    libc_top = ":files",
    linker_files = ":files",
    objcopy_files = ":files",
    strip_files = ":files",
    supports_param_files = 0,
    toolchain_config = ":clang-config",
    toolchain_identifier = "clang",
)

toolchain(
    name = "clang",
    exec_compatible_with = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
    target_compatible_with = [
        "@platforms//cpu:x86_64",
        "@platforms//os:linux",
    ],
    toolchain = ":clang-wrap",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
)
