#include "Facade.h"

int main() {
    ComputerOperator* computer_operator = new ComputerOperator();
    computer_operator->powerOn();
    delete computer_operator;
}