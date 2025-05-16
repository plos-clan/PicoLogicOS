def _default_flags_plos():
    return {
        "flags": [
            "-fvisibility=hidden",
            "-fno-delete-null-pointer-checks",
            "-fno-strict-aliasing",
            "-finput-charset=UTF-8 -fexec-charset=UTF-8",
            "-fno-stack-protector",
            "-fno-asynchronous-unwind-tables",
            "-fno-exceptions",
            "-fno-rtti",
            "-Wno-compound-token-split-by-macro",
            "-ffunction-sections",
            "-fdata-sections",
            "-nostdlib",
            "-nostdinc",
            "-ffreestanding",
        ],
        "cflags": [
            "-std=gnu2x",
        ],
        "cxxflags": [
            "-std=gnu++2b",
        ],
        "linkflags": [
            "-Wl,--gc-sections",
        ],
    }

def _default_flags():
    return {
        "flags": [
            "-fvisibility=hidden",
            "-Wno-compound-token-split-by-macro",
            "-ffunction-sections",
            "-fdata-sections",
        ],
        "cflags": [
            "-std=gnu2x",
        ],
        "cxxflags": [
            "-std=gnu++2b",
        ],
        "linkflags": [
            "-Wl,--gc-sections",
        ],
    }

def get_default_flags(type):
    if type == "plos":
        flags = _default_flags_plos()
    else:
        flags = _default_flags()
    return {
        k: v + flags["flags"]
        for k, v in flags.items()
        if k != "flags"
    }
