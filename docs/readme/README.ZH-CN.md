# Pico Logic OS

Pico Logic OS &trade;

[Plant-OS](https://github.com/min0911Y/Plant-OS) 的第二次重构。<br>
[Powerint-DOS-386](https://github.com/ZhouZhihaos/Powerint-DOS-386) 的第三次重构。<br>
历史储存库地址：

- [Powerint-DOS-386](https://github.com/ZhouZhihaos/Powerint-DOS-386)
- [Plant-OS 1](https://github.com/min0911Y/Plant-OS)
- [Plant-OS 2](https://github.com/plos-clan/Plant-OS)

> 我们保持了之前的简称 plos，但是这次我们不再使用 Plant-OS 这个名字。

一开始我们使用 GPL 3.0 许可，后来改用 MIT 许可，现在我们使用 MIT 和 Apache 2.0 双许可。

虽然这次重构整个操作系统源码还是在一个储存库中，但是我们会尽量保持源码的模块化，以便于未来的维护和扩展。

很遗憾由于各种 API 的变动，之前的许多代码都无法直接使用，但我们会逐个模块地重写这些代码。

## 计划

整个系统的开发将大致按照这个流程进行，可能很久之后内核才能真正跑起来。

- [ ] tools: 自制构建工具
- [ ] base: 基本 C / C++ / Rust / Zig 库<br>
  将在没有标准库的情况下提供一系列基本的函数和数据结构
  - [ ] define: 基本宏定义和类型定义
  - [ ] memory: 内存管理
  - [ ] string: 字符串处理
- [ ] test: 测试框架与单元测试<br>
  将在基本库完成后提供一套测试框架，用于在 Linux 系统或 QEMU 环境中测试各种函数
- [ ] kernel: 基本内核<br>
  将在基本库完成后提供一个简单的内核，使用 limine 引导
- [ ] base: 补全基本函数和数据结构
- [ ] libs: 扩展库<br>
  将在基本库完成后提供一些扩展库，包含一些复杂的功能
- [ ] kernel: 完善内核
- [ ] apps: 应用程序<br>
  将在基本库和内核完成后提供一些简单应用程序
- [ ] libs: 常用 C 库
- [ ] apps: 应用程序<br>
  将在基本库和内核完成后提供一些较复杂的应用程序
- [ ] kernel: 完善内核
- [ ] libs: 常用 C++ / Rust / Zig 库

## 文档

我们会尽量用代码替代注释，用注释替代文档，但是我们仍然会在这里提供一些必须的文档。

查看 [网页版文档](https://plos.plos-clan.org/) 。（未完成）

## 构建

运行 plos 自带的构建工具：

```sh
./build.py
```

如果没有错误，你应该可以看到它输出 `>>>` 提示符。<br>
你可以在这后面输入目标名来执行指定的目标。

如果需要修改默认的编译器或是构建工具找不到编译器，可以在项目根目录创建 `.env` 文件，写入配置如：

```env
CC=clang
CXX=clang++
LD=ld.lld
AR=llvm-ar
```

## 许可证

This project is dual-licensed under either:

- [MIT License](LICENSE-MIT)
- [Apache License 2.0](LICENSE-MIT)

at your option.

You can choose either license according to your needs.

Unless required by applicable law or agreed to in writing,
software distributed under these licenses is distributed on
an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
either express or implied. See the licenses for the specific
language governing permissions and limitations.
