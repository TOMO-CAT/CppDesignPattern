#ifndef VISTOR_H_
#define VISTOR_H_

#include <string>

class Apple;
class Book;

// 抽象访问者
class Vistor {
 public:
    void set_name(std::string name) {
        name_ = name;
    }

    virtual void visit(Apple *apple) = 0;
    virtual void visit(Book *book) = 0;

 protected:
    std::string name_;
};

#endif  // VISTOR_H_