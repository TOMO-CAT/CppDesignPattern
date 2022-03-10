#ifndef SERVICE_H_
#define SERVICE_H_

#include <string>
#include "ServiceInterface.h"

// 视频下载类
// 该类的方法可以向远程视频后端服务请求信息, 请求速度取决于用户和服务器的网络状况
// 如果同时发送大量请求, 即使所请求的信息一模一样, 程序的速度依然会变慢
class ThirdPartyTVClass : public ThirdPartyTVLib {
 public:
    std::string listVideos() override {
        // 向远程视频后端服务发送一个API请求获取视频信息, 这里忽略实现
        return "video list";
    }

    std::string getVideoInfo(int id) override {
        // 向远程视频后端服务发送一个API请求获取某个视频的元数据, 这里忽略实现
        return "video info";
    }
};

#endif  //  SERVICE_H_