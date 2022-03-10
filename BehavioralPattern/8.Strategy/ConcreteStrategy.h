#ifndef CONCRETE_STRATEGY_H_
#define CONCRETE_STRATEGY_H_

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include "Strategy.h"

// 打印vector内容
void printVector(const std::string prefix, const std::vector<int> &vi) {
    std::cout << prefix;
    for (auto i : vi) {
        std::cout << " " << i;
    }
    std::cout << std::endl;
}

// 具体策略类: 冒泡排序
class BubbleSort : public Sort {
 public:
    void sortVector(std::vector<int> &vi) override {
        printVector("冒泡排序前:", vi);
        int len = vi.size();
        // 轮次: 从1到n-1轮
        for (int i = 0; i < len - 1; ++i) {
            // 优化: 判断本轮是否有交换元素, 如果没交换则可直接退出
            bool is_exchange = false;

            for (int j = 0; j < len - i - 1; ++j) {
                if (vi[j] > vi[j+1]) {
                    std::swap(vi[j], vi[j+1]);
                    is_exchange = true;
                }
            }

            // 如果本轮无交换, 则可以直接退出
            if (!is_exchange) {
                printVector("冒泡排序后:", vi);
                return;
            }
        }
        printVector("冒泡排序后:", vi);
    }
};

// 具体策略类: 选择排序
class SelectionSort : public Sort {
 public:
    void sortVector(std::vector<int> &vi) override {
        printVector("选择排序前:", vi);
        // 需要进行 n-1 轮
        for (int i = 0; i < vi.size() - 1; ++i) {
            // 找到此轮的最小值下标
            int min_index = i;
            for (int j = i + 1; j < vi.size(); ++j) {
                if (vi[j] < vi[min_index]) {
                    min_index = j;
                }
            }

            std::swap(vi[i], vi[min_index]);
        }
        printVector("选择排序后:", vi);
    }
};

// 具体策略类: 插入排序
class InsertionSort : public Sort {
 public:
    void sortVector(std::vector<int> &vi) override {
        printVector("插入排序前:", vi);
        // 第一轮不需要操作, 第二轮比较一次, 第n轮比较 n-1 次
        for (int i = 1; i < vi.size(); ++i) {
            // 存储待插入的值和下标
            int insert_value = vi[i];
            int j = i - 1;

            while (j >= 0 && vi[j] > insert_value) {
                vi[j + 1] = vi[j];  // 如果左侧的已排序元素比目标值大, 那么右移
                j--;
            }

            // 注意这里insert_index 需要+1
            vi[j + 1] = insert_value;
        }
        printVector("插入排序后:", vi);
    }
};

#endif  // CONCRETE_STRATEGY_H_