#ifndef INVOKER_H_
#define INVOKER_H_

#include <memory>
#include "Command.h"

// 触发者: 遥控器
class Controller{
 public:
    Controller() {}
    // 设置命令
    void setCommand(std::shared_ptr<Command> cmd) {
        cmd_ = cmd;
    }
    // 执行命令
    void executeCommand() {
        cmd_->execute();
    }

 private:
    std::shared_ptr<Command> cmd_;
};

#endif  // INVOKER_H_