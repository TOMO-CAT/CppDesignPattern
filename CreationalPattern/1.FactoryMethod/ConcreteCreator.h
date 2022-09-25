#ifndef CONCRETE_CREATOR_H_
#define CONCRETE_CREATOR_H_

#include "ConcreteProduct.h"
#include "Creator.h"
#include <memory>

// 具体工厂类 中国生产者
class ChineseProducer : public Factory {
 public:
    std::shared_ptr<Movie> get_movie() override { return std::make_shared<ChineseMovie>(); }
};

// 具体工厂类 日本生产者
class JapaneseProducer : public Factory {
 public:
    std::shared_ptr<Movie> get_movie() override { return std::make_shared<JapaneseMovie>(); }
};

// 具体工厂类 美国生产者
class AmericanProducer : public Factory {
 public:
    std::shared_ptr<Movie> get_movie() override { return std::make_shared<AmericanMovie>(); }
};

#endif  // CONCRETE_CREATOR_H_