---
categories: 
 - [ "Topics", "CLI" ]
title: "common cli"
date: 2023-02-15T10:01:03+08:00
draft: false
include_toc: true
---
# find

正则查找
find <path> -regex "<>"

忽略大小写查找文件
find -iname ***

# 符号查找

静态库
nm libxvidcore.a
-n: sort
-u undefined-only


# 剪贴板 xclip
复制内容到剪贴板
echo "hello xclip" | xclip -selection c

建立别名
alias clip="xclip -selection c"

# 版本管理 update-alternatives
[update-alternatives](https://www.jianshu.com/p/4d27fa2dce86)
```bash
#命令最后的1和10是优先级，如果使用auto选择模式，系统将默认使用优先级高的
#假设只安装了GCC/G++ 7和11版本
sudo update-alternatives --remove-all gcc
sudo update-alternatives --remove-all g++
 
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 1
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10
 
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 1
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10
```
# 忽略输出
startkde  >/dev/null 2>&1

# Install Specific Package Version With Apt Command in Ubuntu

sudo apt install package_name=package_version


# add user to sudo group
usermod -G sudo lull

## check groups
cat /etc/group

## if not in the sudoers file
https://blog.csdn.net/weixin_49192027/article/details/114702099

添加文件
/etc/sudoers.d/lull
```text
lull ALL=(root,lull) ALL
```

# Ubuntu-18.04 install GCC11
[link](https://blog.csdn.net/tytyvyibijk/article/details/123074333)
```bash
add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt update
sudo apt install gcc-11 g++-11

#使用locate命令比find快一些，使用前最好更新一下索引
sudo updatedb && sudo ldconfig
locate gcc | grep -E "/usr/bin/gcc-"
#如果locate不能用
ls /usr/bin/gcc*
ls /usr/bin/g++*

#命令最后的1和10是优先级，如果使用auto选择模式，系统将默认使用优先级高的
#假设只安装了GCC/G++ 7和11版本
sudo update-alternatives --remove-all gcc
sudo update-alternatives --remove-all g++
 
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 1
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 10
 
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-7 1
sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 10

gcc --version
 
g++ --version
```


# 处理wsl与windows的code冲突

原生code使用wsl的code
```bash
# ~/.profile
alias code=/usr/bin/code
# 使用软链接使用windows code, 
ln -s "/mnt/c/Users/lull/AppData/Local/Programs/Microsoft VS Code/bin/code" wcode
```