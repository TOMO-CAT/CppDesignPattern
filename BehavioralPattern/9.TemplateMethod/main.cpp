#include "ConcreteClass.h"

int main() {
    // 存款
    BankTemplateMethod* deposit = new Deposit();
    deposit->process();
    delete deposit;

    // 取款
    BankTemplateMethod* withdraw = new Withdraw();
    withdraw->process();
    delete withdraw;

    // 转账
    BankTemplateMethod* transfer = new Transfer();
    transfer->process();
    delete transfer;
}