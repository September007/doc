---
title: server init
category:
  - Linux
draft: false
url-root: init
date: 2024-02-24 21:25:59
tags:
---
最近重装了服务器，记录以下重装的操作
## 创建用户lull
```bash
sudo su
adduser lull
# 添加到sudo组以使用sudo命令，就不要手动更改sudoers了
usermod -aG sudo lull
```

## 配置SSH登录选项
```bash
mkdir ~/.ssh
# 查看本地公钥 cat ~/.ssh/id_rsa.pub
echo "xxxxx
" >> ~/.ssh/authorized_keys

# 禁止密码登录
# vim /etc/sshd_config
# change properties: 
# PasswordAuthentication no
```

## xrrraay
```bash
# 安装nginx
apt install nginx
# 安装xray
bash -c "$(curl -L https://github.com/XTLS/Xray-install/raw/main/install-release.sh)" @ install
# xray默认用户nobody污染权限
chmod 777 /var/log/xray -r

## 更改xray服务配置 /etc/systemd/system/xray.service.d/10-donot_touch_single_conf.conf
## 添加xray出入口配置文件
## 更改nginx 配置文件

systemctl enable nginx.service
systemctl enable xray.service
```

## node (非系统版本)
nvm 是node版本管理工具
```bash
curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.35.3/install.sh | bash
nvm install --lts
```

## 文档服务器：编译
```bash
sudo mkdir /code
sudo chmod 777 /code

git clone git@github.com:September007/doc-site-hexo.git
cd doc-site-hexo
git submodule update --init --recursive

npm install -g hexo
npm i
hexo g;hexo g; hexo g;

```

## 文档服务器：部署

# certbot生成证书
```bash
sudo apt instal certbot
sudo certbot certonly --standalone -d www.cheerlisten.com
# Successfully received certificate.
# Certificate is saved at: /etc/letsencrypt/live/www.cheerlisten.com/fullchain.pem
# Key is saved at:         /etc/letsencrypt/live/www.cheerlisten.com/privkey.pem
# This certificate expires on 2024-03-02.
# These files will be updated when the certificate renews.
```

服务器配置 `/etc/nginx/conf.d/all/doc-server.conf`
nginx 服务器配置
`sudo ln -s  /etc/nginx/conf.d/all/doc-server.conf /etc/nginx/conf.d/`
```ini
server {
    listen       443 ssl;
    server_name  www.cheerlisten.com;
    ssl_protocols       TLSv1 TLSv1.1 TLSv1.2;
    ssl_ciphers         HIGH:!aNULL:!MD5;
    ssl_certificate /etc/letsencrypt/live/www.cheerlisten.com/fullchain.pem; # managed by Certbot
    ssl_certificate_key     /etc/letsencrypt/live/www.cheerlisten.com/privkey.pem; # managed by Certbot

    location / {
        root /code/doc-site-hexo/public/;
        index index.html tags/index.xml index.xml;
    }
    location /doc/ {
        alias /code/doc-site-hexo/public/;
        index tags/index.html tags/index.xml index.html index.xml;
    }

    #error_page  404              /404.html;

    # redirect server error pages to the static page /50x.html
    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}

```



## 杂项

更改设备名
```bash
sudo echo "LiteServer-ALiYun" > /etc/hostname
```
fix certbot dep urllib error: `pip install -U 'requests-toolbelt>=1'`
