# Pico Logic OS

The second refactor of [Plant-OS](https://github.com/min0911Y/Plant-OS).<br>
The third refactor of [Powerint-DOS-386](https://github.com/ZhouZhihaos/Powerint-DOS-386).<br>
Historical repository addresses:

- [Powerint-DOS-386](https://github.com/ZhouZhihaos/Powerint-DOS-386)
- [Plant-OS 1](https://github.com/min0911Y/Plant-OS)
- [Plant-OS 2](https://github.com/plos-clan/Plant-OS)

> We have kept the previous abbreviation "plos," but this time we are no longer using the name "Plant-OS."

Initially, we used the GPL 3.0 license, then switched to the MIT license, and now we use a dual license of MIT and Apache 2.0.

Although the source code of the operating system is still in a single repository for this refactor, we will try to keep the code modular to facilitate future maintenance and expansion.

Unfortunately, due to various API changes, much of the previous code cannot be reused directly, but we will rewrite these modules one by one.

## Plan

The development of the entire system will roughly follow this process, and it may take a long time before the kernel can actually run.

- [ ] tools: Custom build tools
- [ ] base: Basic C / C++ / Rust / Zig libraries<br>
  Provide a series of basic functions and data structures without relying on standard libraries
  - [ ] define: Basic macro definitions and type definitions
  - [ ] memory: Memory management
  - [ ] string: String handling
- [ ] test: Testing framework and unit tests<br>
  Provide a testing framework after the basic libraries are completed, for testing various functions on Linux systems or in QEMU environments
- [ ] kernel: Basic kernel<br>
  Provide a simple kernel after the basic libraries are completed, using limine for booting
- [ ] base: Complete basic functions and data structures
- [ ] libs: Extended libraries<br>
  Provide some extended libraries after the basic libraries are completed, including more complex features
- [ ] kernel: Improve the kernel
- [ ] apps: Applications<br>
  Provide some simple applications after the basic libraries and kernel are completed
- [ ] libs: Common C libraries
- [ ] apps: Applications<br>
  Provide some more complex applications after the basic libraries and kernel are completed
- [ ] kernel: Improve the kernel
- [ ] libs: Common C++ / Rust / Zig libraries

## Documentation

We will try to replace comments with code and replace documentation with comments, but we will still provide some necessary documentation here.

Check out the [web documentation](https://plos.plos-clan.org/). (Not yet completed)

## Build

Run the build tool provided by plos:

```sh
./build.py
```

If there are no errors, you should see it output the `>>>` prompt.<br>
You can enter the target name after this to execute the specified target.

If you need to modify the default compiler or if the build tool cannot find the compiler, you can create a `.env` file in the project root directory with configurations like:

```env
CC=clang
CXX=clang++
LD=ld.lld
AR=llvm-ar
```

## License

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
