#ifndef CONCRETE_FACTORY_H_
#define CONCRETE_FACTORY_H_

#include <memory>
#include "AbstractFactory.h"
#include "ConcreteProduct.h"

// 具体工厂类 中国生产者
class ChineseProducer : public Factory {
 public:
    std::shared_ptr<Movie> productMovie() override {
        return std::make_shared<ChineseMovie>();
    }

    std::shared_ptr<Book> productBook() override {
        return std::make_shared<ChineseBook>();
    }
};

// 具体工厂类 日本生产者
class JapaneseProducer : public Factory {
 public:
    std::shared_ptr<Movie> productMovie() override {
        return std::make_shared<JapaneseMovie>();
    }

    std::shared_ptr<Book> productBook() override {
        return std::make_shared<JapaneseBook>();
    }
};

#endif  // CONCRETE_FACTORY_H_