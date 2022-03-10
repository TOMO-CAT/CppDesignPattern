#ifndef CONCRETE_MEDIATOR_H_
#define CONCRETE_MEDIATOR_H_

#include <vector>
#include <string>
#include "Component.h"
#include "Mediator.h"

// 具体中介类: 房产中介
class Agency : public Mediator {
 public:
    void registerMethod(Colleague* person) override {
        switch (person->get_person_type()) {
            case kLandlord:
                landlord_list_.push_back(reinterpret_cast<Landlord*>(person));
                break;
            case kTenant:
                tenant_list_.push_back(reinterpret_cast<Tenant*>(person));
                break;
            default:
                printf("wrong person\n");
        }
    }

    void operation(Colleague* person) {
        switch (person->get_person_type()) {
            case kLandlord:
                for (int i = 0; i < tenant_list_.size(); i++) {
                    tenant_list_[i]->answer();
                }
                break;
            case kTenant:
                for (int i = 0; i < landlord_list_.size(); i++) {
                    landlord_list_[i]->answer();
                }
                break;
            default:
                break;
        }
    }

 private:
    std::vector<Landlord*> landlord_list_;
    std::vector<Tenant*> tenant_list_;
};

#endif  // CONCRETE_MEDIATOR_H_