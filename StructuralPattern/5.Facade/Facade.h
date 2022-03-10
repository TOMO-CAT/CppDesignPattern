#ifndef FACADE_H_
#define FACADE_H_

#include "SubSystem.h"

class ComputerOperator {
 public:
    ComputerOperator() {
        memory_ = new Memory();
        processor_ = new Processor();
        hard_disk_ = new HardDisk();
        os_ = new OS();
    }
    ~ComputerOperator() {
        delete memory_;
        delete processor_;
        delete hard_disk_;
        delete os_;
        memory_ = nullptr;
        processor_ = nullptr;
        hard_disk_ = nullptr;
        os_ = nullptr;
    }

    void powerOn() {
        std::cout << "正在开机..." << std::endl;
        memory_->selfCheck();
        processor_->run();
        hard_disk_->read();
        os_->load();
        std::cout << "开机成功!" << std::endl;
    }

 private:
    Memory* memory_;
    Processor* processor_;
    HardDisk* hard_disk_;
    OS* os_;
};

#endif  // FACADE_H_