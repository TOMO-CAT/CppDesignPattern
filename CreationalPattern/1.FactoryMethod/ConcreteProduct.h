#ifndef  CONCRETE_PRODUCT_H_
#define  CONCRETE_PRODUCT_H_

#include <iostream>
#include <string>
#include "Product.h"

// 具体产品类 电影::国产电影
class ChineseMovie : public Movie {
 public:
    std::string get_a_movie() override {
        return "《让子弹飞》";
    }
};

// 具体产品类 电影::日本电影
class JapaneseMovie : public Movie {
 public:
    std::string get_a_movie() override {
        return "《千与千寻》";
    }
};

// 具体产品类 电影::美国电影
class AmericanMovie : public Movie {
 public:
    std::string get_a_movie() override {
        return "《钢铁侠》";
    }
};

#endif  // CONCRETE_PRODUCT_H_