#ifndef CONCRETE_HANDLER_H_
#define CONCRETE_HANDLER_H_

#include <string>
#include <cstdio>
#include "BaseHandler.h"

// 具体处理者: 组长(仅处理面额<=10的票据)
class GroupLeader : public BaseApprover {
 public:
    explicit GroupLeader(std::string name) : BaseApprover(10, name) {}
};

// 具体处理者: 经理(仅处理面额<=100的票据)
class Manager : public BaseApprover {
 public:
    explicit Manager(std::string name) : BaseApprover(100, name) {}
};


// 具体处理者: 老板(仅处理面额<=1000的票据)
class Boss : public BaseApprover {
 public:
    explicit Boss(std::string name) : BaseApprover(1000, name) {}
};



#endif  // CONCRETE_HANDLER_H_