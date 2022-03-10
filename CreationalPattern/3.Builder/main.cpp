#include "Director.h"
#include "ConcreteBuilder.h"

int main() {
    // 抽象建造者(一般是动态确定的)
    CarBuilder* builder;
    // 指挥者
    Director* director = new Director();
    // 产品
    Car car;

    // 建造奔驰
    std::cout << "==========construct benz car==========" << std::endl;
    builder = new BenzBuilder();
    director->set_builder(builder);
    car = director->ConstructCar();
    delete builder;

    // 建造奥迪
    std::cout << "==========construct audi car==========" << std::endl;
    builder = new AudiBuilder();
    director->set_builder(builder);
    car = director->ConstructCar();
    delete builder;

    std::cout << "==========done==========" << std::endl;
    delete director;
}