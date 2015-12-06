//
//  EnemyItemNode.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/22.
//
//

#ifndef EnemyItemNode_hpp
#define EnemyItemNode_hpp

#include "CsbBaseLayer.h"
#include "CharacterData.hpp"

class EnemyItemNode: public CsbBaseLayer
{
    
protected:
    Sprite *imageSprite;
    ui::Text *nameLabel;
    ui::Text *attackLabel;
    ui::Text *defenseLabel;
    ui::Text *hpLabel;
    ui::Text *speedLabel;
    std::string imageName;

    
protected:
    // コンストラクタ／デストラクタ
    EnemyItemNode();
    virtual ~EnemyItemNode();
    
    // 初期化
    bool init(std::string csbName);
    
    
    void eventFinishLoadingImage(EventCustom *event);
    
    
public:
    static EnemyItemNode *create(std::string csbName);
    void setCharacterData(CharacterData *data);
};


#endif /* EnemyItemNode_hpp */
