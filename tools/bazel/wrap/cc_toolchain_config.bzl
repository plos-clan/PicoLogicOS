load("@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl", "tool_path")

def _impl(ctx):
    return cc_common.create_cc_toolchain_config_info(
        abi_libc_version = "unknown",
        abi_version = "unknown",
        compiler = "clang",
        ctx = ctx,
        host_system_name = "local",
        target_cpu = "k8",
        target_libc = "unknown",
        target_system_name = "local",
        tool_paths = [
            tool_path(
                name = "gcc",
                path = "clang.sh",
            ),
            tool_path(
                name = "cpp",
                path = "clang++.sh",
            ),
            tool_path(
                name = "ld",
                path = "clang.sh",
            ),
            tool_path(
                name = "ar",
                path = "llvm-ar.sh",
            ),
            tool_path(
                name = "nm",
                path = "llvm-nm.sh",
            ),
            tool_path(
                name = "objdump",
                path = "llvm-objdump.sh",
            ),
            tool_path(
                name = "strip",
                path = "llvm-strip.sh",
            ),
        ],
        toolchain_identifier = "k8-toolchain",
    )

cc_toolchain_config = rule(
    attrs = {},
    provides = [CcToolchainConfigInfo],
    implementation = _impl,
)
