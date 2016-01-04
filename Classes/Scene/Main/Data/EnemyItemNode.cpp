//
//  EnemyItemNode.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/22.
//
//

#include "EnemyItemNode.hpp"
#include "ImageResourceManager.hpp"
#include "NetworkDefine.h"

EnemyItemNode::EnemyItemNode()
//:imageSprite(nullptr)
:nameLabel(nullptr)
,attackLabel(nullptr)
,defenseLabel(nullptr)
,hpLabel(nullptr)
,speedLabel(nullptr)
,imageName("")
{
    // ---------- イベント登録 ----------
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener(EVENT_DOWNLOAD_ENEMY_IMAGE, CC_CALLBACK_1(EnemyItemNode::eventFinishLoadingImage, this));

}


EnemyItemNode::~EnemyItemNode() {
}

#pragma mark - 初期化
EnemyItemNode *EnemyItemNode::create(std::string csbName)

{
    EnemyItemNode *ret = new EnemyItemNode();
    if (ret->init(csbName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool EnemyItemNode::init(std::string csbName)
{
    if (!CsbBaseLayer::init(csbName))
        return false;
    
    imageSprite  = _mainLayer->getChildByName<Sprite *>("imageSprite");
    nameLabel    = _mainLayer->getChildByName<ui::Text *>("nameLabel");
    attackLabel  = _mainLayer->getChildByName<ui::Text *>("attackLabel");
    defenseLabel = _mainLayer->getChildByName<ui::Text *>("defenseLabel");
    hpLabel      = _mainLayer->getChildByName<ui::Text *>("hpLabel");
    speedLabel   = _mainLayer->getChildByName<ui::Text *>("speedLabel");
    
    return true;
}

// キャラクターデータの表示
void EnemyItemNode::setCharacterData(CharacterData *data) {
    nameLabel->setString(data->name);
    attackLabel->setString(StringUtils::format("攻撃力：%d", data->attack));
    defenseLabel->setString(StringUtils::format("防御力：%d", data->defense));
    hpLabel->setString(StringUtils::format("HP：%d", data->hp));
    speedLabel->setString(StringUtils::format("素早さ：%d", data->speed));
    
    // 画像読み込み開始
    imageName = std::string(AWS_S3_HOME) + "enemies/" + data->imageName;
    ImageResourceManager::getInstance()->loadImage(imageName, EVENT_DOWNLOAD_ENEMY_IMAGE);
}

// 画像読み込み終了時
void EnemyItemNode::eventFinishLoadingImage(cocos2d::EventCustom *event) {
    auto loadedImageName = Util::Event::getEventDataString(event);
    if (imageName == loadedImageName) {
        auto texture = ImageResourceManager::getInstance()->getImage(imageName);
        if (texture) {
            imageSprite->setTexture(texture);
        } else {
            log("error");
        }
        
    }
}



