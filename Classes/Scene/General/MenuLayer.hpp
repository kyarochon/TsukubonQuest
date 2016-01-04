//
//  MenuLayer.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/12/07.
//
//

#ifndef MenuLayer_hpp
#define MenuLayer_hpp

#include "CsbBaseLayer.h"

class MenuLayer: public CsbBaseLayer
{
private:
    enum ButtonTag {
        Enemy = 0,
    };
    
    
    
protected:
    // コンストラクタ／デストラクタ
    MenuLayer();
    virtual ~MenuLayer();
    
    // 初期化
    bool init(std::string csbName);
    
    // ボタン
    void pushedButton(Ref *pSender, ui::Widget::TouchEventType type);
    
    
    void eventShowEnemyListLayer(EventCustom *event);
    void eventCloseEnemyListLayer(EventCustom *event);
    
public:
    static MenuLayer *create(std::string csbName);
    
};

#endif /* MenuLayer_hpp */
