//
//  SSPlayer.cpp
//  magic
//
//  Created by 太田敦士 on 2018/03/02.
//

#include "SsPlayer.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "scripting/js-bindings/manual/js_manual_conversions.h"

JSClass  *jsb_SsPlayerControl_class;
JSObject *jsb_SsPlayerControl_prototype;
JSClass  *jsb_SsPlayer_class;
JSObject *jsb_SsPlayer_prototype;
JSClass  *jsb_SsCustomSprite_class;
JSObject *jsb_SsCustomSprite_prototype;
JSClass  *jsb_SsResourceManager_class;
JSObject *jsb_SsResourceManager_prototype;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

/*
 * SSPlayerControl
 */
bool js_SsPlayerControl_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = ss::SSPlayerControl::create();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::SSPlayerControl>(cx, (ss::SSPlayerControl*)ret));
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_SsPlayerControl_create : wrong number of arguments");
    return false;
}

bool js_SsPlayerControl_getSSPInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    ss::SSPlayerControl* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::SSPlayerControl *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayerControl_getSSPInstance : Invalid Native Object");
    do {
        if (argc == 0) {
            ss::Player* ret = cobj->getSSPInstance();
            JS::RootedValue jsret(cx);
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::Player>(cx, (ss::Player*)ret));
            } else {
                jsret = JSVAL_NULL;
            };
            args.rval().set(jsret);
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayerControl_getSSPInstance : wrong number of arguments");
    return false;
}

bool js_SsPlayerControl_renderingBlendFuncEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    ss::SSPlayerControl* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::SSPlayerControl *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayerControl_renderingBlendFuncEnable : Invalid Native Object");
    do {
        if (argc == 1) {
            bool arg0 = JS::ToBoolean(args.get(0));
            cobj->renderingBlendFuncEnable(arg0);
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayerControl_renderingBlendFuncEnable : wrong number of arguments");
    return false;
}

void js_register_SsPlayerControl(JSContext *cx, JS::HandleObject global) {
    jsb_SsPlayerControl_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsPlayerControl_class->name = "SsPlayerControl";
    jsb_SsPlayerControl_class->addProperty = JS_PropertyStub;
    jsb_SsPlayerControl_class->delProperty = JS_DeletePropertyStub;
    jsb_SsPlayerControl_class->getProperty = JS_PropertyStub;
    jsb_SsPlayerControl_class->setProperty = JS_StrictPropertyStub;
    jsb_SsPlayerControl_class->enumerate = JS_EnumerateStub;
    jsb_SsPlayerControl_class->resolve = JS_ResolveStub;
    jsb_SsPlayerControl_class->convert = JS_ConvertStub;
    // jsb_SsResourceManager_class->finalize = js_SsAvatarNode_finalize;
    jsb_SsPlayerControl_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("getSSPInstance", js_SsPlayerControl_getSSPInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("renderingBlendFuncEnable", js_SsPlayerControl_renderingBlendFuncEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_SsPlayerControl_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::RootedObject parent_proto(cx, jsb_cocos2d_Sprite_prototype);
    jsb_SsPlayerControl_prototype = JS_InitClass(
                                                   cx, global,
                                                   parent_proto,
                                                   jsb_SsPlayerControl_class,
                                                   empty_constructor, 0, // constructor
                                                   properties,
                                                   funcs,
                                                   NULL, // no static properties
                                                   st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsPlayerControl_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsPlayerControl"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ss::SSPlayerControl>(cx, jsb_SsPlayerControl_class, proto, JS::NullPtr());
}

/*
 * SSPlayer
 */
bool js_SsPlayer_setData(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_setData : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setData : Error processing arguments");
            cobj->setData(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_setData : wrong number of arguments");
    return false;
}

bool js_SsPlayer_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_play : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_play : Error processing arguments");
            cobj->play(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_play : wrong number of arguments");
    return false;
}

bool js_SsPlayer_setLoop(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_setLoop : Invalid Native Object");
    do {
        if (argc == 1) {
            int32_t arg0;
            ok &= jsval_to_int32( cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setLoop : Error processing arguments");
            cobj->setLoop(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_setLoop : wrong number of arguments");
    return false;
}

bool js_SsPlayer_setPlayEndCallback(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_setPlayEndCallback : Invalid Native Object");
    do {
        if (argc == 1) {
            std::function<void (ss::Player* player)> arg0;
            do {
                if(JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION)
                {
                    JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                    std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, args.get(0), args.thisv()));
                    auto lambda = [=](ss::Player* player) -> void {
                        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                        JS::RootedValue rval(cx);
                        jsval obj = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::Player>(cx, (ss::Player*)player));
                        bool succeed = func->invoke(1, &obj, &rval);
                        if (!succeed && JS_IsExceptionPending(cx)) {
                            JS_ReportPendingException(cx);
                        }
                    };
                    arg0 = lambda;
                }
                else
                {
                    arg0 = nullptr;
                }
            } while(0)
                ;
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setPlayEndCallback : Error processing arguments");
            cobj->setPlayEndCallback(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_setPlayEndCallback : wrong number of arguments");
    return false;
}

bool js_SsPlayer_indexOfPart(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_indexOfPart : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_indexOfPart : Error processing arguments");
            int index = cobj->indexOfPart(arg0.c_str());
            args.rval().set(INT_TO_JSVAL(index));
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_indexOfPart : wrong number of arguments");
    return false;
}

bool js_SsPlayer_setPartCell(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_setPartCell : Invalid Native Object");
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setPartCell : Error processing arguments");
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setPartCell : Error processing arguments");
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_setPartCell : Error processing arguments");
            cobj->setPartCell(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_setPartCell : wrong number of arguments");
    return false;
}

bool js_SsPlayer_getSpriteData(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::Player* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::Player *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsPlayer_getSpriteData : Invalid Native Object");
    do {
        if (argc == 1) {
            int32_t arg0;
            ok &= jsval_to_int32( cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsPlayer_getSpriteData : Error processing arguments");
            auto ret = cobj->getSpriteData(arg0);
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::CustomSprite>(cx, (ss::CustomSprite*)ret));
            }
            args.rval().set(jsret);
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsPlayer_getSpriteData : wrong number of arguments");
    return false;
}

void js_register_SsPlayer(JSContext *cx, JS::HandleObject global) {
    jsb_SsPlayer_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsPlayer_class->name = "SsPlayer";
    jsb_SsPlayer_class->addProperty = JS_PropertyStub;
    jsb_SsPlayer_class->delProperty = JS_DeletePropertyStub;
    jsb_SsPlayer_class->getProperty = JS_PropertyStub;
    jsb_SsPlayer_class->setProperty = JS_StrictPropertyStub;
    jsb_SsPlayer_class->enumerate = JS_EnumerateStub;
    jsb_SsPlayer_class->resolve = JS_ResolveStub;
    jsb_SsPlayer_class->convert = JS_ConvertStub;
    // jsb_SsResourceManager_class->finalize = js_SsAvatarNode_finalize;
    jsb_SsPlayer_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("setData", js_SsPlayer_setData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_SsPlayer_play, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setLoop", js_SsPlayer_setLoop, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("indexOfPart", js_SsPlayer_indexOfPart, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPartCell", js_SsPlayer_setPartCell, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSpriteData", js_SsPlayer_getSpriteData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlayEndCallback", js_SsPlayer_setPlayEndCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };
    jsb_SsPlayer_prototype = JS_InitClass(
                                                 cx, global,
                                                 JS::NullPtr(),
                                                 jsb_SsPlayer_class,
                                                 empty_constructor, 0, // constructor
                                                 properties,
                                                 funcs,
                                                 NULL, // no static properties
                                                 st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsPlayer_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsPlayer"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ss::Player>(cx, jsb_SsPlayer_class, proto, JS::NullPtr());
}

/*
 * SsCustomSprite
 */

bool js_SsCustomSprite_getSSPlayer(JSContext *cx, uint32_t argc, jsval *vp)
{
    ss::CustomSprite* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::CustomSprite *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsCustomSprite_getSSPlayer : Invalid Native Object");
    do {
        if (argc == 0) {
            auto ret = cobj->getSSPlayer();
            jsval jsret = JSVAL_NULL;
            if (ret) {
                jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::Player>(cx, (ss::Player*)ret));
            }
            args.rval().set(jsret);
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsCustomSprite_getSSPlayer : wrong number of arguments");
    return false;
}

void js_register_SsCustomSprite(JSContext *cx, JS::HandleObject global) {
    jsb_SsCustomSprite_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsCustomSprite_class->name = "SsCustomSprite";
    jsb_SsCustomSprite_class->addProperty = JS_PropertyStub;
    jsb_SsCustomSprite_class->delProperty = JS_DeletePropertyStub;
    jsb_SsCustomSprite_class->getProperty = JS_PropertyStub;
    jsb_SsCustomSprite_class->setProperty = JS_StrictPropertyStub;
    jsb_SsCustomSprite_class->enumerate = JS_EnumerateStub;
    jsb_SsCustomSprite_class->resolve = JS_ResolveStub;
    jsb_SsCustomSprite_class->convert = JS_ConvertStub;
    // jsb_SsResourceManager_class->finalize = js_SsAvatarNode_finalize;
    jsb_SsCustomSprite_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("getSSPlayer", js_SsCustomSprite_getSSPlayer, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };
    jsb_SsCustomSprite_prototype = JS_InitClass(
                                          cx, global,
                                          JS::NullPtr(),
                                          jsb_SsCustomSprite_class,
                                          empty_constructor, 0, // constructor
                                          properties,
                                          funcs,
                                          NULL, // no static properties
                                          st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsCustomSprite_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsCustomSprite"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ss::CustomSprite>(cx, jsb_SsCustomSprite_class, proto, JS::NullPtr());
}

/*
 * SsResourceManager
 */
bool js_SsResourceManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = ss::ResourceManager::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<ss::ResourceManager>(cx, (ss::ResourceManager*)ret));
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_SsResourceManager_getInstance : wrong number of arguments");
    return false;
}

bool js_SsResourceManager_addData(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::ResourceManager* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::ResourceManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsResourceManager_addData : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsResourceManager_addData : Error processing arguments");
            cobj->addData(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsResourceManager_addData : wrong number of arguments");
    return false;
}

bool js_SsResourceManager_removeData(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::ResourceManager* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::ResourceManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsResourceManager_removeData : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsResourceManager_removeData : Error processing arguments");
            cobj->removeData(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsResourceManager_removeData : wrong number of arguments");
    return false;
}

bool js_SsResourceManager_changeTexture(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    ss::ResourceManager* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (ss::ResourceManager *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsResourceManager_changeTexture : Invalid Native Object");
    do {
        if (argc == 3) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsResourceManager_changeTexture : Error processing arguments");
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsResourceManager_changeTexture : Error processing arguments");
            long arg2 = 0;
            ok &= jsval_to_long(cx, args.get(2), (long *)&arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsResourceManager_changeTexture : Error processing arguments");

            cobj->changeTexture((char*)arg0.c_str(), (char*)arg1.c_str(), arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsResourceManager_changeTexture : wrong number of arguments");
    return false;
}

void js_register_SsResourceManager(JSContext *cx, JS::HandleObject global) {
    jsb_SsResourceManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsResourceManager_class->name = "SsResourceManager";
    jsb_SsResourceManager_class->addProperty = JS_PropertyStub;
    jsb_SsResourceManager_class->delProperty = JS_DeletePropertyStub;
    jsb_SsResourceManager_class->getProperty = JS_PropertyStub;
    jsb_SsResourceManager_class->setProperty = JS_StrictPropertyStub;
    jsb_SsResourceManager_class->enumerate = JS_EnumerateStub;
    jsb_SsResourceManager_class->resolve = JS_ResolveStub;
    jsb_SsResourceManager_class->convert = JS_ConvertStub;
    // jsb_SsResourceManager_class->finalize = js_SsAvatarNode_finalize;
    jsb_SsResourceManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("addData", js_SsResourceManager_addData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("removeData", js_SsResourceManager_removeData, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("changeTexture", js_SsResourceManager_changeTexture, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_SsResourceManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    jsb_SsResourceManager_prototype = JS_InitClass(
                                              cx, global,
                                              JS::NullPtr(),
                                              jsb_SsResourceManager_class,
                                              empty_constructor, 0, // constructor
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsResourceManager_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsResourceManager"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<ss::ResourceManager>(cx, jsb_SsResourceManager_class, proto, JS::NullPtr());
}

bool JSB_magic_ssTextureLoad(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "JSB_magic_ssTextureLoad : Error processing arguments");
            long ret = ss::SSTextureLoad(arg0.c_str(), ss::SsTexWrapMode::clamp, ss::SsTexFilterMode::linear, "");
            args.rval().set(long_to_jsval(cx, ret));
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "JSB_magic_ssTextureLoad : wrong number of arguments");
    return false;
}

bool JSB_magic_ssTextureRelease(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    do {
        if (argc == 1) {
            int arg0;
            ok &= jsval_to_int(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "JSB_magic_ssTextureRelease : Error processing arguments");
            ss::SSTextureRelese(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "JSB_magic_ssTextureRelease : wrong number of arguments");
    return false;
}

void register_all_ss_player(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);
    js_register_SsPlayerControl(cx, ns);
    js_register_SsPlayer(cx, ns);
    js_register_SsCustomSprite(cx, ns);
    js_register_SsResourceManager(cx, ns);
    JS_DefineFunction(cx, ns, "ssTextureLoad", JSB_magic_ssTextureLoad, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(cx, ns, "ssTextureRelease", JSB_magic_ssTextureRelease, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}
