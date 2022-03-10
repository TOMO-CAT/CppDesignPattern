#include <iostream>
#include "ConcreteCollection.h"

int main() {
    SkyworthTelevision stv;
    stv.addItem("CCTV-1");
    stv.addItem("CCTV-2");
    stv.addItem("CCTV-3");
    stv.addItem("CCTV-4");
    stv.addItem("CCTV-5");

    auto iter = stv.createIterator();
    while (!iter->isLast()) {
        std::cout << iter->currentChannel() << std::endl;
        iter->next();
    }
    return 0;
}