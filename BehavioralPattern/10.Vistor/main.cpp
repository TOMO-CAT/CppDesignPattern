#include "Client.h"
#include "ConcreteElement.h"
#include "ConcreteVisitor.h"

int main() {
    Book book;
    Apple apple;
    ShoppingCart basket;

    basket.addProduct(&book);
    basket.addProduct(&apple);

    Customer customer;
    customer.set_name("小张");
    basket.accept(&customer);

    Saler saler;
    saler.set_name("小杨");
    basket.accept(&saler);

    return 0;
}