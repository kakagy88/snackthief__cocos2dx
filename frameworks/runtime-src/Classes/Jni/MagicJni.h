//
// Created by 太田敦士 on 2017/09/05.
//

#ifndef PROJ_ANDROID_STUDIO_MAGICJNI_H
#define PROJ_ANDROID_STUDIO_MAGICJNI_H

#include "jsapi.h"
#include <jni.h>

extern "C" {
    JNIEXPORT void JNICALL Java_jp_united_app_magic_JniBridge_onReceivePushNotification(JNIEnv *, jclass, jstring, jstring);
}

#endif //PROJ_ANDROID_STUDIO_MAGICJNI_H
