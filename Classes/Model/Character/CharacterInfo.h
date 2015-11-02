//
//  CharacterInfo.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/05.
//
//

#ifndef __TsukubonQuest__CharacterInfo__
#define __TsukubonQuest__CharacterInfo__


#include "cocos2d.h"
#include "InputManager.h"
#include "CharacterDefine.h"
#include "MapManager.h"

USING_NS_CC;

class CharacterInfo
{
public:


    CharacterInfo(CharacterType characterType);

protected:
    virtual ~CharacterInfo();
    
    // サイズ
    int characterSize;
    
    // 種類
    CharacterType characterType;
    
    // 座標
    Vec2 gridPos;
    
    // 方向
    CharacterDirection direction;
    
    // 画像
    std::string fileName;
    
    
    
public:
    // --- setter ---
    
    // 位置を設定
    void setGridPos(Vec2 pos);
    
    
    // --- getter ---
    
    // 方向を取得
    CharacterDirection getDirection();
    
    // 位置を取得
    Vec2 getGridPos();
    
    // サイズを取得
    int getCharacterSize();
    
    // 画像名を取得
    std::string getFileName();
    
    // 画像を取得
    SpriteFrame *getSpriteFrame(int num);
    
    // 画像の何列目にあるかどうか
    int getImageIndex();
    
    
    // --- update ---
    
    // 方向を更新
    void updateInput();
    
    // 位置を更新
    void updatePos();
    
    
};


#endif /* defined(__TsukubonQuest__CharacterInfo__) */
