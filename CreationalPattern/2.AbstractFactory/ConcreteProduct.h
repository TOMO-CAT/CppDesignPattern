#ifndef  CONCRETE_PRODUCT_H_
#define  CONCRETE_PRODUCT_H_

#include <iostream>
#include <string>
#include "AbstractProduct.h"

// 具体产品类 电影::国产电影
class ChineseMovie : public Movie {
    std::string showMovieName() override {
        return "《让子弹飞》";
    }
};

// 具体产品类 电影::日本电影
class JapaneseMovie : public Movie {
    std::string showMovieName() override {
        return "《千与千寻》";
    }
};

// 具体产品类 书籍::国产书籍
class ChineseBook : public Book {
    std::string showBookName() override {
        return "《三国演义》";
    }
};

// 具体产品类 书籍::日本书籍
class JapaneseBook : public Book {
    std::string showBookName() override {
        return "《白夜行》";
    }
};

#endif  // CONCRETE_PRODUCT_H_