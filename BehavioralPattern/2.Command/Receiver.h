#ifndef RECEIVER_H_
#define RECEIVER_H_

#include <iostream>

// 接受者: 电视
class Television{
 public:
    void open() {
        std::cout << "打开电视机!" << std::endl;
    }

    void close() {
        std::cout << "关闭电视机!" << std::endl;
    }

    void changeChannel(){
        std::cout << "切换电视频道!" << std::endl;
    }
};

#endif  // RECEIVER_H_