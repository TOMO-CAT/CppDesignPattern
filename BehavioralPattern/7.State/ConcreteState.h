#ifndef CONCRETE_STATE_H_
#define CONCRETE_STATE_H_

#include <cstdio>
#include "State.h"

// 具体状态类: 新手
class PrimaryState : public AbstractState {
 public:
    explicit PrimaryState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "新手";
    }
    explicit PrimaryState(ForumAccount *account) {
        account_ = account;
        point_ = 0;
        state_name_ = "新手";
    }
    void downloadFile(int score) override {
        printf("对不起, %s没有下载文件的权限!\n", account_->get_name().c_str());
    }
    void checkState() override;
};

// 具体状态类: 高手
class MiddleState : public AbstractState {
 public:
    explicit MiddleState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "高手";
    }

    void writeNote(int score) override {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score * 2);
        point_ += score * 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }
    void checkState() override;
};

// 具体状态类: 专家
class HighState : public AbstractState {
 public:
    explicit HighState(AbstractState* state) {
        account_ = state->get_account();
        point_ = state->get_point();
        state_name_ = "专家";
    }

    void writeNote(int score) override {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score * 2);
        point_ += score * 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void downloadFile(int score) {
        printf("%s下载文件, 扣除%d积分。\n", account_->get_name().c_str(), score / 2);
        point_ -= score / 2;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    void checkState() override;
};

#endif  // CONCRETE_STATE_H_
