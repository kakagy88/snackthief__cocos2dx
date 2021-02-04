//
//  SsRaidTopNode.hpp
//  magic
//
//  Created by 太田敦士 on 2018/03/16.
//
#ifndef _JS_BINDINGS_SS_RAID_TOP_NODE_hpp
#define _JS_BINDINGS_SS_RAID_TOP_NODE_hpp

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSObject *jsb_cocos2d_Node_prototype;
extern JSClass  *jsb_SsRaidTopNode_class;
extern JSObject *jsb_SsRaidTopNode_prototype;

void register_all_ss_raid_top_node(JSContext *cx, JS::HandleObject object);

#endif /* _JS_BINDINGS_SS_RAID_TOP_NODE_hpp */
