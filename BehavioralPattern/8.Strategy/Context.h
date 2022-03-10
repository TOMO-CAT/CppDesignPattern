#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <vector>
#include "Strategy.h"

class ArrayHandler {
 public:
    void sortVector(std::vector<int> &arr) {
        return sort_->sortVector(arr);
    }
    void setSortStrategy(Sort* sort) {
        sort_ = sort;
    }

 private:
    Sort *sort_;
};

#endif  // CONTEXT_H_