//
//  CharacterBaseNode.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/05.
//
//

#ifndef __TsukubonQuest__CharacterBaseNode__
#define __TsukubonQuest__CharacterBaseNode__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "CharacterInfo.h"
#include "InputManager.h"

#include "ConvertUtil.h"
USING_NS_CC;

class CharacterBaseNode: public Sprite {
    
protected:
//    cocos2d::Layer *_mainLayer;
    
    // コンストラクタ／デストラクタ
    CharacterBaseNode();
    virtual ~CharacterBaseNode();
    
    // Infoから初期化
    virtual bool init(CharacterInfo *characterInfo);
    
    // Info
    CharacterInfo *characterInfo;
        
    // アニメーション
    std::map<CharacterDirection, Animation *> moveAnimationMap;
    SpriteFrame *getSpriteFrame(CharacterDirection direction, int num);
    Animation *createMoveAnimation(CharacterDirection direction);
    void updateAnimation();
    
    
public:
    static CharacterBaseNode *create(CharacterInfo *characterInfo);
    
    // --- メインループ ---
    void updatePos();
    
    // --- setter ---
    // 位置を設定
    void setGridPos(Vec2 pos);
    
    // --- getter ---
    // 位置を取得
    Vec2 getGridPos();
    Vec2 getPixelPos();
    
    
};


#endif /* defined(__TsukubonQuest__CharacterBaseNode__) */
