//
//  CharacterBaseNode.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/10/05.
//
//

#include "CharacterBaseNode.h"

#pragma mark - コンストラクタ／デストラクタ
CharacterBaseNode::CharacterBaseNode()
:characterInfo(nullptr)
{
    moveAnimationMap.clear();
}

CharacterBaseNode::~CharacterBaseNode() {
}

#pragma mark - 初期化
CharacterBaseNode *CharacterBaseNode::create(CharacterInfo *characterInfo)
{
    CharacterBaseNode *ret = new CharacterBaseNode();
    if (ret && ret->init(characterInfo)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CharacterBaseNode::init(CharacterInfo *characterInfo)
{
    this->characterInfo = characterInfo;
#if 0
    auto initSpriteFrame = this->getSpriteFrame(characterInfo->getDirection(), 0);
    if (!Sprite::initWithSpriteFrame(initSpriteFrame))
    {
        return false;
    }
#else
    if (!Sprite::init())
        return false;
#endif
    
    
    // 方向とアニメーションのセットを作成
    std::vector<CharacterDirection> directionVec = {CharacterDirection::UP, CharacterDirection::LEFT, CharacterDirection::RIGHT, CharacterDirection::DOWN};
    for (auto direction : directionVec)
    {
        moveAnimationMap[direction] = this->createMoveAnimation(direction);
    }
    
    // アニメーション更新
    this->updateAnimation();
    
    return true;
}


#pragma mark - メインループ
void CharacterBaseNode::updatePos()
{
    // 入力情報を更新
    characterInfo->updateInput();
    
    // アニメーションを更新
    this->updateAnimation();
    
    // 位置を更新
    float mapHeight = MapManager::getInstance()->getMapSize().height;
//    float mapHeight = GRID_MAX_Y * TILE_SIZE;
    auto pos = Util::Convert::gridToPixel(characterInfo->getGridPos(), mapHeight);
    this->setPosition(pos);
}

#pragma mark - setter
void CharacterBaseNode::setGridPos(Vec2 pos)
{
    this->characterInfo->setGridPos(pos);
}

#pragma mark - getter
Vec2 CharacterBaseNode::getGridPos()
{
    return this->characterInfo->getGridPos();
}

Vec2 CharacterBaseNode::getPixelPos()
{
    return this->getPosition();
}


#pragma mark - アニメーション
// 画像の取得
SpriteFrame *CharacterBaseNode::getSpriteFrame(CharacterDirection direction, int num)
{
    auto index    = characterInfo->getImageIndex();
    auto fileName = characterInfo->getFileName();
    auto size     = characterInfo->getCharacterSize();
    
    Rect rect = Rect(size * num, size * index, size, size);
    
    return SpriteFrame::create(fileName, rect);
}


// アニメーションの作成
Animation *CharacterBaseNode::createMoveAnimation(CharacterDirection direction)
{
    // SpriteFrameの作成
    Vector<SpriteFrame *> spriteFrameVec;
    for (int i = 0; i < CHARACTER_ANIM_NUM; i++)
    {
        spriteFrameVec.pushBack(this->getSpriteFrame(direction, i));
    }
    
    // Animationの作成
    Animation *animation = Animation::createWithSpriteFrames(spriteFrameVec);
    animation->setDelayPerUnit(0.3);
    animation->setLoops(-1);

    return animation;
}

void CharacterBaseNode::updateAnimation()
{
    auto direction = characterInfo->getDirection();
    auto animation = createMoveAnimation(direction);  // moveAnimationMap[direction];
    this->stopAllActions();
    this->runAction(Animate::create(animation));
}

