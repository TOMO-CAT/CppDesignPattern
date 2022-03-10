#include <iostream>
#include "AbstractFactory.h"
#include "ConcreteFactory.h"


int main() {
    std::shared_ptr<Factory> factory;

    // 这里假设从配置中读到的是Chinese(运行时决定的)
    std::string conf = "China";

    // 程序根据当前配置或环境选择创建者的类型
    if (conf == "China") {
        factory = std::make_shared<ChineseProducer>();
    } else if (conf == "Japan") {
        factory = std::make_shared<JapaneseProducer>();
    } else {
        std::cout << "error conf" << std::endl;
    }

    std::shared_ptr<Movie> movie;
    std::shared_ptr<Book> book;
    movie = factory->productMovie();
    book = factory->productBook();
    std::cout << "获取一部电影: " << movie->showMovieName() << std::endl;
    std::cout << "获取一本书: " << book->showBookName() << std::endl;
}