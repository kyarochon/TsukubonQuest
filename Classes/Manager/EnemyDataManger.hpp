//
//  EnemyDataManger.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/12/10.
//
//

#ifndef EnemyDataManger_hpp
#define EnemyDataManger_hpp

USING_NS_CC;

#include "CharacterData.hpp"
#include "HttpUtil.h"

class EnemyDataManger {
    
private:
    EnemyDataManger();
    static EnemyDataManger* enemyDataManger;
    
    // 敵一覧データ
    std::vector<CharacterData *> enemyDataList;
    
    // 読み込み状態
    LoadingState loadingState;
    
public:
    // 初期化
    static EnemyDataManger* getInstance();
    
    void init();
    void load();
    void reload();
    
    
    // 読み込み完了時
    void httpResponseCallBack(HttpResponse *response);
    
    
    // getter
    LoadingState getLoadingState() {return loadingState;}
    std::vector<CharacterData *> getEnemyList() {return enemyDataList;}
};

#endif /* EnemyDataManger_hpp */
