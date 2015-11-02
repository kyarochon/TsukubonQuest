//
//  CsbBaseLayer.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/02.
//
//

#ifndef __TsukubonQuest__CsbBaseLayer__
#define __TsukubonQuest__CsbBaseLayer__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;

class CsbBaseLayer: public Layer {
    
protected:
    cocos2d::Layer *_mainLayer;
    
    // コンストラクタ／デストラクタ
    CsbBaseLayer();
    virtual ~CsbBaseLayer();
    
    // csbファイル名から初期化
    virtual bool init(std::string csbName);
    
    // ボタンイベントの作成
    void addButtonEvent(ui::Button *button, int tag);
    virtual void pushedButton(Ref *pSender, ui::Widget::TouchEventType type);
    
public:
    
};



#endif /* defined(__TsukubonQuest__CsbBaseLayer__) */
