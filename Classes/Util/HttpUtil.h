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
#include "EventDefine.h"
#include "EventUtil.h"

namespace Util {
namespace Http {
    // 一般データの読み込み
    static void getRequest(std::string url, std::function<void(HttpResponse *response)> callbackFunc)
    {
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
            callbackFunc(response);
        });
        
        auto client = HttpClient::getInstance();
        client->enableCookies(NULL);
        client->send(request);
    }
    
    
    // 画像データの読み込み
    // getImageRequest(画像のURL, イベントタイプ, コールバック関数)
    // callbackFunc(レスポンスデータ, 画像のURL, イベントタイプ)
    static void getImageRequest(std::string url, std::string eventType, std::function<void(HttpResponse *response, std::string imageName, std::string eventType)> callbackFunc) {
        auto request = new HttpRequest();
        request->setUrl(url.c_str());
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback([=](HttpClient* client, HttpResponse* response){
            callbackFunc(response, url, eventType);
        });
        
        auto client = HttpClient::getInstance();
        client->enableCookies(NULL);
        client->send(request);
    }
    
}   // end namespace Convert
}   // end namespace Util




#endif /* HttpUtil_h */
