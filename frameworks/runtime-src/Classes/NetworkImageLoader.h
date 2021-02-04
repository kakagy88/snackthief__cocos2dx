//
//  NetworkImageLoader.h
//  magic
//
//  Created by 太田敦士 on 2017/11/16.
//

#ifndef NetworkImageLoader_h
#define NetworkImageLoader_h

#include <string>
#include <functional>
#include <cocos2d.h>

class NetworkImageLoader {
public:
    static NetworkImageLoader* getInstance();
    void initialize();
    void clearCache();
    void deleteCache(const std::string& url);
    void loadTextureFromUrlASync(const std::string& url, std::function<void(cocos2d::Texture2D*)> callback, bool useCache = true, bool saveCache = true);
private:
    static NetworkImageLoader* _instance;
    std::string _cacheDirectoryPath;
};

#endif /* NetworkImageLoader_h */
