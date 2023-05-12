
# find rpath
 readelf  -d QTC |grep path

#  Each shared library in our dependencies is searched in the following locations, in order:

 *  Directories listed in the executable’s rpath.
 *  Directories in the LD_LIBRARY_PATH environment variable, which contains colon-separated list of directories (e.g., /path/to/libdir:/another/path)
 *  Directories listed in the executable’s runpath.
 *  The list of directories in the file /etc/ld.so.conf. This file can include other files, but it is basically a list of directories - one per line.
 *  Default system libraries - usually /lib and /usr/lib (skipped if compiled with -z nodefaultlib).


# rpath

## read rpath
 readelf -d lib1.so |grep path

## set rpath
 patchelf --set-rpath ".:$ORIGIN" lib1.so lib2.so 

# about \$ORIGIN

for rpath ".:$ORIGIN"
* "." mean start from cwd
* "$ORIGIN mean start from where the lib at

for example :
```text
    libQt5Core.so:
    dir: ~/Qt/lib
    deps: libicui18n.so.6
    rpath: $ORIGIN/../libicu

    libicui18n.so.6:
    dir: ~/Qt/libicu
    deps: libicudata.so.6
    rpath: .

    libicudata.so.6:
    dir:~/Qt/libicu

    app:
    dir: ~/apppath
    deps: libQt5Core.so
    rpath: ~/Qt5

so 
cd ~/apppath
./app
will say can not found libicudata.so.6, for libicui18n.so.6 even if in the same dir,
( of course out env var LD_LIBRARY_DIR assume be null)
the problem of RPATH of libicui18n.so.6 is : the dir . accutually is "~/apppath/." not "~/Qt/libicu/."
so the $ORIGIN for libicudata is "~/Qt/libicu", we just need to 
    set libicui18n.so.6 ::rpath="$ORIGIN" then it will successfully link
```