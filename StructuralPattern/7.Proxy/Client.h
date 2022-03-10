#ifndef CLIENT_H_
#define CLIENT_H_

#include <string>
#include <cstdio>
#include "Service.h"

// 之前直接与服务对象交互的 GUI 类不需要改变, 前提是它仅通过接口与服务对象交互。
// 我们可以安全地传递一个代理对象来代替真实服务对象, 因为它们都实现了相同的接口。
class TVManager {
 public:
    explicit TVManager(ThirdPartyTVLib* s) : service_(s) {}
    void renderVideoPage(int id) {
        std::string video_info = service_->getVideoInfo(id);
        // 渲染视频页面, 这里忽略实现
        printf("渲染视频页面: %s\n", video_info.c_str());
        return;
    }
    void renderListPanel() {
        std::string videos = service_->listVideos();
        // 渲染视频缩略图列表, 这里忽略实现
        printf("渲染视频缩略图列表: %s\n", videos.c_str());
        return;
    }

 private:
    ThirdPartyTVLib* service_;
};

#endif  // CLIENT_H_