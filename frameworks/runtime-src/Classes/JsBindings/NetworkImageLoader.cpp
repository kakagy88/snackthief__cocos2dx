//
//  NetworkImageLoader.cpp
//  magic
//
//  Created by 太田敦士 on 2017/11/17.
//

#include "NetworkImageLoader.h"
#include "../NetworkImageLoader.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"

JSClass  *jsb_NetworkImageLoader_class;
JSObject *jsb_NetworkImageLoader_prototype;

USING_NS_CC;

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

bool js_NetworkImageLoader_getInstance(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        auto ret = NetworkImageLoader::getInstance();
        jsval jsret = JSVAL_NULL;
        if (ret) {
            jsret = OBJECT_TO_JSVAL(js_get_or_create_jsobject<NetworkImageLoader>(cx, (NetworkImageLoader*)ret));
        }
        
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_NetworkImageLoader_getInstance : wrong number of arguments");
    return false;

}

bool js_NetworkImageLoader_loadTextureFromUrlASync(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    
    JSB_PRECONDITION2( argc >= 2 && argc <= 4, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    
    JS::RootedObject obj(cx);
    obj.set(args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    NetworkImageLoader* cobj = (NetworkImageLoader *)(proxy ? proxy->ptr : nullptr);
    JSB_PRECONDITION2( cobj, cx, false, "js_NetworkImageLoader_loadTextureFromUrlASync : Invalid Native Object");

    // 引数1
    std::string arg0;
    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    JSB_PRECONDITION2(ok, cx, false, "js_NetworkImageLoader_loadTextureFromUrlASync : Error processing arguments");
    
    std::shared_ptr<JSFunctionWrapper> func;

    // 引数2
    if (JS_TypeOfValue(cx, args.get(1)) == JSTYPE_FUNCTION) {
        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
        JS::RootedValue fval(cx, args.get(1));
        func = std::shared_ptr<JSFunctionWrapper>(new JSFunctionWrapper(cx, jstarget, fval));
    } else {
        ok = false;
    }
    JSB_PRECONDITION2(ok, cx, false, "js_NetworkImageLoader_loadTextureFromUrlASync : Error processing arguments");

    // 引数3
    bool arg2 = true;
    if (argc >= 3) {
        arg2 = JS::ToBoolean(args.get(2));
    }

    // 引数4
    bool arg3 = true;
    if (argc >= 4) {
        arg3 = JS::ToBoolean(args.get(3));
    }

    cobj->loadTextureFromUrlASync(arg0, [=](Texture2D* texture) {
        JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
        jsval largv[1];

        if (texture) {
            largv[0] = OBJECT_TO_JSVAL(js_get_or_create_jsobject<cocos2d::Texture2D>(cx, (cocos2d::Texture2D*)texture));
        } else {
            largv[0] = JSVAL_NULL;
        }
        JS::RootedValue rval(cx);
        bool invokeOk = func->invoke(1, &largv[0], &rval);
        if (!invokeOk && JS_IsExceptionPending(cx)) {
            JS_ReportPendingException(cx);
        }
    }, arg2, arg3);
    return ok;
}

void js_register_NetworkImageLoader(JSContext *cx, JS::HandleObject global) {
    jsb_NetworkImageLoader_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_NetworkImageLoader_class->name = "NetworkImageLoader";
    jsb_NetworkImageLoader_class->addProperty = JS_PropertyStub;
    jsb_NetworkImageLoader_class->delProperty = JS_DeletePropertyStub;
    jsb_NetworkImageLoader_class->getProperty = JS_PropertyStub;
    jsb_NetworkImageLoader_class->setProperty = JS_StrictPropertyStub;
    jsb_NetworkImageLoader_class->enumerate = JS_EnumerateStub;
    jsb_NetworkImageLoader_class->resolve = JS_ResolveStub;
    jsb_NetworkImageLoader_class->convert = JS_ConvertStub;
    jsb_NetworkImageLoader_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    static JSPropertySpec properties[] = {
        JS_PS_END
    };
    static JSFunctionSpec funcs[] = {
        JS_FN("loadTextureFromUrlASync", js_NetworkImageLoader_loadTextureFromUrlASync, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    static JSFunctionSpec st_funcs[] = {
        JS_FN("getInstance", js_NetworkImageLoader_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    jsb_NetworkImageLoader_prototype = JS_InitClass(
                                         cx, global,
                                         JS::NullPtr(),
                                         jsb_NetworkImageLoader_class,
                                         empty_constructor, 0, // constructor
                                         properties,
                                         funcs,
                                         NULL, // no static properties
                                         st_funcs);
    
    JS::RootedObject proto(cx, jsb_NetworkImageLoader_prototype);
    JS::RootedValue className(cx, std_string_to_jsval(cx, "NetworkImageLoader"));
    JS_SetProperty(cx, proto, "_className", className);
    JS_SetProperty(cx, proto, "__nativeObj", JS::TrueHandleValue);
    JS_SetProperty(cx, proto, "__is_ref", JS::FalseHandleValue);
    // add the proto and JSClass to the type->js info hash table
    jsb_register_class<NetworkImageLoader>(cx, jsb_NetworkImageLoader_class, proto, JS::NullPtr());
    
}

void register_all_network_image_loader(JSContext *cx, JS::HandleObject obj) {
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "cc", &ns);
    js_register_NetworkImageLoader(cx, ns);
}
