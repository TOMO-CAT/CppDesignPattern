#ifndef SINGLETON_H_
#define SINGLETON_H_

class Singleton {
 public:
    static Singleton* GetInstance() {
        return instance_;
    }

 private:
    Singleton() {}
    static Singleton* instance_;
};

#endif  // SINGLETON_H_