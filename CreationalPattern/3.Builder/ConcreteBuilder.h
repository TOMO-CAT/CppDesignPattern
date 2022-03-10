#ifndef CONCRETE_BUILDER_H_
#define CONCRETE_BUILDER_H_

#include "Builder.h"

// 具体建造者 奔驰
class BenzBuilder : public CarBuilder {
 public:
    // 具体实现方法
    void buildTire() override {
        car_.set_car_tire("benz_tire");
    }
    void buildSteeringWheel() override {
        car_.set_car_steering_wheel("benz_steering_wheel");
    }
    void buildEngine() override {
        car_.set_car_engine("benz_engine");
    }
};

// 具体建造者 奥迪
class AudiBuilder : public CarBuilder {
 public:
    // 具体实现方法
    void buildTire() override {
        car_.set_car_tire("audi_tire");
    }
    void buildSteeringWheel() override {
        car_.set_car_steering_wheel("audi_steering_wheel");
    }
    void buildEngine() override {
        car_.set_car_engine("audi_engine");
    }
};

#endif  // CONCRETE_BUILDER_H_