//
//  Lwf.h
//  magic
//
//  Created by 太田敦士 on 2017/11/08.
//

#ifndef _JS_BINDINGS_LWF_H_
#define _JS_BINDINGS_LWF_H_

#include <stdio.h>
#include "jsapi.h"
#include "jsfriendapi.h"

extern JSObject *jsb_cocos2d_Sprite_prototype;
extern JSClass  *jsb_LWF_class;
extern JSObject *jsb_LWF_prototype;
extern JSClass  *jsb_LWFNode_class;
extern JSObject *jsb_LWFNode_prototype;

void register_all_lwf(JSContext* cx, JS::HandleObject obj);

#endif /* _JS_BINDINGS_LWF_H_ */
