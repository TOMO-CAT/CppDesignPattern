#ifndef  CREATOR_H_
#define  CREATOR_H_

#include <memory>
#include "Product.h"

// 抽象工厂类 生产电影
class Factory {
 public:
    virtual std::shared_ptr<Movie> get_movie() = 0;
};

#endif  // CREATOR_H_