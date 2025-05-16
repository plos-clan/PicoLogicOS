def compiler_env():
    cc_type = "clang"
    if cc_type == "gcc":
        return {
            arch: {
                "cc": prefix + "-gcc",
                "cxx": prefix + "-g++",
                "ar": prefix + "-ar",
                "ld": prefix + "-ld",
                "ranlib": prefix + "-ranlib",
                "objcopy": prefix + "-objcopy",
                "objdump": prefix + "-objdump",
                "strip": prefix + "-strip",
                "nm": prefix + "-nm",
                "readelf": prefix + "-readelf",
            }
            for arch, prefix in [
                ("amd64", "x86_64-linux-gnu"),
                ("ia32", "i686-linux-gnu"),
                ("riscv64", "riscv64-unknown-elf"),
                ("arm64", "aarch64-none-eabi"),
            ]
        }
    elif cc_type == "clang":
        return {
            arch: {
                "cc": "clang",
                "cxx": "clang++",
                "ar": "llvm-ar",
                "ld": "lld",
                "ranlib": "llvm-ranlib",
                "objcopy": "llvm-objcopy",
                "objdump": "llvm-objdump",
                "strip": "llvm-strip",
                "nm": "llvm-nm",
                "readelf": "llvm-readelf",
            }
            for arch, prefix in [
                ("amd64", "x86_64-linux-gnu"),
                ("ia32", "i686-linux-gnu"),
                ("riscv64", "riscv64-unknown-elf"),
                ("arm64", "aarch64-none-eabi"),
            ]
        }
    else:
        fail("CC_TYPE must be set to either 'gcc' or 'clang'")
