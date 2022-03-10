#ifndef PROTOTYPE_H_
#define PROTOTYPE_H_

// 抽象原型类
class Object {
 public:
    virtual Object* clone() = 0;
};

#endif  // PROTOTYPE_H_