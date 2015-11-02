//
//  InputLayer.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/08/26.
//
//

#ifndef __TsukubonQuest__InputLayer__
#define __TsukubonQuest__InputLayer__

#include "CsbBaseLayer.h"
#include "InputManager.h"

class InputLayer: public CsbBaseLayer
{
    enum InputZOrder {
        LAYER = 0,
    };
    
    
protected:
    // コンストラクタ／デストラクタ
    InputLayer();
    virtual ~InputLayer();

    // 初期化
    bool init(std::string csbName);
    
    // ボタン
    void pushedButton(Ref *pSender, ui::Widget::TouchEventType type);
    
    // メインループ
    void update(float dt);
    
public:
    static InputLayer *create(std::string csbName);
    
};






#endif /* defined(__TsukubonQuest__InputLayer__) */
