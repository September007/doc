# ashe

## linux

1. 虚拟机配置两张虚拟网卡时，一张NAT，一张桥接，建议先打开NAT，再打开桥接，如果不是，可以先关闭桥接，再打开桥接，这样可以使NAT作为首选网卡

### ssh

1. 虚拟机安装ssh客户端 sudo apt install openssh-server
2. 修改ssh服务器配置
```cpp
/etc/ssh/sshd_config
Port 2222
PermitRootLogin yes
```
3. 打开开机自启 sudo systemctl enable ssh
4. 手动打开 ssh服务 sudo service ssh start
5. 测试 虚拟机自己的ssh连接 ssh localhost,this should work
6. 关闭虚拟机防火墙（懒得配置出站规则） sudo systemctl stop firewalld

7. win新建入站规则  click key_win，then new rule:(port 2222) ...
8. win测试连接：先在 linux 查看桥接网卡ip: ip addr,然后win 下powershell: ssh ${linux user name}@${上步查到的地址} -p 2222

vscode连接之

1. 要求安装插件 Remote-SSH
2. 打开状态栏的远程主机（没有就右键状态栏打开它呀），点击 Connect to host，点击 Add New SSH Host，输入ssh连接命令（这个命令同之前powershell里输入的连接命令一样）,回车
3. 选择保存ssh配置的文件，我保存在win下~/.ssh/config，这里可以修改Host（不是Host name）（因为可能会有同ip俩不同用户的ssh连接）
4. 再次点击打开状态栏的远程主机（没有就右键状态栏打开它呀，没有就奇怪了），点击某ssh连接配置，ok
5. 新的vscode让你选择远程主机的平台，大概这个教程是让配的linux？
6. 然后输入密码, 此处若是连接的root用户，那么你可能需要检查root的密码，或者重设root密码，不要老怀疑密码输对了是不是ssh的锅
7. 成功的标志是右下角的远程主机块 显示 SSH:${ssh配置的Host名}
8. ctrl+shift+E 打开文件管理器，当然你点击也行，打开某目录，操作起来！
   
# ashes opengl 

1. gitignore 写 /build只忽视当前路径下build文件夹，但是build会忽视所有名为build的文件夹，包括子路径
2. 片段着色器，它需要一个vec4颜色输出变量，因为片段着色器需要生成一个最终输出的颜色。如果你在片段着色器没有定义输出颜色，OpenGL会把你的物体渲染为黑色（或白色）
3. vetices数组里, 两个 float属性值 中间没有逗号分割也是可以通过的，应为第二个可能是负数表示
4. glUniform4fv is for array,not for vec, follow pe1 get GL_INVALID_OPERATION

```cpp
//in shader : uniform vec4 offset
    GLfloat offset[]={sinf(tm)/4,cosf(tm)/4,0,0};
    glUseProgram(program.getProgram());

    auto uniforms=program.getUniforms();
    auto p=program.getUniformLocation("offset");
    auto pe=glGetError();

    glUniform4fv(p,1,offset);
    auto pe1=glGetError();
    GL_INVALID_OPERATION;
   // glUniform4f(p,sinf(tm)/4,cosf(tm)/4,0,0);
```

5. 一个常见的错误是，将放大过滤的选项设置为多级渐远纹理过滤选项之一。这样没有任何效果，因为多级渐远纹理主要是使用在纹理被缩小的情况下的：纹理放大不会使用多级渐远纹理，为放大过滤设置多级渐远纹理的选项会产生一个GL_INVALID_ENUM错误代码
6. 解绑VAO、VBO、EBO时，先解绑VAO
7. // 不要忘记在设置uniform变量之前激活着色器程序！
8. glUniform1i 这种函数如果给定的第一个参数是-1，即想要设置的变量未找到，这个函数不会设置全局的错误信息（通过glGetError（）获取），默认其变量被优化啦
9. glTexImage2D 设置图片格式参数要小心，如果是RGBA的图像被设置为RGB的格式就会出现显示错误，试试就知道咯



## linux

1. 分区使用gparted
2. 开机自启    systemctl service *** start
