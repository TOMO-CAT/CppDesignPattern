#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <string>

// 抽象迭代器
class TVIterator{
 public:
    virtual void setChannel(int i) = 0;
    virtual void next() = 0;
    virtual void previous() = 0;
    virtual bool isLast() = 0;
    virtual std::string currentChannel() = 0;
    virtual bool isFirst() = 0;
};

#endif  // ITERATOR_H_