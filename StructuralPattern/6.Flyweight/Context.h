#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <string>
#include "Flyweight.h"

// 情景对象包含树类型的「外在状态」, 程序中可以创建数十亿个此类对象, 因为它们体积很小: 仅有两个浮点坐标类型和一个引用成员变量
class Tree {
 public:
    Tree(double x, double y, TreeType* t) : x_(x), y_(y), type_(t) {}
    void draw(std::string canvas) {
        return type_->draw(canvas, x_, y_);
    }

 private:
    double x_;
    double y_;
    TreeType* type_;
};

#endif  // CONTEXT_H_