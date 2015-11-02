//
//  CharacterInfo.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/05.
//
//

#include "CharacterInfo.h"

CharacterInfo::CharacterInfo(CharacterType characterType)
{
    this->characterType = characterType;
    this->gridPos       = Vec2(0, 0);
    this->direction     = CharacterDirection::LEFT;
    this->fileName      = "pipo-charachip019.png";
    this->characterSize = CHARACTER_SIZE;
}

CharacterInfo::~CharacterInfo()
{
    
}

#pragma mark - 更新
void CharacterInfo::updateInput()
{
    int x = 0;
    int y = 0;
    
    // 方向を更新
    switch (InputManager::getInstance()->getInputType()) {
        case InputType::DOWN:
            this->direction = CharacterDirection::DOWN;
            y = 1;
            break;
        case InputType::LEFT:
            this->direction = CharacterDirection::LEFT;
            x = -1;
            break;
        case InputType::RIGHT:
            this->direction = CharacterDirection::RIGHT;
            x = 1;
            break;
        case InputType::UP:
            this->direction = CharacterDirection::UP;
            y = -1;
            break;
        // 決定／キャンセルは特に無し
        default:
            break;
    }
    log("CharacterInfo::updateInput() direction:%d", (int)this->direction);
    
    
    // 位置を更新
    int newPosX = MAX(MIN(this->getGridPos().x + x, GRID_MAX_X - 1), 0);
    int newPosY = MAX(MIN(this->getGridPos().y + y, GRID_MAX_Y - 1), 0);
    
    // 移動先に何もなければ
    if (MapManager::getInstance()->addObjectAt(newPosX, newPosY, MapState::CHARACTER))
    {
        // 現在の位置情報を削除
        MapManager::getInstance()->removeObjectAt(getGridPos().x, getGridPos().y);
        
        // 位置を更新
        this->gridPos = Vec2(newPosX, newPosY);
    }
}

#pragma mark - setter
void CharacterInfo::setGridPos(Vec2 pos)
{
    this->gridPos = pos;
}


#pragma mark - getter
// 方向
CharacterDirection CharacterInfo::getDirection()
{
    return this->direction;
}

// 位置
Vec2 CharacterInfo::getGridPos()
{
    return this->gridPos;
}

// 画像名
std::string CharacterInfo::getFileName()
{
    return this->fileName;
}

// 画像サイズ
int CharacterInfo::getCharacterSize()
{
    return this->characterSize;
}

// 画像の何列目にあるかどうか
int CharacterInfo::getImageIndex()
{
    int index = 0;
    switch (direction) {
        case CharacterDirection::DOWN:
            index = 0;
            break;
        case CharacterDirection::LEFT:
            index = 1;
            break;
        case CharacterDirection::RIGHT:
            index = 2;
            break;
        case CharacterDirection::UP:
            index = 3;
            break;
    }
    
    return index;
}