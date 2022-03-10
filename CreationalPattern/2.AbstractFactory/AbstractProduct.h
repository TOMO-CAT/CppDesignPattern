#ifndef  ABSTRACT_PRODUCT_H_
#define  ABSTRACT_PRODUCT_H_

#include <string>

// 抽象产品类 电影
class Movie {
 public:
    virtual std::string showMovieName() = 0;
};

// 抽象产品类 书籍
class Book {
 public:
    virtual std::string showBookName() = 0;
};

#endif  // ABSTRACT_PRODUCT_H_