//
// Created by 太田敦士 on 2017/09/05.
//

#include "MagicJni.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "platform/android/jni/JniHelper.h"
#include "cocos2d.h"

JNIEXPORT void JNICALL Java_jp_united_app_magic_JniBridge_onReceivePushNotification(JNIEnv *env, jclass, jstring jarg1, jstring jarg2)
{
    std::string string1 = cocos2d::JniHelper::jstring2string(jarg1);
    std::string string2 = cocos2d::JniHelper::jstring2string(jarg2);
    cocos2d::Director::getInstance()->getScheduler()->performFunctionInCocosThread([=](){
        auto cx = ScriptingCore::getInstance()->getGlobalContext();
        auto go = ScriptingCore::getInstance()->getGlobalObject();

        jsval valArr[2];
        valArr[0] = std_string_to_jsval(cx, string1);
        valArr[1] = std_string_to_jsval(cx, string2);
        JS::RootedValue rval(cx);
        JS::RootedValue globalVal(cx, OBJECT_TO_JSVAL(go));
        return ScriptingCore::getInstance()->executeFunctionWithOwner(globalVal, "onReceivePushNotification", JS::HandleValueArray::fromMarkedLocation(2, valArr), &rval);
    });
}
