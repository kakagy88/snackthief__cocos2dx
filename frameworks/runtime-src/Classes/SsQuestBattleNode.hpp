//
//  SsQuestBattleNode.hpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/16.
//

#ifndef SsQuestBattleNode_hpp
#define SsQuestBattleNode_hpp

#include "cocos2d.h"
#include "SSPlayer/SS6Player.h"
#include "SimpleAudioEngine.h"

class SsQuestBattleNode : public cocos2d::Node {
public:
    SsQuestBattleNode() : playerImageHandle_(-1), resultPlayerImageHandle_(-1), enemyImageHandle_(-1) {}
    CREATE_FUNC(SsQuestBattleNode);
    void setInfo(const std::string&, const std::string&, const std::string&, const std::string&);
    void setBattleStepInfo(int stepId, int styleId, int targetScore, int ownScore, int starCount);
    void play();
    void setPlayEndCallback(std::function<void(ss::Player*)>);
protected:
    bool init() override;
    void onExit() override;
    void update(float dt) override;
private:
    ss::ResourceManager* resourceManager_;
    ss::SSPlayerControl* ssPlayer_;
    long playerImageHandle_;
    long resultPlayerImageHandle_;
    long enemyImageHandle_;
    // BGM
    CocosDenshion::SimpleAudioEngine* audio_;
    int bgm1Handle_;
    int bgm2Handle_;
};

#endif /* SsQuestBattleNode_hpp */


