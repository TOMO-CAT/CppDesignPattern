#ifndef SUB_SYSTEM_H_
#define SUB_SYSTEM_H_

#include<iostream>

// 内存
class Memory {
 public:
    Memory() {}
    void selfCheck() {
        std::cout << "内存自检中..." << std::endl;
        std::cout << "内存自检完成!" << std::endl;
    }
};

// 处理器
class Processor {
 public:
    Processor() {}
    void run() {
        std::cout << "启动CPU中..." << std::endl;
        std::cout << "启动CPU成功!" << std::endl;
    }
};

// 硬盘
class HardDisk {
 public:
    HardDisk() {}
    void read() {
        std::cout << "读取硬盘中..." << std::endl;
        std::cout << "读取硬盘成功!" << std::endl;
    }
};

// 操作系统
class OS {
 public:
    OS() {}
    void load() {
        std::cout << "载入操作系统中..." << std::endl;
        std::cout << "载入操作系统成功!" << std::endl;
    }
};

#endif  // SUB_SYSTEM_H_