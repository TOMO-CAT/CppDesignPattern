#ifndef CLIENT_H_
#define CLIENT_H_

#include <list>
#include "Visitor.h"
#include "Element.h"

// 购物车
class ShoppingCart {
 public:
    void accept(Vistor *vistor) {
        for (auto prd : prd_list_) {
            prd->accept(vistor);
        }
    }

    void addProduct(Product *product) {
        prd_list_.push_back(product);
    }

    void removeProduct(Product *product) {
        prd_list_.remove(product);
    }

 private:
    std::list<Product*> prd_list_;
};

#endif  // CLIENT_H_