#ifndef HANDLER_H_
#define HANDLER_H_

// 抽象处理者, 在C++中是抽象基类
class ApproverInterface {
 public:
    // 添加上级
    virtual void setSuperior(ApproverInterface* superior) = 0;
    // 处理票据申请, 参数是票据面额
    virtual void handleRequest(double amount) = 0;
};

#endif  // HANDLER_H_