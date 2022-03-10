#ifndef COMPOSITE_H_
#define COMPOSITE_H_

#include <map>
#include "Component.h"

// 组合类表示可能包含子项目的复杂组件。组合对象通常会将实际工作委派给子项目，然后“汇总”结果。
class CompoundGraphic : public Graphic {
 public:
    void add(int id, Graphic* child) {
        childred_[id] = (child);
    }
    void remove(int id) {
        childred_.erase(id);
    }
    void move2somewhere(int x, int y) override {
        for (auto iter = childred_.cbegin(); iter != childred_.cend(); iter++) {
            iter->second->move2somewhere(x, y);
        }
    }
    void draw() override {
        for (auto iter = childred_.cbegin(); iter != childred_.cend(); iter++) {
            iter->second->draw();
        }
    }

 private:
    // key是图表id, value是图表指针
    std::map<int, Graphic*> childred_;
};

#endif  // COMPOSITE_H_