#ifndef SINGLETON_H_
#define SINGLETON_H_

class Singleton {
 public:
    static Singleton& GetInstance() {
        static Singleton instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

 private:
    Singleton() {}
};

#endif  // SINGLETON_H_