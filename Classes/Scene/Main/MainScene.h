//
//  MainScene.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/02.
//
//

#ifndef __TsukubonQuest__MainScene__
#define __TsukubonQuest__MainScene__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "RpgTiledMap.h"

#include "CharacterInfo.h"

USING_NS_CC;

class MainScene : public Layer
{
    enum MainZOrder {
        MainMap = 0,
        Character,
        InputLayer = 1000,
        MenuLayer,
        EnemyListLayer,
    };
    
    
protected:
    MainScene();
    virtual ~MainScene();
    
    // 読み込み完了時に呼ばれる
//    virtual void onEnterTransitionDidFinish();
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MainScene);
    
private:
    CharacterInfo *characterInfo;
    
    CharacterBaseNode *characterNode;
    RpgTiledMap *rpgTiledMap;
    
    void update(float dt);
    
    
};


#endif /* defined(__TsukubonQuest__MainScene__) */
