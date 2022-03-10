#include "ConcreteHandler.h"

int main() {
    // 请求处理者: 组长、经理和老板
    GroupLeader* group_leader = new GroupLeader("张组长");
    Manager* manager = new Manager("王经理");
    Boss* boss = new Boss("李老板");

    // 设置上级
    group_leader->setSuperior(manager);
    manager->setSuperior(boss);

    // 不同面额的票据统一先交给组长审批
    group_leader->handleRequest(8);
    group_leader->handleRequest(88);
    group_leader->handleRequest(888);
    group_leader->handleRequest(8888);

    delete group_leader;
    delete manager;
    delete boss;

    return 0;
}