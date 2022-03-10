#include "Publisher.h"
#include "ConcreteSubscriber.h"

int main() {
    // 发布者
    Cat cat;

    // 观察者
    Mouse mouse;
    Dog dog;

    // 添加订阅关系
    cat.attach(&mouse);
    cat.attach(&dog);

    // 发布消息
    cat.cry();
    return 0;
}