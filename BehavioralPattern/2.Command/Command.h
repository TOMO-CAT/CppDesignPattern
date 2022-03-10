#ifndef COMMAND_H_
#define COMMAND_H_

// 命令接口, C++中为抽象基类
class Command {
 public:
    virtual void execute() = 0;
};

#endif  // COMMAND_H_