#ifndef CONCRETE_DECORATOR_H_
#define CONCRETE_DECORATOR_H_

#include <string>
#include "BaseDecorator.h"

// 加密装饰器
class EncryptionDecorator : public DataSourceDecorator {
 public:
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(std::string data) override {
        // 1. 对传递数据进行加密(这里仅简单实现)
        data = "已加密(" + data + ")";
        // 2. 将加密后数据传递给被封装对象 writeData（写入数据）方法
        data_source_->writeData(data);
        return;
    }
};

// 压缩装饰器
class CompressionDecorator : public DataSourceDecorator {
 public:
    using DataSourceDecorator::DataSourceDecorator;
    void writeData(std::string data) override {
        // 1. 对传递数据进行压缩(这里仅简单实现)
        data = "已压缩(" + data + ")";
        // 2. 将压缩后数据传递给被封装对象 writeData（写入数据）方法
        data_source_->writeData(data);
        return;
    }
};

#endif  // CONCRETE_DECORATOR_H_