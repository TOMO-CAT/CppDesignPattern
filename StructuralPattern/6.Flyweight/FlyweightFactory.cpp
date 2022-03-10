#include "FlyweightFactory.h"

TreeFactory* TreeFactory::instance_ = nullptr;
std::mutex TreeFactory::mutex_;