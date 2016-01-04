//
//  MenuLayer.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/12/07.
//
//

#include "MenuLayer.hpp"
#include "EventUtil.h"


MenuLayer::MenuLayer()
{
    // イベント登録
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addCustomEventListener(EVENT_SHOW_ENEMY_LIST_LAYER, CC_CALLBACK_1(MenuLayer::eventShowEnemyListLayer, this));
    dispatcher->addCustomEventListener(EVENT_CLOSE_ENEMY_LIST_LAYER, CC_CALLBACK_1(MenuLayer::eventCloseEnemyListLayer, this));

}


MenuLayer::~MenuLayer() {
}

#pragma mark - 初期化
MenuLayer *MenuLayer::create(std::string csbName)
{
    MenuLayer *ret = new MenuLayer();
    if (ret->init(csbName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool MenuLayer::init(std::string csbName)
{
    if (!CsbBaseLayer::init(csbName))
        return false;
    
    // ボタンイベント付与
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    panel->setTouchEnabled(false);
    this->addButtonEvent(panel->getChildByName<ui::Button *>("enemyButton"), ButtonTag::Enemy);
    
    return true;
}



#pragma mark - ボタン
void MenuLayer::pushedButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
        return;
    }

    auto button = static_cast<ui::Button *>(pSender);
    auto tag = button->getTag();
    switch (tag) {
        // エネミーリスト表示
        case ButtonTag::Enemy:
            Util::Event::sendCustomEvent(EVENT_SHOW_ENEMY_LIST_LAYER);
            break;
            
        default:
            break;
    }
}


#pragma mark - イベント
void MenuLayer::eventShowEnemyListLayer(cocos2d::EventCustom *event) {
    this->setVisible(false);
}

void MenuLayer::eventCloseEnemyListLayer(cocos2d::EventCustom *event) {
    this->setVisible(true);
}





