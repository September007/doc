
# QT6.4
```bash
# 1. 安装依赖
sudo apt install bison build-essential clang flex gperf \
libatspi2.0-dev libbluetooth-dev libclang-dev libcups2-dev libdrm-dev \
libegl1-mesa-dev libfontconfig1-dev libfreetype6-dev \
libgstreamer1.0-dev libhunspell-dev libnss3-dev libopengl-dev \
libpulse-dev libssl-dev libts-dev libx11-dev libx11-xcb-dev \
libxcb-glx0-dev libxcb-icccm4-dev libxcb-image0-dev \
libxcb-keysyms1-dev libxcb-randr0-dev libxcb-render-util0-dev \
libxcb-shape0-dev libxcb-shm0-dev libxcb-sync-dev libxcb-util-dev \
libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-xkb-dev libxcb1-dev \
libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev \
libxfixes-dev libxi-dev libxkbcommon-dev libxkbcommon-x11-dev \
libxkbfile-dev libxrandr-dev libxrender-dev libxshmfence-dev \
libxshmfence1 llvm ninja-build nodejs python2

# 2. download

https://download.qt.io/official_releases/qt/6.4/6.4.0/single/qt-everywhere-src-6.4.0.tar.xz

# 3. configure 

mkdir build
cd build
../configure -prefix /usr/local/Qt6
# 4. build
cmake --build . -j8

# 5. 安装
# 在build路径下 
sudo cmake --install .
```

# QTCreator
see its readme

1. download src
https://download.qt.io/official_releases/qtcreator/8.0/8.0.1/qt-creator-opensource-src-8.0.1.tar.gz

2. goto line57 'Linux and macOS'

qt path就是之前指定的prefix即/usr/local/Qt6
