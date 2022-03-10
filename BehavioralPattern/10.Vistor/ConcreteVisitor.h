#ifndef CONCRETE_VISTOR_H_
#define CONCRETE_VISTOR_H_

#include <iostream>
#include "Visitor.h"

// 具体访问者类: 顾客
class Customer : public Vistor {
 public:
    void visit(Apple *apple) {
        std::cout << "顾客" << name_ << "挑选苹果。" << std::endl;
    }

    void visit(Book *book) {
        std::cout << "顾客" << name_ << "买书。" << std::endl;
    }
};

// 具体访问者类： 收银员
class Saler : public Vistor {
 public:
    void visit(Apple *apple) {
        std::cout << "收银员" << name_ << "给苹果过称, 然后计算价格。" << std::endl;
    }

    void visit(Book *book) {
        std::cout << "收银员" << name_ << "计算书的价格。" << std::endl;
    }
};

#endif  // CONCRETE_VISTOR_H_