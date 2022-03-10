#ifndef SERVICE_INTERFACE_H_
#define SERVICE_INTERFACE_H_

#include <string>

// 远程服务接口
class ThirdPartyTVLib {
 public:
    virtual std::string listVideos() = 0;
    virtual std::string getVideoInfo(int id) = 0;
};

#endif  // SERVICE_INTERFACE_H_
