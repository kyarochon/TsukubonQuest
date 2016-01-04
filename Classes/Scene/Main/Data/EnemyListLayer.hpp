//
//  EnemyListLayer.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/18.
//
//

#ifndef EnemyListLayer_hpp
#define EnemyListLayer_hpp



#include "CsbBaseLayer.h"
#include "CharacterData.hpp"
#include "EnemyItemNode.hpp"

class EnemyListLayer: public CsbBaseLayer
{
    enum ButtonTag {
        Close = 0,
        Reload,
    };
    
    
    
protected:
    // コンストラクタ／デストラクタ
    EnemyListLayer();
    virtual ~EnemyListLayer();
    
    // 初期化
    bool init(std::string csbName);
    
    // ボタン
    void pushedButton(Ref *pSender, ui::Widget::TouchEventType type);
    
    
    void updateEnemyList();
    void removeEnemyList();
    
    void eventShowEnemyListLayer(EventCustom *event);
    void eventCloseEnemyListLayer(EventCustom *event);
    void eventFinishLoadingEnemyData(EventCustom *event);
    
    
    
public:
    static EnemyListLayer *create(std::string csbName);
    
};







#endif /* EnemyListLayer_hpp */
