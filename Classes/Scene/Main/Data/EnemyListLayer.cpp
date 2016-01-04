//
//  EnemyListLayer.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/18.
//
//

#include "EnemyListLayer.hpp"
#include "EnemyDataManger.hpp"

#include "network/HttpClient.h"
#include "EventUtil.h"
#include "HttpUtil.h"
#include "spine/Json.h"

#define ENEMY_ITEM_NODE_HEIGHT (160.0f)

using namespace cocos2d::network;


EnemyListLayer::EnemyListLayer()
{
    // イベント登録
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener(EVENT_SHOW_ENEMY_LIST_LAYER, CC_CALLBACK_1(EnemyListLayer::eventShowEnemyListLayer, this));
    dispatcher->addCustomEventListener(EVENT_CLOSE_ENEMY_LIST_LAYER, CC_CALLBACK_1(EnemyListLayer::eventCloseEnemyListLayer, this));
    dispatcher->addCustomEventListener(EVENT_FINISH_LOADING_ENEMY_DATA, CC_CALLBACK_1(EnemyListLayer::eventFinishLoadingEnemyData, this));
}


EnemyListLayer::~EnemyListLayer() {
}

#pragma mark - 初期化
EnemyListLayer *EnemyListLayer::create(std::string csbName)
{
    EnemyListLayer *ret = new EnemyListLayer();
    if (ret->init(csbName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool EnemyListLayer::init(std::string csbName)
{
    if (!CsbBaseLayer::init(csbName))
        return false;
    
    // ボタン設定
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    this->addButtonEvent(panel->getChildByName<ui::Button *>("closeButton"), ButtonTag::Close);
    this->addButtonEvent(panel->getChildByName<ui::Button *>("reloadButton"), ButtonTag::Reload);
    
    // 最初は非表示
    this->setVisible(false);

    
    // 敵一覧情報の読み込み
    auto loadingState = EnemyDataManger::getInstance()->getLoadingState();
    switch (loadingState) {
        // 読み込み完了してる → すぐ表示
        case LoadingState::Finished:
            this->updateEnemyList();
            break;
            
        // 未読み込み or 読み込み失敗 → 読み込み開始
        case LoadingState::Init:
        case LoadingState::Failed:
            EnemyDataManger::getInstance()->load();
            
        // 読込中 → 何もせず終わるのを待つ
        default:
            break;
    }
    

    return true;
}




void EnemyListLayer::updateEnemyList() {
    auto enemyList = EnemyDataManger::getInstance()->getEnemyList();

    // 敵データに沿ってNodeを追加
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    auto scrollView = panel->getChildByName<ui::ScrollView *>("scrollView");
    float scrollViewHeight = enemyList.size() * ENEMY_ITEM_NODE_HEIGHT;
    float scrollViewWidth  = scrollView->getContentSize().width;
    scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, scrollViewHeight));
    for (int i = 0; i < enemyList.size(); i++) {
        auto enemyData = enemyList.at(i);
        auto enemyItemNode = EnemyItemNode::create("EnemyItemNode.csb");
        enemyItemNode->setCharacterData(enemyData);
        enemyItemNode->setPosition(Vec2(scrollViewWidth / 2.0f, scrollViewHeight -  (i + 0.5f) * ENEMY_ITEM_NODE_HEIGHT));
        scrollView->addChild(enemyItemNode);
    }
}

void EnemyListLayer::removeEnemyList() {
    // 削除
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    auto scrollView = panel->getChildByName<ui::ScrollView *>("scrollView");
    scrollView->removeAllChildren();
    scrollView->setInnerContainerSize(Size::ZERO);
}


#pragma mark - ===== ボタン =====
void EnemyListLayer::pushedButton(cocos2d::Ref *pSender, ui::Widget::TouchEventType type) {
    if (type != ui::Widget::TouchEventType::ENDED) {
        return;
    }
    
    auto button = (ui::Button *)pSender;
    auto tag = button->getTag();
    switch (tag) {
        // エネミーリストを閉じる
        case ButtonTag::Close:
            Util::Event::sendCustomEvent(EVENT_CLOSE_ENEMY_LIST_LAYER);
            break;
        case ButtonTag::Reload:
            this->removeEnemyList();
            EnemyDataManger::getInstance()->reload();
            break;
            
        default:
            break;
    }
    
}


#pragma mark - ===== イベント =====
void EnemyListLayer::eventShowEnemyListLayer(cocos2d::EventCustom *event) {
    this->setVisible(true);
}

void EnemyListLayer::eventCloseEnemyListLayer(cocos2d::EventCustom *event) {
    this->setVisible(false);
}

void EnemyListLayer::eventFinishLoadingEnemyData(cocos2d::EventCustom *event) {
    this->updateEnemyList();
}


