---
title: ffmpeg build on alpine
category:
 - [ Topics, ffmpeg]
draft: false
url-root: ffmpeg build on alpine
date: 2024-03-28 00:00:29
tags:
---

```bash
#!/bin/bash
CWD=$(pwd)
INSTALL_PATH=$CWD/install

check_repo(){
    woring_dir=$1
    dir=$2
    required_branch=$3
    repo_url=$4
    cd $woring_dir

    if [[ ! -d $dir ]];then
        git clone $repo_url $dir
    fi

    if [[ "$required_branch" != "" ]]; then
        echo "
            on $dir"
        cd $dir
        git checkout $required_branch
        git reset --hard
    fi
    cd $CWD
}

check_www(){
    woring_dir=$1
    dir=$2
    www_file=$3
    www_url=$4
    shift 4
    if_custom_commands=$@
    cd $woring_dir

    if [[ ! -f $www_file ]];then
        wget $www_url $www_file
    fi

    if [[ ! -d $dir ]]; then
        if [[ "$if_custom_commands" == "" ]]; then
            tar -xvf $www_file
        else
            $@
        fi
    fi
    cd $CWD
}

active_target=
set_target(){ 
    active_target=$1
    echo "
    activating $active_target"
}
check(){
    $@ >$CWD/build/logs/$active_target.log 2>$CWD/build/logs/$active_target.error.log
    retval=$?
    if [[ "$retval" != "0" ]];then
        echo "target $active_target: failed retval=$retval $@"
        exit $retval
    fi
}

##################################################
# 准备目录 #
mkdir -p $CWD/build/logs    2>/dev/null
rm       $CWD/build/logs/*  2>/dev/null
mkdir -p 3rd 2>/dev/null


###################################################
# 第三方库 #

# check_repo 3rd/x264         master  https://code.videolan.org/videolan/x264.git
check_repo 3rd libvpx       main                https://chromium.googlesource.com/webm/libvpx
check_www  3rd lame-3.100   lame-3.100.tar.gz   https://zenlayer.dl.sourceforge.net/project/lame/lame/3.100/lame-3.100.tar.gz

set_target libvpx
cd 3rd/libvpx
check ./configure --prefix=$INSTALL_PATH --enable-vp8 --enable-vp9 --enable-pic --disable-examples --disable-docs --enable-vp9-highbitdepth 
check make install -j
cd $CWD


set_target lame-3.100
cd 3rd/lame-3.100
check ./configure --prefix=$INSTALL_PATH --enable-shared=no
check make install -j
cd $CWD

##################################################
# ffmpeg # 
check_repo . ffmpeg   n6.1   https://github.com/FFmpeg/FFmpeg.git

set_target ffmpeg
export PKG_CONFIG_PATH=$CWD/install/lib/pkgconfig
cd ffmpeg
check ./configure \
    --prefix=$INSTALL_PATH \
    --extra-cflags=-I$CWD/install/include \
    --extra-ldflags=-L$CWD/install/lib \
    --enable-libvpx \
    --enable-libmp3lame
check make install -j
cd $CWD
```
