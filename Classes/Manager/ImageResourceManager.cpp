//
//  ImageResourceManager.cpp
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/11/23.
//
//

#include "ImageResourceManager.hpp"

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
    // キャッシュに存在していれば読み込み完了イベントを送る
    auto fileUtils = FileUtils::getInstance();
    if (fileUtils->isFileExist(imageName)) {
        Util::Event::sendCustomEventWithData(eventType, imageName);
    }
    
    // 画像読み込み開始
    Util::Http::getImageRequest(imageName,
                                eventType,
                                CC_CALLBACK_3(ImageResourceManager::httpResponseCallBack, this)
                                );
}

void ImageResourceManager::httpResponseCallBack(HttpResponse *response, std::string imageName, std::string eventType) {
    // 通信失敗
    if (!response->isSucceed()) {
        return;
    }
    
    // 画像取得
    std::vector<char>* buffer = response->getResponseData();
    auto image = new Image();
    bool succeeded = image->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
    
    // 読み込みに成功
    if (succeeded) {
        // キャッシュに保存
        Director::getInstance()->getTextureCache()->addImage(image, imageName);
        
        // 指定イベントを送信
        Util::Event::sendCustomEventWithData(eventType, imageName);
    }
}



#pragma mark - 画像取得
Texture2D *ImageResourceManager::getImage(std::string imageName) {
    return Director::getInstance()->getTextureCache()->getTextureForKey(imageName);
}


#pragma mark - 画像キャッシュ削除
void ImageResourceManager::removeImage(std::string imageName) {
    Director::getInstance()->getTextureCache()->removeTextureForKey(imageName);
}


