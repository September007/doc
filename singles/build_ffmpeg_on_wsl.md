
---
title: Build ffmpeg on wsl+msvc(中文)
categories: 
 - [ Singles]
date: 2024-01-27T21:07:33+08:00
draft: false
include_toc: true
---
大致配置命令如下
但在配置之前，我们需要关注一下msvc配置的语言（中文？）与Windows Path对于依赖文件`*.d`的影响
```bash
# 初始化 msvc 环境
cmd /k "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
# 进入wsl 环境, 试试configure。
wsl -d u18
./configure --toolchain=msvc --enable-gpl --extra-cflags=/utf-8 --enable-shared --disable-stripping --disable-optimizations --disable-doc --prefix=`pwd`/../install
```

## 头文件中的中文字符
`config.h`: `#define CC_IDENT "用于 x64 的 Microsoft (R) C/C++ 优化编译器 19.16.27051 版"`
可能需要移除，或者翻译，或者转码

转码脚本：
```bash
#!/bin/bash

file=$1

if [[ $(file -i $file) == *"charset=utf-8"* ]]; then
    echo "$file is already utf-8 encoded"
else
    echo "$file is not utf-8 encoded"
    # iconv -f $(file -bi $file | awk -F "=" '{print $2}') -t utf-8 $file > ${file}.utf8
    iconv -f GBK -t utf-8 "$file" > "$file.temp"
    mv "$file.temp" "$file"

fi
```
## Windows路径格式
但此时编译可能会遇到 .d 依赖描述文件的路径格式不兼容问题
例如，手动执行以下语句
```bash
cl.exe -D__STDC_CONSTANT_MACROS -nologo /utf-8 -I. -utf-8 -showIncludes libavcodec/4xm.c
注意: 包含文件:  h:\code\ot\dxva\ffmpeg\libavcodec\get_bits.h
注意: 包含文件:   h:\code\ot\dxva\ffmpeg\libavcodec\mathops.h
注意: 包含文件:    H:\code\ot\dxva\ffmpeg\libavutil/attributes_internal.h
注意: 包含文件:    h:\code\ot\dxva\ffmpeg\libavcodec\x86/mathops.h
注意: 包含文件:     H:\code\ot\dxva\ffmpeg\libavutil/x86/asm.h
注意: 包含文件:   h:\code\ot\dxva\ffmpeg\libavcodec\vlc.h
```
注意到configure 中处理路径格式的片段
```bash
        _DEPCMD='$(DEP$(1)) $(DEP$(1)FLAGS) $($(1)DEP_FLAGS) $< 2>&1 | awk '\''/including/ { sub(/^.*file: */, ""); gsub(/\\/, "/"); if (!match($$0, / /)) print "$@:", $$0 }'\'' > $(@:.o=.d)'
        _DEPFLAGS='$(CPPFLAGS) $(CFLAGS) -showIncludes -Zs'
```
是针对英文与unix版路径的，所以需要替换

### 中文路径
使用 iconv 做管道转码 并更改sed参数
你可以验证以下命令
```bash
$ cl.exe -showIncludes -utf-8  -I. libavcodec/4xm.c 2>&1 |\
 iconv -f GBK -t utf-8 |\
 awk '/包含文件/ { sub(/^.*包含文件: */, ""); gsub(/\\/, "/"); if (!match($0, / /)) { b=substr($0,3);  $0=gensub(/(\w):(.*)/,"/mnt/\\1" b,1,tolower($0)); print "$@:", $0 } }'
```

### windows路径
替换到wsl路径
```bash
$ cl.exe -showIncludes -utf-8  -I. libavcodec/4xm.c 2>&1 |\
 iconv -f GBK -t utf-8 |\
 awk '/including/ { sub(/^.*file: */, ""); gsub(/\\/, "/"); if (!match($0, / /)) { b=substr($0,3);  $0=gensub(/(\w):(.*)/,"/mnt/\\1" b,1,tolower($0)); print "$@:", $0 } }'
```

### 综合
注意如果vs不在中文环境的话，只需替换wsl路径就可以了
总之，综合起来就是
注意，控制台或者configure文件的编码是utf8，所以要求awk处理的中文字符也是utf编码的, 这是我的理解
```bash
$ cl.exe -showIncludes -utf-8  -I. libavcodec/4xm.c 2>&1 |\
 iconv -f GBK -t utf-8 |\
 awk '/包含文件|including/ { sub(/^.*包含文件: *|^.*file: */, ""); gsub(/\\/, "/"); if (!match($0, / /)) { b=substr($0,3);  $0=gensub(/(\w):(.*)/,"/mnt/\\1" b,1,tolower($0)); print "$@:", $0 } }'
```

### 总结
修改configure的内容
```bash
#  elif $_cc -nologo- 2>&1 | grep -q Microsoft || { $_cc -v 2>&1 | grep -q clang && $_cc -? > /dev/null 2>&1; }; then
#         _type=msvc
#         if $_cc -nologo- 2>&1 | grep -q Microsoft; then
#             _ident=$($_cc 2>&1 | head -n1 | tr -d '\r')
#         else
#             _ident=$($_cc --version 2>/dev/null | head -n1 | tr -d '\r')
#         fi
# -       _DEPCMD='$(DEP$(1)) $(DEP$(1)FLAGS) $($(1)DEP_FLAGS) $< 2>&1 | awk '\''/including/ { sub(/^.*file: */, ""); gsub(/\\/, "/"); if (!match($$0, / /)) print "$@:", $$0 }'\'' > $(@:.o=.d)'
# + 
_DEPCMD='$(DEP$(1)) $(DEP$(1)FLAGS) $($(1)DEP_FLAGS) $< 2>&1 | iconv -f GBK -t utf-8 | awk '\''/包含文件|including/ { sub(/^.*包含文件: *|^.*file: */, ""); gsub(/\\/, "/"); if (!match($$0, / /)) { b=substr($$0,3); $$0=gensub(/(\w):(.*)/,"/mnt/\\1" b,1,tolower($$0)); print "$@:", $$0 } }'\'' > $(@:.o=.d)'
```

## configure
```bash
# 1. 初始化 msvc 环境
cmd /k "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
# 2. ... 修改configure的dep gen配置
# 3. 进入wsl 环境
wsl -d u18
# 4. config
./configure --toolchain=msvc --enable-gpl --extra-cflags=/utf-8 --enable-shared --disable-stripping --disable-optimizations --disable-doc --prefix=`pwd`/../install
# 5. 修改 config.h 中的中文CC_INDENT...
# 6. 手动修改 ffbuild/config.mak 中的编译配置也可，例如增加编译选项
# 7. make
make -j
```

cl.exe -showIncludes -utf-8  -I. libavcodec/4xm.c 2>&1 | iconv -f GBK -t utf-8 | awk '/包含文件|including/ { sub(/^.*包含文件: *|^.*file: */, ""); gsub(/\\/, "/"); if (!match($$0, / /)) { b=substr($$0,3);  $$0=gensub(/(\w):(.*)/,"/mnt/\\1" b,1,tolower($$0)); print "$@:", $$0 } }'
## 更多
### 手动修改编译选项
关注 `ffbuild/config.mak`
由于编译时出现了一堆警告 `libavfilter/af_adelay.c(99): warning C4267: “初始化”: 从“size_t”转换到“const int”，可能丢失数据`
故手动添加诸如 `-wd4267` 之类的标志
```makefile
CFLAGS= -nologo /utf-8  -Z7 -W3 -wd4018 -wd4133 -wd4146 -wd4244 -wd4267 -wd4305 -wd4334 -wd4554 -O1 -utf-8
```

# 附录
追踪 dep gen的命令路径：
* configure
* ffbuild/config.mak
* make -n > make.log


````

