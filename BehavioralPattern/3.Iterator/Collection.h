#ifndef COLLECTION_H_
#define COLLECTION_H_

#include <memory>
#include "Iterator.h"

// 抽象集合
class Television {
 public:
    virtual std::shared_ptr<TVIterator> createIterator() = 0;
};

#endif  // COLLECTION_H_