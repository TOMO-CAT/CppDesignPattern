#ifndef ELEMENT_H_
#define ELEMENT_H_

#include "Visitor.h"

// 抽象元素类
class Product {
 public:
    virtual void accept(Vistor *vistor) = 0;
};

#endif  // ELEMENT_H_