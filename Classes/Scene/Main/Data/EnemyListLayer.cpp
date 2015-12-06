//
//  EnemyListLayer.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/18.
//
//

#include "EnemyListLayer.hpp"
#include "network/HttpClient.h"
#include "HttpUtil.h"
#include "spine/Json.h"

#define ENEMY_ITEM_NODE_HEIGHT (160.0f)

using namespace cocos2d::network;


EnemyListLayer::EnemyListLayer()
{
}


EnemyListLayer::~EnemyListLayer() {
}

#pragma mark - 初期化
EnemyListLayer *EnemyListLayer::create(std::string csbName)
{
    EnemyListLayer *ret = new EnemyListLayer();
    if (ret->init(csbName)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}


bool EnemyListLayer::init(std::string csbName)
{
    if (!CsbBaseLayer::init(csbName))
        return false;
    
    // HTTP通信
    auto request = new HttpRequest();
    request->setUrl(ENEMY_LIST_API);
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
        if (response->isSucceed()) {
            std::vector<char>* responseData = response->getResponseData();
            std::string result(responseData->begin(), responseData->end());
            this->httpResponseCallBack(result);
        } else {
            this->httpResponseCallBack("");
        }
    });
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
    client->send(request);
    
    
//    Util::Http::getRequest("https://s3-ap-northeast-1.amazonaws.com/kyarochon/TsukubonQuest/enemies/pipo-enemy001.png");
//    Util::Http::getRequest("https://qiita-image-store.s3.amazonaws.com/0/7063/2903f4b7-a428-2105-574e-f6f6b0e041db.jpeg");

    return true;
}


void EnemyListLayer::httpResponseCallBack(std::string result) {
    log("result:%s", result.c_str());
    
    // キャラクターデータをパース
    characterDataList.clear();
    Json *json = Json_create(result.c_str());
    Json *item = json->child;
    while (item) {
        int characterId  = std::atoi(Json_getString(item, "character_id", "-1"));
        std::string name = Json_getString(item, "name", "");
        std::string attributeId = Json_getString(item, "attribute_id", "");
        std::string tribeId = Json_getString(item, "tribe_id", "");
        std::string imageName = Json_getString(item, "image_name", "");
        int hp = std::atoi(Json_getString(item, "hp", "0"));
        int attack = std::atoi(Json_getString(item, "attack", "0"));
        int defense = std::atoi(Json_getString(item, "defense", "0"));
        int speed = std::atoi(Json_getString(item, "speed", "0"));
        int exp = std::atoi(Json_getString(item, "exp", "0"));
        int gold = std::atoi(Json_getString(item, "gold", "0"));
        
        auto characterData = new CharacterData(characterId, name, attributeId, tribeId, imageName, hp, attack, defense, speed, exp, gold);
        characterDataList.push_back(characterData);
        
        item = item->next;
    }

    // キャラクターデータに沿ってNodeを追加
    auto panel = _mainLayer->getChildByName<ui::Layout *>("panel");
    auto scrollView = panel->getChildByName<ui::ScrollView *>("scrollView");
    float scrollViewHeight = characterDataList.size() * ENEMY_ITEM_NODE_HEIGHT;
    float scrollViewWidth  = scrollView->getContentSize().width;
    scrollView->setInnerContainerSize(Size(scrollView->getContentSize().width, scrollViewHeight));
    for (int i = 0; i < characterDataList.size(); i++) {
        auto characterData = characterDataList.at(i);
        auto enemyItemNode = EnemyItemNode::create("EnemyItemNode.csb");
        enemyItemNode->setCharacterData(characterData);
        enemyItemNode->setPosition(Vec2(scrollViewWidth / 2.0f, scrollViewHeight -  (i + 0.5f) * ENEMY_ITEM_NODE_HEIGHT));
        scrollView->addChild(enemyItemNode);
    }
    
    
    
    
    
    
}

