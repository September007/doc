---
title: xray 流量路径分析
category:
  - Linux
draft: true
url-root: xray 流量路径分析
date: 2024-02-25 00:43:56
tags:
---

## 外部流量入口
此处port=10001 可以切换成其他端口

然后所有这类流量先通过 dokodemo-door 通通传入38001
```json
{
  "inbounds": [
	{
	  "listen": "0.0.0.0",
	  "port": 10001,
	  "protocol": "dokodemo-door",
	  "settings": {
		"address": "127.0.0.1",
		"port": 38001,
		"network": "tcp",
		"followRedirect": false
	  }
	}
  ]
}
```
## 分流
此处fallbacks描述分流规则

* 默认回落流量到31296，一般无法解析的流量会分发给nginx，以隐藏xray的响应特征
* 满足TLS ALPN协商的走到31302
* 尝试匹配首包 HTTP PATH，成功走到31297 | 31299

```json
{
  "inbounds": [
    {
      "port": 38001,
        "fallbacks": [
          {
            "dest": 31296,
            "xver": 1
          },
          {
            "alpn": "h2",
            "dest": 31302,
            "xver": 0
          },
          {
            "path": "/path",
            "dest": 31297,
            "xver": 1
          }
        ]
...
  ]
}
```

# 