#include <iostream>
#include "Client.h"
#include "Adapter.h"

int main() {
    // 半径为10的圆孔
    RoundHole* hole = new RoundHole(10);

    // 半径分别为5和20的大小方钉 + 它们的适配器
    SquarePeg* samll_square_peg = new SquarePeg(5);
    SquarePeg* large_square_peg = new SquarePeg(20);
    SquarePegAdapter* small_square_peg_adapter = new SquarePegAdapter(samll_square_peg);
    SquarePegAdapter* large_square_peg_adapter = new SquarePegAdapter(large_square_peg);

    // hole->isFit(samll_square_peg);  // 编译报错
    // hole->isFit(large_square_peg);  // 编译报错
    if (hole->isFit(small_square_peg_adapter)) {
        std::cout << "small square peg fits the hole" << std::endl;
    } else {
        std::cout << "small square peg don't fit the hole" << std::endl;
    }
    if (hole->isFit(large_square_peg_adapter)) {
        std::cout << "large square peg fits the hole" << std::endl;
    } else {
        std::cout << "large square peg don't fit the hole" << std::endl;
    }
}