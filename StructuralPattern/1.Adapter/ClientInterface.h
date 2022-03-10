#ifndef CLIENT_INTERFACE_H_
#define CLIENT_INTERFACE_H_

// 圆钉: 客户端接口, 在C++中定义成抽象基类
class RoundPeg {
 public:
    RoundPeg() {}
    virtual int get_radius() = 0;
};

#endif  // CLIENT_INTERFACE_H_