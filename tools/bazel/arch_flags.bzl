def arch_flags():
    # 目前强制 clang 编译所以这里就写 clang 参数
    return {k: {
        "CFLAGS": v["#CFLAGS"] + v["CFLAGS"],
        "CXXFLAGS": v["#CFLAGS"] + v["CXXFLAGS"],
        "LDFLAGS": v["#CFLAGS"] + v["LDFLAGS"],
    } for k, v in {
        "#default": {
            # 目前没用
            "#CFLAGS": [
                "-fvisibility=hidden",
                "-Wno-compound-token-split-by-macro",
                "-ffunction-sections",
                "-fdata-sections",
            ],
            "CFLAGS": ["-std=gnu2x"],
            "CXXFLAGS": ["-std=gnu++2b"],
            "LDFLAGS": ["-Wl,--gc-sections"],
        },
        "amd64": {
            "#CFLAGS": [
                "--target=x86_64-unknown-elf",
                "-march=x86-64",
            ],
            "CFLAGS": [],
            "CXXFLAGS": [],
            "LDFLAGS": [],
        },
        "ia32": {
            "#CFLAGS": [
                "--target=i686-unknown-elf",
                "-march=i386",
            ],
            "CFLAGS": [],
            "CXXFLAGS": [],
            "LDFLAGS": [],
        },
        "riscv64": {
            "#CFLAGS": [
                "--target=riscv64-unknown-elf",
                "-march=rv64imac",
                "-mabi=lp64",
            ],
            "CFLAGS": [],
            "CXXFLAGS": [],
            "LDFLAGS": [],
        },
        "arm64": {
            "#CFLAGS": [
                "--target=aarch64-unknown-elf",
                "-march=armv8-a",
                "-mabi=aapcs-linux",
            ],
            "CFLAGS": [],
            "CXXFLAGS": [],
            "LDFLAGS": [],
        },
    }.items()}
