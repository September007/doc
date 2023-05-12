
# qt6.4

[qt6 deps](https://doc.qt.io/qt-6/linux-requirements.html)

```bash
# 解压；创建构建目录（离源创建）；进入构建目录。假设当前下载的源码包为 qtsrc.tar.gz
tar -xvf qtsrc.tar.gz
mkdir build
cd build

# 安装依赖 缺失依赖配置也不一定失败，不过你会看见某一些目标不会再被构建，不被构建的原因会在输出里，请不要忽略configure的输出
# 最致命的是xcb不构建(这就需要你去配置其他来源的 qpa：qt platform abstraction，要是构建环境不一样，你可能会遇见运行时glibcxx**找不着哈哈哈)
sudo apt update && sudo apt upgrade && sudo apt install -y libfontconfig1-dev  libfreetype6-dev  libx11-dev  libx11-xcb-dev  libxext-dev  libxfixes-dev  libxi-dev  libxrender-dev  libxcb1-dev  libxcb-glx0-dev  libxcb-keysyms1-dev  libxcb-image0-dev  libxcb-shm0-dev  libxcb-icccm4-dev  libxcb-sync-dev  libxcb-xfixes0-dev  libxcb-shape0-dev  libxcb-randr0-dev  libxcb-render-util0-dev  libxcb-util-dev  libxcb-xinerama0-dev  libxcb-xkb-dev  libxkbcommon-dev  libxkbcommon-x11-dev

# 配置cmake，事实上这个configure会转换成cmake的命令，你可以在configure的输出里看见转换的cmake命令，多是一些宏定义
../configure -nomake examples  -nomake tests -opensource  -c++std c++11 -skip qtwebengine -skip qt3d -skip qt3d  -skip qtcharts -skip qtcoap -skip qtconnectivity   -skip qtdatavis3d -skip qtdoc -skip qtlottie -skip qtmqtt -skip qtnetworkauth -skip qtopcua   -skip qtserialport -skip qtpositioning -skip qtquicktimeline -skip qtquick3d -skip qtremoteobjects   -skip qtsensors -skip qtserialbus -skip qtvirtualkeyboard -skip qtwayland   -skip qtwebchannel -skip qtwebengine -skip qtwebview -skip qtquick3dphysics -skip qtspeech -skip qtlocation   -skip qthttpserver -skip qsb  -skip qtscxml -skip qtmultimedia -xcb -xcb-xlib  -feature-xkbcommon -feature-xkbcommon-x11 -- -DQT_FEATURE_xkbcommon_x11=on 

# 编译，-j指定线程数
cmake --build . -j16
# 安装到 某个路径 ， 我将其安装到pack路径
cmake --install . -prefix pack

# 你可以任意移动pack目录, 假设当前pack目录在 /usr/local/qt6-pack
# 可以在 cmake 中这样使用qt

```

# qt5.12.8

[qt5 deps](https://doc.qt.io/qt-5/linux-requirements.html)

```bash
# 依赖
sudo apt update && sudo apt upgrade && sudo apt install -y libfontconfig1-dev  libfreetype6-dev  libx11-dev  libx11-xcb-dev  libxext-dev  libxfixes-dev  libxi-dev  libxrender-dev  libxcb1-dev  libxcb-glx0-dev  libxcb-keysyms1-dev  libxcb-image0-dev  libxcb-shm0-dev  libxcb-icccm4-dev  libxcb-sync0-dev  libxcb-xfixes0-dev  libxcb-shape0-dev  libxcb-randr0-dev  libxcb-render-util0-dev  libxcb-xinerama0-dev  libxkbcommon-dev  libxkbcommon-x11-dev

# 因为不知道gmake如何指定安装路径，而且我看gmake的makfile里的安装路径都写死了（不知道gmake有没有其他的generator），所以需要在 configure阶段写明 安装路径
../configure -nomake examples  -nomake tests -opensource  -c++std c++11 -skip qtwebengine -skip qt3d -skip qt3d  -skip qtcharts  -skip qtconnectivity   -skip qtdatavis3d -skip qtdoc  -skip qtnetworkauth   -skip qtserialport  -skip qtremoteobjects   -skip qtsensors -skip qtserialbus -skip qtvirtualkeyboard -skip qtwayland   -skip qtwebchannel -skip qtwebengine -skip qtwebview  -skip qtspeech -skip qtlocation    -skip qtscxml -skip qtmultimedia -xcb -xcb-xlib  -feature-xkbcommon  
-prefix pack

gmake -j16
gmake install

```


# QTCreator
see its readme

1. download src
https://download.qt.io/official_releases/qtcreator/8.0/8.0.1/qt-creator-opensource-src-8.0.1.tar.gz

2. goto line57 'Linux and macOS'

qt path指定qt pack路径