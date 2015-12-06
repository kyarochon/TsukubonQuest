//
//  EventUtil.h
//  TsukubonQuest
//
//  Created by kiyotaka-saitou on 2015/12/07.
//
//

#ifndef EventUtil_h
#define EventUtil_h

#include "cocos2d.h"
#include "EventDefine.h"

USING_NS_CC;

namespace Util {
namespace Event {
    

    // 単純なイベント送信
    static void sendCustomEvent(std::string eventName) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            auto event = EventCustom(eventName);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        });
    }

    // データ付きイベント送信
    static void sendCustomEventWithData(std::string eventName, int data) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            auto event = EventCustom(eventName);
            auto value = Value(data);
            event.setUserData(&value);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        });
    }
    static void sendCustomEventWithData(std::string eventName, std::string data) {
        Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
            auto event = EventCustom(eventName);
            auto value = Value(data);
            event.setUserData(&value);
            Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
        });
    }
    
    
    
    // データの取得
    static bool getEventDataBool(EventCustom *event) {
        auto value = (Value *)event->getUserData();
        return value->asBool();
    }
    static int getEventDataInt(EventCustom *event) {
        auto value = (Value *)event->getUserData();
        return value->asInt();
    }
    static float getEventDataFloat(EventCustom *event) {
        auto value = (Value *)event->getUserData();
        return value->asFloat();
    }
    static float getEventDataDouble(EventCustom *event) {
        auto value = (Value *)event->getUserData();
        return value->asDouble();
    }
    static std::string getEventDataString(EventCustom *event) {
        auto value = (Value *)event->getUserData();
        return value->asString();
    }
    
    
    
}
}


#endif /* EventUtil_h */
