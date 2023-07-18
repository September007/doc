
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

# package
总是假定用户lull,root

* sudoers: [cnblog](https://www.cnblogs.com/yanling-coder/p/10947157.html)


## check groups
cat /etc/group

## add user to sudo group
usermod -G sudo lull

## fixs

#### is not in the sudoers file
https://blog.csdn.net/weixin_49192027/article/details/114702099

添加文件
/etc/sudoers.d/lull
```text
lull ALL=(root,lull) ALL
```

# Install Specific Package Version With Apt Command in Ubuntu

sudo apt install package_name=package_version

