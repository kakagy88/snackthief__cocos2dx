//
//  SsRaidTopNode.hpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/23.
//

#ifndef SsRaidTopNode_hpp
#define SsRaidTopNode_hpp

#include <stdio.h>

#include "cocos2d.h"
#include "SSPlayer/SS6Player.h"

class SsRaidTopNode : public cocos2d::Node {
public:
    SsRaidTopNode() : memberImageHandle1_(-1), memberImageHandle2_(-1), memberImageHandle3_(-1), memberImageHandle4_(-1), memberImageHandle5_(-1) {}
    CREATE_FUNC(SsRaidTopNode);
    void setInfo(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    void play();
    void setPlayEndCallback(std::function<void(ss::Player*)>);
protected:
    bool init() override;
    void onExit() override;
private:
    ss::ResourceManager* resourceManager_;
    ss::SSPlayerControl* ssPlayer_;
    long memberImageHandle1_;
    long memberImageHandle2_;
    long memberImageHandle3_;
    long memberImageHandle4_;
    long memberImageHandle5_;
};

#endif /* SsRaidTopNode_hpp */

