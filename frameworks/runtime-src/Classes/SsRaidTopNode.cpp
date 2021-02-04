//
//  SsRaidTopNode.cpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/23.
//

#include "SsRaidTopNode.hpp"

USING_NS_CC;
using namespace std;
using namespace StringUtils;

bool SsRaidTopNode::init() {
    if (!Node::init()) {
        return false;
    }
    
    resourceManager_ = ss::ResourceManager::getInstance();
    resourceManager_->addData("res/ss/raidTop/rt_001.ssbp");
    ssPlayer_ = ss::SSPlayerControl::create();
    ssPlayer_->getSSPInstance()->setData("rt_001");
    addChild(ssPlayer_);
    
    scheduleUpdate();
    
    return true;
}

void SsRaidTopNode::onExit() {
    Node::onExit();
    if (memberImageHandle1_ >= 0) {
        ss::SSTextureRelese(memberImageHandle1_);
    }
    if (memberImageHandle2_ >= 0) {
        ss::SSTextureRelese(memberImageHandle2_);
    }
    if (memberImageHandle3_ >= 0) {
        ss::SSTextureRelese(memberImageHandle3_);
    }
    if (memberImageHandle4_ >= 0) {
        ss::SSTextureRelese(memberImageHandle4_);
    }
    if (memberImageHandle5_ >= 0) {
        ss::SSTextureRelese(memberImageHandle5_);
    }
}

void SsRaidTopNode::setInfo(const std::string& memberImage1, const std::string& memberImage2, const std::string& memberImage3, const std::string& memberImage4, const std::string& memberImage5) {
    auto playerIn = ssPlayer_->getSSPInstance()->getSpriteData(ssPlayer_->getSSPInstance()->indexOfPart("rt_top_top_1_in_1"))->getSSPlayer();
    // メンバー画像
    {
        if (!memberImage1.empty()) {
            memberImageHandle1_ = ss::SSTextureLoad(memberImage1.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle1_ >= 0) {
                resourceManager_->changeTexture("rt_001", "chara1_sample", memberImageHandle1_);
            } else {
                playerIn->setPartVisible("chara1_sample", false);
            }
        } else {
            playerIn->setPartVisible("chara1_sample", false);
        }
        if (!memberImage2.empty()) {
            memberImageHandle2_ = ss::SSTextureLoad(memberImage2.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle2_ >= 0) {
                resourceManager_->changeTexture("rt_001", "chara2_sample", memberImageHandle2_);
            } else {
                playerIn->setPartVisible("chara1_sample_1", false);
            }
        } else {
            playerIn->setPartVisible("chara1_sample_1", false);
        }
        if (!memberImage3.empty()) {
            memberImageHandle3_ = ss::SSTextureLoad(memberImage3.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle3_ >= 0) {
                resourceManager_->changeTexture("rt_001", "chara3_sample", memberImageHandle3_);
            } else {
                playerIn->setPartVisible("chara1_sample_2", false);
            }
        } else {
            playerIn->setPartVisible("chara1_sample_2", false);
        }
        if (!memberImage4.empty()) {
            memberImageHandle4_ = ss::SSTextureLoad(memberImage4.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle4_ >= 0) {
                resourceManager_->changeTexture("rt_001", "chara4_sample", memberImageHandle4_);
            } else {
                playerIn->setPartVisible("chara1_sample_3", false);
            }
        } else {
            playerIn->setPartVisible("chara1_sample_3", false);
        }
        if (!memberImage5.empty()) {
            memberImageHandle5_ = ss::SSTextureLoad(memberImage1.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle5_ >= 0) {
                resourceManager_->changeTexture("rt_001", "chara5_sample", memberImageHandle5_);
            } else {
                playerIn->setPartVisible("chara1_sample_4", false);
            }
        } else {
            playerIn->setPartVisible("chara1_sample_4", false);
        }
    }
}

void SsRaidTopNode::play() {
    ssPlayer_->getSSPInstance()->play("rt_kakunin/kakunin");
    ssPlayer_->getSSPInstance()->setLoop(1);
}

void SsRaidTopNode::setPlayEndCallback(std::function<void(ss::Player*)> callback) {
    ssPlayer_->getSSPInstance()->setPlayEndCallback(callback);
}

