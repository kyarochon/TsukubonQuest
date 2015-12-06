//
//  ImageResourceManager.hpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/23.
//
//

#ifndef ImageResourceManager_hpp
#define ImageResourceManager_hpp

#include "cocos2d.h"
#include "EventUtil.h"

USING_NS_CC;


class ImageResourceManager {
    
private:
    ImageResourceManager();
    static ImageResourceManager* imageResourceManager;
    Map<std::string, Texture2D *> textureCache;
    
public:
    // 初期化
    static ImageResourceManager* getInstance();
    void loadImage(std::string imageName, std::string eventType);
    Texture2D *getImage(std::string imageName);
};

#endif /* ImageResourceManager_hpp */
