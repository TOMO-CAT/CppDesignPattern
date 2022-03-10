#include "ConcreteState.h"

#include <memory>

void PrimaryState::checkState() {
    if (point_ >= 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    } else if (point_ >= 100) {
        account_->set_state(std::make_shared<MiddleState>(this));
    }
}

void MiddleState::checkState() {
    if (point_ >= 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    } else if (point_ < 100) {
        account_->set_state(std::make_shared<PrimaryState>(this));
    }
}

void HighState::checkState() {
    if (point_ < 100) {
        account_->set_state(std::make_shared<PrimaryState>(this));
    } else if (point_ < 1000) {
        account_->set_state(std::make_shared<HighState>(this));
    }
}