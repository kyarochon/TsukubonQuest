//
//  RpgTiledMap.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/12.
//
//

#ifndef __TsukubonQuest__RpgTiledMap__
#define __TsukubonQuest__RpgTiledMap__

#include "cocos2d.h"
#include "CharacterBaseNode.h"
USING_NS_CC;

class RpgTiledMap: public TMXTiledMap {
    
protected:
    // コンストラクタ／デストラクタ
    RpgTiledMap();
    virtual ~RpgTiledMap();
    
    // Tiledファイル名から初期化
    virtual bool init(std::string fileName);

    
    // タップ
    void tapped(Touch *touch);
    
private:
//    cocos2d::Layer *_mainLayer;
    
public:
    static RpgTiledMap *create(std::string fileName);
    
    void updatePos(CharacterBaseNode *characterNode);
    void addCharacter(CharacterBaseNode *characterNode);
    
};


#endif /* defined(__TsukubonQuest__RpgTiledMap__) */
