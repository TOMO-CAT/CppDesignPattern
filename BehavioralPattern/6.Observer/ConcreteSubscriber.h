#ifndef CONCRETE_SUBSCRIBER_H_
#define CONCRETE_SUBSCRIBER_H_

#include <iostream>
#include "Subscriber.h"

// 具体观察者1: 老鼠
class Mouse : public AbstractObserver {
 public:
    void response() override {
        std::cout << "老鼠逃跑" << std::endl;
    }
};

// 具体观察者2: 狗
class Dog : public AbstractObserver {
 public:
    void response() override {
        std::cout << "狗追猫" << std::endl;
    }
};


#endif  // CONCRETE_SUBSCRIBER_H_