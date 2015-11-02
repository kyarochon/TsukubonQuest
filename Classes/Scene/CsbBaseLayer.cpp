//
//  CsbBaseLayer.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/02.
//
//

#include "CsbBaseLayer.h"

#pragma mark - コンストラクタ／デストラクタ
CsbBaseLayer::CsbBaseLayer()
:_mainLayer(nullptr)
{
}

CsbBaseLayer::~CsbBaseLayer() {
}

#pragma mark - 初期化
bool CsbBaseLayer::init(std::string csbName)
{
    if (!Layer::init()) {
        return false;
    }
    auto size = Director::getInstance()->getWinSize();
    
    // csbファイル読み込み
    _mainLayer = static_cast<Layer *>(CSLoader::getInstance()->createNode(csbName));
    this->addChild(_mainLayer);
    
    return true;
}


#pragma mark - ボタン
void CsbBaseLayer::addButtonEvent(ui::Button *button, int tag)
{
    button->setTag(tag);
    button->addTouchEventListener(CC_CALLBACK_2(CsbBaseLayer::pushedButton, this));
}


void CsbBaseLayer::pushedButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    if (type != ui::Widget::TouchEventType::ENDED)
        return;
    
    log("CsbBaseLayer::pushedButton");
}





