#include "Composite.h"
#include "Leaf.h"

int main() {
    // 组合图
    CompoundGraphic* all = new CompoundGraphic();

    // 添加子图
    Dot* dot1 = new Dot(1, 2);
    Circle *circle = new Circle(5, 2, 2);
    CompoundGraphic* child_graph = new CompoundGraphic();
    Dot* dot2 = new Dot(4, 7);
    Dot* dot3 = new Dot(3, 2);
    child_graph->add(0, dot2);
    child_graph->add(1, dot3);

    // 将所有图添加到组合图中
    all->add(0, dot1);
    all->add(1, circle);
    all->add(2, child_graph);

    // 绘制
    all->draw();

    delete all;
    delete dot1;
    delete dot2;
    delete dot3;
    delete circle;
    return 0;
}