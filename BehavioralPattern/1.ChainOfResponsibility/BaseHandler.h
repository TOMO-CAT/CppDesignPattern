#ifndef BASE_HANDLER_H_
#define BASE_HANDLER_H_

#include <string>
#include "Handler.h"

class BaseApprover : public ApproverInterface {
 public:
    BaseApprover(double mpa, std::string n) : max_processible_amount_(mpa), name_(n), superior_(nullptr) {}
    // 设置上级
    void setSuperior(ApproverInterface* superior) {
        superior_ = superior;
    }
    // 处理票据
    void handleRequest(double amount) {
        // 可处理时直接处理即可
        if (amount <= max_processible_amount_) {
            printf("%s处理了该票据, 票据面额:%f\n", name_.c_str(), amount);
            return;
        }
        // 无法处理时移交给上级
        if (superior_ != nullptr) {
            printf("%s无权处理, 转交上级...\n", name_.c_str());
            superior_->handleRequest(amount);
            return;
        }
        // 最上级依然无法处理时报错
        printf("无人有权限处理该票据, 票据金额:%f\n", name_.c_str(), amount);
    }

 private:
    double max_processible_amount_;  // 可处理的最大面额
    std::string name_;
    ApproverInterface* superior_;
};

#endif  // BASE_HANDLER_H_