#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <iostream>
#include <string>
#include <mutex>

class Singleton {
 public:
    static Singleton* GetInstance() {
        if (instance_ == nullptr) {
            // 加锁保证多个线程并发调用getInstance()时只会创建一个实例
            m_mutex_.lock();
            if (instance_ == nullptr) {
                instance_ = new Singleton();
            }
            m_mutex_.unlock();
        }
        return instance_;
    }
 private:
    Singleton() {}
    static Singleton* instance_;
    static std::mutex m_mutex_;
};

#endif  // SINGLETON_H_