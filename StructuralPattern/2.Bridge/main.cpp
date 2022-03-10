#include "ConcreteImplementation.h"
#include "RefinedAbstraction.h"

int main() {
    // 客户端根据运行时参数获取对应的Color和Pen
    Color* color = new Red();
    Pen* pen = new SmallPencil();

    pen->set_color(color);
    pen->draw("太阳");

    delete color;
    delete pen;
}