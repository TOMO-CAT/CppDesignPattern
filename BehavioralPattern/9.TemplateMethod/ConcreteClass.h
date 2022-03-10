#ifndef CONCRETE_METHOD_H_
#define CONCRETE_METHOD_H_

#include "AbstractClass.h"

// 具体类: 存款
class Deposit : public BankTemplateMethod {
 public:
    void transact() override {
        std::cout << "存款..." << std::endl;
    }
};

// 具体类: 取款
class Withdraw : public BankTemplateMethod {
 public:
    void transact() override {
        std::cout << "取款..." << std::endl;
    }
};

// 具体类: 转账
class Transfer : public BankTemplateMethod {
 public:
    void transact() override {
        std::cout << "转账..." << std::endl;
    }
};

#endif  // CONCRETE_METHOD_H_