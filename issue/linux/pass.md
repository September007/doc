总是假定用户lull,root

* sudoers: [cnblog](https://www.cnblogs.com/yanling-coder/p/10947157.html)


# check groups
cat /etc/group

# add user to sudo group
usermod -G sudo lull

# fixs

## is not in the sudoers file
https://blog.csdn.net/weixin_49192027/article/details/114702099

添加文件
/etc/sudoers.d/lull
```text
lull ALL=(root,lull) ALL
```
