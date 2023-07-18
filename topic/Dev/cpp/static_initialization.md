---
title: 函数内静态变量初始化过程 (GCC)
category:
  - [Dev, cpp]
draft: false
url-root: static_initialization
date: 2023-06-21 19:33:40
tags:
---
```
 读一点汇编代码，早日升天
```

以前一直有个疑虑：函数内的静态变量初始化是否是线程安全的？
[Is C++ static member variable initialization thread-safe?](https://stackoverflow.com/questions/1962880/is-c-static-member-variable-initialization-thread-safe)

## source code
```cpp
#include <stdio.h>

struct XX
{
    XX(int d_) :
        d(d_)
    {
        printf("XX:XX()\n");
    }
    int d = 2;
};
XX& si()
{
    static XX x = { 10 };
    return x;
}
int main()
{
    si();
    auto& _again = si();
    *((unsigned char*)(&_again) + 8) = 0x0;
    auto& _again2 = si();
}
```
运行输出:（注意静态变量初始化了两次）
```bash
XX::XX()
XX::XX()
```
## 关闭线程安全
添加 gcc 编译选项 -fno-threadsafe-statics
这样可以去掉部分恼人的汇编

## si() 反汇编代码
反汇编结果来自 qtcreator,删除部分无关信息
```nasm
0x555555555149 endbr64
0x55555555514d push   %rbp
0x55555555514e mov    %rsp,%rbp
        14 [1]	    static XX x = { 10 };
0x555555555151  lea    0x2ec8(%rip),%rax
0x555555555158  movzbl (%rax),%eax
0x55555555515b  test   %al,%al
0x55555555515d  jne    0x55555555517d 
0x55555555515f  mov    $0xa,%esi
0x555555555164  lea    0x2ead(%rip),%rax
0x55555555516b  mov    %rax,%rdi
0x55555555516e  call   0x5555555551bc
0x555555555173  lea    0x2ea6(%rip),%rax
0x55555555517a  movb   $0x1,(%rax)
        15 [1]	    return x;
0x55555555517d 0x2e94(%rip),%rax 
        16 [1]	}
0x555555555184  <+   59>        5d                    pop    %rbp
0x555555555185  <+   60>        c3                    ret
```

注解：
```cpp
// 记录当前函数栈 基指针
0x55555555514d push   %rbp
0x55555555514e mov    %rsp,%rbp
        14 [1]	    static XX x = { 10 };
// *rax = 0x2ec8 + *rip  
// *eax = int32_t(*(uint8_t)rax)
// rip 记录下一行指令的地址，这个地址加上固定偏移，将指向某个绝对地址，这个地址存储着静态变量的守护变量
// 将其加载到 eax 寄存器中
0x555555555151  lea    0x2ec8(%rip),%rax
0x555555555158  movzbl (%rax),%eax
// al 是eax的低8位
// 这里 test 将 al的值做自与，计算结果影响cpu zero flag
// jne： jump if not zero flag
//  ！！！！ 如果静态变量guard 被设置了非零值，则此处跳过静态变量初始化指令，直接到达 下方的 return 点
0x55555555515b  test   %al,%al
0x55555555515d  jne    0x55555555517d 
// 0x2ead(%rip) 是静态变量地址
// 此处将类this指针压栈，并调用静态变量初始化构造
0x55555555515f  mov    $0xa,%esi
0x555555555164  lea    0x2ead(%rip),%rax
0x55555555516b  mov    %rax,%rdi
0x55555555516e  call   0x5555555551bc
// 完成初始化之后，写入初始化标志, 此处的 0x2ea6(%rip) 与之前的 0x2ec8(%rip)所指都是 静态变量xx的守护变量
0x555555555173  lea    0x2ea6(%rip),%rax
0x55555555517a  movb   $0x1,(%rax)
        15 [1]	    return x;
// 静态变量地址
0x55555555517d mov     0x2e94(%rip),%rax 
        16 [1]	}
0x555555555184  <+   59>        5d                    pop    %rbp
0x555555555185  <+   60>        c3                    ret
```

截至目前为止，我们已经可以理解 为什么前述的代码中静态变量会初始化两次，因为我们重置了 静态变量的守护变量

## 打开线程安全
去除  -fno-threadsafe-statics 编译标志

