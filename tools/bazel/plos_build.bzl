load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:arch_flags.bzl", "arch_flags")
load("//tools/bazel:compiler_env.bzl", "compiler_env")

def _dep_name(name, arch, type):
    if name.endswith("#"):
        return name[:-1] + "%" + arch + "+" + type
    else:
        return name

def plos_binary(name, srcdir, type = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    env = compiler_env()
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        base_srcs = native.glob([srcdir + "/*.c"], exclude = [srcdir + "/*.*.c"], allow_empty = True)
        arch_srcs = native.glob([srcdir + "/*." + arch + ".c"], allow_empty = True)

        if type == "all" or type == "dynamic":
            cc_binary(
                name = name + "%" + arch + "+dynamic",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if type == "all" or type == "static":
            cc_binary(
                name = name + "%" + arch + "+static",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )

def plos_library(name, srcdir, type = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    env = compiler_env()
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        base_srcs = native.glob([srcdir + "/*.c"], exclude = [srcdir + "/*.*.c"], allow_empty = True)
        arch_srcs = native.glob([srcdir + "/*." + arch + ".c"], allow_empty = True)
        if type == "all" or type == "dynamic":
            cc_library(
                name = name + "%" + arch + "+dynamic",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if type == "all" or type == "static":
            cc_library(
                name = name + "%" + arch + "+static",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )
