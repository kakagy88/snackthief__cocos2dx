//
//  Downloader.hpp
//  magic
//
//  Created by 太田敦士 on 2018/04/05.
//

#ifndef _JS_BINDINGS_DOWNLOADER_hpp
#define _JS_BINDINGS_DOWNLOADER_hpp

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_Downloader_class;
extern JSObject *jsb_Downloader_prototype;

void register_all_downloader(JSContext *cx, JS::HandleObject object);

#endif /* _JS_BINDINGS_DOWNLOADER_hpp */
