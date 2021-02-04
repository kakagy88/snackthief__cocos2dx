//
//  SsDirectionNode.cpp
//  magic-client-cpp-test
//
//  Created by 太田敦士 on 2018/03/16.
//

#include "SsQuestBattleNode.hpp"

USING_NS_CC;
using namespace std;
using namespace StringUtils;
using namespace experimental;
using namespace CocosDenshion;

bool SsQuestBattleNode::init() {
    if (!Node::init()) {
        return false;
    }
    
    resourceManager_ = ss::ResourceManager::getInstance();
    resourceManager_->addData("res/ss/questBattle/qb_001.ssbp");
    ssPlayer_ = ss::SSPlayerControl::create();
    ssPlayer_->getSSPInstance()->setData("qb_001");
    addChild(ssPlayer_);
    
    audio_ = SimpleAudioEngine::getInstance();
    audio_->preloadBackgroundMusic("res/bgm/bgm_quest_01.mp3");
    audio_->preloadBackgroundMusic("res/bgm/bgm_quest_battle_01.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_01.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_02.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_03.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_04.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_05.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_06.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_07.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_08.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_09.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_10.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_11.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_12.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_13.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_14.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_15.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_16.mp3");
    audio_->preloadEffect("res/se/se_quest_battle_17.mp3");
    
    scheduleUpdate();
    
    return true;
}

void SsQuestBattleNode::setInfo(const std::string& playerImagePath, const std::string& resultPlayerImagePath, const std::string& enemyImagePath, const std::string& ranking) {
    auto tc = cocos2d::Director::getInstance()->getTextureCache();
    // 自分画像
    tc->reloadTexture(playerImagePath);
    playerImageHandle_ = ss::SSTextureLoad(playerImagePath.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
    resourceManager_->changeTexture("qb_001", "chara_player", playerImageHandle_);
    
    // 敵画像
    tc->reloadTexture(enemyImagePath);
    enemyImageHandle_ = ss::SSTextureLoad(enemyImagePath.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
    resourceManager_->changeTexture("qb_001", "chara2_sample", enemyImageHandle_);
    
    ssPlayer_->getSSPInstance()->setUserDataCallback([=](ss::Player* player, const ss::UserData* userData){
        if (strcmp("startResult", userData->str) == 0) {
            // 自分結果画像
            tc->reloadTexture(resultPlayerImagePath);
            resultPlayerImageHandle_ = ss::SSTextureLoad(resultPlayerImagePath.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            resourceManager_->changeTexture("qb_001", "chara_player", resultPlayerImageHandle_);
        }
    });
    
    // ランク
    {
        auto partIndex = ssPlayer_->getSSPInstance()->indexOfPart("c03_result_result_1_win_1");
        auto player = ssPlayer_->getSSPInstance()->getSpriteData(partIndex)->getSSPlayer();
        if (ranking == "S" || ranking == "s") {
            player->setPartCell("rank", "qb_1", "rank_s");
        }
        else if (ranking == "A" || ranking == "a") {
            player->setPartCell("rank", "qb_1", "rank_a");
        }
        else if (ranking == "B" || ranking == "b") {
            player->setPartCell("rank", "qb_1", "rank_b");
        }
        else if (ranking == "C" || ranking == "c") {
            player->setPartCell("rank", "qb_1", "rank_c");
        }
        else {
            player->setPartCell("rank", "qb_1", "rank_f");
        }
    }
}

void SsQuestBattleNode::update(float dt) {
    Node::update(dt);
    
    auto frame = ssPlayer_->getSSPInstance()->getFrameNo();
    
    if (frame == 3) {
        audio_->stopBackgroundMusic();
        audio_->playBackgroundMusic("res/bgm/bgm_quest_battle_01.mp3", false);
    }
    // 変身
    if (frame == 75 || frame == 130) {
        audio_->playEffect("res/se/se_quest_battle_01.mp3");
    }
    if (frame == 185) {
        audio_->playEffect("res/se/se_quest_battle_02.mp3");
    }
    if (frame == 218) {
        audio_->playEffect("res/se/se_quest_battle_03.mp3");
    }
    if (frame == 314) {
        audio_->playEffect("res/se/se_quest_battle_04.mp3");
    }
    
    if (frame >= 400 && frame < 430) {
        audio_->setBackgroundMusicVolume((430.f - (float)frame) / 30.f);
    }
    if (frame == 430) {
        audio_->stopBackgroundMusic();
        audio_->setBackgroundMusicVolume(1.0f);
        audio_->playBackgroundMusic("res/bgm/bgm_quest_01.mp3", false);
    }
    // バトル開始
    if (frame == 458) {
        audio_->playEffect("res/se/se_quest_battle_05.mp3");
    }
    
    // バトル
    if (frame == 518 + 230 * 0 || frame == 518 + 230 * 1 || frame == 518 + 230 * 2 || frame == 518 + 230 * 3 || frame == 518 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_06.mp3");
    }
    if (frame == 600 + 230 * 0 || frame == 600 + 230 * 1 || frame == 600 + 230 * 2 || frame == 600 + 230 * 3 || frame == 600 + 230 * 4) {
        std::random_device rnd;
        switch (rnd() % 4) {
            case 0:
                audio_->playEffect("res/se/se_quest_battle_07.mp3");
                break;
            case 1:
                audio_->playEffect("res/se/se_quest_battle_08.mp3");
                break;
            case 2:
                audio_->playEffect("res/se/se_quest_battle_09.mp3");
                break;
            case 3:
                audio_->playEffect("res/se/se_quest_battle_10.mp3");
                break;
        }
    }
    if (frame == 640 + 230 * 0 || frame == 640 + 230 * 1 || frame == 640 + 230 * 2 || frame == 640 + 230 * 3 || frame == 640 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_11.mp3");
    }
    if (frame == 646 + 230 * 0 || frame == 646 + 230 * 1 || frame == 646 + 230 * 2 || frame == 646 + 230 * 3 || frame == 646 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_11.mp3");
    }
    if (frame == 652 + 230 * 0 || frame == 652 + 230 * 1 || frame == 652 + 230 * 2 || frame == 652 + 230 * 3 || frame == 652 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_11.mp3");
    }
    if (frame == 665 + 230 * 0 || frame == 665 + 230 * 1 || frame == 665 + 230 * 2 || frame == 665 + 230 * 3 || frame == 665 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_02.mp3");
    }
    if (frame == 688 + 230 * 0 || frame == 688 + 230 * 1 || frame == 688 + 230 * 2 || frame == 688 + 230 * 3 || frame == 688 + 230 * 4) {
        audio_->playEffect("res/se/se_quest_battle_12.mp3");
        audio_->playEffect("res/se/se_quest_battle_13.mp3");
        audio_->playEffect("res/se/se_quest_battle_14.mp3");
    }
    if (frame == 1665) {
        audio_->playEffect("res/se/se_quest_battle_01.mp3");
    }
    if (frame == 1672) {
        audio_->playEffect("res/se/se_quest_battle_15.mp3");
    }
    if (frame == 2020) {
        audio_->playEffect("res/se/se_quest_battle_12.mp3");
        audio_->playEffect("res/se/se_quest_battle_13.mp3");
        audio_->playEffect("res/se/se_quest_battle_14.mp3");
    }
    if (frame == 2240) {
        audio_->playEffect("res/se/se_quest_battle_06.mp3");
    }
    if (frame == 2655) {
        audio_->playEffect("res/se/se_quest_battle_16.mp3");
    }
    if (frame == 2665) {
        audio_->playEffect("res/se/se_quest_battle_17.mp3");
    }
}

int ctoi(const char c){
    if('0' <= c && c <= '9') return (c-'0');
    return -1;
}

void SsQuestBattleNode::setBattleStepInfo(int stepId, int styleId, int targetScore, int ownScore, int starCount) {
    stringstream ss1, ss2;
    ss1 << targetScore;
    ss2 << ownScore;
    auto tagetScoreString = ss1.str();
    auto ownScoreString = ss2.str();
    string numCellNames[] = {"num0", "num1", "num2", "num3", "num4", "num5", "num6", "num7", "num8", "num9"};
    string ownNumPartNames[] = {"num0", "num0_1", "num0_2", "num0_3", "num0_4"};
    string targetNumPartNames[] = {"num0_5", "num0_6", "num0_7", "num0_8", "num0_9"};
    // 各ステップ画面
    {
        auto animationPartName = StringUtils::format("c02_battle_battle_2_main_%d", stepId);
        auto partIndex = ssPlayer_->getSSPInstance()->indexOfPart(animationPartName.c_str());
        auto player = ssPlayer_->getSSPInstance()->getSpriteData(partIndex)->getSSPlayer();
        // スコア反映
        {
            for (int i = tagetScoreString.length() - 1, j = 4; i >= 0; --i, --j) {
                auto partName = targetNumPartNames[j];
                auto cellName = numCellNames[ctoi(tagetScoreString[i])];
                player->setPartCell(partName.c_str(), "qb_1", cellName.c_str());
            }
            for (int i = ownScoreString.length() - 1, j = 4; i >= 0; --i, --j) {
                auto partName = ownNumPartNames[j];
                auto cellName = numCellNames[ctoi(ownScoreString[i])];
                player->setPartCell(partName.c_str(), "qb_1", cellName.c_str());
            }
        }
        // 何番目かを反映
        {
            string cellNames[] = {"style_1st", "style_2nd", "style_3th", "style_4th", "style_5th"};
            player->setPartCell("style_1st", "qb_1", cellNames[stepId - 1]);
            player->setPartCell("style_1st_1", "qb_1", cellNames[stepId - 1]);
        }
        // スタイルを反映
        {
            player->setPartCell("style_heart1", "qb_1", StringUtils::format("style_%d", styleId));
            player->setPartCell("style_heart1_1", "qb_1", StringUtils::format("style_%d", styleId));
            player->setPartCell("style_name1", "qb_1", StringUtils::format("style_name_%d", styleId));
            player->setPartCell("style_name1_1", "qb_1", StringUtils::format("style_name_%d", styleId));
            player->setPartCell("cutin_player1", "qb_2", StringUtils::format("cutin_%d", styleId));
        }
        // 星の数を反映
        {
            if (starCount <= 2) {
                player->setPartVisible("bubble3_on", false);
                player->setPartVisible("ef_wave3c", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on", false);
                player->setPartVisible("ef_wave3b", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble1_on", false);
                player->setPartVisible("ef_wave3a", false);
            }
        }
        // 倍率文字列を設定
        {
            if (starCount == 3) {
                player->setPartCell("score3", "qb_1", "score3");
            } else if (starCount == 2) {
                player->setPartCell("score3", "qb_1", "score2");
            } else {
                player->setPartVisible("score3", false);
            }
        }
        // スキルは一旦なし
        {
            player->setPartVisible("skill", false);
        }
    }
    // 結果画面
    {
        auto partIndex = ssPlayer_->getSSPInstance()->indexOfPart("c03_result_result_1_win_1");
        auto player = ssPlayer_->getSSPInstance()->getSpriteData(partIndex)->getSSPlayer();
        vector<string> numPartNames;
        // スコア
        if (stepId == 1) {
            numPartNames = {"num0", "num0_1", "num0_2", "num0_3", "num0_4"};
        } else if (stepId == 2) {
            numPartNames = {"num0_5", "num0_6", "num0_7", "num0_8", "num0_9"};
        } else if (stepId == 3) {
            numPartNames = {"num0_10", "num0_11", "num0_12", "num0_13", "num0_14"};
        } else if (stepId == 4) {
            numPartNames = {"num0_15", "num0_16", "num0_17", "num0_18", "num0_19"};
        } else if (stepId == 5) {
            numPartNames = {"num0_20", "num0_21", "num0_22", "num0_23", "num0_24"};
        }
        for (int i = ownScoreString.length() - 1, j = 4; i >= 0; --i, --j) {
            player->setPartCell(numPartNames[j].c_str(), "qb_1", numCellNames[ctoi(ownScoreString[i])].c_str());
        }
        // スタイル
        player->setPartCell(StringUtils::format("heart_%d", stepId), "qb_1", StringUtils::format("style_%d", styleId));
        // 取得した星の数
        if (stepId == 1) {
            if (starCount <= 2) {
                player->setPartVisible("bubble3_on", false);
                player->setPartVisible("ef_wave3c", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on", false);
                player->setPartVisible("ef_wave3b", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble1_on", false);
                player->setPartVisible("ef_wave3a", false);
            }
        } else if (stepId == 2) {
            if (starCount <= 2) {
                player->setPartVisible("bubble1_on_3", false);
                player->setPartVisible("ef_wave3c_1", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on_3", false);
                player->setPartVisible("ef_wave3b_1", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble3_on_3", false);
                player->setPartVisible("ef_wave3a_1", false);
            }
        } else if (stepId == 3) {
            if (starCount <= 2) {
                player->setPartVisible("bubble1_on_5", false);
                player->setPartVisible("ef_wave3c_2", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on_5", false);
                player->setPartVisible("ef_wave3b_2", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble3_on_5", false);
                player->setPartVisible("ef_wave3a_2", false);
            }
        } else if (stepId == 4) {
            if (starCount <= 2) {
                player->setPartVisible("bubble1_on_7", false);
                player->setPartVisible("ef_wave3c_3", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on_7", false);
                player->setPartVisible("ef_wave3b_3", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble3_on_7", false);
                player->setPartVisible("ef_wave3a_3", false);
            }
        } else if (stepId == 5) {
            if (starCount <= 2) {
                player->setPartVisible("bubble1_on_9", false);
                player->setPartVisible("ef_wave3c_4", false);
            }
            if (starCount <= 1) {
                player->setPartVisible("bubble2_on_9", false);
                player->setPartVisible("ef_wave3b_4", false);
            }
            if (starCount <= 0) {
                player->setPartVisible("bubble3_on_9", false);
                player->setPartVisible("ef_wave3a_4", false);
            }
        }
        
    }
}

void SsQuestBattleNode::onExit() {
    Node::onExit();
    if (playerImageHandle_ >= 0) {
        ss::SSTextureRelese(playerImageHandle_);
    }
    if (resultPlayerImageHandle_ >= 0) {
        ss::SSTextureRelese(resultPlayerImageHandle_);
    }
    if (enemyImageHandle_ >= 0) {
        ss::SSTextureRelese(enemyImageHandle_);
    }
    audio_->stopBackgroundMusic();
}

void SsQuestBattleNode::play() {
    ssPlayer_->getSSPInstance()->play("qb_kakunin/kakunin");
    ssPlayer_->getSSPInstance()->setLoop(1);
}

void SsQuestBattleNode::setPlayEndCallback(std::function<void(ss::Player*)> callback) {
    ssPlayer_->getSSPInstance()->setPlayEndCallback(callback);
}


