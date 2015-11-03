//
//  MapManager.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/11.
//
//

#include "MapManager.h"
#include "ConvertUtil.h"

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


#pragma mark - マップサイズ設定
void MapManager::initMap(int gridMaxX, int gridMaxY)
{
    // 現在のマップのサイズを設定
    this->gridMaxX = gridMaxX;
    this->gridMaxY = gridMaxY;
    this->scrollX  = 0;
    this->scrollY  = 0;
    
    
    // データを初期化
    for (int i = 0; i < GRID_MAX_X; i++)
    {
        for (int j = 0; j < GRID_MAX_Y; j++)
        {
            // マップサイズ内は全てNONE
            if (i < gridMaxX && j < gridMaxX)
            {
                this->addObjectAt(i, j, MapState::NONE);
            }
            // マップサイズ外は全て障害物
            else
            {
                this->addObjectAt(i, j, MapState::OBJECT);
            }
        }
    }
}


#pragma mark - 障害物データ設定
void MapManager::setCollisionData(TMXLayer *collisionLayer)
{
    if (collisionLayer)
    {
        for (int i = 0; i < gridMaxX; i++) {
            for (int j = 0; j < gridMaxY; j++) {
                auto tile = collisionLayer->getTileAt(Vec2(i, j));
                if (tile)
                {
                    log("[T] RpgTiledMap::init collision(%d,%d)", i, j);
                    mapManager->addObjectAt(i, j, MapState::OBJECT);
                    tile->setVisible(false);
                }
            }
        }
    }
}


#pragma mark - オブジェクトデータ設定
void MapManager::setObjectData(cocos2d::TMXObjectGroup *objectGroup)
{
    auto objects = objectGroup->getObjects();
    for (Value object : objects)
    {
        ValueMap objectInfo = object.asValueMap();
        auto type = objectInfo.at("type").asString();
        auto name = objectInfo.at("name").asString();
        
        float x = objectInfo.at("x").asFloat();
        float y = objectInfo.at("y").asFloat();
        
        int gridX = (int)(x / TILE_SIZE);
        int gridY = (int)(y / -TILE_SIZE) + (gridMaxY - 2);
        
        // 移動用オブジェクト
        if (type == "move")
        {
            this->addObjectAt(gridX, gridY, MapState::MOVE);
        }
    }
}

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

#pragma mark - タップ
void MapManager::tapped(Vec2 position)
{
    int gridX = scrollX + position.x / TILE_SIZE;
    int gridY = gridMaxY - position.y / TILE_SIZE - 1 - scrollY;
    
    // 横のスクロールが必要な場合
    if (gridX < GRID_SCREEN_X / 2)
    {
        scrollX = 0;
    }
    else if (gridX > gridMaxX - GRID_SCREEN_X / 2)
    {
        scrollX = gridMaxX - GRID_SCREEN_X;
    }
    else
    {
        scrollX = gridX - GRID_SCREEN_X / 2;
    }
    
    
    // 縦のスクロールが必要な場合
    if (gridY < GRID_SCREEN_Y / 2)
    {
        scrollY = gridMaxY - GRID_SCREEN_Y;
    }
    else if (gridY > gridMaxY - GRID_SCREEN_Y / 2)
    {
        scrollY = 0;
    }
    else
    {
        scrollY = gridMaxY - (gridY + GRID_SCREEN_Y / 2);
    }
    
    
    log("tapped (%f, %f) -> (%d, %d) S(%d, %d)", position.x, position.y, gridX, gridY, scrollX, scrollY);
}


Vec2 MapManager::getScrollPos()
{
    float pixelX = -1.0f * (float)scrollX * TILE_SIZE;
    float pixelY = -1.0f * (float)scrollY * TILE_SIZE;
    
    return Vec2(pixelX, pixelY);
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