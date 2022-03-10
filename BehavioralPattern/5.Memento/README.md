# 备忘录模式（Memento）

## 别名

快照（Snapshot）。

## 定义

备忘录是一种行为设计模式，允许在不暴露对象实现细节的情况下保存和恢复对象之前的状态。

## 前言

#### 1. 问题

假设你正在开发一款文字编辑器应用程序，除了简单的文字编辑功能外，编辑器中还要有设置文本格式和插入内嵌图片等功能。

后来你决定让用户能撤销施加在文本上的任何操作。你选择采用最直接的方式来实现该功能：程序在执行任何操作前会记录所有的对象状态， 并将其保存下来。当用户此后需要撤销某个操作时，程序将从历史记录中获取最近的快照，然后使用它来恢复所有对象的状态。

![程序在执行操作前保存所有对象的状态快照](image/image-20220226130150834.png)

想要保存状态快照存在如下问题：

* 生成快照需要遍历对象的所有成员变量并将其数值复制保存，然而大部分对象会用私有成员变量来存储重要数据，这样别人就无法轻易查看其中的内容
* 即使对象的所有成员变量都是共有（public）的，未来添加或删除一些成员变量时需要对负责复制受影响对象状态的类进行更改

我们似乎走进了一条死胡同：要么暴露类的的所有内部细节而使其过于脆弱；要么会限制对其状态的访问权限而无法生成快照。那么我们应该如何实现“撤销”功能呢？

#### 2. 解决方案

备忘录模式将创建状态快照（Snapshot）的工作委派给实际状态的拥有者原发器（Originator）对象。这样其他对象就不再需要从“外部”复制编辑器状态了，编辑器类拥有其状态的完全访问权，因此可以自行生成快照。 

模 式 建 议 将 对 象 状 态 的 副 本 存 储 在 一 个 名 为 备 忘 录（Memento）的特殊对象中。除了创建备忘录的对象外，任何对象都不能访问备忘录的内容。其他对象必须使用受限接口与备忘录进行交互，它们可以获取快照的元数据（创建时间和操作名称等），但不能获取快照中原始对象的状态。

![原发器拥有对备忘录的完全访问权限](image/image-20220226131459813.png)

这种限制策略允许你将备忘录保存在通常被称为负责人（Caretakers）的对象中。由于负责人仅通过受限接口与备忘录互动，故其无法修改存储在备忘录内部的状态。同时，原发器拥有对备忘录所有成员的访问权限，从而能随时恢复其以前的状态。

在文字编辑器的示例中， 我们可以创建一个独立的历史（History）类作为负责人。编辑器每次执行操作前，存储在负责人中的备忘录栈都会生长。你甚至可以在应用的 UI 中渲染该栈，为用户显示之前的操作历史。

当用户触发撤销操作时，历史类将从栈中取回最近的备忘录，并将其传递给编辑器以请求进行回滚。由于编辑器拥有对备忘录的完全访问权限，因此它可以使用从备忘录中获取的数值来替换自身的状态。

## 结构

#### 1. 基于嵌套类的实现

该模式的经典实现方式依赖于许多流行编程语言（例如 C++、C# 和 Java）所支持的嵌套类。 

![基于嵌套类的实现](image/image-20220226135305377.png)

1. **原发器**（Originator）类可以生成自身状态的快照，也可以在需要时通过快照恢复自身状态。
2. **备忘录** （Memento） 是原发器状态快照的值对象 （valueobject）。通常做法是将备忘录设为不可变的，并通过构造函数一次性传递数据。
3. **负责人**（Caretaker）仅知道“何时”和“为何”捕捉原发器的状态，以及何时恢复状态。负责人通过保存备忘录栈来记录原发器的历史状态。当原发器需要回溯历史状态时，负责人将从栈中获取最顶部的备忘录，并将其传递给原发器的恢复（restoration）方法。
4. 在该实现方法中，备忘录类将被嵌套在原发器中。这样原发器就可访问备忘录的成员变量和方法，即使这些方法被声明为私有。另一方面，负责人对于备忘录的成员变量和方法的访问权限非常有限：它们只能在栈中保存备忘录，而不能修改其状态。

#### 2. 基于中间接口的实现

另外一种实现方法适用于不支持嵌套类的编程语言（PHP）。

![基于中间接口的实现](image/image-20220226135514697.png)

1. 在没有嵌套类的情况下，你可以规定负责人仅可通过明确声明的中间接口与备忘录互动，该接口仅声明与备忘录元数据相关的方法，限制其对备忘录成员变量的直接访问权限。
2. 另一方面，原发器可以直接与备忘录对象进行交互，访问备忘录类中声明的成员变量和方法。这种方式的缺点在于你需要将备忘录的所有成员变量声明为公有。

#### 3. 封装更加严格的实现

如果你不想让其他类有任何机会通过备忘录来访问原发器的状态，那么还有另一种可用的实现方式。

![image-20220226151635483](image/image-20220226151635483.png)

1. 这种实现方式允许存在多种不同类型的原发器和备忘录。每种原发器都和其相应的备忘录类进行交互。原发器和备忘录都不会将其状态暴露给其他类。
2. 负责人此时被明确禁止修改存储在备忘录中的状态。但负责人类将独立于原发器，因为此时恢复方法被定义在了备忘录类中。
3. 每个备忘录将与创建了自身的原发器连接。原发器会将自己及状态传递给备忘录的构造函数。由于这些类之间的紧密联系，只要原发器定义了合适的设置器（setter），备忘录就能恢复其状态。

## 适用场景

* 当你需要创建对象状态快照来恢复其之前的状态时，可以使用备忘录模式。

备忘录模式允许你复制对象中的全部状态（包括私有成员变量），并将其独立于对象进行保存。尽管大部分人因为“撤 销”这个用例才记得该模式，但其实它在处理事务（比如需要在出现错误时回滚一个操作）的过程中也必不可少。

* 当直接访问对象的成员变量、获取器或设置器将导致封装被突破时，可以使用该模式。

备忘录让对象自行负责创建其状态的快照。任何其他对象都不能读取快照，这有效地保障了数据的安全性。

## 实现方式

1. 确定担任原发器角色的类。重要的是明确程序使用的一个原发器中心对象，还是多个较小的对象。
2. 创建备忘录类。逐一声明对应每个原发器成员变量的备忘录成员变量。
3. 将备忘录类设为不可变。备忘录只能通过构造函数一次性接收数据。该类中不能包含设置器。
4. 如果你所使用的编程语言支持嵌套类，则可将备忘录嵌套在原发器中；如果不支持，那么你可从备忘录类中抽取一个空接口，然后让其他所有对象通过接口来引用备忘录。你可在该接口中添加一些元数据操作，但不能暴露原发器的状态。
5. 在原发器中添加一个创建备忘录的方法。原发器必须通过备忘录构造函数的一个或多个实际参数来将自身状态传递给备忘录。 该方法返回结果的类型必须是你在上一步中抽取的接口（如果你已经抽取了）。实际上，创建备忘录的方法必须直接与备忘录类进行交互。
6. 在原发器类中添加一个用于恢复自身状态的方法。该方法接受备忘录对象作为参数。如果你在之前的步骤中抽取了接口，那么可将接口作为参数的类型。在这种情况下，你需要将输入对象强制转换为备忘录，因为原发器需要拥有对该对象的完全访问权限。 
7. 无论负责人是命令对象、 历史记录或其他完全不同的东西，它都必须要知道何时向原发器请求新的备忘录、如何存储备忘录以及何时使用特定备忘录来对原发器进行恢复。
8. 负责人与原发器之间的连接可以移动到备忘录类中。在本例中，每个备忘录都必须与创建自己的原发器相连接。恢复方法也可以移动到备忘录类中，但只有当备忘录类嵌套在原发器中，或者原发器类提供了足够多的设置器并可对其状态进行重写时，这种方式才能实现。

## 优点

* 你可以在不破坏对象封装情况的前提下创建对象状态快照。
* 你可以通过让负责人维护原发器状态历史记录来简化原发器代码。 

## 缺点

* 如果客户端过于频繁地创建备忘录，程序将消耗大量内存。
* 负责人必须完整跟踪原发器的生命周期，这样才能销毁弃用的备忘录。
* 绝大部分动态编程语言（例如 PHP、 Python 和 JavaScript）不能确保备忘录中的状态不被修改。

## 与其他模式的关系

* 你可以同时使用**命令**和**备忘录**来实现“撤销”。在这种情况下，命令用于对目标对象执行各种不同的操作，备忘录用来保存一条命令执行前该对象的状态。
* 你可以同时使用**备忘录**和**迭代器**来获取当前迭代器的状态，并且在需要的时候进行回滚。 
* 有时候**原型**可以作为**备忘录**的一个简化版本，其条件是你需要在历史记录中存储的对象的状态比较简单，不需要链接其他外部资源，或者链接可以方便地重建。 

## 实例

Memento.h：

```c++
#ifndef MEMENTO_H_
#define MEMENTO_H_

#include <string>

// 备忘录类保存编辑器的过往状态
class Snapshot {
 public:
    Snapshot(std::string text, int x, int y, double width)
        : text_(text), cur_x_(x), cur_y_(y), selection_width_(width) {}
    std::string get_text() {
        return text_;
    }
    int get_cur_x() {
        return cur_x_;
    }
    int get_cur_y() {
        return cur_y_;
    }
    double get_selection_width() {
        return selection_width_;
    }

 private:
    const std::string text_;
    const int cur_x_;
    const int cur_y_;
    const double selection_width_;
};

#endif  // MEMENTO_H_
```

Originator.h：

```c++
#ifndef ORIGINATOR_H_
#define ORIGINATOR_H_

#include <cstdio>
#include <string>
#include <memory>
#include "Memento.h"

// 原发器中包含了一些可能会随时间变化的重要数据
// 它还定义了在备忘录中保存自身状态的方法, 以及从备忘录中恢复状态的方法
class Editor {
 public:
    void setText(std::string text) {
        text_ = text;
    }
    void setCursor(int x, int y) {
        cur_x_ = x;
        cur_y_ = y;
    }
    void setSelectionWidth(double width) {
        selection_width_ = width;
    }

    // 在备忘录中保存当前的状态
    std::shared_ptr<Snapshot> createSnapshot() {
        // 备忘录是不可变的对象, 因此原发器会将自身状态作为参数传递给备忘录的构造函数
        auto res = std::make_shared<Snapshot>(text_, cur_x_, cur_y_, selection_width_);
        printf("创建编辑器快照成功, text:%s x:%d y:%d width:%.2f\n", text_.c_str(), cur_x_, cur_y_, selection_width_);
        return res;
    }

    void resotre(std::shared_ptr<Snapshot> sptr_snapshot) {
        text_ = sptr_snapshot->get_text();
        cur_x_ = sptr_snapshot->get_cur_x();
        cur_y_ = sptr_snapshot->get_cur_y();
        selection_width_ = sptr_snapshot->get_selection_width();
        printf("恢复编辑器状态成功, text:%s x:%d y:%d width:%.2f\n", text_.c_str(), cur_x_, cur_y_, selection_width_);
    }

 private:
    // 文本
    std::string text_;
    // 光标位置
    int cur_x_;
    int cur_y_;
    // 当前滚动条位置
    double selection_width_;
};

#endif  // ORIGINATOR_H_
```

Caretaker.h：

```c++
#ifndef CARETAKER_H_
#define CARETAKER_H_

#include <memory>
#include "Memento.h"
#include "Originator.h"

class Command {
 public:
    explicit Command(Editor* e) : editor_(e) {}
    void makeBackup() {
        backup_ = editor_->createSnapshot();
    }
    void undo() {
        if (backup_) {
            editor_->resotre(backup_);
        }
    }

 private:
    Editor *editor_;
    std::shared_ptr<Snapshot> backup_;
};

#endif  // CARETAKER_H_
```

main.cpp：

```c++
#include "Caretaker.h"

int main() {
    // 创建原发器和负责人
    Editor editor;
    Command command(&editor);

    // 定义初始状态
    editor.setText("TOMOCAT");
    editor.setCursor(21, 34);
    editor.setSelectionWidth(3.4);

    // 保存状态
    command.makeBackup();

    // 更改编辑器状态
    editor.setText("KKKK");
    editor.setCursor(111, 222);
    editor.setSelectionWidth(111.222);

    // 撤销
    command.undo();

    return 0;
}
```

编译运行：

```bash
$g++ -g main.cpp -o memento -std=c++11
$./memento
创建编辑器快照成功, text:TOMOCAT x:21 y:34 width:3.40
恢复编辑器状态成功, text:TOMOCAT x:21 y:34 width:3.40
```

