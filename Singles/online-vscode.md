---
title: online vscode
category:
  - IDE
draft: false
url-root: online-vscode
date: 2023-11-30 22:26:28
tags:
---

install code server on ubuntu
using vscode in browser

## install code server
```bash
sudo apt update
curl -fsSL https://code-server.dev/install.sh | sh
sudo apt install ~/Downloads/code-server_*_amd64.deb
# sudo systemctl enable --now code-server@$USER
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

### add autostart service
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


### xray forward
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


### enable SSL Certificate

1. using certbot to generate certs
```bash
sudo apt instal certbot
sudo certbot certonly --standalone -d www.yourdomain.com
# Successfully received certificate.
# Certificate is saved at: /etc/letsencrypt/live/www.yourdomain.com/fullchain.pem
# Key is saved at:         /etc/letsencrypt/live/www.yourdomain.com/privkey.pem
# This certificate expires on 2024-03-02.
# These files will be updated when the certificate renews.
```

2. change service to run as root
vim /etc/systemd/system/my-code-server.service
```config
[Unit]
Description=Code Server

[Service]
User=root
ExecStart=/usr/bin/code-server
Restart=always

[Install]
WantedBy=multi-user.target
```

3. change code-server config
```config
bind-addr: 0.0.0.0:8082
auth: password
log: debug
password: yourdomain
cert: /etc/letsencrypt/live/code.yourdomain.com/cert.pem
cert-key: /etc/letsencrypt/live/code.yourdomain.com/privkey.pem
```

4. restart service
```bash
sudo systemctl daemon-reload
sudo systemctl restart my-code-server.service
```


### enable SSL Certificate( as normal user)
1.
 same to [enable-ssl-certificate](#enable-ssl-certificate), generate keys first, note cerbot keep multi version keys for same domain name, see `ll /etc/letsencrypt/live/code.yourdomain.com/cert.pem`

2. copy cert files
```bash
# copy real cert file not symbolic link
sudo cp /etc/letsencrypt/live/code.yourdomain.com/ -rL .
sudo chown lull:lull code.yourdomain.com/*
```
3. change code-server config
vim ~/.config/code-server/config.yaml
note: **service started by system, run as user, so keep cert path as absolute** 
```yaml
bind-addr: 0.0.0.0:8082
auth: password
password: yourdomain
cert: /home/lull/.config/code-server/code.yourdomain.com/cert.pem
cert-key: /home/lull/.config/code-server/code.yourdomain.com/privkey.pem
```

4. revert service config to run as normal user
vim /etc/systemd/system/my-code-server.service

```config
[Service]
User=lull
```

5. restart service