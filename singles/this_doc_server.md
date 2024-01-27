---
categories: 
  - [Singles]
title: "Hugo + nginx + domain: this doc server"
date: 2023-01-29T11:57:48+08:00
draft: false
include_toc: true
---

# deps
* hugo: transformating markdown file to static-site html
* nginx: handle https request

# keys

## hugo

### config.toml

https://gohugo.io/getting-started/configuration/#all-configuration-settings
```toml
baseURL = 'https://www.353546.online:80/doc/'
languageCode = 'zh-cn'
title = "lull's doc"
theme = 'book'

[[cascade]]
categories  = ["default cate"]
```

### themes under ./themes
the most important thing theme provide is content&arche template 
    the difference between content-template & arche template: arche is for front matters of a new file; content-template is for rendering files

## nginx

/etc/nginx/conf.d/default.conf
```conf
server {
   listen       80 ssl;
   server_name  www.353546.online;
   ssl_protocols       TLSv1 TLSv1.1 TLSv1.2;
   ssl_ciphers         HIGH:!aNULL:!MD5;
   ssl_certificate  /etc/letsencrypt/live/www.353546.online/fullchain.pem;
   ssl_certificate_key /etc/letsencrypt/live/www.353546.online/privkey.pem;
    # listen        80;
    # server_name   www.353546.online;

    #access_log  /var/log/nginx/host.access.log  main;

    location / {
        root /home/lull/code/doc-site/public/;
        index tags/index.html tags/index.xml;
    }
    location /doc/ {
        alias /home/lull/code/doc-site/public/;
    }

    #error_page  404              /404.html;

    # redirect server error pages to the static page /50x.html
    #
    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}
```

### ssl
cert file comes from https://certbot.eff.org/ (from doc of https://letsencrypt.org/)
just use the certbot from ubuntu apt source
*notice* : you need a domain
the nginx ssl conf keys: ssl_certificate;ssl_certificate_key are 

see https://www.digitalocean.com/community/tutorials/how-to-use-certbot-standalone-mode-to-retrieve-let-s-encrypt-ssl-certificates-on-ubuntu-20-04
```text
privkey.pem: This is the private key for the certificate. This needs to be kept safe and secret, which is why most of the /etc/letsencrypt directory has very restrictive permissions and is accessible by only the root user. Most software configuration will refer to this as something similar to ssl-certificate-key or ssl-certificate-key-file.
fullchain.pem: This is our certificate, bundled with all intermediate certificates. Most software will use this file for the actual certificate, and will refer to it in their configuration with a name like ‘ssl-certificate’.
```

