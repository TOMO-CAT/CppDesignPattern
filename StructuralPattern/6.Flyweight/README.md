# 享元模式（Flyweight）

## 别名

缓存（Cache）。

## 定义

享元是一种结构型设计模式，它摒弃了在每个对象中保存所有数据的方式，通过共享多个对象所共有的相同状态，让你能在有限的内存容量中载入更多对象。

## 前言

#### 1. 问题

假如你希望在长时间工作后放松一下，所以开发了一款简单的游戏：玩家们在地图上移动并相互射击。你决定实现一个真实的粒子系统，并将其作为游戏的特色。大量的子弹、导弹和爆炸弹片会在整个地图上穿行，为玩家提供紧张刺激的游戏体验。

开发完成后，你推送提交了最新版本的程序，并在编译游戏后将其发送给了一个朋友进行测试。尽管该游戏在你的电脑上完美运行，但是你的朋友却无法长时间进行游戏：游戏总是会在他的电脑上运行几分钟后崩溃。在研究了几个小时的调试消息记录后，你发现导致游戏崩溃的原因是内存容量不足。朋友的设备性能远比不上你的电脑，因此游戏运行在他的电脑上时很快就会出现问题。

真正的问题与粒子系统有关。每个粒子（一颗子弹、一枚导弹或一块弹片）都由包含完整数据的独立对象来表示。当玩家在游戏中鏖战进入高潮后的某一时刻，游戏将无法在剩余内存中载入新建粒子，于是程序就崩溃了。

![image-20220304120113624](image/image-20220304120113624.png)

#### 2. 解决方案

仔细观察粒子（Particle）类， 你可能会注意到颜色（color）和精灵图（sprite）这两个成员变量所消耗的内存要比其他变量多得多。更糟糕的是，对于所有的粒子来说，这两个成员变量所存储的数据几乎完全一样（比如所有子弹的颜色和精灵图都一样）。

![image-20220304120217188](image/image-20220304120217188.png)

每个粒子的另一些状态（坐标、移动矢量和速度）则是不同的。因为这些成员变量的数值会不断变化。这些数据代表粒子在存续期间不断变化的情景，但每个粒子的颜色和精灵图则会保持不变。

对象的常量数据通常被称为内在状态，其位于对象中，其他对象只能读取但不能修改其数值。而对象的其他状态常常能被其他对象“从外部”改变，因此被称为外在状态。

享元模式建议不在对象中存储外在状态，而是将其传递给依赖于它的一个特殊方法。程序只在对象中保存内在状态，以方便在不同情景下重用。这些对象的区别仅在于其内在状态（与外在状态相比，内在状态的变体要少很多），因此你所需的对象数量会大大削减。

![image-20220304120459605](image/image-20220304120459605.png)

让我们回到游戏中。假如能从粒子类中抽出外在状态，那么我们只需三个不同的对象（子弹、导弹和弹片）就能表示游戏中的所有粒子。你现在很可能已经猜到了，我们将这样一个仅存储内在状态的对象称为享元。

#### 3. 外在状态存储

那么外在状态会被移动到什么地方呢？总得有类来存储它们，对不对？在大部分情况中，它们会被移动到容器对象中，也就是我们应用享元模式前的聚合对象中。

在我们的例子中， 容器对象就是主要的游戏（Game）对象，其会将所有粒子存储在名为粒子（particles）的成员变量中。为了能将外在状态移动到这个类中，你需要创建多个数组成员变量来存储每个粒子的坐标、方向矢量和速度。除此之外，你还需要另一个数组来存储指向代表粒子的特定享元的引用。这些数组必须保持同步，这样你才能够使用同一索引来获取关于某个粒子的所有数据。

![image-20220304120645109](image/image-20220304120645109.png)

更优雅的解决方案是创建独立的情景类来存储外在状态和对享元对象的引用。在该方法中，容器类只需包含一个数组。

稍等！这样的话情景对象数量不是会和不采用该模式时的对象数量一样多吗？ 的确如此， 但这些对象要比之前小很多。消耗内存最多的成员变量已经被移动到很少的几个享元对象中了。现在， 一个享元大对象会被上千个情境小对象复用，因此无需再重复存储数千个大对象的数据。

#### 4. 享元与不可变性

由于享元对象可在不同的情景中使用，你必须确保其状态不能被修改。享元类的状态只能由构造函数的参数进行一次性初始化，它不能对其他对象公开其设置器或公有成员变量。

#### 5. 享元工厂

为了能更方便地访问各种享元，你可以创建一个工厂方法来管理已有享元对象的缓存池。工厂方法从客户端处接收目标享元对象的内在状态作为参数，如果它能在缓存池中找到所需享元，则将其返回给客户端；如果没有找到，它就会新建一个享元，并将其添加到缓存池中。

你可以选择在程序的不同地方放入该函数。最简单的选择就是将其放置在享元容器中。除此之外，你还可以新建一个工厂类，或者创建一个静态的工厂方法并将其放入实际的享元类中。

## 结构

![image-20220209201147526](image/image-20220209201147526.png)

1. 享元模式只是一种优化。在应用该模式之前，你要确定程序中存在与大量类似对象同时占用内存相关的内存消耗问题，并且确保该问题无法使用其他更好的方式来解决。
2. 享元（Flyweight）类包含原始对象中部分能在多个对象中共享的状态。同一享元对象可在许多不同情景中使用。享元中存储的状态被称为“内在状态”。传递给享元方法的状态被称为“外在状态”。
3. 情景（Context）类包含原始对象中各不相同的外在状态。情景与享元对象组合在一起就能表示原始对象的全部状态。
4. 通常情况下，原始对象的行为会保留在享元类中。因此调用享元方法必须提供部分外在状态作为参数。但你也可将行为移动到情景类中，然后将连入的享元作为单纯的数据对象。
5. 客户端（Client）负责计算或存储享元的外在状态。在客户端看来，享元是一种可在运行时进行配置的模板对象，具体的配置方式为向其方法中传入一些情景数据参数。
6. 享元工厂（Flyweight Factory）会对已有享元的缓存池进行管理。有了工厂后，客户端就无需直接创建享元，它们只需调用工厂并向其传递目标享元的一些内在状态即可。工厂会根据参数在之前已创建的享元中进行查找，如果找到满足条件的享元就将其返回；如果没有找到就根据参数新建享元。

## 适用场景

仅在程序必须支持大量对象且没有足够的内存容量时使用享元模式，应用该模式所获的收益大小取决于使用它的方式和情景。它在下列情况中最有效：

* 程序需要生成数量巨大的相似对象
* 这将耗尽目标设备的所有内存
* 对象中包含可抽取且能在多个对象间共享的重复状态。

## 实现方式

1. 将需要改写为享元的类成员变量拆分为两个部分：
   * 内在状态：包含不变的、可在许多对象中重复使用的数据的成员变量。
   * 外在状态：包含每个对象各自不同的情景数据的成员变量。

2. 保留类中表示内在状态的成员变量，并将其属性设置为不可修改。这些变量仅可在构造函数中获得初始数值。
3. 找到所有使用外在状态成员变量的方法，为在方法中所用的每个成员变量新建一个参数，并使用该参数代替成员变量。
4. 你可以有选择地创建工厂类来管理享元缓存池，它负责在新建享元时检查已有的享元。如果选择使用工厂，客户端就只能通过工厂来请求享元，它们需要将享元的内在状态作为参数传递给工厂。
5. 客户端必须存储和计算外在状态（情景）的数值，因为只有这样才能调用享元对象的方法。为了使用方便，外在状态和引用享元的成员变量可以移动到单独的情景类中。

## 优点

如果程序中有很多相似对象，那么你将可以节省大量内存。

## 缺点

* 你可能需要牺牲执行速度来换取内存，因为他人每次调用享元方法时都需要重新计算部分情景数据。
* 代码会变得更加复杂。团队中的新成员总是会问：“为什么要像这样拆分一个实体的状态？”。

## 与其他模式的关系

* 你可以使用享元实现组合树的共享叶节点以节省内存。
* 享元展示了如何生成大量的小型对象，外观则展示了如何用一个对象来代表整个子系统。
* 如果你能将对象的所有共享状态简化为一个享元对象，那么享元就和单例类似了。但这两个模式有两个根本性的不同。
  * 单例只会有一个实体，但是享元类可以有多个实体，各实体的内在状态也可以不同。
  * 单例对象可以是可变的。享元对象是不可变的。

## 实例

在本例中，享元模式能有效减少在画布上渲染数百万个树状对象时所需的内存。

Flyweight.h：

```c++
#ifndef FLYWEIGHT_H_
#define FLYWEIGHT_H_

#include <string>

// 享元类包含了树类型的部分状态, 这些成员变量保存的数值对于特定树而言是唯一的。
// 很多树木之间包含共同的名字、颜色和纹理, 如果在每棵树中都存储这些数据就会浪费大量内存。
// 因此我们将这些「内在状态」导出到一个单独的对象中, 然后让众多的单个树对象去引用它。
class TreeType {
 public:
    TreeType(std::string n, std::string c, std::string t) :
        name_(n), color_(c), texture_(t) {}
    void draw(std::string canvas, double x, double y) {
        // 1. 创建特定类型、颜色和纹理的位图
        // 2. 在画布坐标(x,y)处绘制位图
        return;
    }

 private:
    std::string name_;
    std::string color_;
    std::string texture_;
};

#endif  // FLYWEIGHT_H_
```

Context.h：

```c++
#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <string>
#include "Flyweight.h"

// 情景对象包含树类型的「外在状态」, 程序中可以创建数十亿个此类对象, 因为它们体积很小: 仅有两个浮点坐标类型和一个引用成员变量
class Tree {
 public:
    Tree(double x, double y, TreeType* t) : x_(x), y_(y), type_(t) {}
    void draw(std::string canvas) {
        return type_->draw(canvas, x_, y_);
    }

 private:
    double x_;
    double y_;
    TreeType* type_;
};

#endif  // CONTEXT_H_
```

FlyweightFactory.h：

```c++
#ifndef FLYWEIGHT_FACTORY_H_
#define FLYWEIGHT_FACTORY_H_

#include <map>
#include <string>
#include <mutex>
#include "Flyweight.h"

// 享元工厂: 决定是否复用已有享元或者创建一个新的对象, 同时它也是一个单例模式
class TreeFactory {
 public:
    static TreeFactory* getInstance() {
        if (instance_ == nullptr) {
            mutex_.lock();
            if (instance_ == nullptr) {
                instance_ = new TreeFactory();
            }
            mutex_.unlock();
        }
        return instance_;
    }
    TreeType* getTreeType(std::string name, std::string color, std::string texture) {
        std::string key = name + "_" + color + "_" + texture;
        auto iter = tree_types_.find(key);
        if (iter == tree_types_.end()) {
            // 新的tree type
            TreeType* new_tree_type = new TreeType(name, color, texture);
            tree_types_[key] = new_tree_type;
            return new_tree_type;
        } else {
            // 已存在的tree type
            return iter->second;
        }
    }

 private:
    TreeFactory() {}
    static TreeFactory* instance_;
    static std::mutex mutex_;

    // 共享池, 其中key格式为name_color_texture
    std::map<std::string, TreeType*> tree_types_;
};

#endif  // FLYWEIGHT_FACTORY_H_
```

FlyweightFactory.cpp：

```c++
#include "FlyweightFactory.h"

TreeFactory* TreeFactory::instance_ = nullptr;
std::mutex TreeFactory::mutex_;
```

Client.h：

```c++
#ifndef CLIENT_H_
#define CLIENT_H_

#include <vector>
#include <iostream>
#include <string>
#include "FlyweightFactory.h"
#include "Context.h"

// Forest包含数量及其庞大的Tree
class Forest {
 public:
    void planTree(double x, double y, std::string name, std::string color, std::string texture) {
        TreeType* type = TreeFactory::getInstance()->getTreeType(name, color, texture);
        Tree tree = Tree(x, y, type);
        trees_.push_back(tree);
    }
    void draw() {
        for (auto tree : trees_) {
            tree.draw("canvas");
        }
    }

 private:
    std::vector<Tree> trees_;
};

#endif  // CLIENT_H_
```

main.cpp：

```c++
#include "Client.h"

int main() {
    Forest* forest = new Forest();

    // 在forest中种植很多棵树
    for (int i = 0; i < 500; i++) {
        for (int j = 0; j < 500; j++) {
            double x = i;
            double y = j;
            // 树类型1: 红色的杉树
            forest->planTree(x, y, "杉树", "红色", "");
            // 树类型2: 绿色的榕树
            forest->planTree(x, y, "榕树", "绿色", "");
            // 树类型3: 白色的桦树
            forest->planTree(x, y, "桦树", "白色", "");
        }
    }

    forest->draw();

    delete forest;
}
```

编译运行：

```bash
$g++ -g main.cpp FlyweightFactory.cpp -std=c++11 -o flyweight
$./flyweight 
```

## Reference

[1] https://manyones.files.wordpress.com/2010/07/dp-2nd.pdf