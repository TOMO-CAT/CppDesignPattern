#ifndef  DIRECTOR_H_
#define  DIRECTOR_H_

#include "Builder.h"

class Director {
 public:
    Director() : builder_(nullptr) {}

    void set_builder(CarBuilder *cb) {
        builder_ = cb;
    }

    // 组装汽车
    Car ConstructCar() {
        builder_->buildTire();
        builder_->buildSteeringWheel();
        builder_->buildEngine();
        return builder_->getCar();
    }

 private:
    CarBuilder* builder_;
};

#endif  // DIRECTOR_H_