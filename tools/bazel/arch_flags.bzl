def arch_flags():
    return {
        "amd64": {
            "CFLAGS": ["-m64"],
            "CXXFLAGS": ["-m64"],
            "LDFLAGS": ["-m64"],
        },
        "ia32": {
            "CFLAGS": ["-m32"],
            "CXXFLAGS": ["-m32"],
            "LDFLAGS": ["-m32"],
        },
        "riscv64": {
            "CFLAGS": ["-march=rv64imac -mabi=ilp32"],
            "CXXFLAGS": ["-march=rv64imac -mabi=ilp32"],
            "LDFLAGS": ["-march=rv64imac -mabi=ilp32"],
        },
        "arm64": {
            "CFLAGS": ["-march=armv8-a -mabi=aapcs-linux"],
            "CXXFLAGS": ["-march=armv8-a -mabi=aapcs-linux"],
            "LDFLAGS": ["-march=armv8-a -mabi=aapcs-linux"],
        },
    }
