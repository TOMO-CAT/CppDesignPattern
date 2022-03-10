#ifndef STRATEGY_H_
#define STRATEGY_H_

#include <vector>

// 抽象策略类: 排序
class Sort {
 public:
    virtual void sortVector(std::vector<int> &arr) = 0;
};

#endif  // STRATEGY_H_