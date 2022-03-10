#ifndef CONCRETE_ITERATOR_H_
#define CONCRETE_ITERATOR_H_

#include <string>
#include <vector>
#include "Iterator.h"

// 具体迭代器
class SkyworthIterator : public TVIterator{
 public:
    explicit SkyworthIterator(std::vector<std::string> &tvs) : tvs_(tvs) {}

    void next() override {
        if (current_index_ < tvs_.size()) {
            current_index_++;
        }
    }

    void previous() override {
        if (current_index_ > 0) {
            current_index_--;
        }
    }

    void setChannel(int i) override {
        current_index_ = i;
    }

    std::string currentChannel() override {
        return tvs_[current_index_];
    }

    bool isLast() override {
        return current_index_ == tvs_.size();
    }

    bool isFirst() override {
        return current_index_ == 0;
    }

 private:
    std::vector<std::string> &tvs_;
    int current_index_ = 0;
};

#endif  // CONCRETE_ITERATOR_H_