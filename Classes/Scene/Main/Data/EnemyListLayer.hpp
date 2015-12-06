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

    
protected:
    // コンストラクタ／デストラクタ
    EnemyListLayer();
    virtual ~EnemyListLayer();
    
    // 初期化
    bool init(std::string csbName);
    
    // ボタン
  //  void pushedButton(Ref *pSender, ui::Widget::TouchEventType type);
    
    // メインループ
//    void update(float dt);
    
    void httpResponseCallBack(std::string result);
    std::vector<CharacterData *> characterDataList;
    
public:
    static EnemyListLayer *create(std::string csbName);
    
};







#endif /* EnemyListLayer_hpp */
