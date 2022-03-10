# 适配器模式（Adapter）

## 定义

适配器是一种结构型设计模式，它能使接口不兼容的对象能够相互合作。

## 别名

封装器模式（Wrapper）。

## 前言

#### 1. 问题

假如你正在开发一款股票市场监测程序，它会从不同来源下载 XML 格式的股票数据，然后向用户呈现出美观的图表。

在开发过程中， 你决定在程序中整合一个第三方智能分析函数库。但是遇到了一个问题， 那就是分析函数库只兼容JSON 格式的数据。

![image-20220303194522408](image/image-20220303194522408.png)

你可以修改程序库来支持XML。但是，这可能需要修改部分依赖该程序库的现有代码。甚至还有更糟糕的情况，你可能根本没有程序库的源代码，从而无法对其进行修改。

#### 2. 解决方案

你可以创建一个适配器。这是一个特殊的对象，能够转换对象接口，使其能与其他对象进行交互。

适配器模式通过封装对象将复杂的转换过程隐藏于幕后。被封装的对象甚至察觉不到适配器的存在。例如，你可以使用一个将所有数据转换为英制单位（如英尺和英里）的适配器封装运行于米和千米单位制中的对象。

适配器不仅可以转换不同格式的数据，其还有助于采用不同接口的对象之间的合作。它的运作方式如下：

* 适配器实现与其中一个现有对象兼容的接口。
* 现有对象可以使用该接口安全地调用适配器方法。
* 适配器方法被调用后将以另一个对象兼容的格式和顺序将请求传递给该对象。

有时你甚至可以创建一个双向适配器来实现双向转换调用。

![image-20220303194719540](image/image-20220303194719540.png)

让我们回到股票市场程序。为了解决数据格式不兼容的问题，你可以为分析函数库中的每个类创建将XML 转换为JSON 格式的适配器，然后让客户端仅通过这些适配器来与函数库进行交流。当某个适配器被调用时，它会将传入的XML 数据转换为 JSON 结构，并将其传递给被封装分析对象的相应方法。

## 结构

#### 1. 对象适配器

实现时使用了构成原则：适配器实现了其中一个对象的接口，并对另一个对象进行封装。所有流行的编程语言都可以实现适配器。

![image-20220303195423768](image/image-20220303195423768.png)

1. 客户端（Client）是包含当前程序业务逻辑的类。
2. 客户端接口（Client Interface） 描述了其他类与客户端代码合作时必须遵循的协议。
3. 服务（Service）中有一些功能类（通常来自第三方或遗留系统）。客户端与其接口不兼容，因此无法直接调用其功能。
4. 适配器（Adapter） 是一个可以同时与客户端和服务交互的类：它在实现客户端接口的同时封装了服务对象。适配器接受客户端通过适配器接口发起的调用，并将其转换为适用于被封装服务对象的调用。
5. 客户端代码只需通过接口与适配器交互即可，无需与具体的适配器类耦合。因此，你可以向程序中添加新类型的适配器而无需修改已有代码。这在服务类的接口被更改或替换时很有用：你无需修改客户端代码就可以创建新的适配器类。

#### 2. 类适配器

这一实现使用了继承机制：适配器同时继承两个对象的接口。请注意， 这种方式仅能在支持多重继承的编程语言中实现，例如 C++。

![image-20220303195644956](image/image-20220303195644956.png)

类适配器不需要封装任何对象，因为它同时继承了客户端和服务的行为。适配功能在重写的方法中完成。最后生成的适配器可替代已有的客户端类进行使用。

## 适用场景

* 当你希望使用某个类，但是其接口与其他代码不兼容时，可以使用适配器类。

适配器模式允许你创建一个中间层类，其可作为代码与遗留类、第三方类或提供怪异接口的类之间的转换器。

* 如果您需要复用这样一些类，他们处于同一个继承体系，并且他们又有了额外的一些共同的方法，但是这些共同的方法不是所有在这一继承体系中的子类所具有的共性。

你可以扩展每个子类，将缺少的功能添加到新的子类中。但是，你必须在所有新子类中重复添加这些代码，这样会使得代码有坏味道。将缺失功能添加到一个适配器类中是一种优雅得多的解决方案。然后你可以将缺少功能的对象封装在适配器中，从而动态地获取所需功能。如要这一点正常运作，目标类必须要有通用接口，适配器的成员变量应当遵循该通用接口。这种方式同装饰模式非常相似。

## 实现方式

1. 确保至少有两个类的接口不兼容：
   * 一个无法修改（通常是第三方、遗留系统或者存在众多已有依赖的类）的功能性服务类。
   * 一个或多个将受益于使用服务类的客户端类。
2. 声明客户端接口，描述客户端如何与服务交互。
3. 创建遵循客户端接口的适配器类。所有方法暂时都为空。
4. 在适配器类中添加一个成员变量用于保存对于服务对象的引用。通常情况下会通过构造函数对该成员变量进行初始化，但有时在调用其方法时将该变量传递给适配器会更方便。
5. 依次实现适配器类客户端接口的所有方法。适配器会将实际工作委派给服务对象，自身只负责接口或数据格式的转换。
6. 客户端必须通过客户端接口使用适配器。这样一来，你就可以在不影响客户端代码的情况下修改或扩展适配器。

## 优点

* 单一职责原则你可以将接口或数据转换代码从程序主要业务逻辑中分离。
* 开闭原则。只要客户端代码通过客户端接口与适配器进行交互，你就能在不修改现有客户端代码的情况下在程序中添加新类型的适配器。

## 缺点

代码整体复杂度增加，因为你需要新增一系列接口和类。有时直接更改服务类使其与其他代码兼容会更简单。

## 与其他模式的关系

* 桥接通常会于开发前期进行设计，使你能够将程序的各个部分独立开来以便开发。另一方面，适配器通常在已有程序中使用，让相互不兼容的类能很好地合作。
* 适配器可以对已有对象的接口进行修改，装饰则能在不改变对象接口的前提下强化对象功能。此外，装饰还支持递归组合，适配器则无法实现。
* 适配器能为被封装对象提供不同的接口，代理能为对象提供相同的接口，装饰则能为对象提供加强的接口。
* 外观为现有对象定义了一个新接口，适配器则会试图运用已有的接口。适配器通常只封装一个对象，外观通常会作用于整个对象子系统上。
* 桥接、状态和策略（在某种程度上包括适配器）模式的接口非常相似。实际上， 它们都基于组合模式——即将工作委派给其他对象，不过也各自解决了不同的问题。模式并不只是以特定方式组织代码的配方，你还可以使用它们来和其他开发者讨论模式所解决的问题。

## 实例

考虑经典的“方钉和圆孔”的问题，我们要做的是让方钉适配圆孔。

适配器让方钉假扮成一个圆钉（RoundPeg），其半径等于方钉（SquarePeg）横截面对角线的一半（即能容纳方钉的最小外接圆的半径）。

ClientInterface.h：

```c++
#ifndef CLIENT_INTERFACE_H_
#define CLIENT_INTERFACE_H_

// 圆钉: 客户端接口, 在C++中定义成抽象基类
class RoundPeg {
 public:
    RoundPeg() {}
    virtual int get_radius() = 0;
};

#endif  // CLIENT_INTERFACE_H_
```

Adapter.h：

```c++
#ifndef ADAPTER_H_
#define ADAPTER_H_

#include <cmath>
#include "Service.h"
#include "ClientInterface.h"

// 方钉适配器: 该适配器能让客户端将方钉放入圆孔中
class SquarePegAdapter : public RoundPeg {
 public:
    explicit SquarePegAdapter(SquarePeg* sp) : square_peg_(sp) {}
    int get_radius() override {
        return square_peg_->get_width() * sqrt(2) / 2;
    }

 private:
    SquarePeg* square_peg_;
};

#endif  // ADAPTER_H_
```

Service.h：

```c++
#ifndef SERVICE_H_
#define SERVICE_H_

// 方钉: 适配者类, 即和客户端不兼容的类
class SquarePeg {
 public:
    explicit SquarePeg(int w) : width_(w) {}
    int get_width() {
        return width_;
    }

 private:
    int width_;
};

#endif  // SERVICE_H_
```

Client.h：

```c++
#ifndef CLIENT_H_
#define CLIENT_H_

#include "ClientInterface.h"

// 圆孔: 客户端类
class RoundHole {
 public:
    explicit RoundHole(int r) : radius_(r) {}
    int get_radius() {
        return radius_;
    }
    bool isFit(RoundPeg* rp) {
        return radius_ >= rp->get_radius();
    }

 private:
    int radius_;
};

#endif  // CLIENT_H_
```

main.cpp：

```c++
#include <iostream>
#include "Client.h"
#include "Adapter.h"

int main() {
    // 半径为10的圆孔
    RoundHole* hole = new RoundHole(10);

    // 半径分别为5和20的大小方钉 + 它们的适配器
    SquarePeg* samll_square_peg = new SquarePeg(5);
    SquarePeg* large_square_peg = new SquarePeg(20);
    SquarePegAdapter* small_square_peg_adapter = new SquarePegAdapter(samll_square_peg);
    SquarePegAdapter* large_square_peg_adapter = new SquarePegAdapter(large_square_peg);

    // hole->isFit(samll_square_peg);  // 编译报错
    // hole->isFit(large_square_peg);  // 编译报错
    if (hole->isFit(small_square_peg_adapter)) {
        std::cout << "small square peg fits the hole" << std::endl;
    } else {
        std::cout << "small square peg don't fit the hole" << std::endl;
    }
    if (hole->isFit(large_square_peg_adapter)) {
        std::cout << "large square peg fits the hole" << std::endl;
    } else {
        std::cout << "large square peg don't fit the hole" << std::endl;
    }
}
```

编译运行：

```bash
$g++ -g main.cpp -o adapter -std=c++11
$./adapter
small square peg fits the hole
large square peg don't fit the hole
```

