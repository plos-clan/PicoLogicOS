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

# --target=x86_64-unknown-elf -march=x86-64
# --target=i686-unknown-elf -march=i386
# --target=riscv64-unknown-elf -march=rv64imac -mabi=lp64
# --target=aarch64-unknown-elf -march=armv8-a -mabi=aapcs-linux

def arch_flags_rust():
    return {
        "amd64": ["--target=x86_64-unknown-elf"],
        "ia32": ["--target=i686-unknown-elf"],
        "riscv64": ["--target=riscv64-unknown-elf"],
        "arm64": ["--target=aarch64-unknown-elf"],
    }

def arch_flags_go():
    return {
        "amd64": {
            "GOARCH": "amd64",
            "GOOS": "linux",
        },
        "ia32": {
            "GOARCH": "386",
            "GOOS": "linux",
        },
        "riscv64": {
            "GOARCH": "riscv64",
            "GOOS": "linux",
        },
        "arm64": {
            "GOARCH": "arm64",
            "GOOS": "linux",
        },
    }
