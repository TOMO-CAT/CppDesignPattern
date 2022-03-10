#ifndef FLYWEIGHT_FACTORY_H_
#define FLYWEIGHT_FACTORY_H_

#include <map>
#include <string>
#include <mutex>
#include "Flyweight.h"

// 享元工厂: 决定是否复用已有享元或者创建一个新的对象, 同时它也是一个单例模式
class TreeFactory {
 public:
    static TreeFactory* getInstance() {
        if (instance_ == nullptr) {
            mutex_.lock();
            if (instance_ == nullptr) {
                instance_ = new TreeFactory();
            }
            mutex_.unlock();
        }
        return instance_;
    }
    TreeType* getTreeType(std::string name, std::string color, std::string texture) {
        std::string key = name + "_" + color + "_" + texture;
        auto iter = tree_types_.find(key);
        if (iter == tree_types_.end()) {
            // 新的tree type
            TreeType* new_tree_type = new TreeType(name, color, texture);
            tree_types_[key] = new_tree_type;
            return new_tree_type;
        } else {
            // 已存在的tree type
            return iter->second;
        }
    }

 private:
    TreeFactory() {}
    static TreeFactory* instance_;
    static std::mutex mutex_;

    // 共享池, 其中key格式为name_color_texture
    std::map<std::string, TreeType*> tree_types_;
};

#endif  // FLYWEIGHT_FACTORY_H_