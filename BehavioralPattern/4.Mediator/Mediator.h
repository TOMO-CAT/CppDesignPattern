#ifndef MEDIATOR_H_
#define MEDIATOR_H_

#include <string>

class Colleague;

// 抽象中介者
class Mediator {
 public:
    // 声明抽象方法
    virtual void registerMethod(Colleague*) = 0;
    // 声明抽象方法
    virtual void operation(Colleague*) = 0;
};

#endif  // MEDIATOR_H_