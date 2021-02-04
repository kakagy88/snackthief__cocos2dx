//
//  SsAvatarNode.cpp
//  magic
//
//  Created by 太田敦士 on 2018/01/22.
//

#include "SsAvatarNode.hpp"
#include "../SsAvatarNode.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

JSClass  *jsb_SsAvatarNode_class;
JSObject *jsb_SsAvatarNode_prototype;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

bool js_SsAvatarNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = SsAvatarNode::create();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<SsAvatarNode>(cx, (SsAvatarNode*)ret));
        }
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_SsAvatarNode_create : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_setSsDirectoryPath(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_setSsDirectoryPath : Error processing arguments");
        SsAvatarNode::setSsDirectoryPath(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_SsAvatarNode_setSsDirectoryPath : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_setSsUrl(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_setSsUrl : Error processing arguments");
        SsAvatarNode::setSsUrl(arg0);
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_SsAvatarNode_setSsUrl : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_attachEquipment(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsAvatarNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsAvatarNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsAvatarNode_attachEquipment : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_attachEquipment : Error processing arguments");
            cobj->attachEquipment(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsAvatarNode_attachEquipment : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_detachEquipment(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsAvatarNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsAvatarNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsAvatarNode_detachEquipment : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_detachEquipment : Error processing arguments");
            cobj->detachEquipment(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsAvatarNode_detachEquipment : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_setPose(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsAvatarNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsAvatarNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsAvatarNode_setPose : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_setPose : Error processing arguments");
            cobj->setPose(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsAvatarNode_setPose : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_setExpression(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    SsAvatarNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsAvatarNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsAvatarNode_setExpression : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_SsAvatarNode_setExpression : Error processing arguments");
            cobj->setExpression(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsAvatarNode_setExpression : wrong number of arguments");
    return false;
}

bool js_SsAvatarNode_renderingBlendFuncEnable(JSContext *cx, uint32_t argc, jsval *vp)
{
    SsAvatarNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (SsAvatarNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_SsAvatarNode_renderingBlendFuncEnable : Invalid Native Object");
    do {
        if (argc == 1) {
            bool arg0 = JS::ToBoolean(args.get(0));
            cobj->renderingBlendFuncEnable(arg0);
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_SsAvatarNode_renderingBlendFuncEnable : wrong number of arguments");
    return false;
}

void js_register_SsAvatarNode(JSContext *cx, JS::HandleObject global) {
    jsb_SsAvatarNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_SsAvatarNode_class->name = "SsAvatarNode";
    jsb_SsAvatarNode_class->addProperty = JS_PropertyStub;
    jsb_SsAvatarNode_class->delProperty = JS_DeletePropertyStub;
    jsb_SsAvatarNode_class->getProperty = JS_PropertyStub;
    jsb_SsAvatarNode_class->setProperty = JS_StrictPropertyStub;
    jsb_SsAvatarNode_class->enumerate = JS_EnumerateStub;
    jsb_SsAvatarNode_class->resolve = JS_ResolveStub;
    jsb_SsAvatarNode_class->convert = JS_ConvertStub;
    // jsb_SsAvatarNode_class->finalize = js_SsAvatarNode_finalize;
    jsb_SsAvatarNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("attachEquipment", js_SsAvatarNode_attachEquipment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("detachEquipment", js_SsAvatarNode_detachEquipment, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPose", js_SsAvatarNode_setPose, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setExpression", js_SsAvatarNode_setExpression, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("renderingBlendFuncEnable", js_SsAvatarNode_renderingBlendFuncEnable, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_SsAvatarNode_create, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSsDirectoryPath", js_SsAvatarNode_setSsDirectoryPath, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSsUrl", js_SsAvatarNode_setSsUrl, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::RootedObject parent_proto(cx, jsb_cocos2d_Node_prototype);
    jsb_SsAvatarNode_prototype = JS_InitClass(
                                         cx, global,
                                         parent_proto,
                                         jsb_SsAvatarNode_class,
                                         empty_constructor, 0, // constructor
                                         properties,
                                         funcs,
                                         NULL, // no static properties
                                         st_funcs);
    
    JS::RootedObject proto(cx, jsb_SsAvatarNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "SsAvatarNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<SsAvatarNode>(cx, jsb_SsAvatarNode_class, proto, JS::NullPtr());
    
}

void register_all_ss_avatar_node(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);
    js_register_SsAvatarNode(cx, ns);
}
