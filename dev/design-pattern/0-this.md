---
categories: ["default cate"]
title: "设计模式"
date: 2023-04-24
draft: true
include_toc: true
---

## 1. 单例

[source](1.singleleton.h)

通过控制对象 构造函数的 可访问性，制止外部创建对象。可数（唯一）的对象由指定的途径（一般是类静态方法，也可以是某些friend）创建并提供访问

## 2. 工厂

[source](2.Factory.h)

由某一个接口提供一类对象的创建

## 3. 抽象工厂

[source](3.abstract_factory.h)

将 [工厂](#2-工厂) 中的接口 抽象化，提供对 多个族 类型对象的 统一接口

## 4. 模板

[source](4.template.h)

抽象父类提供算法框架，而将一些步骤延迟到子类中实现 

## 5. 建造者模式

和 4 大同小异, 模板着重于 封装某个过程框架 ;建造者封装 创建过程

## 6. 代理模式

没有想到应用场景, 大致就是 通过访问同继承树上的兄弟族类 达到代理的效果

## 7. 