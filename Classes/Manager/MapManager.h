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
    int gridMaxX;
    int gridMaxY;
    
    // 現在のマップのスクロール位置
    int scrollX;
    int scrollY;
    
    
public:
    // 初期化
    static MapManager* getInstance();
    
    
    // ----- マップ初期設定 -----
    // マップサイズ設定
    void initMap(int gridMaxX, int gridMaxY);
    
    // 障害物データ設定
    void setCollisionData(TMXLayer *collisionLayer);
    
    // オブジェクトデータ設定
    void setObjectData(TMXObjectGroup *objectGroup);
    bool addObjectAt(int x, int y, MapState mapState);
    bool removeObjectAt(int x, int y);
    
    
    // ----- タップ -----
    void tapped(Vec2 position);
    
    
    
    // ----- データ取得 -----
    // 現在のスクロール位置
    Vec2 getScrollPos() {
        float pixelX = -1.0f * (float)scrollX * TILE_SIZE;
        float pixelY = -1.0f * (float)scrollY * TILE_SIZE;
        return Vec2(pixelX, pixelY);
    }
    
    // 現在のマップサイズ
    Size getMapSize() {
        return Size(this->gridMaxX, this->gridMaxY);
    }
    
    
    
    // --- デバッグ機能 ---
    // データ確認
    void debugCheckData();
};


#endif /* defined(__TsukubonQuest__MapManager__) */
