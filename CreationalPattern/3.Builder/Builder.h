#ifndef  BUILDER_H_
#define  BUILDER_H_

#include "Product.h"

// 抽象建造者
class CarBuilder {
 public:
    Car getCar() {
        return car_;
    }

    // 抽象方法
    virtual void buildTire() = 0;
    virtual void buildSteeringWheel() = 0;
    virtual void buildEngine() = 0;

 protected:
    Car car_;
};

#endif  // BUILDER_H_