#ifndef ABSTRACTION_H_
#define ABSTRACTION_H_

#include <string>
#include "Implementation.h"

// 抽象类: Pen
class Pen {
 public:
    virtual void draw(std::string name) = 0;
    void set_color(Color* color) {
        color_ = color;
    }

 protected:
    Color* color_;
};

#endif  // ABSTRACTION_H_