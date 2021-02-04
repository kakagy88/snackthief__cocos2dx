//
//  SsRaidBattleNode.cpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/23.
//

#include "SsRaidBattleNode.hpp"

USING_NS_CC;
using namespace std;
using namespace StringUtils;

bool SsRaidBattleNode::init() {
    if (!Node::init()) {
        return false;
    }
    
    resourceManager_ = ss::ResourceManager::getInstance();
    resourceManager_->addData("res/ss/raidBattle/rb_001.ssbp");
    ssPlayer_ = ss::SSPlayerControl::create();
    ssPlayer_->getSSPInstance()->setData("rb_001");
    addChild(ssPlayer_);
    
    scheduleUpdate();
    
    return true;
}

void SsRaidBattleNode::onExit() {
    Node::onExit();
    if (playerImageHandle_ >= 0) {
        ss::SSTextureRelese(playerImageHandle_);
    }
    if (enemyImageHandle_ >= 0) {
        ss::SSTextureRelese(enemyImageHandle_);
    }
    if (helpImageHandle_ >= 0) {
        ss::SSTextureRelese(helpImageHandle_);
    }
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
}

void SsRaidBattleNode::setInfo(int currentHp, int maxHp, int totalDamage, bool isMine, const std::string& playerImage, const std::string& enemyImage, const std::string& helpImage, const std::string& memberImage1, const std::string& memberImage2, const std::string& memberImage3, const std::string& memberImage4) {
    currentHp_ = currentHp;
    maxHp_ = maxHp;
    totalDamage_ = totalDamage;
    isMine_ = isMine;
    
    auto playerStart = ssPlayer_->getSSPInstance()->getSpriteData(ssPlayer_->getSSPInstance()->indexOfPart("rb_c02_battle_battle_1_start_1"))->getSSPlayer();
    auto playerMain = ssPlayer_->getSSPInstance()->getSpriteData(ssPlayer_->getSSPInstance()->indexOfPart("rb_c02_battle_battle_2_main_1"))->getSSPlayer();
    
    // 成功 or 大成功
    {
        ss::Instance param;
        param.clear();
        param.independent = true;
        param.infinity = false;
        if (totalDamage_ >= currentHp_) {
            param.refEndframe = resourceManager_->getEndFrame("rb_001", "rb_c03_result/result_1_daiseikou");
            ssPlayer_->getSSPInstance()->changeInstanceAnime("rb_c03_result_result_1_daiseik_1", "rb_c03_result/result_1_daiseikou", true, param);
        } else {
            param.refEndframe = resourceManager_->getEndFrame("rb_001", "rb_c03_result/result_2_seikou");
            ssPlayer_->getSSPInstance()->changeInstanceAnime("rb_c03_result_result_1_daiseik_1", "rb_c03_result/result_2_seikou", true, param);
        }
    }
    
    // 自分画像
    playerImageHandle_ = ss::SSTextureLoad(playerImage.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
    resourceManager_->changeTexture("rb_001", "chara_player", playerImageHandle_);
    
    // 敵画像
    enemyImageHandle_ = ss::SSTextureLoad(enemyImage.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
    resourceManager_->changeTexture("rb_001", "raid", enemyImageHandle_);
    
    // 援護射撃画像
    {
        if (!helpImage.empty()) {
            helpImageHandle_ = ss::SSTextureLoad(helpImage.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            resourceManager_->changeTexture("rb_001", "chara_help", helpImageHandle_);
        } else {
            playerStart->setPartVisible("cutin1", false);
            playerStart->setPartVisible("cutin1_1", false);
            playerStart->setPartVisible("chara_help", false);
            playerStart->setPartVisible("help_1", false);
        }
    }
    
    // メンバー画像
    {
        if (!memberImage1.empty()) {
            memberImageHandle1_ = ss::SSTextureLoad(memberImage1.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle1_ >= 0) {
                resourceManager_->changeTexture("rb_001", "chara2_sample", memberImageHandle1_);
            } else {
                playerStart->setPartVisible("chara1_sample_1", false);
                playerMain->setPartVisible("chara1_sample_1", false);
            }
        } else {
            playerStart->setPartVisible("chara1_sample_1", false);
            playerMain->setPartVisible("chara1_sample_1", false);
        }
        if (!memberImage2.empty()) {
            memberImageHandle2_ = ss::SSTextureLoad(memberImage2.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle2_ >= 0) {
                resourceManager_->changeTexture("rb_001", "chara3_sample", memberImageHandle2_);
            } else {
                playerStart->setPartVisible("chara1_sample_2", false);
                playerMain->setPartVisible("chara1_sample_2", false);
            }
        } else {
            playerStart->setPartVisible("chara1_sample_2", false);
            playerMain->setPartVisible("chara1_sample_2", false);
        }
        if (!memberImage3.empty()) {
            memberImageHandle3_ = ss::SSTextureLoad(memberImage3.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle3_ >= 0) {
                resourceManager_->changeTexture("rb_001", "chara4_sample", memberImageHandle3_);
            } else {
                playerStart->setPartVisible("chara1_sample_3", false);
                playerMain->setPartVisible("chara1_sample_3", false);
            }
        } else {
            playerStart->setPartVisible("chara1_sample_3", false);
            playerMain->setPartVisible("chara1_sample_3", false);
        }
        if (!memberImage4.empty()) {
            memberImageHandle4_ = ss::SSTextureLoad(memberImage4.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            if (memberImageHandle4_ >= 0) {
                resourceManager_->changeTexture("rb_001", "chara5_sample", memberImageHandle4_);
            } else {
                playerStart->setPartVisible("chara1_sample_4", false);
                playerMain->setPartVisible("chara1_sample_4", false);
            }
        } else {
            playerStart->setPartVisible("chara1_sample_4", false);
            playerMain->setPartVisible("chara1_sample_4", false);
        }
    }
    
    ssPlayer_->getSSPInstance()->setUserDataCallback([=](ss::Player* player, const ss::UserData* userData){
        // スコア
        if (strcmp("setTotalScore", userData->str) == 0) {
            stringstream ss;
            ss << totalDamage;
            auto totalDamageString = ss.str();
            string totalDamageNumPartNames[] = {"num0", "num0_1", "num0_2", "num0_3", "num0_4"};
            for (int i = totalDamageString.length() - 1, j = 4; i >= 0; --i, --j) {
                auto partName = totalDamageNumPartNames[j];
                auto cellName = StringUtils::format("num%c", totalDamageString[i]);
                playerMain->setPartCell(partName.c_str(), "rb_1", cellName.c_str());
            }
        }
        // 結果画面
        else if (strcmp("startResult", userData->str) == 0) {
            gaugeAnimationStarted_ = true;
            gaugeAnimationFrameCount_ = 0;
            spriteGaugeBg_ = Sprite::create("res/ss/raidBattle/gauge_bg.png");
            spriteGaugeBg_->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            spriteGaugeBg_->setPosition(Vec2(-307, -440));
            addChild(spriteGaugeBg_);
            spriteGauge_ = Sprite::create("res/ss/raidBattle/gauge.png");
            spriteGauge_->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
            spriteGauge_->setPosition(Vec2(-300, -440));
            spriteGauge_->setTextureRect(Rect(0, 0, 0, 72));
            addChild(spriteGauge_);
        }
        else if (strcmp("endResult", userData->str) == 0) {
            gaugeAnimationStarted_ = false;
            spriteGaugeBg_->removeFromParent();
            spriteGauge_->removeFromParent();
            // 自分がみつけてHPをゼロにした場合はペンダント演出に移行、そうでないなら演出すぐに終了。
            bool showPendant = isMine && (currentHp_ - totalDamage_ <= 0);
            if (!showPendant) {
                ssPlayer_->getSSPInstance()->setEndFrame(ssPlayer_->getSSPInstance()->getFrameNo() + 2);
            }
        }
    });
    
    playerMain->setPartVisible("style_mark_1", false);
    playerMain->setPartVisible("style_mark_2", false);
    playerMain->setPartVisible("style_mark_3", false);
    playerMain->setPartVisible("style_mark_4", false);
    playerMain->setPartVisible("style_mark_5", false);
    playerMain->setPartVisible("player_part1", false);
    playerMain->setPartVisible("player_part2", false);
    playerMain->setPartVisible("player_part3", false);
    playerMain->setPartVisible("player_part4", false);
    playerMain->setPartVisible("player_part5", false);
}

void SsRaidBattleNode::setStepInfo(int stepId, int styleId, int damage) {
    auto playerStart = ssPlayer_->getSSPInstance()->getSpriteData(ssPlayer_->getSSPInstance()->indexOfPart("rb_c02_battle_battle_1_start_1"))->getSSPlayer();
    auto playerMain = ssPlayer_->getSSPInstance()->getSpriteData(ssPlayer_->getSSPInstance()->indexOfPart("rb_c02_battle_battle_2_main_1"))->getSSPlayer();
    // BattleStart画面
    {
        playerStart->setPartCell(StringUtils::format("style_mark_%d", stepId),
                                 "rb_1",
                                 StringUtils::format("style_%d", styleId));
        playerStart->setPartCell(StringUtils::format("style_name_%d", stepId),
                                 "rb_1",
                                 StringUtils::format("style_name_%d", styleId));
    }
    // BattleMain画面
    {
        playerMain->setPartCell(StringUtils::format("style_mark_%d", stepId),
                                "rb_1",
                                StringUtils::format("style_%d", styleId));
        playerMain->setPartCell(StringUtils::format("style_mark_gray_%d", stepId),
                                "rb_1",
                                StringUtils::format("style_%d", styleId));
        // カットイン背景
        playerMain->setPartCell(StringUtils::format("cutin_bg_part%d", stepId),
                                "rb_2",
                                StringUtils::format("cutin_part%d_%d", stepId, styleId));
        playerMain->setPartVisible(StringUtils::format("style_mark_%d", stepId), true);
        playerMain->setPartVisible(StringUtils::format("style_mark_gray_%d", stepId), false);
        playerMain->setPartVisible(StringUtils::format("player_part%d", stepId), true);
        playerMain->setPartVisible(StringUtils::format("player_gray_part%d", stepId), false);
    }
    
}

void SsRaidBattleNode::update(float dt) {
    Node::update(dt);
    
    // 100fでゲージ動き切る事
    if (gaugeAnimationStarted_ && gaugeAnimationFrameCount_ <= 100) {
        auto startX = ((maxHp_ - currentHp_) / maxHp_) * 600.0f;
        auto endX = ((maxHp_ - (currentHp_ - totalDamage_)) / maxHp_) * 600.0f;
        auto restWidth = endX - startX;
        auto currentX = startX + restWidth * ((float)gaugeAnimationFrameCount_ / 100.0f);
        spriteGauge_->setTextureRect(Rect(0, 0, currentX, 72));
        ++ gaugeAnimationFrameCount_;
    }
}

void SsRaidBattleNode::play() {
    ssPlayer_->getSSPInstance()->play("rb_kakunin/kakunin");
    ssPlayer_->getSSPInstance()->setLoop(1);
}

void SsRaidBattleNode::setPlayEndCallback(std::function<void(ss::Player*)> callback) {
    ssPlayer_->getSSPInstance()->setPlayEndCallback(callback);
}

