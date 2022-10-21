
first call build.bash
then， the dir looks like
```bash
total 120
drwxrwxr-x 3 ws ws  4096  9月 28 09:51 ./
drwxrwxr-x 3 ws ws  4096  9月 27 21:34 ../
-rwxrwxr-x 1 ws ws 17256  9月 28 09:38 foo*
-rw-rw-r-- 1 ws ws   278  9月 28 09:38 foo.c
#
-rwxrwxr-x 1 ws ws 17256  9月 28 09:51 foo.g*
-rwxrwxr-x 1 ws ws  5872  9月 28 09:51 foo.g.debug*
-rwxrwxr-x 1 ws ws 15784  9月 28 09:51 foo.g.strip*
# 
-rwxrwxr-x 1 ws ws 15928  9月 28 09:51 foo.nog*
-rwxrwxr-x 1 ws ws  4544  9月 28 09:51 foo.nog.debug*
-rwxrwxr-x 1 ws ws 15784  9月 28 09:51 foo.nog.strip*

```
打开两个窗口

查看  可执行文件差异
注意 推荐使用vscode插件'Compare Helper' 查看文件差异

## diff foo.g.s foo.nog.s

```bash
diff foo.g.s foo.nog.s
# 输出格式： 
# <line of file1> c <line of file2>       
# '< ...'      multiline,content of file1
# '> ...'      multiline,content of file2
#        <line of file*> :<number> [, <number>]  , 表范围
```
 忽略文件头（名）差异，余下差异 （以section为单位）
1. .note.gnu.build-id

编译时命令 -Wl,--build-id=none 可以阻止生成此段
 测试之，
 gcc foo.c -o foo.o
 gcc foo.c  -Wl,--build-id=none -o foo.onow
 objdump -s foo.o >foo.o.s
 objdump -s foo.onow >foo.onow.sa
 然后 diff foo.o.s foo.onow.s 发现 foo.onow 确实缺少 section .note.gnu.build-id 

2. section debug*
...

## foo.g.debug

objdump -s foo.g.debug

发现 foo.g.debug 保留了 foo.g 里的debug相关段

## foo.g.strip

与 foo.g.debug 互补， 去掉了 foo.g 里的debug 相关段

## foo.g.strip-all [.with-debug-link] .s
objcopy --add-gnu-debuglink之后，文件多了 section .gnu_debuglink
添加 gnu-debuglink 之后，直接使用gdb调试时，不在需要显示指定 -s 符号文件 了
 测试：删除其他文件，仅保留vscode launch.json（记得配置参数）+ foo.c foo.g.debug foo.g.strip-all.with-debug-link，发起对应调试任务（"debug foo.g.strip-all.with-debug-link"）vscode依然能够停在断点 

 
