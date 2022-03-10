#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>

// 部件: 是具体部件和装饰类的共同基类, 在C++中实现成抽象基类
class DataSource {
 public:
    virtual void writeData(std::string data) = 0;
};

#endif  // COMPONENT_H_