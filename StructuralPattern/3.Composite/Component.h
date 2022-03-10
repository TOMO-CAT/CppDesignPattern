#ifndef COMPONENT_H_
#define COMPONENT_H_

// 组件接口会声明组合中简单和复杂对象的通用操作, C++中实现成抽象基类。
class Graphic {
 public:
    virtual void move2somewhere(int x, int y) = 0;
    virtual void draw() = 0;
};

#endif  // COMPONENT_H_