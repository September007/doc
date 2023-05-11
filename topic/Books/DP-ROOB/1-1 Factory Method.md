
# Factory Method
 工厂方法指的是 *创建接口类实例的接口*
 工厂方法的核心在于 *将所依赖的接口的实例化延迟到 子类*
 
 框架使用抽象类定义和维护对象之间的关系，于是框架中的某些顶层抽象类 并没有 能够实例化 其所依赖的接口类的能力--所以该顶层抽象类只能将 *实例化 某些接口类* 的方法 委托给自己的子类（那些有足够信息的子类）去实现这些接口

## 实例
如下的 IMachine::CreateComps 就是 工厂方法，没有定义返回值或者没有参数影响创建结果并不影响这是 工厂方法（见CMaine:::CreateComps 直接影响到 compA 和 compB 成员不是一样的么）
```cpp
// 框架接口层
struct IComp{
    virtual void StartWork()=0;
};
struct IMachine{
    virtual void StartAllComps{
        CreateComps();
        compA->StartWork();
        compB->StartWork();
    }
    virtual void CreateComps()=0;
    private:
    IComp * compA,compB;
}

// 框架实现
struct CCompA:IComp{
    void StartWork()override{}
};
struct CCompB:IComp{
    void StartWork()override{}
};

struct CMachine:IMachine{
    virtual void CreateComps()override{
        compA = new CCompA;
        compB = new CCompB;
    }  
}
```
 另一方面，假如顶层抽象类有 对工厂方法的缺省实现，这个时候，工厂方法的存在就是对组件的扩展的支持---允许子类重载工厂方法

## 相关 设计模式

* 模版模式：工厂模式也像 模版模式，由顶层类定义一部分行为，将对象创建这个过程留待子类实现
* 抽象工厂方法：

## 延伸
### 连接平行类层次

当一个类将它的一些职责委托给一个独立的类的时候，就产生了平行类层次。考虑可以被交互操纵的图形；也就是说，它们可以用鼠标进行伸展、移动，或者旋转。实现这样一些交互并不总是那么容易，它通常需要存储和更新在给定时刻刻记录操纵状态的信息，这个状态仅仅在操纵时需要。因此它不需要被保存在图形对象中。此外，当用户操纵图形时，不同的图形有不同的行为。例如，将直线图形拉长可能会产生一个端点被移动的效果，而伸展正文图形则可能会改变行距。

有了这些限制，最好使用一个独立的 Manipulator 对象实现交互并保存所需要的任何与特定操纵相关的状态。不同的图形将使用不同的 Manipulator 子类来处理特定的交互。得到的 Manipulator 类层次与 Figure 类层次是平行（至少部分平行），如下图所示。

Figure 类提供了一个 CreateManipulator 工厂方法，它使得客户可以创建一个与 Figure 相对应的 Manipulator。Figure 子类重定义该方法以返回一个合适的 Manipulator 子类实例。做为一种选择，Figure 类可以实现 CreateManipulator 以返回一个默认的 Manipulator 实例，而 Figure 子类可以只是继承这个缺省实现。这样的 Figure 类不需要相应的 Manipulator 子类——因此该层次只是部分平行的。

注意工厂方法是怎样定义两个类层次之间的连接的。它将哪些类应一同工作工作的信息局部化了。