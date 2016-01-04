//
//  EnemyDataManger.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/12/10.
//
//

#include "EnemyDataManger.hpp"
#include "ImageResourceManager.hpp"
#include "network/HttpClient.h"
#include "EventUtil.h"
#include "spine/Json.h"


#pragma mark - 初期化
EnemyDataManger* EnemyDataManger::enemyDataManger = nullptr;
EnemyDataManger::EnemyDataManger()
:loadingState(LoadingState::Init)
{
}

EnemyDataManger *EnemyDataManger::getInstance()
{
    if(enemyDataManger == nullptr)
    {
        enemyDataManger = new EnemyDataManger();
        enemyDataManger->init();
    }
    return enemyDataManger;
}


void EnemyDataManger::init() {
    // 初期化
    loadingState = LoadingState::Init;
    
    // 通信開始
    this->load();
}

void EnemyDataManger::load() {
    // 既に読み込み終了してたら、終わってるよーイベント返す
    if (this->loadingState == LoadingState::Finished) {
        Util::Event::sendCustomEvent(EVENT_FINISH_LOADING_ENEMY_DATA);
        return;
    }
    
    // 読み込み開始
    this->loadingState = LoadingState::Loading;
    Util::Http::getRequest(ENEMY_LIST_API, CC_CALLBACK_1(EnemyDataManger::httpResponseCallBack, this));
}



void EnemyDataManger::httpResponseCallBack(HttpResponse* response) {
    // 通信失敗
    if (!response->isSucceed()) {
        this->loadingState = LoadingState::Failed;
        Util::Event::sendCustomEvent(EVENT_FINISH_LOADING_ENEMY_DATA);
        return;
    }

    std::vector<char>* responseData = response->getResponseData();
    std::string result(responseData->begin(), responseData->end());
    
    // 結果が空なら失敗
    if (result.empty()) {
        this->loadingState = LoadingState::Failed;
        Util::Event::sendCustomEvent(EVENT_FINISH_LOADING_ENEMY_DATA);
        return;
    }
    
    this->enemyDataList.clear();
    // キャラクターデータをパース
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
        enemyDataList.push_back(characterData);
        
        item = item->next;
    }
    
    // 読み込み完了状態にする
    this->loadingState = LoadingState::Finished;
    Util::Event::sendCustomEvent(EVENT_FINISH_LOADING_ENEMY_DATA);
}


// 再読み込み
void EnemyDataManger::reload() {
    // 読み込み状態初期化
    this->loadingState = LoadingState::Init;

    // 画像キャッシュ消す
    for (auto enemyData : this->enemyDataList) {
        ImageResourceManager::getInstance()->removeImage(enemyData->imageName);
    }
    
    // リストデータを削除して読み込み開始
    this->enemyDataList.clear();
    this->load();
}
