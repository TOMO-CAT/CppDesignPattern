#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Mediator.h"
#include <cstdio>
#include <string>

enum PERSON_TYPE {
    kUnknown,
    kLandlord,
    kTenant,
};

// 组件基类
class Colleague {
 public:
    void set_mediator(Mediator *m) {
        mediator_ = m;
    }
    Mediator* get_mediator() {
        return mediator_;
    }
    void set_personType(PERSON_TYPE pt) {
        person_type_ = pt;
    }
    PERSON_TYPE get_person_type() {
        return person_type_;
    }
    virtual void ask() = 0;
    virtual void answer() = 0;
 private:
    Mediator* mediator_;
    PERSON_TYPE person_type_;
};

// 具体组件1: 房东
class Landlord : public Colleague {
 public:
    Landlord() {
        name_ = "unknown";
        price_ = -1;
        address_ = "unknown";
        phone_number_ = "unknown";
        set_personType(kUnknown);
    }

    Landlord(std::string name, int price, std::string address, std::string phone_number) {
        name_ = name;
        price_ = price;
        address_ = address;
        phone_number_ = phone_number;
        set_personType(kLandlord);
    }

    void answer() override {
        printf("房东姓名:%s 房租:%d 地址:%s 电话:%s\n", name_.c_str(), price_, address_.c_str(), phone_number_.c_str());
    }

    void ask() override {
        printf("房东%s查看租客信息: \n", name_.c_str());
        this->get_mediator()->operation(this);
    }

 private:
    std::string name_;
    int price_;
    std::string address_;
    std::string phone_number_;
};

// 具体组件2: 租客
class Tenant : public Colleague {
 public:
    Tenant() {
        name_ = "unknown";
    }
    explicit Tenant(std::string name) {
        name_ = name;
        set_personType(kTenant);
    }
    void ask() {
        printf("租客%s询问房东信息:\n", name_.c_str());
        this->get_mediator()->operation(this);
    }
    void answer() {
        printf("租客姓名: %s\n", name_.c_str());
    }

 private:
    std::string name_;
};

#endif  // COMPONENT_H_