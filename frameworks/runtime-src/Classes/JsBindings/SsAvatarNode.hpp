//
//  SsAvatarNode.hpp
//  magic
//
//  Created by 太田敦士 on 2018/01/22.
//

#ifndef _JS_BINDINGS_SS_AVATAR_NODE_hpp
#define _JS_BINDINGS_SS_AVATAR_NODE_hpp

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSObject *jsb_cocos2d_Node_prototype;
extern JSClass  *jsb_SsAvatarNode_class;
extern JSObject *jsb_SsAvatarNode_prototype;

void register_all_ss_avatar_node(JSContext *cx, JS::HandleObject object);

#endif /* _JS_BINDINGS_SS_AVATAR_NODE_hpp */
