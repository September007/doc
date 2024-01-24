---
title: Code Style
category:
  - uncategorized
draft: true
typora-root-url: Code Style
date: 2023-05-18 21:31:55
tags:
---

  代码风格苦我久矣

### Names and Order of Includes
Include headers in the following order: Related header, C system headers, C++ standard library headers, other libraries' headers, your project's headers.
```cpp
// gtest-printers.cc

#include "gtest/gtest-printers.h"

#include <stdio.h>

#include <cctype>
#include <cstdint>
#include <cwchar>
#include <iomanip>
#include <ios>
#include <ostream>  // NOLINT
#include <string>
#include <type_traits>

#include "gtest/internal/gtest-port.h"
#include "src/gtest-internal-inl.h"
```

## Local Variables
Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.
```cpp

int jobs = NumJobs();
// More code...
f(jobs);      // Bad -- declaration separate from use.

int jobs = NumJobs();
f(jobs);      // Good -- declaration immediately (or closely) followed by use.
```

## Decision on initialization ( 静态变量 )
核心就是 最好是 constexpr 初始化；或者不依赖其他static var的动态初始化

```cpp

int n = 5;    // Fine
int m = f();  // ? (Depends on f)
Foo x;        // ? (Depends on Foo::Foo)
Bar y = g();  // ? (Depends on g and on Bar::Bar)

int p = getpid();  // Allowed, as long as no other static variable
                   // uses p in its own initialization.
```
my style
```cpp
extern "C" Type * Instance(){
  static Type * ins =0;
  static std::mutex lock_ins;

  if(ins == 0){
    std::unique_lock _(lock_ins);
    if(!ins)
       ins = new Type(...);
  }
  return ins;
}

```


## tips
* no inline namespace ( only for huge complex project version control )
*    inline function  ( only for code less then 10 lines )
* Prefer placing nonmember functions in a namespace; use completely global functions rarely. Do not use a class simply to group static members. Static methods of a class should generally be closely related to instances of the class or the class's static data.
* Do not define implicit conversions. Use the explicit keyword for conversion operators and single-argument constructors.
* 
