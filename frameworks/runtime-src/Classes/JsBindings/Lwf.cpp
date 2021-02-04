//
//  Lwf.cpp
//  magic
//
//  Created by 太田敦士 on 2017/11/08.
//

#include "Lwf.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "lwf_cocos2dx.h"

USING_NS_CC;

/*
 * LWF
 */
JSClass  *jsb_LWF_class;
JSObject *jsb_LWF_prototype;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

bool js_LWF_FitForHeight(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    LWF::LWF* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (LWF::LWF *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_LWF_FitForHeight : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_LWF_FitForHeight : Error processing arguments");
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_LWF_FitForHeight : Error processing arguments");
            cobj->FitForHeight(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_LWF_FitForHeight : wrong number of arguments");
    return false;
}

bool js_LWF_FitForWidth(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    LWF::LWF* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (LWF::LWF *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_LWF_FitForHeight : Invalid Native Object");
    do {
        if (argc == 2) {
            double arg0 = 0;
            ok &= JS::ToNumber( cx, args.get(0), &arg0) && !std::isnan(arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_LWF_FitForHeight : Error processing arguments");
            double arg1 = 0;
            ok &= JS::ToNumber( cx, args.get(1), &arg1) && !std::isnan(arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_LWF_FitForHeight : Error processing arguments");
            cobj->FitForWidth(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_LWF_FitForHeight : wrong number of arguments");
    return false;
}

void js_register_LWF(JSContext *cx, JS::HandleObject global) {
    jsb_LWF_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LWF_class->name = "LWF";
    jsb_LWF_class->addProperty = JS_PropertyStub;
    jsb_LWF_class->delProperty = JS_DeletePropertyStub;
    jsb_LWF_class->getProperty = JS_PropertyStub;
    jsb_LWF_class->setProperty = JS_StrictPropertyStub;
    jsb_LWF_class->enumerate = JS_EnumerateStub;
    jsb_LWF_class->resolve = JS_ResolveStub;
    jsb_LWF_class->convert = JS_ConvertStub;
    jsb_LWF_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("fitForHeight", js_LWF_FitForHeight, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("fitForWidth", js_LWF_FitForWidth, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };
    jsb_LWF_prototype = JS_InitClass(
                                         cx, global,
                                         JS::NullPtr(),
                                         jsb_LWF_class,
                                         empty_constructor, 0, // constructor
                                         properties,
                                         funcs,
                                         NULL, // no static properties
                                         st_funcs);
    
    JS::RootedObject proto(cx, jsb_LWF_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "LWF"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<LWF::LWF>(cx, jsb_LWF_class, proto, JS::NullPtr());
}

/*
 * LWFNode
 */
JSClass  *jsb_LWFNode_class;
JSObject *jsb_LWFNode_prototype;


bool js_LWFNode_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    LWFNode* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    
    do {
        if (argc == 0) {
            cobj = new (std::nothrow) LWFNode();
            
            js_type_class_t *typeClass = js_get_type_from_native<LWFNode>(cobj);
            JS::RootedObject proto(cx, typeClass->proto.ref());
            JS::RootedObject parent(cx, typeClass->parentProto.ref());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            jsb_non_ref_init(cx, &p->obj, cobj, "LWFNode");
        }
    } while(0);
    
    if (cobj) {
        if (JS_HasProperty(cx, obj, "_ctor", &ok) && ok)
            ScriptingCore::getInstance()->executeFunctionWithOwner(OBJECT_TO_JSVAL(obj), "_ctor", args);
        
        args.rval().set(OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_LWFNode_constructor : wrong number of arguments");
    return false;
}

bool js_LWFNode_create(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_LWFNode_create : Error processing arguments");

        auto ret = LWFNode::create(arg0.c_str());
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<LWFNode>(cx, (LWFNode*)ret));
        }
        
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_LWFNode_create : wrong number of arguments");
    return false;
}

void js_LWFNode_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (LWFNode)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    JS::RootedObject jsobj(cx, obj);
    jsproxy = jsb_get_js_proxy(jsobj);
    if (jsproxy) {
        LWFNode *nobj = static_cast<LWFNode *>(jsproxy->ptr);
        nproxy = jsb_get_native_proxy(jsproxy->ptr);
        
        if (nobj) {
            jsb_remove_proxy(nproxy, jsproxy);
            JS::RootedValue flagValue(cx);
            JS_GetProperty(cx, jsobj, "__cppCreated", &flagValue);
            if (flagValue.isNullOrUndefined()){
                delete nobj;
            }
        }
        else
            jsb_remove_proxy(nullptr, jsproxy);
    }
}

static bool js_LWFNode_lwf(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    LWFNode* cobj = (LWFNode *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_LWFNode_lwf : Invalid Native Object");
    LWF::LWF* ret = cobj->lwf.get();
    JS::RootedValue jsret(cx);
    if (ret) {
        jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<LWF::LWF>(cx, (LWF::LWF*)ret));
    } else {
        jsret = JSVAL_NULL;
    };
    args.rval().set(jsret);
    return true;
}

void js_register_LWFNode(JSContext *cx, JS::HandleObject global) {
    jsb_LWFNode_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_LWFNode_class->name = "LWFNode";
    jsb_LWFNode_class->addProperty = JS_PropertyStub;
    jsb_LWFNode_class->delProperty = JS_DeletePropertyStub;
    jsb_LWFNode_class->getProperty = JS_PropertyStub;
    jsb_LWFNode_class->setProperty = JS_StrictPropertyStub;
    jsb_LWFNode_class->enumerate = JS_EnumerateStub;
    jsb_LWFNode_class->resolve = JS_ResolveStub;
    jsb_LWFNode_class->convert = JS_ConvertStub;
    jsb_LWFNode_class->finalize = js_LWFNode_finalize;
    jsb_LWFNode_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("lwf", js_LWFNode_lwf, JSPROP_ENUMERATE | JSPROP_PERMANENT),
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("create", js_LWFNode_create, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    JS::RootedObject parent_proto(cx, jsb_cocos2d_Sprite_prototype);
    jsb_LWFNode_prototype = JS_InitClass(
                                                 cx, global,
                                                 parent_proto,
                                                 jsb_LWFNode_class,
                                                 js_LWFNode_constructor, 0, // constructor
                                                 properties,
                                                 funcs,
                                                 NULL, // no static properties
                                                 st_funcs);
    
    JS::RootedObject proto(cx, jsb_LWFNode_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "LWFNode"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<LWFNode>(cx, jsb_LWFNode_class, proto, JS::NullPtr());

}


void register_all_lwf(JSContext* cx, JS::HandleObject obj) {
    // Get the global ns
    // JS::RootedObject ns(cx, ScriptingCore::getInstance()->getGlobalObject());
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);

    js_register_LWF(cx, ns);
    js_register_LWFNode(cx, ns);
}
