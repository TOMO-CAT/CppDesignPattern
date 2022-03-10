#include <iostream>
#include "ConcreteMediator.h"
#include "Component.h"

int main() {
    // 房产中介
    Agency *mediator = new Agency();

    // 三位房东
    Landlord *l1 = new Landlord("张三", 1820, "天津", "1333");
    Landlord *l2 = new Landlord("李四", 2311, "北京", "1555");
    Landlord *l3 = new Landlord("王五", 3422, "河北", "1777");
    l1->set_mediator(mediator);
    l2->set_mediator(mediator);
    l3->set_mediator(mediator);
    mediator->registerMethod(l1);
    mediator->registerMethod(l2);
    mediator->registerMethod(l3);

    // 两位租客
    Tenant *t1 = new Tenant("Zhang");
    Tenant *t2 = new Tenant("Yang");
    t1->set_mediator(mediator);
    t2->set_mediator(mediator);
    mediator->registerMethod(t1);
    mediator->registerMethod(t2);

    // 业务逻辑
    t1->ask();
    std::cout << std::endl;
    l1->ask();

    delete mediator;
    delete l1;
    delete l2;
    delete l3;
    delete t1;
    delete t2;
}