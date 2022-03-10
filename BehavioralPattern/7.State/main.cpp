#include "Context.h"

int main() {
    // 注册新用户
    ForumAccount account("TOMOCAT");
    account.writeNote(20);
    account.downloadFile(20);
    account.replyNote(100);
    account.writeNote(40);
    account.downloadFile(80);
    account.writeNote(1000);
    account.downloadFile(80);
    return 0;
}