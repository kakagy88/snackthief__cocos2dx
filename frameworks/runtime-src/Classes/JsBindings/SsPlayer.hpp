//
//  SSPlayer.hpp
//  magic
//
//  Created by 太田敦士 on 2018/03/02.
//

#ifndef _JS_BINDINGS_SS_PLAYER_hpp
#define _JS_BINDINGS_SS_PLAYER_hpp

#include <stdio.h>
#include "../SSPlayer/SS6Player.h"

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSObject *jsb_cocos2d_Sprite_prototype;
extern JSClass  *jsb_SsPlayerControl_class;
extern JSObject *jsb_SsPlayerControl_prototype;
extern JSClass  *jsb_SsPlayer_class;
extern JSObject *jsb_SsPlayer_prototype;
extern JSClass  *jsb_SsCustomSprite_class;
extern JSObject *jsb_SsCustomSprite_prototype;
extern JSClass  *jsb_SsResourceManager_class;
extern JSObject *jsb_SsResourceManager_prototype;

void register_all_ss_player(JSContext *cx, JS::HandleObject obj);

#endif /* _JS_BINDINGS_SS_PLAYER_hpp */
