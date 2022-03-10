#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include "ConcreteStrategy.h"
#include "Context.h"

std::vector<int> test_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

int main() {
    ArrayHandler array_handler;

    {
        // 冒泡排序
        BubbleSort* bubble_sort = new BubbleSort();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(test_array), std::end(test_array), rng);
        array_handler.setSortStrategy(bubble_sort);
        array_handler.sortVector(test_array);
        delete bubble_sort;
    }

    {
        // 选择排序
        SelectionSort* select_sort = new SelectionSort();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(test_array), std::end(test_array), rng);
        array_handler.setSortStrategy(select_sort);
        array_handler.sortVector(test_array);
        delete select_sort;
    }

    {
        // 插入排序
        InsertionSort* insert_sort = new InsertionSort();
        auto rng = std::default_random_engine {};
        std::shuffle(std::begin(test_array), std::end(test_array), rng);
        array_handler.setSortStrategy(insert_sort);
        array_handler.sortVector(test_array);
        delete insert_sort;
    }


    return 0;
}