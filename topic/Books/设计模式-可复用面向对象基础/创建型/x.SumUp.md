---
title: 创建型 Sum Up
category:
 - [ Books,设计模式-可复用面向对象基础, 创建型]
draft: false
typora-root-url: 'x. Sum Up'
date: 2023-05-15 23:02:10
tags:
---

### 1. 实现的Hook
 这几个模式里，或多或少都跟 接口有关，这使得我们可以把一部分工作 委托给子类去实现。
 这一点我们会在后边的 诸如桥模式、模版模式等中再次见到

  *善用接口*
### 2. 隐藏可变部分
 隐藏 可变的部分或者可能会变化的部分，可以提供更安全的接口和更简单的环境去 更改实现
 
## Builder 模式

核心在于 隐藏 复杂对象创建过程过程中的细节
Builder 隐藏了 ComplicatedObj的创建细节。
```cpp
struct ComplicatedObj;
class Builder{
    ComplicatedObj * obj;
    Builder();

    virtual void AddInt(int i);
    virtual void AddFloat(double f);
    virtual ComplicatedObj * GetObj();
}
struct ComplicatedObj{
    std::vector<std::variant<int,char *>> comps;
};

// ... .cpp
struct ComplicatedObj{
    std::vector<std::variant<int,double>> comps;
};

Builder::Builder{
    obj = new ComplicatedObj;
}
Builder::AddInt(int i){
    obj->comps.push_back(i);
}
Builder::AddFloat(double f){
    obj->comps.push_back(f);
}
Builder::GetObj(){
    auto ret = obj;
    obj = 0;
    return ret;
}
```