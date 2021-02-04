//
//  Downloader.cpp
//  magic
//
//  Created by 太田敦士 on 2018/04/04.
//

#include "Downloader.hpp"

USING_NS_CC;
using namespace std;

void Downloader::addTask(const std::string& srcUrl, const std::string& dstPath) {
    queue_.push(std::make_pair(srcUrl, dstPath));
}

void Downloader::startDownload() {
    totalStep_ = queue_.size();
    downloader_->setOnTaskProgress([&](const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected){
        onTaskProgress(task, bytesReceived, totalBytesReceived, totalBytesExpected);
    });
    downloader_->setOnTaskError([&](const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr){
        onTaskError(task, errorCode, errorCodeInternal, errorStr);
    });
    downloader_->setOnFileTaskSuccess([&](const cocos2d::network::DownloadTask& task){
        onFileTaskSuccess(task);
    });
    downloader_->onDataTaskSuccess = [&](const network::DownloadTask& task, std::vector<unsigned char>& data){
        onDataTaskSuccess(task, data);
    };
    tryNext();
}

void Downloader::tryNext() {
    auto fu = FileUtils::getInstance();
    if (queue_.empty()) {
        if (completeCallback_) {
            completeCallback_(successCount_, errorCount_, totalStep_);
        }
    } else {
        auto task = queue_.front();
        queue_.pop();
        // zipか非zipか
        auto isZip = false;
        if (task.first.length() >= 4) {
            auto extensionName = task.first.substr(task.first.length() - 4, 4);
            isZip = (extensionName == ".zip");
        }
        // writablePath直下は上書きしないようにエラーに
        if (task.second.empty()) {
            ++ step_;
            ++ errorCount_;
            tryNext();
        } else {
            if (!isZip) {
                // zipでない場合はそのままファイルダウンロード
                downloader_->createDownloadFileTask(task.first, fu->getWritablePath() + "/" + task.second);
            } else {
                // zipの場合は一旦メモリにダウンロードし、解凍してファイルに書き込み。
                downloader_->createDownloadDataTask(task.first, fu->getWritablePath() + "/" + task.second);
            }
        }
    }
}

void Downloader::unzip(const void* data, ssize_t datasize, const std::string& dstPath) {
    // zipに含まれるファイル情報リストを取得
    cocos2d::ZipFile* zipfile = cocos2d::ZipFile::createWithBuffer(data, datasize);
    for(std::string filename = zipfile->getFirstFilename(); !filename.empty(); filename = zipfile->getNextFilename()){
        if(*filename.rbegin() == '/'){
            // It's a directory.
            cocos2d::FileUtils::getInstance()->createDirectory(dstPath + "/" + filename);
        }else{
            // It's a file.
            ssize_t filesize;
            unsigned char* filedata = zipfile->getFileData(filename, &filesize);
            {
                const std::string fullPath(dstPath + "/" + filename);
                FILE* file = fopen(fullPath.c_str(), "wb");
                fwrite(filedata, filesize, 1, file);
                fclose(file);
            }
            free(filedata);
        }
    }
    delete zipfile;
}

void Downloader::onTaskProgress(const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected) {
    if (progressCallback_) {
        progressCallback_(step_, totalStep_, bytesReceived, totalBytesReceived, totalBytesExpected);
    }
}

void Downloader::onFileTaskSuccess(const network::DownloadTask& task) {
    ++ step_;
    ++ successCount_;
    tryNext();
}

void Downloader::onDataTaskSuccess(const network::DownloadTask& task, std::vector<unsigned char>& data) {
    // zip解凍
    const char *p = (char *)data.data();
    auto size = data.size();
    unzip(p, size, task.identifier);
    ++ step_;
    ++ successCount_;
    tryNext();
}

void Downloader::onTaskError(const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
    ++ step_;
    ++ errorCount_;
    tryNext();
}

void Downloader::setProgressCallback(std::function<void(int, int, int64_t, int64_t, int64_t)> callback) {
    progressCallback_ = callback;
}

void Downloader::setCompleteCallback(std::function<void(int, int, int)> callback) {
    completeCallback_ = callback;
}

