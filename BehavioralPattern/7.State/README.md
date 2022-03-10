# 状态模式（State）

## 定义

**状态**是一种行为设计模式，让你能在一个对象的内部状态变化时改变其行为，使其看上去就像改变了自身所属的类一样。

## 前言

#### 1. 问题

状态模式与**有限状态机**的概念紧密相关。

其主要思想是程序在任意时刻仅可处于几种有限的状态中。在任何一个特定状态中，程序的行为都不相同，且可瞬间从一个状态切换到另一个状态。不过，根据当前状态，程序可能会切换到另外一种状态，也可能会保持当前状态不变。这些数量有限且预先定义的状态切换规则被称为转移。

![有限状态机](image/image-20220226194042764.png)

你还可将该方法应用在对象上。 假如你有一个文档（Document）类，文档可能处于草稿（Draft）、审阅中（Moderation）和已发布（Published）三种状态中的一种。文档的publish方法在不同状态下的行为略有不同：

* 处于草稿状态时，它会将文档转移到审阅中状态。
* 处于审阅中状态时，如果当前用户是管理员，它会公开发布文档。
* 处于已发布状态时，它不会进行任何操作。

![文档的全部状态与转移](image/image-20220226194400665.png)

状态机通常由众多条件运算符（ if 或 switch ）实现，可根据对象的当前状态选择相应的行为。“状态”通常只是对象中的一组成员变量值。 即使你之前从未听说过有限状态机，你也很可能已经实现过状态模式。下面的代码应该能帮助你回忆起来：

```c++
enum DocumentState {
    kDraft = 0,
    kModeration = 1,
    kPublished = 2,
}

class Document {
 public:
    void publish() {
        switch (state_) {
            case kDraft:
                state_ = kModeration;
                break;
            case kModeration:
                if (currentUser.role == 'admin') {
                    state_ = kPublished;
                }
                break;
            case kPublished:
                // do nothing
                break;
        }
    }

 private:
    DocumentState state_;
};
```

当我们逐步在Document类中添加更多状态和依赖于状态的行为后，基于条件语句的状态机就会暴露其最大的弱点。为了能根据当前状态选择完成相应行为的方法，绝大部分方法中会包含复杂的条件语句。修改其转换逻辑可能会涉及到修改所有方法中的状态条件语句，导致代码的维护工作非常艰难。

这个问题会随着项目进行变得越发严重。我们很难在设计阶段预测到所有可能的状态和转换。随着时间推移，最初仅包含有限条件语句的简洁状态机可能会变成臃肿的一团乱麻。

#### 2. 解决方案

状态模式建议为对象的所有可能状态新建一个类，然后将所有状态的对应行为抽取到这些类中。

原始对象被称为上下文（context），它并不会自行实现所有行为，而是会保存一个指向表示当前状态的状态对象的引用，且将所有与状态相关的工作委派给该对象。

![文档将工作委派给一个状态对象](image/image-20220226195511971.png)

如需将上下文转换为另外一种状态，则需将当前活动的状态对象替换为另外一个代表新状态的对象。采用这种方式是有前提的：所有状态类都必须遵循同样的接口，而且上下文必须仅通过接口与这些对象进行交互。

这个结构可能看上去与**策略**模式相似，但有一个关键性的不同——在状态模式中， 特定状态知道其他所有状态的存在，且能触发从一个状态到另一个状态的转换；策略则几乎完全不知道其他策略的存在。

## 结构

![状态模式结构](image/image-20220226195630481.png)

1. **上下文**（Context）保存了对于一个具体状态对象的引用，并会将所有与该状态相关的工作委派给它。上下文通过状态接口与状态对象交互，且会提供一个设置器用于传递新的状态对象。

2. **状态**（State）接口会声明特定于状态的方法。这些方法应能被其他所有具体状态所理解，因为你不希望某些状态所拥有的方法永远不会被调用。 

3. **具体状态**（Concrete States）会自行实现特定于状态的方法。为了避免多个状态中包含相似代码，你可以提供一个封装有部分通用行为的中间抽象类。状态对象可存储对于上下文对象的反向引用。状态可以通过

   该引用从上下文处获取所需信息，并且能触发状态转移。

4. 上下文和具体状态都可以设置上下文的下个状态，并可通过替换连接到上下文的状态对象来完成实际的状态转换。

## 适用场景

* 如果对象需要根据自身当前状态进行不同行为，同时状态的数量非常多且与状态相关的代码会频繁变更的话，可使用状态模式。

模式建议你将所有特定于状态的代码抽取到一组独立的类中。这样一来，你可以在独立于其他状态的情况下添加新状态或修改已有状态，从而减少维护成本。

* 如果某个类需要根据成员变量的当前值改变自身行为，从而需要使用大量的条件语句时，可使用该模式。

状态模式会将这些条件语句的分支抽取到相应状态类的方法中。同时，你还可以清除主要类中与特定状态相关的临时成员变量和帮手方法代码。

* 当相似状态和基于条件的状态机转换中存在许多重复代码时，可使用状态模式。

状态模式让你能够生成状态类层次结构，通过将公用代码抽取到抽象基类中来减少重复。 

## 实现方式

1. 确定哪些类是上下文。它可能是包含依赖于状态的代码的已有类；如果特定于状态的代码分散在多个类中，那么它可能是一个新的类。
2. 声明状态接口。虽然你可能会需要完全复制上下文中声明的所有方法，但最好是仅把关注点放在那些可能包含特定于状态的行为的方法上。
3. 为每个实际状态创建一个继承于状态接口的类。然后检查上下文中的方法并将与特定状态相关的所有代码抽取到新建的类中。在将代码移动到状态类的过程中，你可能会发现它依赖于上下文中的一些私有成员。你可以采用以下几种变通方式： 
   * 将这些成员变量或方法设为公有。 
   * 将需要抽取的上下文行为更改为上下文中的公有方法，然后在状态类中调用。这种方式简陋却便捷，你可以稍后再对其进行修补。 
   * 将状态类嵌套在上下文类中。这种方式需要你所使用的编程语言支持嵌套类。
4. 在上下文类中添加一个状态接口类型的引用成员变量，以及一个用于修改该成员变量值的公有设置器。 
5. 再次检查上下文中的方法，将空的条件语句替换为相应的状态对象方法。
6. 为切换上下文状态，你需要创建某个状态类实例并将其传递给上下文。你可以在上下文、各种状态或客户端中完成这项工作。无论在何处完成这项工作，该类都将依赖于其所实例化的具体类。

## 优点

* 单一职责原则。将与特定状态相关的代码放在单独的类中。
* 开闭原则。无需修改已有状态类和上下文就能引入新状态。
* 通过消除臃肿的状态机条件语句简化上下文代码。

## 缺点

如果状态机只有很少的几个状态，或者很少发生改变，那么应用该模式可能会显得小题大作。

## 与其他模式的关系

* **桥接**、**状态**和**策略**（在某种程度上包括**适配器**）模式的接口非常相似。实际上，它们都基于**组合**模式——即将工作委派给其他对象，不过也各自解决了不同的问题。模式并不只是以特定方式组织代码的配方，你还可以使用它们来和其他开发者讨论模式所解决的问题。 
* **状态**可被视为**策略**的扩展。两者都基于组合机制：它们都通过将部分工作委派给“帮手”对象来改变其在不同情景下的行为。策略使得这些对象相互之间完全独立，它们不知道其他对象的存在。 但状态模式没有限制具体状态之间的依赖，且允许它们自行改变在不同情景下的状态。

## 实例

Context.h：

```c++
#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <string>
#include <memory>

class AbstractState;

// 论坛账号
class ForumAccount {
 public:
    explicit ForumAccount(std::string name);
    void set_state(std::shared_ptr<AbstractState> state) {
        state_ = state;
    }
    std::shared_ptr<AbstractState> get_state() {
        return state_;
    }
    std::string get_name() {
        return name_;
    }
    void downloadFile(int score);
    void writeNote(int score);
    void replyNote(int score);

 private:
    std::shared_ptr<AbstractState> state_;
    std::string name_;
};

#endif  // CONTEXT_H_
```

Context.cpp：

```c++
#include "Context.h"

#include "ConcreteState.h"
#include <string>

ForumAccount::ForumAccount(std::string name)
    : name_(name), state_(std::make_shared<PrimaryState>(this)) {
    printf("账号%s注册成功!\n", name.c_str());
}

void ForumAccount::downloadFile(int score) {
    state_->downloadFile(score);
}

void ForumAccount::writeNote(int score) {
    state_->writeNote(score);
}

void ForumAccount::replyNote(int score) {
    state_->replyNote(score);
}
```

State.h：

```c++
#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <cstdio>
#include "Context.h"

class AbstractState {
 public:
    virtual void checkState() = 0;

    void set_point(int point) {
        point_ = point;
    }
    int get_point() {
        return point_;
    }
    void set_state_name(std::string name) {
        state_name_ = name;
    }
    std::string get_state_name() {
        return state_name_;
    }
    ForumAccount* get_account() {
        return account_;
    }

    virtual void downloadFile(int score) {
        printf("%s下载文件, 扣除%d积分。\n", account_->get_name().c_str(), score);
        point_ -= score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void writeNote(int score) {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score);
        point_ += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void replyNote(int score) {
        printf("%s回复留言, 增加%d积分。\n", account_->get_name().c_str(), score);
        point_ += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

 protected:
    ForumAccount* account_;
    int point_;
    std::string state_name_;
};

#endif  // STATE_H_
```

ConcreteState.h：

```c++
#ifndef CONCRETE_STATE_H_
#define CONCRETE_STATE_H_

#include <cstdio>
#include "State.h"

// 具体状态类: 新手
class PrimaryState : public AbstractState {
 public:
    explicit PrimaryState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "新手";
    }
    explicit PrimaryState(ForumAccount *account) {
        account_ = account;
        point_ = 0;
        state_name_ = "新手";
    }
    void downloadFile(int score) override {
        printf("对不起, %s没有下载文件的权限!\n", account_->get_name().c_str());
    }
    void checkState() override;
};

// 具体状态类: 高手
class MiddleState : public AbstractState {
 public:
    explicit MiddleState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "高手";
    }

    void writeNote(int score) override {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score * 2);
        point_ += score * 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }
    void checkState() override;
};

// 具体状态类: 专家
class HighState : public AbstractState {
 public:
    explicit HighState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "专家";
    }

    void writeNote(int score) override {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score * 2);
        point_ += score * 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void downloadFile(int score) {
        printf("%s下载文件, 扣除%d积分。\n", account_->get_name().c_str(), score / 2);
        point_ -= score / 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    void checkState() override;
};

#endif  // CONCRETE_STATE_H_

```

ConcreteState.cpp：

```c++
#include "ConcreteState.h"

#include <memory>

void PrimaryState::checkState() {
    if (point_ >= 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    } else if (point_ >= 100) {
        account_->set_state(std::make_shared<MiddleState>(this));
    }
}

void MiddleState::checkState() {
    if (point_ >= 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    } else if (point_ < 100) {
        account_->set_state(std::make_shared<PrimaryState>(this));
    }
}

void HighState::checkState() {
    if (point_ < 100) {
        account_->set_state(std::make_shared<PrimaryState>(this));
    } else if (point_ < 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    }
}
```

main.cpp：

```c++
#include "Context.h"

int main() {
    // 注册新用户
    ForumAccount account("TOMOCAT");
    account.writeNote(20);
    account.downloadFile(20);
    account.replyNote(100);
    account.writeNote(40);
    account.downloadFile(80);
    account.writeNote(1000);
    account.downloadFile(80);
    return 0;
}
```

编译运行：

```bash
$g++ -g main.cpp Context.cpp ConcreteState.cpp -o state -std=c++11
$./state 
账号TOMOCAT注册成功!
TOMOCAT发布留言, 增加20积分。
TOMOCAT剩余积分为20, 当前级别为新手。
对不起, TOMOCAT没有下载文件的权限!
TOMOCAT回复留言, 增加100积分。
TOMOCAT剩余积分为120, 当前级别为高手。
TOMOCAT发布留言, 增加80积分。
TOMOCAT剩余积分为200, 当前级别为高手。
TOMOCAT下载文件, 扣除80积分。
TOMOCAT剩余积分为120, 当前级别为高手。
TOMOCAT发布留言, 增加2000积分。
TOMOCAT剩余积分为2120, 当前级别为专家。
TOMOCAT下载文件, 扣除40积分。
TOMOCAT剩余积分为2080, 当前级别为专家。
```

