#ifndef SERVICE_H_
#define SERVICE_H_

// 方钉: 适配者类, 即和客户端不兼容的类
class SquarePeg {
 public:
    explicit SquarePeg(int w) : width_(w) {}
    int get_width() {
        return width_;
    }

 private:
    int width_;
};

#endif  // SERVICE_H_