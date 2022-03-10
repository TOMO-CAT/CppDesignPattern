#ifndef LEAF_H_
#define LEAF_H_

#include <cstdio>
#include "Component.h"

// 叶节点类代表组合的中断对象。叶节点对象中不能包含任何子对象。
// 叶节点对象通常会完成实际的工作, 组合对象则仅会将工作委派给自己的子部件。

// 点
class Dot : public Graphic {
 public:
    Dot(int x, int y) : x_(x), y_(y) {}
    void move2somewhere(int x, int y) override {
        x_ += x;
        y_ += y;
        return;
    }
    void draw() override {
        printf("在(%d,%d)处绘制点\n", x_, y_);
        return;
    }

 private:
    int x_;
    int y_;
};

// 圆
class Circle : public Graphic {
 public:
    explicit Circle(int r, int x, int y) : radius_(r), x_(x), y_(y) {}
    void move2somewhere(int x, int y) override {
        x_ += x;
        y_ += y;
        return;
    }
    void draw() override {
        printf("以(%d,%d)为圆心绘制半径为%d的圆\n", x_, y_, radius_);
    }

 private:
    // 半径与圆心坐标
    int radius_;
    int x_;
    int y_;
};

#endif  // LEAF_H_