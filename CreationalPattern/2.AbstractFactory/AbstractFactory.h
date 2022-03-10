#ifndef  ABSTRACT_FACTORY_H_
#define  ABSTRACT_FACTORY_H_

#include <memory>
#include "AbstractProduct.h"

// 抽象工厂类 生产电影和书籍类等
class Factory {
 public:
    virtual std::shared_ptr<Movie> productMovie() = 0;
    virtual std::shared_ptr<Book> productBook() = 0;
};

#endif  // ABSTRACT_FACTORY_H_