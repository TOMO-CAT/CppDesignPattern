#ifndef CONCRETE_COMPONENT_H_
#define CONCRETE_COMPONENT_H_

#include <string>
#include <cstdio>
#include <iostream>
#include "Component.h"

// 具体组件提供操作的默认实现, 这些类在程序中可能会有几个变体
class FileDataSource : public DataSource {
 public:
    explicit FileDataSource(std::string file_name) : file_name_(file_name) {}
    void writeData(std::string data) override {
        printf("写入文件%s中: %s\n", file_name_.c_str(), data.c_str());
        return;
    }

 private:
    std::string file_name_;
};

#endif  // CONCRETE_COMPONENT_H_