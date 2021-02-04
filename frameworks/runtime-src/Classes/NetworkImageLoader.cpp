//
//  NetworkImageLoader.cpp
//  magic
//
//  Created by 太田敦士 on 2017/11/16.
//
#include "NetworkImageLoader.h"
#include "network/HttpRequest.h"
#include "network/HttpClient.h"
#include "network/HttpResponse.h"
#include "platform/CCFileUtils.h"
#include <iostream>
#include <stdio.h>

using namespace cocos2d::network;
USING_NS_CC;

NetworkImageLoader* NetworkImageLoader::_instance = NULL;

NetworkImageLoader* NetworkImageLoader::getInstance() {
    if (!_instance) {
        _instance = new (std::nothrow) NetworkImageLoader;
    }
    return _instance;
}

std::string encode(const std::string &str) {
    std::ostringstream os;
    
    for (int i = 0; i < str.size(); i++) {
        char c = str[i];
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '-' || c == '_' || c == '.' || c == '~') {
            os << c;
        } else {
            char s[4];
            snprintf(s, sizeof(s), "%%%02x", c & 0xff);
            os << s;
        }
    }
    
    return os.str();
}
//
void NetworkImageLoader::initialize() {
    auto fu = FileUtils::getInstance();
    _cacheDirectoryPath = fu->getWritablePath() + "magic/imageCache/";
    if (!fu->isDirectoryExist(_cacheDirectoryPath)) {
        fu->createDirectory(_cacheDirectoryPath);
    }
}

void NetworkImageLoader::deleteCache(const std::string &url) {
    auto fu = FileUtils::getInstance();
    auto filePath = _cacheDirectoryPath + encode(url);
    fu->removeFile(filePath);
}

void NetworkImageLoader::clearCache() {
    auto fu = FileUtils::getInstance();
    if (fu->isDirectoryExist(_cacheDirectoryPath)) {
        fu->removeDirectory(_cacheDirectoryPath);
        fu->createDirectory(_cacheDirectoryPath);
    }
}

void NetworkImageLoader::loadTextureFromUrlASync(const std::string &url, std::function<void (Texture2D*)> callback, bool useCache, bool saveCache) {
    auto filePath = _cacheDirectoryPath + encode(url);
    // ダウンロード済みだ
    Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(filePath);
    if (useCache && texture) {
        callback(texture);
    }
    // ダウンロード済みでない
    else {
        HttpRequest* request = new HttpRequest();
        request->setUrl(url);
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient *sender, HttpResponse *response) {
            if ( ! response->isSucceed() || response->getResponseCode() != 200 ) {
                callback(nullptr);
                return;
            }
            std::vector<char> *buffer = response->getResponseData();
            Image* image = new Image();
            image->autorelease();
            image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
            
            Texture2D* texture = new Texture2D();
            texture->autorelease();
            texture->initWithImage(image);
            
            // ファイルに保存しておく
            if (saveCache) {
                FILE * fp = fopen(filePath.c_str(), "wb");
                fwrite(&(buffer->front()), 1, buffer->size(), fp);
                fclose(fp);
            }

            callback(texture);
        });
        HttpClient::getInstance()->send(request);
        request->release();
    }
}
