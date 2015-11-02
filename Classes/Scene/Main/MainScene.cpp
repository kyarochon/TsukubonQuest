//
//  MainScene.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/02.
//
//

#include "MainScene.h"
#include "InputLayer.h"
#include "CharacterBaseNode.h"

#pragma mark - 初期化
MainScene::MainScene()
:characterNode(nullptr)
,rpgTiledMap(nullptr)
{
}

MainScene::~MainScene()
{
    CC_SAFE_RELEASE_NULL(characterNode);
    CC_SAFE_RELEASE_NULL(rpgTiledMap);
}


Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    auto size = Director::getInstance()->getWinSize();
    
    
    auto inputLayer = InputLayer::create("InputLayer.csb");
    this->addChild(inputLayer, MainZOrder::INPUT_LAYER);

#if 1
    rpgTiledMap = RpgTiledMap::create("college_map.tmx");
#else
    rpgTiledMap = RpgTiledMap::create("world_map.tmx");
#endif
    rpgTiledMap->setPosition(0, 0);
    this->addChild(rpgTiledMap, MainZOrder::MAIN_MAP);
    
    auto characterInfo = new CharacterInfo(CharacterType::MAN);
    characterNode = CharacterBaseNode::create(characterInfo);
    rpgTiledMap->addCharacter(characterNode);
    
    
    // 5秒ごとにデータを自動保存
    this->scheduleUpdate();
    
    return true;
}


#pragma mark - メインループ
void MainScene::update(float dt) {
    // 入力の更新があれば画像を更新
    auto inputManager = InputManager::getInstance();
    if (inputManager->hasChangedInputState() && inputManager->getInputPhase() == InputPhase::END)
    {
        // 位置更新
        characterNode->updatePos();
        
        // 位置更新
        rpgTiledMap->updatePos(characterNode);
    }
}
