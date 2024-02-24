---
title: ubuntu 磁盘占用过高
category:
  - Linux
draft: false
url-root: disks_full
date: 2024-02-23 23:50:53
tags:
---

## 磁盘占用工具 ncdu
左右键进出目录
```bash
sudo apt install ncdu
sudo su
cd /
ncdu
#  15.2 GiB [##########] /var                                                                                                                                                         
#   6.7 GiB [####      ] /home
#   5.0 GiB [###       ] /usr
#   4.0 GiB [##        ] /root
#   1.7 GiB [#         ] /lib
```

## 处理
```bash
# 1. 额外用户xxx
sudo deluser xxx; sudo rm -r /home/xxx
# 2. 清除root账户vscode缓存
sudo rm /root/.vscode-server -r; sudo rm /root/.vscode-server-insiders -r
```
### /var
```log
--- /var ----------------------------
    8.9 GiB [##########] /log
    5.5 GiB [######    ] /lib                                                                                                                                                         
  723.0 MiB [          ] /cache
    3.3 MiB [          ] /backups
   32.0 KiB [          ] /tmp
   32.0 KiB [          ] /spool
   28.0 KiB [          ] /snap
e   4.0 KiB [          ] /opt
e   4.0 KiB [          ] /mail
e   4.0 KiB [          ] /local
@   0.0   B [          ]  lock
@   0.0   B [          ]  run
```

#### /var/log
编辑 `/etc/logrotate.conf`: rotate 属性默认2
编辑 `/etc/logrotate.d/rsyslog`: 添加 属性 size 100k
编辑 `/etc/systemd/journald.conf`限制journal 大小: SystemMaxUse=100M
删除docker服务: `sudo service docker stop;sudo apt remove docker; sudo apt autoremove; rm /var/log`

<!-- 手动执行logrotate: `logrotate /etc/logrotate.conf` -->

至此，37.8G-->22.3G, 懒得动手了
