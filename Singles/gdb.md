---
title: gdb
category:
  - [ Singles ]
draft: true
typora-root-url: gdb
date: 2023-05-12 10:51:00
tags:
---

## dir
GDB 设置的调试信息目录  
https://blog.csdn.net/CaspianSea/article/details/43083977

```text
GDB 设置的调试信息目录是通过配置选项 --with-separate-debug-dir 设定的，　
(gdb) show configuration 
This GDB was configured as follows:
   configure --host=i686-linux-gnu --target=i686-linux-gnu
             --with-auto-load-dir=$debugdir:$datadir/auto-load
             --with-auto-load-safe-path=$debugdir:$datadir/auto-load
             --with-expat
             --with-gdb-datadir=/usr/share/gdb (relocatable)
             --with-jit-reader-dir=/usr/lib/gdb (relocatable)
             --without-libunwind-ia64
             --with-lzma
             --with-python=/usr (relocatable)
             --with-separate-debug-dir=/usr/lib/debug (relocatable)
             --with-system-gdbinit=/etc/gdb/gdbinit
             --with-zlib
             --without-babeltrace

gdb在调试过程中，也可以用 set debug-file-directory directories 设置全局的调试信息目录.
(gdb) show debug-file-directory 
The directory where separate debug symbols are searched for is "/usr/lib/debug".
```