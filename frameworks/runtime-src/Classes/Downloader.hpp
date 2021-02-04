//
//  Downloader.hpp
//  magic
//
//  Created by 太田敦士 on 2018/04/04.
//

#ifndef Downloader_hpp
#define Downloader_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "network/CCDownloader.h"

class Downloader {
public:
    Downloader() : step_(0), totalStep_(0), successCount_(0), errorCount_(0), progressCallback_(nullptr), completeCallback_(nullptr) {
        downloader_ = std::make_shared<cocos2d::network::Downloader>();
    }
    void addTask(const std::string&, const std::string&);
    void startDownload();
    void setProgressCallback(std::function<void(int, int, int64_t, int64_t, int64_t)>);
    void setCompleteCallback(std::function<void(int, int, int)>);
private:
    int step_;
    int totalStep_;
    int successCount_;
    int errorCount_;
    std::queue<std::pair<std::string, std::string>> queue_;
    std::function<void(int, int, int64_t, int64_t, int64_t)> progressCallback_;
    std::function<void(int, int, int)> completeCallback_;
    void tryNext();
    void unzip(const void* data, ssize_t datasize, const std::string& dstPath);
    std::shared_ptr<cocos2d::network::Downloader> downloader_;
    void onTaskProgress(const cocos2d::network::DownloadTask&, int64_t, int64_t, int64_t);
    void onFileTaskSuccess(const cocos2d::network::DownloadTask&);
    void onDataTaskSuccess(const cocos2d::network::DownloadTask&, std::vector<unsigned char>&);
    void onTaskError(const cocos2d::network::DownloadTask&, int, int, const std::string&);
};

#endif /* Downloader_hpp */
