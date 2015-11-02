//
//  RpgTiledMap.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/12.
//
//

#include "RpgTiledMap.h"
#include "MapManager.h"
#include "ConvertUtil.h"

#define LAYER_NAME_OBJECT    "object"
#define LAYER_NAME_COLLISION "collision"


#pragma mark - 初期化
RpgTiledMap::RpgTiledMap()
:gridMaxX(0)
,gridMaxY(0)
{
    
}

RpgTiledMap::~RpgTiledMap()
{
    
}


RpgTiledMap *RpgTiledMap::create(std::string fileName)
{
    RpgTiledMap *ret = new RpgTiledMap();
    if (ret->init(fileName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool RpgTiledMap::init(std::string fileName)
{
    if (!TMXTiledMap::initWithTMXFile(fileName))
        return false;
    
    auto mapManager = MapManager::getInstance();
    
    // 左上基準
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->setPosition(Vec2(0.0f, this->getContentSize().height));
    
    // マップサイズを取得 ＆ 設定
    auto size = this->getContentSize();
    auto tile = this->getTileSize();
    gridMaxX = size.width / tile.width;
    gridMaxY = size.height / tile.height;
    mapManager->setMapSize(Size(gridMaxX, gridMaxY));
    
    
    // データを初期化
    for (int i = 0; i < GRID_MAX_X; i++)
    {
        for (int j = 0; j < GRID_MAX_Y; j++)
        {
            // マップサイズ内は全てNONE
            if (i < gridMaxX && j < gridMaxY)
            {
                mapManager->addObjectAt(i, j, MapState::NONE);
            }
            // マップサイズ外は全て障害物
            else
            {
                mapManager->addObjectAt(i, j, MapState::OBJECT);
            }
        }
    }
    
    // 障害物データを設定
    TMXLayer *collisionLayer = this->getLayer(LAYER_NAME_COLLISION);
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
    
    // オブジェクトを設定
    TMXObjectGroup *objectGroup = this->getObjectGroup(LAYER_NAME_OBJECT);
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
            mapManager->addObjectAt(gridX, gridY, MapState::MOVE);
        }
    }
    
    
    
    mapManager->debugCheckData();
    

    
    
/*
    // キャラクターノードを追加
    auto objects = this->getObjectGroups();
    if (!objects.empty())
    {
        for (auto object : objects)
        {
            ValueMap objectInfo = object->getProperties();
            
            
            
            if (object->get)
            // 表示位置(マップのタイルの中心にくるように)
            auto tileSize = tiledMap->getTileSize();
            
            // 取れる位置は左下起点なので調整
            auto x = objectInfo.at("x").asFloat() + tileSize.width * 0.5;
            auto y = objectInfo.at("y").asFloat() + tileSize.height * 0.5;
        }
        
    }
 */
    
    
    
    
    return true;
}


void RpgTiledMap::updatePos(CharacterBaseNode *characterNode)
{
    float characterX = characterNode->getPixelPos().x;
    float characterY = characterNode->getPixelPos().y;
    
    float newPosX = 0.0f;
    float newPosY = 0.0f;
    
    float mapWidth  = this->getContentSize().width;
    float mapHeight = this->getContentSize().height;
    
    // 横のスクロールが必要な場合
    if (mapWidth > SCREEN_WIDTH)
    {
        if (characterX < SCREEN_WIDTH / 2.0f)
        {
            newPosX = 0.0f;
        }
        else if (characterX > mapWidth - SCREEN_WIDTH / 2.0f)
        {
            newPosX = SCREEN_WIDTH - mapWidth;
        }
        else
        {
            newPosX = - characterX + SCREEN_WIDTH / 2.0f;
        }
    }
    
    // 縦のスクロールが必要な場合
    if (mapHeight > SCREEN_HEIGHT)
    {
        if ( (mapHeight - characterY) < SCREEN_HEIGHT / 2.0f)
        {
            newPosY = SCREEN_HEIGHT - mapHeight;
        }
        else if ( (mapHeight - characterY) > mapHeight - SCREEN_HEIGHT / 2.0f)
        {
            newPosY = 0.0f;
        }
        else
        {
            newPosY =  - characterY + SCREEN_HEIGHT / 2.0f;
        }
    }
    
    
    this->setPosition(Vec2(newPosX, newPosY));
    log("(%f, %f) -> (%f, %f)", characterX, characterY, newPosX, newPosY);
}


void RpgTiledMap::addCharacter(CharacterBaseNode *characterNode)
{
    
    characterNode->setGridPos(Vec2(6, 99));
//    characterNode->setGridPos(Vec2(15, 45));
    this->addChild(characterNode);
}