---
title: cpp foreach macro
category:
  - ["Topics","cpp"]
draft: false
url-root: cpp foreach macro
date: 2024-01-25 00:24:25
tags:
---

# showcase

1.  EqualToAnyOf
    ```cpp
    // 注意 递归单元
    EqualToAnyOf(3, 1, 2, 3); // 0 || (3 == 1) || (3 == 2) || (3 == 3) 
    ```
2.  MAKE\_ENUM
    ```cpp
    MAKE_ENUM(EE,"name_prefix",E1,E2,E3);
    // 展开到
    enum class EE {E1, E2,E3 };
    const char *GetStr(EE e)
    {g
        switch (e)
        {
        case EE::E1:
            return "name_prefix" "E1";
        case EE::E2:
            return "name_prefix" "E2";
        case EE::E3:
            return "name_prefix" "E3";
        default:
            return "name_prefix" "";
        }
    };
    ```

# 介绍

```cpp
// prototype
#define FOREACH(pps,...) ...
// acutually params 
#define FOREACH(pps,it_operator,...)
```

`pps`: 打包参数，形如 `(arg1)`, `(arg1,arg2)`
`it_operator`: 迭代宏函数，如此使用：`ite_operator(pps,it)`
`...`: 迭代参数集合，展开后作为 `ite_oprator`的最后一个参数

# 实现

## 辅助宏函数

1.  \_\_Choose20th
    ```cpp
    #define __Choose20th(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13,_14, _15, _16, _17, _18, _19, _20, ...) \
    _20
    ```

2.  ID
    **msvc默认的宏展开有一点区别于gcc like编译器，所以老是需要用ID去做展开**
    ```cpp
    #define ID(_1, ...) _1
    #define IDx(...) __VA_ARGS__
    ```

3.  `Callx` + `CallxPPS`

    ```cpp
    #define Callx(f, ...) IDx(f(__VA_ARGS__))
    #define CallxPPS(f, _1) IDx(f _1)
    ```

    两种形式的宏函数代理调用
    因为当我遇到 `MacroFunc(IDx pps, otherArgs)`时，外部套一层 `IDx`也无法使展开的`pps`作为分离参数传入`MacroFunc`

    感觉 ID只能辅助展开`__VA_ARGS__`,所以这里 ` Callx(MacroFunc, IDx pps, otherArgs)` 将所有参数压缩成变长参数之后再由 `Callx`重新展开

## 过程

OK, finally.

### Show me the code

```cpp
#define __Choose20th(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, ...) _20
#define ID(_1, ...) _1
#define IDx(...) __VA_ARGS__
#define Callx(f, ...) IDx(f(__VA_ARGS__))
#define CallxPPS(f, _1) IDx(f _1)

#define FOREACH0(it_operator, pps)
#define FOREACH1(it_operator, pps, _1) IDx(it_operator(pps, _1) FOREACH0(it_operator, pps))
#define FOREACH2(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH1(it_operator, pps, __VA_ARGS__))
#define FOREACH3(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH2(it_operator, pps, __VA_ARGS__))
#define FOREACH4(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH3(it_operator, pps, __VA_ARGS__))
#define FOREACH5(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH4(it_operator, pps, __VA_ARGS__))
#define FOREACH6(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH5(it_operator, pps, __VA_ARGS__))
#define FOREACH7(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH6(it_operator, pps, __VA_ARGS__))
#define FOREACH8(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH7(it_operator, pps, __VA_ARGS__))
#define FOREACH9(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH8(it_operator, pps, __VA_ARGS__))
#define FOREACH10(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH9(it_operator, pps, __VA_ARGS__))
#define FOREACH11(it_operator, pps, _1, ...) IDx(it_operator(pps, _1) FOREACH10(it_operator, pps, __VA_ARGS__))

```

## Use Case

1.  `EqualToAnyOf`

```cpp
#define __EqualToPlain(x, y) || (x == y)
#define __EqualToPacket(px, y) Callx(__EqualToPlain, IDx px, y)
#define EqualToAnyOf(val, ...) 0 FOREACH(__EqualToPacket, (val), __VA_ARGS__)
```

1.  `MAKE_ENUM`

```cpp
#define MAKE_ENUM_Declare(ClsName,...) enum class ClsName{__VA_ARGS__};
#define MAKE_ENUM_ITEM_Begin(ClsName) \
    const char *GetStr(ClsName e)     \
    {                                 \
        switch (e)                    \
        {
#define MAKE_ENUM_ITEM(ClsName, Prefix, name) \
    case ClsName::name:                       \
        return Prefix #name;
// #define MAKE_ENUM_ITEM_PPS(pps, item) CallxPPS( Callx,(MAKE_ENUM_ITEM, IDx pps, item))
#define MAKE_ENUM_ITEM_PPS(pps, item) Callx(MAKE_ENUM_ITEM, IDx pps, item)
#define MAKE_ENUM_ITEM_End(ClsName, Prefix) \
    default:                                \
        return Prefix "";                   \
        }                                   \
        }
#define MAKE_ENUM(ClsName, Prefix, ...)                               \
    MAKE_ENUM_Declare(ClsName, __VA_ARGS__)                           \
    MAKE_ENUM_ITEM_Begin(ClsName)                                     \
    IDx(FOREACH(MAKE_ENUM_ITEM_PPS, (ClsName, Prefix), __VA_ARGS__))  \
    MAKE_ENUM_ITEM_End(ClsName, Prefix);
```

# 附录

1.  检查 预处理器输出

​	即使是vs2022默认的智能感知引擎也无法在hover tip上正确显示预处理的结果，所以需要手动用编译器展开观察中间结果

```powershell
# MSVC	>> foreach_macro.i
while($true)
{
	cl /P foreach_macro.cpp
	sleep 1
}

# CLANG  >> stdout	(or append "-o foreach_macro.i")
while($true)
{
	clang -E foreach_macro.cpp
	sleep 1
}
```

