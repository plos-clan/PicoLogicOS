load("@rules_cc//cc:cc_binary.bzl", "cc_binary")
load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_rust//rust:rust_binary.bzl", "rust_binary")
load("@rules_rust//rust:rust_library.bzl", "rust_library")
load("//tools/bazel:arch_flags.bzl", "arch_flags", "arch_flags_go", "arch_flags_rust")

def _dep_name(name, arch, linktype):
    if name.endswith("#"):
        return name[:-1] + "%" + arch + "+" + linktype
    else:
        return name

def _find_srcs(srcdir, arch, is_plos = False):
    base_srcs = native.glob([srcdir + "/*.c"], exclude = [srcdir + "/*.*.c"], allow_empty = True)
    arch_srcs = native.glob([srcdir + "/*." + arch + ".c"], allow_empty = True)
    plos_srcs = native.glob([srcdir + "/*.plos.c"], allow_empty = True) if is_plos else []
    return base_srcs + arch_srcs + plos_srcs

def plos_binary(name, srcdir, linktype = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    """Build a PLOS binary for multiple architectures."""
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            cc_binary(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            cc_binary(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )

def plos_library(name, srcdir, linktype = "all", copts = [], cxxopts = [], linkopts = [], deps = [], **kwargs):
    """Build a PLOS library for multiple architectures."""
    flags = arch_flags()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            cc_library(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                linkstatic = False,
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            cc_library(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                copts = flags[arch]["CFLAGS"] + copts,
                cxxopts = flags[arch]["CXXFLAGS"] + cxxopts,
                linkopts = flags[arch]["LDFLAGS"] + linkopts,
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                linkstatic = True,
                **kwargs
            )

### 以下内容仅为测试用 ###

def _find_srcs_rust(srcdir, arch, is_plos = False):
    base_srcs = native.glob([srcdir + "/*.rs"], exclude = [srcdir + "/*.*.rs"], allow_empty = True)
    arch_srcs = native.glob([srcdir + "/*." + arch + ".rs"], allow_empty = True)
    plos_srcs = native.glob([srcdir + "/*.plos.rs"], allow_empty = True) if is_plos else []
    return base_srcs + arch_srcs + plos_srcs

def plos_rust_binary(name, srcdir, linktype = "all", deps = [], **kwargs):
    """Build a PLOS Rust binary for multiple architectures."""
    flags = arch_flags_rust()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs_rust(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            rust_binary(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                crate_name = name,
                edition = "2021",
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            rust_binary(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                crate_name = name,
                edition = "2021",
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                **kwargs
            )

def plos_rust_library(name, srcdir, linktype = "all", deps = [], **kwargs):
    """Build a PLOS Rust library for multiple architectures."""
    flags = arch_flags_rust()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs_rust(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            rust_library(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                crate_name = name,
                edition = "2021",
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            rust_library(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                crate_name = name,
                edition = "2021",
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                **kwargs
            )

def _find_srcs_go(srcdir, arch, is_plos = False):
    base_srcs = native.glob([srcdir + "/*.go"], exclude = [srcdir + "/*.*.go"], allow_empty = True)
    arch_srcs = native.glob([srcdir + "/*." + arch + ".go"], allow_empty = True)
    plos_srcs = native.glob([srcdir + "/*.plos.go"], allow_empty = True) if is_plos else []
    return base_srcs + arch_srcs + plos_srcs

def plos_go_binary(name, srcdir, linktype = "all", deps = [], **kwargs):
    """Build a PLOS Go binary for multiple architectures."""
    flags = arch_flags_go()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs_go(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            native.go_binary(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                goarch = flags[arch]["GOARCH"],
                goos = flags[arch]["GOOS"],
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            native.go_binary(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                goarch = flags[arch]["GOARCH"],
                goos = flags[arch]["GOOS"],
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                **kwargs
            )

def plos_go_library(name, srcdir, linktype = "all", deps = [], **kwargs):
    """Build a PLOS Go library for multiple architectures."""
    flags = arch_flags_go()

    for arch in ["amd64", "ia32", "riscv64", "arm64"]:
        srcs = _find_srcs_go(srcdir, arch, is_plos = True)

        if linktype == "all" or linktype == "dynamic":
            native.go_library(
                name = name + "%" + arch + "+dynamic",
                srcs = srcs,
                goarch = flags[arch]["GOARCH"],
                goos = flags[arch]["GOOS"],
                deps = [_dep_name(dep, arch, "dynamic") for dep in deps],
                **kwargs
            )
        if linktype == "all" or linktype == "static":
            native.go_library(
                name = name + "%" + arch + "+static",
                srcs = srcs,
                goarch = flags[arch]["GOARCH"],
                goos = flags[arch]["GOOS"],
                deps = [_dep_name(dep, arch, "static") for dep in deps],
                **kwargs
            )
