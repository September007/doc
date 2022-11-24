
# cmake 构建系统

[cmake build-system doc](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html)

cmake： crossplatform make
make：The Linux make command is used to build and maintain groups of programs and files from the source code. In Linux, it is one of the most frequently used commands by the developers. It assists developers to install and compile many utilities from the terminal. *Linux make 命令用于从源代码构建和维护程序和文件组。在 Linux 中，它是开发人员最常用的命令之一。它帮助开发人员从终端安装和编译许多实用程序。*

然而，windows上并没有make程序，（mingw-make那种不算）
cmake 表现得更先像是一个 build-tool generator，生成类似于make、ninja、vcproj或者codeblocks-proj（这个几乎就是makefile的，跟原始的codeblocks感觉出入有点大）的工程
由于make的构建系统极为简单，（ninja也不难，不过懒得学习ninja了），后边我们在考察cmake脚本的变化的时候可以到最终生成的makefile里去找他的变化，从而认识cmake

## make
自然是需要简单的介绍一下make，如下是一个简单的makefile

```make
test:test.cpp include/header.h
	g++ test.cpp -Iinclude -lstdc++ -o test
```
make目标由三个部分组成
```bash
${targetname}: ${target_dependencies}
   ${build_command}
```
即是说，当 \${target_dependencies} 发生变化时，认为 \${targetname} 过时了，然后运行\${build_command} 重新生成它

问题：
    1. 要是构架命令没有生成目标怎么办，比如g++ test.cpp -Iinclude -lstdc++ -o test_another_target
```bash
lull@DESKTOP-TUB0OQU:/mnt/e/CODE/doc/dev/common/proj/cmake/test$ make
g++ test.cpp -Iinclude -lstdc++ -o tests
lull@DESKTOP-TUB0OQU:/mnt/e/CODE/doc/dev/common/proj/cmake/test$ make
g++ test.cpp -Iinclude -lstdc++ -o tests
```
    他每次都会重新调用构建命令,至于为何，请见(todo)


## cmake 变量 和属性
正如你调试程序 一般都需要观察程序状态才能去推断程序的执行行为一样，你可以通过断点查看变量值，或者打印日志的方式去通知你你的程序的状态、
我们观察cmake的执行状态只能通过打印变量值的方式，如果你知道有什么cmake断点调试工具，请一定通知我（我好像发现了什么了不得的商机）

如下是简单的打印语句
```cmake
message("this message call print var of project name :${PROJECT_MAME}")
```
### 打印什么？
打印变量？，自然是要打印变量，但问题是哪些变量

cmake可以选择 generator，
```bash
lull@DESKTOP-TUB0OQU:/mnt/e/CODE/doc/dev/common/proj/cmake/test$ cmake --help |grep generator
  -G <generator-name>          = Specify a build system generator.
  KDevelop3 - Unix Makefiles   = Generates KDevelop 3 project files.
```
我们选择生成器 为 Unix MakeFiles 时，cmake 的configure阶段会生成makefile，瞅瞅这些makfile对于理解cmake有益处

参照 makefile的目标的结构，我们主要关注三种属性
|name|kind|specificition|
|---|---|---|
|*INCLUDE_DIRECTORIES|DC | 文件的查找路径 |
|*LINK_LIBRARIES  | C |  链接的对象，如静态库  |
|COMPILE_OPTIONS|C| 编译选项|
|COMPILE_DEFINITIONS|C  |编译预定义宏   |
|*OUTPUT_DIRECTORY  |C  |输出目录   |

以上几乎就是所有需要被关注的属性，[属性文档](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html)，kind是说种类：C：构建指令，D：依赖
更多私人的理解仿佛无根之萍的猜测，便不先拿出来了。

### 属性的工作原理

你可以在属性文档里查到
```
Directories::INCLUDE_DIRECTORIES
Targets::INCLUDE_DIRECTORIES
Targets::INTERFACE_INCLUDE_DIRECTORIES
Targets:SYSTEM_INCLUDE_DIRECTORIES
Source Files::INCLUDE_DIRECTORIES
```
如何工作？ 如下是我的理解
```bash
1. 声明目标时，like add_excutable
    A: 复制Directories::INCLUDE_DIRECTORIES 到当前目标的属性， [INCLUDE_DIRECTORIES](https://cmake.org/cmake/help/v3.25/prop_tgt/INCLUDE_DIRECTORIES.html)
2. target_include_directories(***)
    根据调用参数 [SYSTEM] <INTERFACE|PUBLIC|PRIVATE> 追加 dirs 到 INCLUDE_DIRECTORIES | INTERFACE_INCLUDE_DIRECTORIES | INTERFACE_SYSTEM_INCLUDE_DIRECTORIES


```
