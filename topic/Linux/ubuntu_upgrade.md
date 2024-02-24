---
title: ubuntu 升级操作系统
category:
  - Linux
draft: false
url-root: ubuntu 升级操作系统
date: 2024-02-24 00:29:51
tags:
---

```bash
# 更新当前包
sudo apt update; sudo apt upgrade -y
sudo apt dist-upgrade
sudo apt autoremove

sudo apt install update-manager-core

# reboot

sudo do-release-upgrade --check-dist-upgrade-only -d
sudo do-release-upgrade -d
```