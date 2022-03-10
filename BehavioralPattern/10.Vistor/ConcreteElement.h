#ifndef CONCRETE_ELEMENT_H_
#define CONCRETE_ELEMENT_H_

#include "Element.h"

// 具体产品类: 苹果
class Apple : public Product {
 public:
    void accept(Vistor *vistor) override {
        vistor->visit(this);
    }
};

// 具体产品类: 书籍
class Book : public Product {
 public:
    void accept(Vistor *vistor) override {
        vistor->visit(this);
    }
};


#endif  // CONCRETE_ELEMENT_H_