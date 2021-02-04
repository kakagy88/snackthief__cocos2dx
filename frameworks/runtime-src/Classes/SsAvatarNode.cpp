//
//  SsAvatarNode.cpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/01/22.
//

#include "SsAvatarNode.hpp"
#include "network/CCDownloader.h"

USING_NS_CC;
using namespace std;
using namespace StringUtils;

string SsAvatarNode::ssDirectoryPath;
string SsAvatarNode::ssUrl;

std::map<std::string, std::vector<std::string>> SsAvatarNode::CATEGORIES = {
    {"11", {"hair"}},
    {"21", {"face"}},
    {"31", {"lingerie"}},
    {"33", {"top", "inner"}},
    {"34", {"bottom"}},
    {"35", {"top", "inner", "bottom"}},
    {"41", {"socks"}},
    {"42", {"shoes_under"}},
    {"51", {"hat"}},
    {"55", {"acceh_r"}},
    {"56", {"acceh_l"}}
};

bool SsAvatarNode::init() {
    if (!Node::init()) {
        return false;
    }
    setCascadeOpacityEnabled(true);

    // アバター表示
    resourceManager_ = ss::ResourceManager::getInstance();
    resourceManager_->addData(ssDirectoryPath + "/body.ssbp");
    
    ssPlayer_ = ss::SSPlayerControl::create();
    ssPlayer_->getSSPInstance()->setData("body");
    ssPlayer_->getSSPInstance()->play("body/base");
    attachEquipment("13100");
    addChild(ssPlayer_);

    return true;
}

void SsAvatarNode::attachEquipment(const std::string& equipmentName) {
    auto categoryId = equipmentName.substr(1, 2);
    detachEquipment(categoryId);
    equipmentsMap_[categoryId] = equipmentName;
#ifdef SSBP_FROM_NETWORK
    auto fu = FileUtils::getInstance();
    
    auto pngPath = fu->getWritablePath() + "magic/equipment/" + equipmentName + ".png";
    auto ssbpPath = fu->getWritablePath() + "magic/equipment/" + equipmentName + ".ssbp";
    auto fileDownloaded = fu->isFileExist(pngPath) && fu->isFileExist(ssbpPath);
    if (fileDownloaded) {
        // ssbpとpngが両方ダウンロード済みならそれを使う。
        attachEquipmentSub(equipmentName);
    } else {
        // ssbpとpngが入ったzipファイルをダウンロードし、解凍して使う。
        std::string url = format("%s/%s.zip", ssUrl.c_str(), equipmentName.c_str());
        std::string directoryPath = fu->getWritablePath() + "magic/equipment/";
        if (!fu->isDirectoryExist(directoryPath)) {
            fu->createDirectory(directoryPath);
        }
        network::Downloader *downloader = new (std::nothrow) network::Downloader();
        downloader->onTaskProgress = ([] (const network::DownloadTask& task, int64_t bytesReceived, int64_t totalBytesReceived, int64_t totalBytesExpected) {
            // CCLOG("onTaskProgress");
            //downloading progress
        });
        downloader->onFileTaskSuccess = ([] (const network::DownloadTask& task) {
            //file downloaded, do what you need next
            // CCLOG("onFileTaskSuccess");
        });
        downloader->onDataTaskSuccess = ([this, equipmentName] (const network::DownloadTask& task, std::vector<unsigned char>& data) {
            const char *p = (char *)data.data();
            auto size = data.size();
            // CCLOG("onDataTaskSuccess");
            unzip(p, size);
            Director::getInstance()->getScheduler()->performFunctionInCocosThread([this, equipmentName](){
                attachEquipmentSub(equipmentName);
            });
        });
        downloader->onTaskError = ([] (const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
            //file downloading error
            // CCLOG("onTaskError");
        });
        downloader->createDownloadDataTask(url);
    }
#else
    attachEquipmentSub(equipmentName);
#endif
}

void SsAvatarNode::attachEquipmentSub(const std::string& equipmentName) {
    // 先ずは対象のssbpファイルを登録し
#ifdef SSBP_FROM_NETWORK
    resourceManager_->addData(format("%s/magic/equipment/%s.ssbp", FileUtils::getInstance()->getWritablePath().c_str(), equipmentName.c_str()));
#else
    resourceManager_->addData(format("%s/equipments/%s.ssbp", ssDirectoryPath.c_str(), equipmentName.c_str()));
#endif
    bool isFace = equipmentName.substr(1, 2) == "21";
    if (isFace) {
        // もしfaceの場合は表情に応じたアニメを設定する
        ss::Instance param;
        param.clear();
        param.independent = true;
        param.infinity = true;
        param.refEndframe = resourceManager_->getEndFrame(equipmentName, format("%s/face_%s_head_f", equipmentName.c_str(), expression_.c_str()));
        ssPlayer_->getSSPInstance()->changeInstanceAnime("face_head_f", equipmentName, format("%s/face_%s_head_f", equipmentName.c_str(), expression_.c_str()), true, param);
    } else {
        // face以外の場合はssaeに含まれるアニメ名(=セット先のパーツ名に対応)一覧を取得
        auto animeNames = resourceManager_->getInstance()->getAnimeName(equipmentName, equipmentName);
        // それぞれを対象のパーツにセットする
        for (auto animeName : animeNames) {
            if (animeName != "Setup") {
                auto partName = animeName;
                ss::Instance param;
                param.clear();
                param.independent = true;
                param.infinity = true;
                param.refEndframe = resourceManager_->getEndFrame(equipmentName, format("%s/%s", equipmentName.c_str(), partName.c_str()));
                ssPlayer_->getSSPInstance()->changeInstanceAnime(partName, equipmentName, format("%s/%s", equipmentName.c_str(), partName.c_str()), true, param);
            }
        }
    }
}

void SsAvatarNode::detachEquipment(const std::string& categoryId) {
    for (auto category : CATEGORIES[categoryId]) {
        detachEquipmentSub(category);
    }
}
void SsAvatarNode::detachEquipmentSub(const std::string& category) {
    hidePartsByCategory(category);
    if (equipmentsMap_.count(category) >= 1) {
        auto equipmentName = equipmentsMap_.at(category);
        if (resourceManager_->isDataKeyExists(equipmentName)) {
            resourceManager_->removeData(equipmentName);
        }
        equipmentsMap_.erase(category);
    }
}

void SsAvatarNode::setPose(const std::string& poseName) {
    if (poseName == "wait") {
        ssPlayer_->getSSPInstance()->play("body2/base");
    } else {
        ssPlayer_->getSSPInstance()->play(format("body/%s", poseName.c_str()));
    }
    attachEquipment("13100");
}

void SsAvatarNode::renderingBlendFuncEnable(bool flag) {
    ssPlayer_->renderingBlendFuncEnable(flag);
}

void SsAvatarNode::setExpression(const std::string& expression) {
    expression_ = expression;
    if (equipmentsMap_.count("21") == 1) {
        auto equipmentName = equipmentsMap_.at("21");
        ss::Instance param;
        param.clear();
        param.independent = true;
        param.infinity = true;
        param.refEndframe = resourceManager_->getEndFrame(equipmentName, format("%s/face_%s_head_f", equipmentName.c_str(), expression_.c_str()));
        ssPlayer_->getSSPInstance()->changeInstanceAnime("face_head_f", equipmentName, format("%s/face_%s_head_f", equipmentName.c_str(), expression_.c_str()), true, param);
    }
}

// 特定のカテゴリの全パーツをdummy/nullへの参照に戻す。
void SsAvatarNode::hidePartsByCategory(const std::string& category) {
    auto partsCount = ssPlayer_->getSSPInstance()->getPartsCount();
    for (int i = 0; i < partsCount; ++ i) {
        auto partName = std::string(ssPlayer_->getSSPInstance()->getPartName(i));
        if (partName.size() >= category.size() &&
            std::equal(std::begin(category), std::end(category), std::begin(partName))) {
            ss::Instance param;
            param.clear();
            ssPlayer_->getSSPInstance()->changeInstanceAnime(partName, "body", "dummy/null", true, param);
        }
    }
}


#ifdef SSBP_FROM_NETWORK
void SsAvatarNode::unzip(const void* data, ssize_t datasize) {
    // 出力先のルートパスを取得
    const std::string writablePath( cocos2d::FileUtils::getInstance()->getWritablePath() + "magic/equipment/" );
    
    // zipに含まれるファイル情報リストを取得
    cocos2d::ZipFile* zipfile = cocos2d::ZipFile::createWithBuffer( data, datasize );
    for( std::string filename = zipfile->getFirstFilename(); !filename.empty(); filename = zipfile->getNextFilename() ){
        if( *filename.rbegin() == '/' ){
            
            // It's a directory.
            cocos2d::FileUtils::getInstance()->createDirectory( writablePath + filename );
            
        }else{
            
            // It's a file.
            ssize_t filesize;
            unsigned char* filedata = zipfile->getFileData( filename, &filesize );
            {
                const std::string fullPath( writablePath + filename );
                FILE* file = fopen( fullPath.c_str(), "wb" );
                fwrite( filedata, filesize, 1, file );
                fclose( file );
            }
            free( filedata );
            
        }
    }
    delete zipfile;
}
#endif

void SsAvatarNode::setSsDirectoryPath(const std::string& path) {
    ssDirectoryPath = path;
}

void SsAvatarNode::setSsUrl(const std::string& url) {
    ssUrl = url;
}
