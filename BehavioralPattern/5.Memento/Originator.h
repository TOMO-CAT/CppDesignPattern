#ifndef ORIGINATOR_H_
#define ORIGINATOR_H_

#include <cstdio>
#include <string>
#include <memory>
#include "Memento.h"

// 原发器中包含了一些可能会随时间变化的重要数据
// 它还定义了在备忘录中保存自身状态的方法, 以及从备忘录中恢复状态的方法
class Editor {
 public:
    void setText(std::string text) {
        text_ = text;
    }
    void setCursor(int x, int y) {
        cur_x_ = x;
        cur_y_ = y;
    }
    void setSelectionWidth(double width) {
        selection_width_ = width;
    }

    // 在备忘录中保存当前的状态
    std::shared_ptr<Snapshot> createSnapshot() {
        // 备忘录是不可变的对象, 因此原发器会将自身状态作为参数传递给备忘录的构造函数
        auto res = std::make_shared<Snapshot>(text_, cur_x_, cur_y_, selection_width_);
        printf("创建编辑器快照成功, text:%s x:%d y:%d width:%.2f\n", text_.c_str(), cur_x_, cur_y_, selection_width_);
        return res;
    }

    void resotre(std::shared_ptr<Snapshot> sptr_snapshot) {
        text_ = sptr_snapshot->get_text();
        cur_x_ = sptr_snapshot->get_cur_x();
        cur_y_ = sptr_snapshot->get_cur_y();
        selection_width_ = sptr_snapshot->get_selection_width();
        printf("恢复编辑器状态成功, text:%s x:%d y:%d width:%.2f\n", text_.c_str(), cur_x_, cur_y_, selection_width_);
    }

 private:
    // 文本
    std::string text_;
    // 光标位置
    int cur_x_;
    int cur_y_;
    // 当前滚动条位置
    double selection_width_;
};

#endif  // ORIGINATOR_H_