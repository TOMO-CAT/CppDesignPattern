#ifndef CLIENT_H_
#define CLIENT_H_

#include "ClientInterface.h"

// 圆孔: 客户端类
class RoundHole {
 public:
    explicit RoundHole(int r) : radius_(r) {}
    int get_radius() {
        return radius_;
    }
    bool isFit(RoundPeg* rp) {
        return radius_ >= rp->get_radius();
    }

 private:
    int radius_;
};

#endif  // CLIENT_H_