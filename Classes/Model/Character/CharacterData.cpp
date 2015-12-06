//
//  CharacterData.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/22.
//
//

#include "CharacterData.hpp"


CharacterData::CharacterData(int characterId, std::string name, std::string attributeId, std::string tribeId, std::string imageName, int hp, int attack, int defense, int speed, int exp, int gold) {
    this->characterId = characterId;
    this->name = name;
    this->attributeId = attributeId;
    this->tribeId = tribeId;
    this->imageName = imageName;
    this->hp = hp;
    this->attack = attack;
    this->defense = defense;
    this->speed = speed;
    this->exp = exp;
    this->gold = gold;
}

CharacterData::~CharacterData() {
    
}