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
    

    // ----- タップイベント -----
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event*event)->bool {
        return true;
    };
    listener->onTouchMoved = [this](Touch *touch, Event *event) {
    };
    listener->onTouchEnded = [this](Touch *touch, Event *event) {
        this->tapped(touch);
    };
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    dispatcher->setPriority(listener, -1);
    
    

    // ----- マップ初期化 -----
    auto mapManager = MapManager::getInstance();
    
    // 左上基準
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    this->setPosition(Vec2(0.0f, this->getContentSize().height));
    
    // マップサイズ設定
    auto size = this->getContentSize();
    auto tile = this->getTileSize();
    int gridMaxX = size.width / tile.width;
    int gridMaxY = size.height / tile.height;
    mapManager->initMap(gridMaxX, gridMaxY);
    
    // 障害物データ設定
    TMXLayer *collisionLayer = this->getLayer(LAYER_NAME_COLLISION);
    mapManager->setCollisionData(collisionLayer);
    
    // オブジェクトデータ設定
    TMXObjectGroup *objectGroup = this->getObjectGroup(LAYER_NAME_OBJECT);
    mapManager->setObjectData(objectGroup);

    // 設定データ確認
    mapManager->debugCheckData();
    
    return true;
}



//
void RpgTiledMap::tapped(Touch *touch)
{
    auto mapManager = MapManager::getInstance();
    
    auto pos = touch->getLocation();
    mapManager->tapped(pos);
    
    
    this->setPosition(mapManager->getScrollPos());
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