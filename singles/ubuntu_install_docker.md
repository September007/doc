---
title: ubuntu install docker
category:
  - [Singles]
draft: false
url-root: ubuntu_install_docker
date: 2024-03-27 23:43:18
tags:
---

## docker installation
```bash
for pkg in docker.io docker-doc docker-compose docker-compose-v2 podman-docker containerd runc; do sudo apt-get remove $pkg; done

# Add Docker's official GPG key:
sudo apt-get update
sudo apt-get install ca-certificates curl
sudo install -m 0755 -d /etc/apt/keyrings
sudo curl -fsSL https://download.docker.com/linux/ubuntu/gpg -o /etc/apt/keyrings/docker.asc
sudo chmod a+r /etc/apt/keyrings/docker.asc
# Add the repository to Apt sources:
echo   "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/ubuntu \
  $(. /etc/os-release && echo "$VERSION_CODENAME") stable" |   sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
```

## user config
```bash
usermod -aG docker lull
```

## pull alpine
even if docker hub shows no alpine 3.15
```bash
docker pull alpine:3.15
```
## create container
* -i: keep STDIN, 否则 docker start 直接退出，docker exec 也无效，非交互模式应该是在启动脚本里加入long live server
* -t: 创建伪终端，更好的cli交互体验
* --name alpine: 指定名字
* --publish-all: 公开端口
* -v /e:/e 共享挂载目录
* 
```bash
docker run -it --name alpine --publish-all -v /e:/e alpine:3.15
```

## run
start container if not yet
```bash
docker ps  |grep alpine || docker start alpine
```
run interactive ali
```bash
docker exec -it  alpine sh
```


## Appendix

running ssh service in these containers is a bit annoying

although you could just run 
```bash
apk add openssh
`which sshd`
```