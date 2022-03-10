#ifndef BASE_DECORATOR_H_
#define BASE_DECORATOR_H_

#include <string>
#include "Component.h"

// 装饰基类和其他组件遵循相同的接口。该类的主要任务是定义所有具体装饰的封装接口。
// 封装的默认实现代码中可能会包含一个保存被封装组件的成员变量，并且负责对其进行初始化。
class DataSourceDecorator : public DataSource {
 public:
    explicit DataSourceDecorator(DataSource* ds) : data_source_(ds) {}
    void writeData(std::string data) override {
        data_source_->writeData(data);
    }

 protected:
    DataSource* data_source_;  // component
};

#endif  // BASE_DECORATOR_H_