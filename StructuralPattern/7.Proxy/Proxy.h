#ifndef PROXY_H_
#define PROXY_H_

#include <string>
#include "ServiceInterface.h"

// 为了节省网络带宽, 我们可以将请求缓存下来并保存一段时间
// 当代理类接受到真实请求后才会将其委派给服务对象
class CachedTVClass : public ThirdPartyTVLib {
 public:
    explicit CachedTVClass(ThirdPartyTVLib* service) : service_(service), need_reset_(false), list_cache_(""), video_cache_("") {}
    void reset() {
        need_reset_ = true;
    }

    std::string listVideos() override {
        if (list_cache_ == "" || need_reset_) {
            list_cache_ = service_->listVideos();
        }
        return list_cache_;
    }

    std::string getVideoInfo(int id) override {
        if (video_cache_ == "" || need_reset_) {
            video_cache_ = service_->getVideoInfo(id);
        }
        return video_cache_;
    }

 private:
    ThirdPartyTVLib* service_;
    std::string list_cache_;
    std::string video_cache_;
    bool need_reset_;
};

#endif  // PROXY_H_