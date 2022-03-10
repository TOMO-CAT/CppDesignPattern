#ifndef MEMENTO_H_
#define MEMENTO_H_

#include <string>

// 备忘录类保存编辑器的过往状态
class Snapshot {
 public:
    Snapshot(std::string text, int x, int y, double width)
        : text_(text), cur_x_(x), cur_y_(y), selection_width_(width) {}
    std::string get_text() {
        return text_;
    }
    int get_cur_x() {
        return cur_x_;
    }
    int get_cur_y() {
        return cur_y_;
    }
    double get_selection_width() {
        return selection_width_;
    }

 private:
    const std::string text_;
    const int cur_x_;
    const int cur_y_;
    const double selection_width_;
};

#endif  // MEMENTO_H_