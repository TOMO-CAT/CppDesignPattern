#ifndef FLYWEIGHT_H_
#define FLYWEIGHT_H_

#include <string>

// 享元类包含了树类型的部分状态, 这些成员变量保存的数值对于特定树而言是唯一的。
// 很多树木之间包含共同的名字、颜色和纹理, 如果在每棵树中都存储这些数据就会浪费大量内存。
// 因此我们将这些「内在状态」导出到一个单独的对象中, 然后让众多的单个树对象去引用它。
class TreeType {
 public:
    TreeType(std::string n, std::string c, std::string t) :
        name_(n), color_(c), texture_(t) {}
    void draw(std::string canvas, double x, double y) {
        // 1. 创建特定类型、颜色和纹理的位图
        // 2. 在画布坐标(x,y)处绘制位图
        return;
    }

 private:
    std::string name_;
    std::string color_;
    std::string texture_;
};

#endif  // FLYWEIGHT_H_