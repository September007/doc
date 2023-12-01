---
title: doc/topic/IDE/vscode/code-server
category:
  - uncategorized
draft: true
url-root: doc/topic/IDE/vscode/code-server
date: 2023-11-30 22:26:28
tags:
---

# online vscode

install code server on ubuntu
using vscode in browser

## install code server
```bash
sudo apt update
curl -fsSL https://code-server.dev/install.sh | sh
sudo apt install ~/Downloads/code-server_*_amd64.deb
sudo systemctl enable --now code-server@$USER
```

## config code server
配置文件 ~/.config/code-server/config.yaml
密码是你登录时需要输入的
```yaml
bind-addr: 0.0.0.0:8082
auth: password
password: xxxyyy # your customed password
```

## check running
on one terminal, just type `code-server`, it will automatically using config file listed above
on another terminal, type 
```bash
curl http://localhost:8082 # ok if local-machine alright
curl http://xx.xx.ipv4:8082 # if failed, need check firewall settings
```


# more

## add autostart service
edit service file `/etc/systemd/system/my-code-server.service`
```config
[Unit]
Description=Code Server

[Service]
User=lull
ExecStart=/usr/bin/code-server
Restart=always

[Install]
WantedBy=multi-user.target

```
start service: `sudo systemctl start my-code-server`
set autostart: `sudo systemctl enable my-code-server`

## xray forward
add xray config file `xray-rootdir/conf/99_code-server.json`
this wil redirect incoming 0.0.0.0:7401 into localhost:8082
```json
{
	"inbounds": [
	  {
		"listen": "0.0.0.0",
		"port": 7401,
		"protocol": "dokodemo-door",
		"settings": {
		  "network": "tcp",
		  "address": "127.0.0.1",
		  "port": 8082,
		  "followRedirect": false
		},
		"sniffing": {
		  "enabled": true,
		  "destOverride": ["http", "tls"]
		}
	  }
	],
	"outbounds": [
	  {
		"protocol": "freedom",
		"settings": {},
		"tag": "direct"
	  },
	  {
		"protocol": "blackhole",
		"settings": {},
		"tag": "blocked"
	  }
	],
	"routing": {
	  "rules": [
		{
		  "type": "field",
		  "ip": ["0.0.0.0/0"],
		  "outboundTag": "direct"
		}
	  ]
	}
  }
  
```