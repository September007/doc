
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