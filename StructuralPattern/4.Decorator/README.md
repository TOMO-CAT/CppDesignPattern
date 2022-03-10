# 装饰模式（Decorator）

## 别名

装饰者模式（Wrapper）。

## 定义

装饰是一种结构型设计模式，允许你通过将对象放入包含行为的特殊封装对象中来为原对象绑定新的行为。

## 前言

#### 1. 问题

假设你正在开发一个提供通知功能的库，其他程序可使用它向用户发送关于重要事件的通知。

库的最初版本基于通知器Notifier 类，其中只有很少的几个成员变量，一个构造函数和一个send 发送方法。该方法可以接收来自客户端的消息参数，并将该消息发送给一系列的邮箱，邮箱列表则是通过构造函数传递给通知器的。作为客户端的第三方程序仅会创建和配置通知器对象一次，然后在有重要事件发生时对其进行调用。

![程序可以使用通知器类向预定义的邮箱发送重要事件通知](image/image-20220304110706594.png)

此后某个时刻，你会发现库的用户希望使用除邮件通知之外的功能。许多用户会希望接收关于紧急事件的手机短信，还有些用户希望在微信上接收消息， 而公司用户则希望在QQ上接收消息。

![每种通知类型都将作为通知器的一个子类得以实现](image/image-20220304110817211.png)

但是很快有人会问：“为什么不同时使用多种通知形式呢？如果房子着火了，你大概会想在所有渠道中都收到相同的消息吧。”

你可以尝试创建一个特殊子类来将多种通知方法组合在一起以解决该问题。但这种方式会使得代码量迅速膨胀，不仅仅是程序库代码，客户端代码也会如此。

![子类组合数量爆炸](image/image-20220304111008892.png)

你必须找到其他方法来规划通知类的结构，否则它们的数量会在不经意之间打破吉尼斯纪录。

#### 2. 解决方案

当你需要更改一个对象的行为时，第一个跳入脑海的想法就是扩展它所属的类。但是，你不能忽视继承可能引发的几个严重问题。

* 继承是静态的。你无法在运行时更改已有对象的行为，只能使用由不同子类创建的对象来替代当前的整个对象。
* 子类只能有一个父类。大部分编程语言不允许一个类同时继承多个类的行为。

其中一种方法是用聚合或组合1， 而不是继承。两者的工作方式几乎一模一样： 一个对象包含指向另一个对象的引用，并将部分工作委派给引用对象；继承中的对象则继承了父类的行为，它们自己能够完成这些工作。

你可以使用这个新方法来轻松替换各种连接的“小帮手”对象，从而能在运行时改变容器的行为。一个对象可以使用多个类的行为，包含多个指向其他对象的引用，并将各种工作委派给引用对象。

聚合（或组合）组合是许多设计模式背后的关键原则（包括装饰在内）。记住这一点后，让我们继续关于模式的讨论。

> 聚合：对象A包含对象B；B可以独立于A存在。
>
> 组合：对象A由对象B构成；A负责管理B的生命周期。B无法独立于A存在。

![继承与聚合的对比](image/image-20220304111406122.png)

封装器是装饰模式的别称，这个称谓明确地表达了该模式的主要思想。“封装器”是一个能与其他“目标”对象连接的对象。封装器包含与目标对象相同的一系列方法，它会将所有接收到的请求委派给目标对象。但是，封装器可以在将请求委派给目标前后对其进行处理，所以可能会改变最终结果。

那么什么时候一个简单的封装器可以被称为是真正的装饰呢？正如之前提到的， 封装器实现了与其封装对象相同的接口。因此从客户端的角度来看，这些对象是完全一样的。封装器中的引用成员变量可以是遵循相同接口的任意对象。这使得你可以将一个对象放入多个封装器中，并在对象中添加所有这些封装器的组合行为。

比如在消息通知示例中，我们可以将简单邮件通知行为放在基类通知器中，但将所有其他通知方法放入装饰中。

![将各种通知方法放入装饰](image/image-20220304111753796.png)

客户端代码必须将基础通知器放入一系列自己所需的装饰中。因此最后的对象将形成一个栈结构。

![程序可以配置由通知装饰构成的复杂栈](image/image-20220304111827636.png)

实际与客户端进行交互的对象将是最后一个进入栈中的装饰对象。由于所有的装饰都实现了与通知基类相同的接口，客户端的其他代码并不在意自己到底是与“纯粹”的通知器对象，还是与装饰后的通知器对象进行交互。

我们可以使用相同方法来完成其他行为（例如设置消息格式或者创建接收人列表）。只要所有装饰都遵循相同的接口，客户端就可以使用任意自定义的装饰来装饰对象。

## 结构

![image-20220208163356309](image/image-20220208163356309.png)

1. 部件（Component）声明封装器和被封装对象的公用接口。
2. 具体部件（Concrete Component）类是被封装对象所属的类。它定义了基础行为，但装饰类可以改变这些行为。
3. 基础装饰（Base Decorator）类拥有一个指向被封装对象的引用成员变量。该变量的类型应当被声明为通用部件接口，这样它就可以引用具体的部件和装饰。装饰基类会将所有操作委派给被封装的对象。
4. 具体装饰类（Concrete Decorators） 定义了可动态添加到部件的额外行为。具体装饰类会重写装饰基类的方法，并在调用父类方法之前或之后进行额外的行为。
5. 客户端（Client）可以使用多层装饰来封装部件， 只要它能使用通用接口与所有对象互动即可。

## 适用场景

* 如果你希望在无需修改代码的情况下即可使用对象，且希望在运行时为对象新增额外的行为，可以使用装饰模式。

装饰能将业务逻辑组织为层次结构，你可为各层创建一个装饰，在运行时将各种不同逻辑组合成对象。由于这些对象都遵循通用接口，客户端代码能以相同的方式使用这些对象。

* 如果用继承来扩展对象行为的方案难以实现或者根本不可行，你可以使用该模式。

许多编程语言使用final 最终关键字来限制对某个类的进一步扩展。复用最终类已有行为的唯一方法是使用装饰模式：用封装器对其进行封装。

## 实现方式

1. 确保业务逻辑可用一个基本组件及多个额外可选层次表示。
2. 找出基本组件和可选层次的通用方法。创建一个组件接口并 在其中声明这些方法。
3. 创建一个具体组件类，并定义其基础行为。
4. 创建装饰基类，使用一个成员变量存储指向被封装对象的引 用。该成员变量必须被声明为组件接口类型，从而能在运行 时连接具体组件和装饰。装饰基类必须将所有工作委派给被 封装的对象。
5. 确保所有类实现组件接口。
6. 将装饰基类扩展为具体装饰。具体装饰必须在调用父类方法（总是委派给被封装对象）之前或之后执行自身的行为。
7. 客户端代码负责创建装饰并将其组合成客户端所需的形式。

## 优点

* 你无需创建新子类即可扩展对象的行为。
* 你可以在运行时添加或删除对象的功能。
* 你可以用多个装饰封装对象来组合几种行为。
* 单一职责原则。你可以将实现了许多不同行为的一个大类拆 分为多个较小的类。

## 缺点

* 在封装器栈中删除特定封装器比较困难。
* 实现行为不受装饰栈顺序影响的装饰比较困难。
* 各层的初始化配置代码看上去可能会很糟糕。

## 与其他模式的关系

* 适配器可以对已有对象的接口进行修改，装饰则能在不改变 对象接口的前提下强化对象功能。此外，装饰还支持递归组 合，适配器则无法实现。
* 适配器能为被封装对象提供不同的接口，代理能为对象提供 相同的接口，装饰则能为对象提供加强的接口。
* 责任链和装饰模式的类结构非常相似。两者都依赖递归组合 将需要执行的操作传递给一系列对象。但是，两者有几点重 要的不同之处。责任链的管理者可以相互独立地执行一切操作，还可以随时 停止传递请求。另一方面，各种装饰可以在遵循基本接口的 情况下扩展对象的行为。此外，装饰无法中断请求的传递。
* 组合和装饰的结构图很相似，因为两者都依赖递归组合来组 织无限数量的对象。装饰类似于组合，但其只有一个子组件。此外还有一个明显 不同：装饰为被封装对象添加了额外的职责，组合仅对其子 节点的结果进行了“求和”。但是，模式也可以相互合作：你可以使用装饰来扩展组合树 中特定对象的行为。
* 大量使用组合和装饰的设计通常可从对于原型的使用中获益。 你可以通过该模式来复制复杂结构，而非从零开始重新构造。
* 装饰可让你更改对象的外表，策略则让你能够改变其本质。
* 装饰和代理有着相似的结构，但是其意图却非常不同。这两 个模式的构建都基于组合原则，也就是说一个对象应该将部 分工作委派给另一个对象。两者之间的不同之处在于代理通 常自行管理其服务对象的生命周期，而装饰的生成则总是由客户端进行控制。

## 实例

正常情况下磁盘中的数据文件可以直接读取，但是对于敏感数据需要进行压缩和加密。我们需要实现两个装饰器，它们都改变了从磁盘读写数据的方式

* 加密：对数据进行脱敏处理
* 压缩：对数据进行压缩处理

Component.h：

```c++
#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

// 部件: 是具体部件和装饰类的共同基类, 在C++中实现成抽象基类
class DataSource {
 public:
    virtual void writeData(std::string data) = 0;
};

#endif  // COMPONENT_H_
```

ConcreteComponent.h：

```c++
#ifndef CONCRETE_COMPONENT_H_
#define CONCRETE_COMPONENT_H_

#include <string>
#include <cstdio>
#include <iostream>
#include "Component.h"

// 具体组件提供操作的默认实现, 这些类在程序中可能会有几个变体
class FileDataSource : public DataSource {
 public:
    explicit FileDataSource(std::string file_name) : file_name_(file_name) {}
    void writeData(std::string data) override {
        printf("写入文件%s中: %s\n", file_name_.c_str(), data.c_str());
        return;
    }

 private:
    std::string file_name_;
};

#endif  // CONCRETE_COMPONENT_H_
```

BaseDecorator.h：

```c++
#ifndef BASE_DECORATOR_H_
#define BASE_DECORATOR_H_

#include <string>
#include "Component.h"

// 装饰基类和其他组件遵循相同的接口。该类的主要任务是定义所有具体装饰的封装接口。
// 封装的默认实现代码中可能会包含一个保存被封装组件的成员变量，并且负责对其进行初始化。
class DataSourceDecorator : public DataSource {
 public:
    explicit DataSourceDecorator(DataSource* ds) : data_source_(ds) {}
    void writeData(std::string data) override {
        data_source_->writeData(data);
    }

 protected:
    DataSource* data_source_;  // component
};

#endif  // BASE_DECORATOR_H_
```

ConcreteDecorator.h：

```c++
#ifndef CONCRETE_DECORATOR_H_
#define CONCRETE_DECORATOR_H_

#include <string>
#include "BaseDecorator.h"

// 加密装饰器
class EncryptionDecorator : public DataSourceDecorator {
 public:
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(std::string data) override {
        // 1. 对传递数据进行加密(这里仅简单实现)
        data = "已加密(" + data + ")";
        // 2. 将加密后数据传递给被封装对象 writeData（写入数据）方法
        data_source_->writeData(data);
        return;
    }
};

// 压缩装饰器
class CompressionDecorator : public DataSourceDecorator {
 public:
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(std::string data) override {
        // 1. 对传递数据进行压缩(这里仅简单实现)
        data = "已压缩(" + data + ")";
        // 2. 将压缩后数据传递给被封装对象 writeData（写入数据）方法
        data_source_->writeData(data);
        return;
    }
};

#endif  // CONCRETE_DECORATOR_H_
```

main.cpp：

```c++
#include "ConcreteComponent.h"
#include "ConcreteDecorator.h"

int main() {
    FileDataSource* source1 = new FileDataSource("stdout");

    // 将明码数据写入目标文件
    source1->writeData("tomocat");

    // 将压缩数据写入目标文件
    CompressionDecorator* source2 = new CompressionDecorator(source1);
    source2->writeData("tomocat");

    // 将压缩且加密数据写入目标文件
    EncryptionDecorator* source3 = new EncryptionDecorator(source2);
    source3->writeData("tomocat");

    delete source1;
    delete source2;
    delete source3;
}
```

编译运行：

```bash
$g++ -g main.cpp -o decorator -std=c++11
$./decorator 
写入文件stdout中: tomocat
写入文件stdout中: 已压缩(tomocat)
写入文件stdout中: 已压缩(已加密(tomocat))
```

