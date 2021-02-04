//
//  SsRaidBattleNode.cpp
//  magic
//
//  Created by 太田敦士 on 2018/03/16.
//

#include "SsRaidBattleNode.hpp"
#include "../SsRaidBattleNode.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

JSClass  *jsb_SsRaidBattleNode_class;
JSObject *jsb_SsRaidBattleNode_prototype;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

bool js_SsRaidBattleNode_setInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsRaidBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsRaidBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsRaidBattleNode_setInfo : Invalid Native Object");
    do {
        if (argc == 11) {
            int32_t arg0;
            ok &= jsval_to_int32(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            int32_t arg1;
            ok &= jsval_to_int32(cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            int32_t arg2;
            ok &= jsval_to_int32(cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            bool arg3 = JS::ToBoolean(args.get(3));
            std::string arg4;
            ok &= jsval_to_std_string(cx, args.get(4), &arg4);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg5;
            ok &= jsval_to_std_string(cx, args.get(5), &arg5);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg6;
            ok &= jsval_to_std_string(cx, args.get(6), &arg6);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg7;
            ok &= jsval_to_std_string(cx, args.get(7), &arg7);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg8;
            ok &= jsval_to_std_string(cx, args.get(8), &arg8);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg9;
            ok &= jsval_to_std_string(cx, args.get(9), &arg9);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            std::string arg10;
            ok &= jsval_to_std_string(cx, args.get(10), &arg10);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setInfo : Error processing arguments");
            cobj->setInfo(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsRaidBattleNode_setInfo : wrong number of arguments");
    return false;
}

bool js_SsRaidBattleNode_setStepInfo(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsRaidBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsRaidBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsRaidBattleNode_setBattleStepInfo : Invalid Native Object");
    do {
        if (argc == 3) {
            int32_t arg0;
            ok &= jsval_to_int32( cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg1;
            ok &= jsval_to_int32( cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setBattleStepInfo : Error processing arguments");
            int32_t arg2;
            ok &= jsval_to_int32( cx, args.get(2), &arg2);
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setBattleStepInfo : Error processing arguments");
            cobj->setStepInfo(arg0, arg1, arg2);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsRaidBattleNode_setBattleStepInfo : wrong number of arguments");
    return false;
}

bool js_SsRaidBattleNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = SsRaidBattleNode::create();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<SsRaidBattleNode>(cx, (SsRaidBattleNode*)ret));
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_SsRaidBattleNode_create : wrong number of arguments");
    return false;
}

bool js_SsRaidBattleNode_play(JSContext *cx, uint32_t argc, jsval *vp)
{
    SsRaidBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsRaidBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsRaidBattleNode_play : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->play();
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsRaidBattleNode_play : wrong number of arguments");
    return false;
}

bool js_SsRaidBattleNode_setPlayEndCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    SsRaidBattleNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsRaidBattleNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsRaidBattleNode_setPlayEndCallback : Invalid Native Object");
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
            JSB_PRECONDITION2(ok, cx, false, "js_SsRaidBattleNode_setPlayEndCallback : Error processing arguments");
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
    
    JS_ReportError(cx, "js_SsRaidBattleNode_setPlayEndCallback : wrong number of arguments");
    return false;
}

void js_register_SsRaidBattleNode(JSContext *cx, JS::HandleObject global) {
    jsb_SsRaidBattleNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsRaidBattleNode_class->name = "SsRaidBattleNode";
    jsb_SsRaidBattleNode_class->addProperty = JS_PropertyStub;
    jsb_SsRaidBattleNode_class->delProperty = JS_DeletePropertyStub;
    jsb_SsRaidBattleNode_class->getProperty = JS_PropertyStub;
    jsb_SsRaidBattleNode_class->setProperty = JS_StrictPropertyStub;
    jsb_SsRaidBattleNode_class->enumerate = JS_EnumerateStub;
    jsb_SsRaidBattleNode_class->resolve = JS_ResolveStub;
    jsb_SsRaidBattleNode_class->convert = JS_ConvertStub;
    // jsb_SsRaidBattleNode_class->finalize = js_SsRaidBattleNode_finalize;
    jsb_SsRaidBattleNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("setInfo", js_SsRaidBattleNode_setInfo, 10, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setStepInfo", js_SsRaidBattleNode_setStepInfo, 3, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("play", js_SsRaidBattleNode_play, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPlayEndCallback", js_SsRaidBattleNode_setPlayEndCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_SsRaidBattleNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_SsRaidBattleNode_prototype = JS_InitClass(
                                              cx, global,
                                              parent_proto,
                                              jsb_SsRaidBattleNode_class,
                                              empty_constructor, 0, // constructor
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsRaidBattleNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsRaidBattleNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<SsRaidBattleNode>(cx, jsb_SsRaidBattleNode_class, proto, JS::NullPtr());

}

void register_all_ss_raid_battle_node(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);
    js_register_SsRaidBattleNode(cx, ns);
}
