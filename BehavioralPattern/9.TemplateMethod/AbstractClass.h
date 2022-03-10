#ifndef ABSTRACT_METHOD_H_
#define ABSTRACT_METHOD_H_

#include <iostream>

// 抽象类: 银行业务办理流程
class BankTemplateMethod {
 public:
    void takeNumber() {
        std::cout << "排队取号。" << std::endl;
    }

    virtual void transact() = 0;

    void evalute() {
        std::cout << "反馈评分。" << std::endl;
    }

    void process() {
        takeNumber();
        transact();
        evalute();
    }
};

#endif  // ABSTRACT_METHOD_H_