//
//  MapManager.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#ifndef __TsukubonQuest__MapManager__
#define __TsukubonQuest__MapManager__

#include "cocos2d.h"
#include "MapDefine.h"

USING_NS_CC;

class MapManager {
    
private:
    MapManager();
    static MapManager* mapManager;
    
    // マップ情報
    MapState mapData[GRID_MAX_X][GRID_MAX_Y];
    
    // 現在のマップのサイズ
    Size mapSize;
    
public:
    // 初期化
    static MapManager* getInstance();
    
    // マップサイズの設定／取得
    void setMapSize(Size mapSize);
    Size getMapSize();
    
    // オブジェクトの追加
    bool addObjectAt(int x, int y, MapState mapState);
    bool removeObjectAt(int x, int y);
    
    // --- デバッグ機能 ---
    // データ確認
    void debugCheckData();
};


#endif /* defined(__TsukubonQuest__MapManager__) */
