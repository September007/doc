---
categories: 
 - CLI
title: "Vsftpd"
date: 2023-03-01T17:16:09+08:00
draft: false
include_toc: true
---

# config vsftp

```txt
# Standalone mode
listen=YES
max_clients=200
max_per_ip=4
# Access rights
anonymous_enable=YES
local_enable=YES
write_enable=YES
anon_upload_enable=YES
anon_mkdir_write_enable=NO
anon_other_write_enable=NO
# Security
anon_world_readable_only=NO
connect_from_port_20=YES
hide_ids=YES
pasv_min_port=50000
pasv_max_port=60000
# Features
xferlog_enable=YES
ls_recurse_enable=NO
ascii_download_enable=NO
async_abor_enable=YES
# Performance
one_process_model=NO
idle_session_timeout=120
data_connection_timeout=300
accept_timeout=60
connect_timeout=60
anon_max_rate=50000
anon_mkdir_write_enable=NO
anon_other_write_enable=NO
download_enable=YES

local_umask=000
chroot_local_user=YES
local_root=/home/ftp/$USER
user_sub_token=$USER
```