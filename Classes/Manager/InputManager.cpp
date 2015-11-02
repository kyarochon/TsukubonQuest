//
//  InputManager.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#include "InputManager.h"

#pragma mark - 初期化
InputManager* InputManager::inputManager = nullptr;
InputManager::InputManager()
:inputType(InputType::NONE)
,inputPhase(InputPhase::NONE)
,changedInputState(false)
{
}

InputManager *InputManager::getInstance()
{
    if(inputManager == nullptr)
    {
        inputManager = new InputManager();
    }
    return inputManager;
}



#pragma mark - 入力
// 入力受付
void InputManager::touchBegan(InputType inputType)
{
    this->inputQueue.push(std::pair<InputType, InputPhase>(inputType, InputPhase::BEGIN));
}

void InputManager::touchMoved(InputType inputType)
{
    this->inputQueue.push(std::pair<InputType, InputPhase>(inputType, InputPhase::TOUCHING));
}

void InputManager::touchEnded(InputType inputType)
{
    this->inputQueue.push(std::pair<InputType, InputPhase>(inputType, InputPhase::END));
}

void InputManager::touchCanceled(InputType inputType)
{
    this->inputQueue.push(std::pair<InputType, InputPhase>(inputType, InputPhase::NONE));
}


// ループ
void InputManager::update(float dt)
{
    this->changedInputState = false;
    
    // タッチ終了の場合は1フレーム待っとく
    if (this->inputPhase == InputPhase::END)
    {
        this->inputPhase = InputPhase::NONE;
        this->inputType  = InputType::NONE;
        this->changedInputState = true;
        return;
    }
    
    // キューが溜まっていれば1フレームごとに処理していく
    if (inputQueue.size() > 0)
    {
        auto inputPair = inputQueue.front();
        transferPhase(inputPair.first, inputPair.second);
        inputQueue.pop();
    }
    
}


// 入力遷移
void InputManager::transferPhase(InputType nextType, InputPhase nextPhase)
{
    log("InputType: %d, InputPhase:%d", (int)nextType, (int)nextPhase);
    
    // 遷移可能かチェック
    bool enableTransition = true;
    switch (nextPhase) {
        case InputPhase::BEGIN:
            enableTransition = (inputPhase == InputPhase::NONE);
            break;
        case InputPhase::TOUCHING:
            enableTransition = (inputPhase == InputPhase::BEGIN);
            break;
        case InputPhase::END:
            enableTransition = (inputPhase == InputPhase::BEGIN || inputPhase == InputPhase::TOUCHING);
            break;
        case InputPhase::NONE:
            break;
    }
    if (!enableTransition)
        return;
    
    // 情報更新
    this->inputType  = nextType;
    this->inputPhase = nextPhase;
    this->changedInputState = true;
}

void InputManager::updatePhase()
{
    switch (inputPhase) {
        case InputPhase::BEGIN:
            this->changedInputState = false;
            break;
        case InputPhase::TOUCHING:
            this->changedInputState = false;
            break;
        case InputPhase::END:
            this->inputPhase = InputPhase::NONE;
            this->inputType  = InputType::NONE;
            this->changedInputState = true;
            break;
        case InputPhase::NONE:
            this->changedInputState = false;
            break;
    }
}

bool InputManager::hasChangedInputState()
{
    return this->changedInputState;
}



#pragma mark - getter
InputType InputManager::getInputType()
{
    return this->inputType;
}

InputPhase InputManager::getInputPhase()
{
    return this->inputPhase;
}

