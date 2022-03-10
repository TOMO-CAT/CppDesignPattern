#ifndef REFINED_ABSTRACTION_H_
#define REFINED_ABSTRACTION_H_

#include <string>
#include "Abstraction.h"

// 精确抽象类: BigPen
class BigPen : public Pen {
 public:
    void draw(std::string name) {
        std::string pen_type = "大号钢笔绘制";
        color_->bepaint(pen_type, name);
    }
};

// 精确抽象类: SmallPencil
class SmallPencil : public Pen {
 public:
    void draw(std::string name) {
        std::string pen_type = "小号铅笔绘制";
        color_->bepaint(pen_type, name);
    }
};

#endif  // REFINED_ABSTRACTION_H_