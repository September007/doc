
# iptable & filter
ref: [iptable cnblog](https://www.cnblogs.com/metoy/p/4320813.html)
## pre
![routings](https://images0.cnblogs.com/blog2015/569491/201503/071933304925554.png)

*tables comes form routings*
![tables](https://images0.cnblogs.com/blog2015/569491/201503/071934139309258.png)
规则表之间的优先顺序：

Raw——mangle——nat——filter
规则链之间的优先顺序（分三种情况）：

* 第一种情况：入站数据流向

从外界到达防火墙的数据包，先被PREROUTING规则链处理（是否修改数据包地址等），之后会进行路由选择（判断该数据包应该发往何处），如果数据包 的目标主机是防火墙本机（比如说Internet用户访问防火墙主机中的web服务器的数据包），那么内核将其传给INPUT链进行处理（决定是否允许通 过等），通过以后再交给系统上层的应用程序（比如Apache服务器）进行响应。

* 第二种情况：转发数据流向

来自外界的数据包到达防火墙后，首先被PREROUTING规则链处理，之后会进行路由选择，如果数据包的目标地址是其它外部地址（比如局域网用户通过网 关访问QQ站点的数据包），则内核将其传递给FORWARD链进行处理（是否转发或拦截），然后再交给POSTROUTING规则链（是否修改数据包的地 址等）进行处理。

* 第三种情况：出站数据流向

防火墙本机向外部地址发送的数据包（比如在防火墙主机中测试公网DNS服务器时），首先被OUTPUT规则链处理，之后进行路由选择，然后传递给POSTROUTING规则链（是否修改数据包的地址等）进行处理。

## 管理和设置iptables规则

![](https://images0.cnblogs.com/blog2015/569491/201503/071935158831919.jpg)
![](https://images0.cnblogs.com/blog2015/569491/201503/071936081026171.jpg)
