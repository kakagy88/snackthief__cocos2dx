//
//  Downloader.cpp
//  magic
//
//  Created by 太田敦士 on 2018/04/05.
//

#include "Downloader.hpp"
#include "../Downloader.hpp"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

JSClass  *jsb_Downloader_class;
JSObject *jsb_Downloader_prototype;

bool js_Downloader_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    Downloader* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    
    do {
        if (argc == 0) {
            cobj = new (std::nothrow) Downloader();
            
            js_type_class_t *typeClass = js_get_type_from_native<Downloader>(cobj);
            JS::RootedObject proto(cx, typeClass->proto.ref());
            JS::RootedObject parent(cx, typeClass->parentProto.ref());
            obj = JS_NewObject(cx, typeClass->jsclass, proto, parent);
            js_proxy_t* p = jsb_new_proxy(cobj, obj);
            jsb_non_ref_init(cx, &p->obj, cobj, "Downloader");
        }
    } while(0);
    
    if (cobj) {
        args.rval().set(OBJECT_TO_JSVAL(obj));
        return true;
    }
    JS_ReportError(cx, "js_Downloader_constructor : wrong number of arguments");
    return false;
}

bool js_Downloader_addTask(JSContext *cx, uint32_t argc, jsval *vp)
{
    bool ok = true;
    Downloader* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (Downloader *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_Downloader_addTask : Invalid Native Object");
    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            JSB_PRECONDITION2(ok, cx, false, "js_Downloader_addTask : Error processing arguments");
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            JSB_PRECONDITION2(ok, cx, false, "js_Downloader_addTask : Error processing arguments");
            cobj->addTask(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_Downloader_addTask : wrong number of arguments");
    return false;
}

bool js_Downloader_setProgressCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    Downloader* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (Downloader *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_Downloader_setProgressCallback : Invalid Native Object");
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
            JSB_PRECONDITION2(ok, cx, false, "js_Downloader_setProgressCallback : Error processing arguments");
            auto lambda = [=](int arg0, int arg1, int64_t arg2, int64_t arg3, int64_t arg4) {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[5];
                arg[0] = INT_TO_JSVAL(arg0);
                arg[1] = INT_TO_JSVAL(arg1);
                arg[2] = long_long_to_jsval(cx, arg2);
                arg[3] = long_long_to_jsval(cx, arg3);
                arg[4] = long_long_to_jsval(cx, arg4);
                JS::RootedValue rval(cx);
                
                bool ok = func->invoke(5, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            cobj->setProgressCallback(lambda);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_Downloader_setProgressCallback : wrong number of arguments");
    return false;
}

bool js_Downloader_setCompleteCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    Downloader* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (Downloader *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_Downloader_setCompleteCallback : Invalid Native Object");
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
            JSB_PRECONDITION2(ok, cx, false, "js_Downloader_setCompleteCallback : Error processing arguments");
            auto lambda = [=](int arg0, int arg1, int arg2) {
                JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
                jsval arg[3];
                arg[0] = INT_TO_JSVAL(arg0);
                arg[1] = INT_TO_JSVAL(arg1);
                arg[2] = INT_TO_JSVAL(arg2);
                JS::RootedValue rval(cx);
                
                bool ok = func->invoke(3, arg, &rval);
                if (!ok && JS_IsExceptionPending(cx)) {
                    JS_ReportPendingException(cx);
                }
            };
            cobj->setCompleteCallback(lambda);
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_Downloader_setCompleteCallback : wrong number of arguments");
    return false;
}

bool js_Downloader_startDownload(JSContext *cx, uint32_t argc, jsval *vp)
{
    Downloader* cobj = nullptr;
    
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (Downloader *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_Downloader_startDownload : Invalid Native Object");
    do {
        if (argc == 0) {
            cobj->startDownload();
            args.rval().setUndefined();
            return true;
        }
    } while(0);
    
    JS_ReportError(cx, "js_Downloader_startDownload : wrong number of arguments");
    return false;
}

void js_register_Downloader(JSContext *cx, JS::HandleObject global) {
    jsb_Downloader_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_Downloader_class->name = "Downloader";
    jsb_Downloader_class->addProperty = JS_PropertyStub;
    jsb_Downloader_class->delProperty = JS_DeletePropertyStub;
    jsb_Downloader_class->getProperty = JS_PropertyStub;
    jsb_Downloader_class->setProperty = JS_StrictPropertyStub;
    jsb_Downloader_class->enumerate = JS_EnumerateStub;
    jsb_Downloader_class->resolve = JS_ResolveStub;
    jsb_Downloader_class->convert = JS_ConvertStub;
    // jsb_SsRaidBattleNode_class->finalize = js_SsRaidBattleNode_finalize;
    jsb_Downloader_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("addTask", js_Downloader_addTask, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("startDownload", js_Downloader_startDownload, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setProgressCallback", js_Downloader_setProgressCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCompleteCallback", js_Downloader_setCompleteCallback, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FS_END
    };
    jsb_Downloader_prototype = JS_InitClass(
                                                  cx, global,
                                                  JS::NullPtr(),
                                                  jsb_Downloader_class,
                                                  js_Downloader_constructor, 0, // constructor
                                                  properties,
                                                  funcs,
                                                  NULL, // no static properties
                                                  st_funcs);
    
    JS::RootedObject proto(cx, jsb_Downloader_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "Downloader"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<Downloader>(cx, jsb_Downloader_class, proto, JS::NullPtr());
    
}

void register_all_downloader(JSContext *cx, JS::HandleObject object) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, object, "cc", &ns);
    js_register_Downloader(cx, ns);
}
