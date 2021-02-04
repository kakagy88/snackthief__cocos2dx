//
//  NetworkImageLoader.h
//  magic
//
//  Created by 太田敦士 on 2017/11/17.
//

#ifndef _JS_BINDINGS_NETWORK_IMAGE_LOADER_H_
#define _JS_BINDINGS_NETWORK_IMAGE_LOADER_H_

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_NetworkImageLoader_class;
extern JSObject *jsb_NetworkImageLoader_prototype;

void register_all_network_image_loader(JSContext *_cx, JS::HandleObject object);

#endif /* _JS_BINDINGS_NETWORK_IMAGE_LOADER_H_ */
