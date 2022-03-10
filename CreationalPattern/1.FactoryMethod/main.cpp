#include "ConcreteCreator.h"

int main() {
    std::shared_ptr<Factory> factory;
    std::shared_ptr<Movie> product;

    // 这里假设从配置中读到的是Chinese(运行时决定的)
    std::string conf = "China";

    // 程序根据当前配置或环境选择创建者的类型
    if (conf == "China") {
        factory = std::make_shared<ChineseProducer>();
    } else if (conf == "Japan") {
        factory = std::make_shared<JapaneseProducer>();
    } else if (conf == "America") {
        factory = std::make_shared<AmericanProducer>();
    } else {
        std::cout << "error conf" << std::endl;
    }

    product = factory->get_movie();
    std::cout << "获取一部电影: " << product->get_a_movie() << std::endl;
}