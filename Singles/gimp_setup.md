---
title: GIMP 调试环境初始化
category:
  - [Singles]
draft: false
url-root: GIMP setup
date: 2023-12-09 00:11:25
tags:
---

系统: ubuntu 24.04(wsl)

gimp 依赖大量gnu 组件，windows编译较为麻烦，故此使用wsl

## 1. code
拉取GIMP 及某些依赖的代码自无甚讲头
目录树如下组织
```bash
├── 3rd
│   ├── babl
│   ├── gegl
├── install
└── gimp
```

```
git clone git@github.com:GNOME/gimp.git gimp
git clone https://gitlab.gnome.org/GNOME/gegl.git 3rd/gegl
git clone https://gitlab.gnome.org/GNOME/babl.git/ 3rd/babl
```

## 2. env
依赖组件默认使用系统源安装，仅当需要时再手动编译
```bash
sudo apt build-dep babl -y
sudo apt build-dep gegl -y
sudo apt build-dep gimp -y
# there are some missing deps, if you got more, see #more.deps-founding
sudo apt install libgtk-3-dev libappstream-glib-dev -y
```

## 3. build
### 3.1 build babl+gegl
babl is simple
```bash
meson setup mbuild  --buildtype=debug --prefix=`pwd`/../../install
ninja install -C mbuild/
```

gegl may need check a buildable branch
```bash
git switch GEGL_0_4_44
git branch GEGL_0_4_44
git checkout GEGL_0_4_44
# gegl docs building have got some error there
meson setup mbuild -Ddocs=false --buildtype=debug --prefix=`pwd`/../../install
ninja install -C mbuil
```
### 3.2 build gimp
</br>

pkg config file of babl may mismatch with gimp needs

`ln -s install/lib/x86_64-linux-gnu/pkgconfig/babl-0.1.pc install/lib/x86_64-linux-gnu/pkgconfig/babl.pc`

</br>

since we build GEGL_0_4_44, so we may adjust gimp version
```bash
git log|grep "depend on GEGL" -4
# found this 
# commit b85032d8b6bceb1114452bffb53754a65d977f50
# Author: Øyvind Kolås <pippin@gimp.org>
# Date:   Sun Nov 13 17:16:49 2022 +0100

#     meson, configure, app: depend on GEGL 0.4.40
git checkout b85032d8b6bceb1114452bffb53754a65d977f50
git branch gegl44
git switch gegl44
```
```bash
export PKG_CONFIG_PATH+=:/mnt/d/code/ln/gimp/install/lib/x86_64-linux-gnu/pkgconfig 
meson setup mbuild  --buildtype=debug --prefix=`pwd`/../install
```

## debug env
dont forgot install gdb `sudo apt install gdb`

this is a available launch.json config
note:
* *-enable-pretty-printing* is harmful for vscode debugger module

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "install/gimp-2.99",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/install/bin/gimp-2.99",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/install/bin",
            "environment": [
                {
                    "name": "LD_LIBRARY_PATH",
                    "value": ".:${workspaceFolder}/install/lib/x86_64-linux-gnu:$ENV{LD_LIBRARY_PATH}"
                }
            ],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                // this may lead to vscode failing to list var's member(GObject) on WATCH window
                // {
                //     "description": "Enable pretty-printing for gdb",
                //     "text": "-enable-pretty-printing",
                //     "ignoreFailures": true
                // },
                {
                    "description": "Set Disassembly Flavor to Intel",
                    "text": "-gdb-set disassembly-flavor intel",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

## appendix
### 1. display setting
wsl中调试图形程序需要x server, 使用 vcxsrv 或者 X410 均可

然后cli环境 `export DISPLAY=127.0.0.1:0` 即可 

注意本地环回地址貌似在wsl2中无法使用，需要获取windows的wsl虚拟网络适配器的网络地址