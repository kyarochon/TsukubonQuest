//
//  InputLayer.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/08/26.
//
//

#include "InputLayer.h"



InputLayer::InputLayer()
{
}


InputLayer::~InputLayer() {
}

#pragma mark - 初期化
InputLayer *InputLayer::create(std::string csbName)
{
    InputLayer *ret = new InputLayer();
    if (ret->init(csbName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool InputLayer::init(std::string csbName)
{
    if (!CsbBaseLayer::init(csbName))
        return false;
    
    // ボタンイベント付与
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    std::vector<std::string> buttonNameVec = {"downButton", "leftButton", "rightButton", "upButton", "okButton", "cancelButton"};
    std::vector<InputType> inputTypeVec = {InputType::DOWN, InputType::LEFT, InputType::RIGHT, InputType::UP, InputType::OK, InputType::CANCEL};
    for (int i = 0; i < buttonNameVec.size(); i++)
    {
        auto buttonName = buttonNameVec.at(i);
        auto inputType  = inputTypeVec.at(i);
        this->addButtonEvent(panel->getChildByName<ui::Button *>(buttonName), (int)inputType);
    }
    
    // update
    this->scheduleUpdate();
    
    return true;
}

#pragma mark - メインループ
void InputLayer::update(float dt)
{
    // ループ
    InputManager::getInstance()->update(dt);
}


#pragma mark - ボタン
void InputLayer::pushedButton(Ref *pSender, ui::Widget::TouchEventType type)
{
    auto button = static_cast<ui::Button *>(pSender);
    auto inputManager = InputManager::getInstance();
    auto inputType = (InputType)button->getTag();
    
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            inputManager->touchBegan(inputType);
            break;
        case cocos2d::ui::Widget::TouchEventType::MOVED:
            inputManager->touchMoved(inputType);
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            inputManager->touchEnded(inputType);
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            inputManager->touchCanceled(inputType);
            break;
    }
}






