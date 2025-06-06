load("@rules_cc//cc:cc_library.bzl", "cc_library")
load("@rules_multirun//:defs.bzl", "command", "multirun")

# TODO 添加对头文件生成器的支持
cc_library(
    name = "header-gen",
    visibility = ["//visibility:public"],
    deps = [
    ],
)

# 几把的 rust 规则怎么依赖 cc 啊

command(
    name = "rust_analyzer",
    command = "@rules_rust//tools/rust_analyzer:gen_rust_project",
)

multirun(
    name = "init",
    commands = [
        "rust_analyzer",
    ],
)
