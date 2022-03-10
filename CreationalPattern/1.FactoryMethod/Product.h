#ifndef  PRODUCT_H_
#define  PRODUCT_H_

#include <string>

// 抽象产品类 电影
class Movie {
 public:
    virtual std::string get_a_movie() = 0;
};

#endif  // PRODUCT_H_