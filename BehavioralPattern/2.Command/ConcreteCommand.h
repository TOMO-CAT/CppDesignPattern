#ifndef CONCRETE_COMMAND_H_
#define CONCRETE_COMMAND_H_

#include <memory>
#include "Command.h"
#include "Receiver.h"

// 具体命令类: 打开电视
class TVOpenCommand : public Command{
 public:
    explicit TVOpenCommand(std::shared_ptr<Television> tv) : tv_(tv) {}

    void execute() {
        tv_->open();
    }

 private:
    std::shared_ptr<Television> tv_;
};

// 具体命令类: 关闭电视
class TVCloseCommand : public Command{
 public:
    explicit TVCloseCommand(std::shared_ptr<Television> tv) : tv_(tv) {}

    void execute() {
        tv_->close();
    }

 private:
    std::shared_ptr<Television> tv_;
};


// 具体命令类: 切换频道
class TVChangeCommand : public Command{
 public:
    explicit TVChangeCommand(std::shared_ptr<Television> tv) : tv_(tv) {}
    void execute() {
        tv_->changeChannel();
    }

 private:
    std::shared_ptr<Television> tv_;
};

#endif  // CONCRETE_COMMAND_H_