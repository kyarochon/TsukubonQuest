//
//  InputManager.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#ifndef __TsukubonQuest__InputManager__
#define __TsukubonQuest__InputManager__

#include "cocos2d.h"
#include "InputDefine.h"

USING_NS_CC;

class InputManager {
    
private:
    InputManager();
    static InputManager* inputManager;
    
    // 入力情報
    InputType inputType;
    InputPhase inputPhase;
    bool changedInputState;
    
    // 状態の遷移
    void transferPhase(InputType nextType, InputPhase nextPhase);
    
    
    //
    std::queue<std::pair<InputType, InputPhase>> inputQueue;
    
    
public:
    // 初期化
    static InputManager* getInstance();
    
    // 入力受付
    void touchBegan(InputType inputType);
    void touchMoved(InputType inputType);
    void touchEnded(InputType inputType);
    void touchCanceled(InputType inputType);
    
    // メインループ
    void update(float dt);
    // 入力情報の更新
    void updatePhase();
    // 更新があったかどうか
    bool hasChangedInputState();
    
    
    // getter
    InputType getInputType();
    InputPhase getInputPhase();
    
};


#endif /* defined(__TsukubonQuest__InputManager__) */
