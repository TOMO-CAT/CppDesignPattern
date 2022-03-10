#include "ConcretePrototype.h"

#include <cstdio>

int main() {
    Email* email = new Email("最初的文案", "最初的附件");
    Email* copy_email = email->clone();
    copy_email->changeText("新文案");
    copy_email->changeAttachment("新附件");
    std::cout << "original email:" << std::endl;
    email->display();
    std::cout << "copy email:" << std::endl;
    copy_email->display();

    delete email;
    delete copy_email;
}