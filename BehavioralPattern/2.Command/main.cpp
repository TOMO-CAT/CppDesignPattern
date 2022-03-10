#include "Invoker.h"
#include "ConcreteCommand.h"

int main() {
    // 接收者: 电视机
    std::shared_ptr<Television> tv = std::make_shared<Television>();

    // 命令
    std::shared_ptr<Command> openCommand = std::make_shared<TVOpenCommand>(tv);
    std::shared_ptr<Command> closeCommand = std::make_shared<TVCloseCommand>(tv);
    std::shared_ptr<Command> changeCommand = std::make_shared<TVChangeCommand>(tv);

    // 调用者: 遥控器
    std::shared_ptr<Controller> controller = std::make_shared<Controller>();

    // 测试
    controller->setCommand(openCommand);
    controller->executeCommand();
    controller->setCommand(closeCommand);
    controller->executeCommand();
    controller->setCommand(changeCommand);
    controller->executeCommand();
}