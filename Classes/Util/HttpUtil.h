//
//  HttpUtil.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/22.
//
//

#ifndef HttpUtil_h
#define HttpUtil_h

#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace cocos2d::network;

#include "NetworkDefine.h"
#include "EventUtil.h"

namespace Util {
namespace Http {
    static void getRequest(std::string url, std::function<void(std::string result)> callbackFunc)
    {
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
            if (response->isSucceed()) {
                std::vector<char>* responseData = response->getResponseData();
                std::string result(responseData->begin(), responseData->end());
                callbackFunc(result);
            } else {
                callbackFunc("");
            }
            
            
/*
            Size visibleSize = Director::getInstance()->getVisibleSize();
            Vec2 origin = Director::getInstance()->getVisibleOrigin();
            
            auto fileUtils = FileUtils::getInstance();
            std::string filename = fileUtils->getWritablePath() + "hoge.jpg";
            
            if (fileUtils->isFileExist(filename)) {
                
                auto sprite = Sprite::create(filename.c_str());
                sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
                this->addChild(sprite, 0);
                
            } else if (response->isSucceed()) {
                
                std::vector<char>* buffer = response->getResponseData();
                auto* img = new Image();
                img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
                img->saveToFile(filename.c_str());
                auto* texture = new Texture2D();
                texture->initWithImage(img);
                auto sprite = Sprite::createWithTexture(texture);
                sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
                this->addChild(sprite, 0);
                
            }
*/
        });
        
        auto client = HttpClient::getInstance();
        client->enableCookies(NULL);
        client->send(request);
        
    }
}   // end namespace Convert
}   // end namespace Util




#endif /* HttpUtil_h */
