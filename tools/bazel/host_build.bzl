load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("//tools/bazel:arch_flags.bzl", "arch_flags")
load("//tools/bazel:compiler_env.bzl", "compiler_env")

def _dep_name(name, arch, linktype):
    if name.endswith("#"):
        if "+" in name:
            return name.split("+", 1)[0] + "%" + arch + "+" + name.split("+", 1)[1]
        else:
            return name[:-1] + "%" + arch + "+" + linktype
    else:
        return name

def host_binary(name, srcdir, linktype = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    env = compiler_env()
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        base_srcs = native.glob([srcdir + "/*.c"], exclude = [srcdir + "/*.*.c"], allow_empty = True)
        arch_srcs = native.glob([srcdir + "/*." + arch + ".c"], allow_empty = True)

        if linktype == "all" or linktype == "dynamic":
            cc_binary(
                name = "host-" + name + "%" + arch + "+dynamic",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            cc_binary(
                name = "host-" + name + "%" + arch + "+static",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )

def host_library(name, srcdir, linktype = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    env = compiler_env()
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        base_srcs = native.glob([srcdir + "/*.c"], exclude = [srcdir + "/*.*.c"], allow_empty = True)
        arch_srcs = native.glob([srcdir + "/*." + arch + ".c"], allow_empty = True)
        if linktype == "all" or linktype == "dynamic":
            cc_library(
                name = "host-" + name + "%" + arch + "+dynamic",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            cc_library(
                name = "host-" + name + "%" + arch + "+static",
                srcs = base_srcs + arch_srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )
