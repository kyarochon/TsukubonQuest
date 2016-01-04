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
#include "HttpUtil.h"

USING_NS_CC;


class ImageResourceManager {
    
private:
    ImageResourceManager();
    static ImageResourceManager* imageResourceManager;
    Map<std::string, Texture2D *> textureCache;
    
public:
    // 初期化
    static ImageResourceManager* getInstance();
    
    // 画像の読み込み／取得／削除
    void loadImage(std::string imageName, std::string eventType);
    Texture2D *getImage(std::string imageName);
    void removeImage(std::string imageName);
    
    
    // 読み込み完了時
    void httpResponseCallBack(HttpResponse *response, std::string imageName, std::string eventType);

};

#endif /* ImageResourceManager_hpp */
