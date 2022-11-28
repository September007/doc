# ashe

## linux

1. 虚拟机配置两张虚拟网卡时，一张NAT，一张桥接，建议先打开NAT，再打开桥接，如果不是，可以先关闭桥接，再打开桥接，这样可以使NAT作为首选网卡


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
