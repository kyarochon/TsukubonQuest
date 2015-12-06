//
//  CharacterData.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/22.
//
//

#ifndef CharacterData_hpp
#define CharacterData_hpp


class CharacterData
{
public:
    CharacterData(int characterId, std::string name, std::string attributeId, std::string tribeId, std::string imageName, int hp, int attack, int defense, int speed, int exp, int gold);
    
protected:
    virtual ~CharacterData();

    
public:
    int characterId;
    std::string name;
    std::string attributeId;
    std::string tribeId;
    std::string imageName;
    int hp;
    int attack;
    int defense;
    int speed;
    int exp;
    int gold;
};

#endif /* CharacterData_hpp */
