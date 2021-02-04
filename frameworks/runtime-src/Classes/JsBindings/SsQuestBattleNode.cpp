//
//  SsQuestBattleNode.cpp
//  magic
//
//  Created by 太田敦士 on 2018/03/16.
//

#include "SsQuestBattleNode.hpp"
#include "../SsQuestBattleNode.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

JSClass  *jsb_SsQuestBattleNode_class;
JSObject *jsb_SsQuestBattleNode_prototype;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

bool js_SsQuestBattleNode_setInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsQuestBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsQuestBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsQuestBattleNode_setInfo : Invalid Native Object");
    do {
        if (argc == 4) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setInfo : Error processing arguments");
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setInfo : Error processing arguments");
            std::string arg2;
            ok &= jsval_to_std_string(cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setInfo : Error processing arguments");
            std::string arg3;
            ok &= jsval_to_std_string(cx, args.get(3), &arg3);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setInfo : Error processing arguments");
            cobj->setInfo(arg0, arg1, arg2, arg3);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsQuestBattleNode_setInfo : wrong number of arguments");
    return false;
}

bool js_SsQuestBattleNode_setBattleStepInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsQuestBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsQuestBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Invalid Native Object");
    do {
        if (argc == 5) {
            int32_t arg0;
            ok &= jsval_to_int32( cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg1;
            ok &= jsval_to_int32( cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg2;
            ok &= jsval_to_int32( cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg3;
            ok &= jsval_to_int32( cx, args.get(3), &arg3);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg4;
            ok &= jsval_to_int32( cx, args.get(4), &arg4);
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setBattleStepInfo : Error processing arguments");
            cobj->setBattleStepInfo(arg0, arg1, arg2, arg3, arg4);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsQuestBattleNode_setBattleStepInfo : wrong number of arguments");
    return false;
}

bool js_SsQuestBattleNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = SsQuestBattleNode::create();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<SsQuestBattleNode>(cx, (SsQuestBattleNode*)ret));
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_SsQuestBattleNode_create : wrong number of arguments");
    return false;
}

bool js_SsQuestBattleNode_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    SsQuestBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsQuestBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsQuestBattleNode_play : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->play();
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsQuestBattleNode_play : wrong number of arguments");
    return false;
}

bool js_SsQuestBattleNode_setPlayEndCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    SsQuestBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsQuestBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsQuestBattleNode_setPlayEndCallback : Invalid Native Object");
    do {
        if (argc == 1) {
            std::shared_ptr<JSFunctionWrapper> func;
            
            // 引数1
            if (JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION) {
                JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
                JS::RootedValue fval(cx, args.get(0));
                func = std::shared_ptr<JSFunctionWrapper>(new JSFunctionWrapper(cx, jstarget, fval));
            } else {
                ok = false;
            }
            JSB_PRECONDITION2(ok, cx, false, "js_SsQuestBattleNode_setPlayEndCallback : Error processing arguments");
            cobj->setPlayEndCallback([=](ss::Player* player) {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                JS::RootedValue rval(cx);
                bool succeed = func->invoke(0, nullptr, &rval);
                if (!succeed && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            });
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsQuestBattleNode_setPlayEndCallback : wrong number of arguments");
    return false;
}

void js_register_SsQuestBattleNode(JSContext *cx, JS::HandleObject global) {
    jsb_SsQuestBattleNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsQuestBattleNode_class->name = "SsQuestBattleNode";
    jsb_SsQuestBattleNode_class->addProperty = JS_PropertyStub;
    jsb_SsQuestBattleNode_class->delProperty = JS_DeletePropertyStub;
    jsb_SsQuestBattleNode_class->getProperty = JS_PropertyStub;
    jsb_SsQuestBattleNode_class->setProperty = JS_StrictPropertyStub;
    jsb_SsQuestBattleNode_class->enumerate = JS_EnumerateStub;
    jsb_SsQuestBattleNode_class->resolve = JS_ResolveStub;
    jsb_SsQuestBattleNode_class->convert = JS_ConvertStub;
    // jsb_SsQuestBattleNode_class->finalize = js_SsQuestBattleNode_finalize;
    jsb_SsQuestBattleNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("setInfo", js_SsQuestBattleNode_setInfo, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setBattleStepInfo", js_SsQuestBattleNode_setBattleStepInfo, 5, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_SsQuestBattleNode_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlayEndCallback", js_SsQuestBattleNode_setPlayEndCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_SsQuestBattleNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_SsQuestBattleNode_prototype = JS_InitClass(
                                              cx, global,
                                              parent_proto,
                                              jsb_SsQuestBattleNode_class,
                                              empty_constructor, 0, // constructor
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsQuestBattleNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsQuestBattleNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<SsQuestBattleNode>(cx, jsb_SsQuestBattleNode_class, proto, JS::NullPtr());

}

void register_all_ss_quest_battle_node(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);
    js_register_SsQuestBattleNode(cx, ns);
}
