# ashe

## linux

1. 虚拟机配置两张虚拟网卡时，一张NAT，一张桥接，建议先打开NAT，再打开桥接，如果不是，可以先关闭桥接，再打开桥接，这样可以使NAT作为首选网卡

### ssh

1. 虚拟机安装ssh客户端 sudo apt install openssh-server
2. 修改ssh服务器配置
```cpp
/etc/ssh/sshd_config
Port 2222
PermitRootLogin yes
```
3. 打开开机自启 sudo systemctl enable ssh
4. 手动打开 ssh服务 sudo service ssh start
5. 测试 虚拟机自己的ssh连接 ssh localhost,this should work
6. 关闭虚拟机防火墙（懒得配置出站规则） sudo systemctl stop firewalld

7. win新建入站规则  click key_win，then new rule:(port 2222) ...
8. win测试连接：先在 linux 查看桥接网卡ip: ip addr,然后win 下powershell: ssh ${linux user name}@${上步查到的地址} -p 2222

vscode连接之

1. 要求安装插件 Remote-SSH
2. 打开状态栏的远程主机（没有就右键状态栏打开它呀），点击 Connect to host，点击 Add New SSH Host，输入ssh连接命令（这个命令同之前powershell里输入的连接命令一样）,回车
3. 选择保存ssh配置的文件，我保存在win下~/.ssh/config，这里可以修改Host（不是Host name）（因为可能会有同ip俩不同用户的ssh连接）
4. 再次点击打开状态栏的远程主机（没有就右键状态栏打开它呀，没有就奇怪了），点击某ssh连接配置，ok
5. 新的vscode让你选择远程主机的平台，大概这个教程是让配的linux？
6. 然后输入密码, 此处若是连接的root用户，那么你可能需要检查root的密码，或者重设root密码，不要老怀疑密码输对了是不是ssh的锅
7. 成功的标志是右下角的远程主机块 显示 SSH:${ssh配置的Host名}
8. ctrl+shift+E 打开文件管理器，当然你点击也行，打开某目录，操作起来！
   
   