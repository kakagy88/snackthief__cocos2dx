//
//  SsRaidBattleNode.hpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/23.
//

#ifndef SsRaidBattleNode_hpp
#define SsRaidBattleNode_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "SSPlayer/SS6Player.h"

class SsRaidBattleNode : public cocos2d::Node {
public:
    SsRaidBattleNode() : playerImageHandle_(-1), enemyImageHandle_(-1), helpImageHandle_(-1), memberImageHandle1_(-1), memberImageHandle2_(-1), memberImageHandle3_(-1), memberImageHandle4_(-1), gaugeAnimationFrameCount_(0), gaugeAnimationStarted_(false) {}
    CREATE_FUNC(SsRaidBattleNode);
    void setInfo(int currentHp, int maxHp, int totalDamage, bool isMine, const std::string& playerImage, const std::string& enemyImage, const std::string& helpImage, const std::string& memberImage1, const std::string& memberImage2, const std::string& memberImage3, const std::string& memberImage4);
    void setStepInfo(int stepId, int styleId, int damage);
    void play();
    void setPlayEndCallback(std::function<void(ss::Player*)>);
protected:
    bool init() override;
    void onExit() override;
    void update(float dt) override;
private:
    ss::ResourceManager* resourceManager_;
    ss::SSPlayerControl* ssPlayer_;
    float currentHp_;
    float maxHp_;
    float totalDamage_;
    bool isMine_;
    long playerImageHandle_;
    long enemyImageHandle_;
    long helpImageHandle_;
    long memberImageHandle1_;
    long memberImageHandle2_;
    long memberImageHandle3_;
    long memberImageHandle4_;
    // ゲージ周り
    bool gaugeAnimationStarted_;
    int gaugeAnimationFrameCount_;
    cocos2d::Sprite* spriteGaugeBg_;
    cocos2d::Sprite* spriteGauge_;
};

#endif /* SsRaidBattleNode_hpp */

