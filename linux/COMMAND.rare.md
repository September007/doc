
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