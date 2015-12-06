//
//  ImageResourceManager.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/23.
//
//

#include "ImageResourceManager.hpp"
#include "network/HttpClient.h"

using namespace cocos2d::network;

#pragma mark - 初期化
ImageResourceManager* ImageResourceManager::imageResourceManager = nullptr;
ImageResourceManager::ImageResourceManager()
{
}

ImageResourceManager *ImageResourceManager::getInstance()
{
    if(imageResourceManager == nullptr)
    {
        imageResourceManager = new ImageResourceManager();
    }
    return imageResourceManager;
}


#pragma mark - 画像読み込み
void ImageResourceManager::loadImage(std::string imageName, std::string eventType) {
    auto fileUtils = FileUtils::getInstance();
    if (fileUtils->isFileExist(imageName)) {
        Util::Event::sendCustomEventWithData(eventType, imageName);
    }
    
    auto request = new HttpRequest();
    request->setUrl(imageName.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        if (response->isSucceed()) {
            std::vector<char>* buffer = response->getResponseData();
            auto image = new Image();
            image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
            
            Director::getInstance()->getTextureCache()->addImage(image, imageName);
//            auto* texture = new Texture2D();
//            texture->initWithImage(img);
            Util::Event::sendCustomEventWithData(eventType, imageName);
        }
    });
    
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
    client->send(request);
}

#pragma mark - 画像取得
Texture2D *ImageResourceManager::getImage(std::string imageName) {
    return Director::getInstance()->getTextureCache()->getTextureForKey(imageName);
}

