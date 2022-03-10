#ifndef IMPLEMENTATION_H_
#define IMPLEMENTATION_H_

#include <string>
#include <iostream>

// 实现类接口: 颜色
class Color {
 public:
    virtual void bepaint(std::string pen_type, std::string name) = 0;
};

#endif  // IMPLEMENTATION_H_