//
//  MapManager.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#include "MapManager.h"


#pragma mark - 初期化
MapManager* MapManager::mapManager = nullptr;
MapManager::MapManager()
{
    // 初期化
    for (int i = 0; i < GRID_MAX_X; i++) {
        for (int j = 0; j < GRID_MAX_Y; j++) {
            mapData[i][j] = MapState::NONE;
        }
    }
}

MapManager *MapManager::getInstance()
{
    if(mapManager == nullptr)
    {
        mapManager = new MapManager();
    }
    return mapManager;
}


#pragma mark - マップ遷移


#pragma mark - マップサイズの設定／取得
void MapManager::setMapSize(Size mapSize)
{
    this->mapSize = mapSize;
}

Size MapManager::getMapSize()
{
    return this->mapSize;
}

#pragma mark - オブジェクト配置
bool MapManager::addObjectAt(int x, int y, MapState mapState)
{
    // すでに何か配置済みならfalse
    if (mapData[x][y] != MapState::NONE)
        return false;
    
    // 何もなければ配置してtrue
    mapData[x][y] = mapState;
    
    return true;
}

bool MapManager::removeObjectAt(int x, int y)
{
    // 何もなければfalse
    if (mapData[x][y] == MapState::NONE)
        return false;
    
    // 何かあれば削除してtrue
    mapData[x][y] = MapState::NONE;
    
    return true;
}



#pragma mark - デバッグ機能
void MapManager::debugCheckData()
{
    log("【MapData】");
    for (int j = 0; j < GRID_MAX_Y; j++)
    {
        std::string dataStr = "";
        for (int i = 0 ; i < GRID_MAX_X; i++)
        {
            if (mapData[i][j] == MapState::NONE)
            {
                dataStr += " ";
            }
            else if (mapData[i][j] == MapState::OBJECT)
            {
                dataStr += "x";
            }
            else if (mapData[i][j] == MapState::MOVE)
            {
                dataStr += "M";
            }
        }
        log("%s", dataStr.c_str());
    }
    log("------------------------");
}