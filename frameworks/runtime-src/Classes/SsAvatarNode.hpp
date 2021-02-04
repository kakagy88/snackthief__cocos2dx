//
//  SsAvatarNode.hpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/01/22.
//

#ifndef SsAvatarNode_hpp
#define SsAvatarNode_hpp

#include "cocos2d.h"
#include "SSPlayer/SS6Player.h"

#define SSBP_FROM_NETWORK

class SsAvatarNode : public cocos2d::Node {
public:
    SsAvatarNode() : expression_("normal") {}
    CREATE_FUNC(SsAvatarNode);
    void attachEquipment(const std::string& equipmentName);
    void detachEquipment(const std::string& categoryId);
    void setPose(const std::string& poseName);
    void renderingBlendFuncEnable(bool flag);
    void setExpression(const std::string& expression);
    static void setSsDirectoryPath(const std::string& path);
    static void setSsUrl(const std::string& url);
    static std::map<std::string, std::vector<std::string>> CATEGORIES;
protected:
    bool init() override;
private:
    ss::ResourceManager* resourceManager_;
    ss::SSPlayerControl* ssPlayer_;
    std::map<std::string, std::string> equipmentsMap_;
    std::string expression_;
    void attachEquipmentSub(const std::string& equipmentName);
    void detachEquipmentSub(const std::string& category);
    void hidePartsByCategory(const std::string& category);
#ifdef SSBP_FROM_NETWORK
    void unzip(const void* data, ssize_t datasize);
#endif
    static std::string ssDirectoryPath;
    static std::string ssUrl;
};

#endif /* SsAvatarNode_hpp */

