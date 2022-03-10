#ifndef STATE_H_
#define STATE_H_

#include <string>
#include <cstdio>
#include "Context.h"

class AbstractState {
 public:
    virtual void checkState() = 0;

    void set_point(int point) {
        point_ = point;
    }
    int get_point() {
        return point_;
    }
    void set_state_name(std::string name) {
        state_name_ = name;
    }
    std::string get_state_name() {
        return state_name_;
    }
    ForumAccount* get_account() {
        return account_;
    }

    virtual void downloadFile(int score) {
        printf("%s下载文件, 扣除%d积分。\n", account_->get_name().c_str(), score);
        point_ -= score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void writeNote(int score) {
        printf("%s发布留言, 增加%d积分。\n", account_->get_name().c_str(), score);
        point_ += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

    virtual void replyNote(int score) {
        printf("%s回复留言, 增加%d积分。\n", account_->get_name().c_str(), score);
        point_ += score;
        checkState();
        printf("%s剩余积分为%d, 当前级别为%s。\n", account_->get_name().c_str(), point_, account_->get_state()->get_state_name().c_str());
    }

 protected:
    ForumAccount* account_;
    int point_;
    std::string state_name_;
};

#endif  // STATE_H_