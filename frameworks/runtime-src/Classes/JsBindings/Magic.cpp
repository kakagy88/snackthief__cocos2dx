#include "Magic.h"
#include <stdio.h>
#include "scripting/js-bindings/manual/js_bindings_config.h"
#include "scripting/js-bindings/manual/js_bindings_core.h"
#include "scripting/js-bindings/manual/cocos2d_specifics.hpp"
#include "network/HttpClient.h"
#include "platform/CCFileUtils.h"
#include "AppDelegate.h"

// TODO:JSからコールバックをもらって非同期で呼び戻す。
bool JSB_magic_printHoge(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    printf("hoge\n");

    args.rval().setUndefined();
    return true;
}

bool JSB_magic_doSomethingWithCallback(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;

    JSB_PRECONDITION2( argc == 1, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    printf("doSomething\n");
    
    if (JS_TypeOfValue(cx, args.get(0)) == JSTYPE_FUNCTION) {
        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
        JS::RootedValue fval(cx, args.get(0));
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, fval));
        JS::RootedValue rval(cx);
        
        ok &= func->invoke(0, nullptr, &rval);
    } else {
        ok = false;
    }

    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");
    return ok;
}

void postFile(const std::string& url, const std::string& path, std::function<void (const bool)> callback) {
    printf("postFile\n");
    // cocos2d::network::HttpClient::getInstance()->enableCookies(nullptr);

    std::string basename = "mobileFile";
    
    ssize_t bufferSize = 0;
    unsigned char* pBuffer = cocos2d::FileUtils::getInstance()->getFileData(path.c_str(), "r", &bufferSize);
    
    //The same file stored as a string of "bytes" (it may contain zeroes)
    std::string data = std::string((const char*)pBuffer, bufferSize);

    //Create an http post request
    cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
    request->setUrl(url.c_str());
    request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
    
    //Include this boundary in the header and in the body of the request
    std::string boundary = "---------------------------14737809831466499882746641449";
    
    //The content of the request must be multipart/form-data
    std::vector<std::string> contentType;
    contentType.push_back("Content-Type: multipart/form-data; boundary=" + boundary);
    
    //Set the header with the previous content type
    request->setHeaders(contentType);
    
    //Build the body of the request. Include the boundary, basename and file name.
    //Specify the content disposition and type
    
    std::string body = "\r\n--" + boundary + "\r\n";
    body = body + "Content-Disposition: form-data; name=\"" + basename
    + "\"; filename=\"" + path + "\"\r\n";
    body = body + "Content-Type: application/octet-stream\r\n\r\n";
    
    //Then append the file data and again the boundary
    body = body + data;
    body = body + "\r\n--" + boundary + "--\r\n";
    
    request->setRequestData(body.data(), body.size());
    
    //Just a tag...
    request->setTag("UPLOAD FILE");
    
    //Check that everything went OK when the request response calls your app back:
    request->setResponseCallback( [=]
                                 (cocos2d::network::HttpClient* client,
                                  cocos2d::network::HttpResponse* response)
                                 {
                                     
                                     std::vector<char> *buffer = response->getResponseData();
                                     printf("Get data from server:\n");
                                     
                                     for (unsigned int i = 0; i < buffer->size(); i++)
                                     { printf("%c", (*buffer)[i]); }
                                     
                                     printf(" Response Code %li   ", response->getResponseCode());
                                     if (200 == response->getResponseCode()){ printf("OK \n"); }
                                     else{ printf("failed \n"); }
                                     
                                 });
    
    //Finally send the request:
    cocos2d::network::HttpClient::getInstance()->send(request);
    
    //And then get rid of it:
    request->release();
    
    // callback(true);
}
bool JSB_magic_postFile(JSContext *cx, uint32_t argc, jsval *vp) {
    bool ok = true;
    
    JSB_PRECONDITION2( argc == 3, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);

    std::string arg0;
    ok &= jsval_to_std_string(cx, args.get(0), &arg0);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    std::string arg1;
    ok &= jsval_to_std_string(cx, args.get(1), &arg1);
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    std::function<void (float)> callback;
    if (JS_TypeOfValue(cx, args.get(2)) == JSTYPE_FUNCTION) {
        JS::RootedObject jstarget(cx, args.thisv().toObjectOrNull());
        JS::RootedValue fval(cx, args.get(2));
        std::shared_ptr<JSFunctionWrapper> func(new JSFunctionWrapper(cx, jstarget, fval));
        auto lambda = [=](bool larg0) -> void {
            JSB_AUTOCOMPARTMENT_WITH_GLOBAL_OBJCET
            jsval largv[1];
            largv[0] = BOOLEAN_TO_JSVAL(larg0);
            JS::RootedValue rval(cx);
            bool invokeOk = func->invoke(1, &largv[0], &rval);
            if (!invokeOk && JS_IsExceptionPending(cx)) {
                JS_ReportPendingException(cx);
            }
        };
        callback = lambda;
    } else {
        ok = false;
    }
    JSB_PRECONDITION2(ok, cx, false, "Error processing arguments");

    postFile(arg0, arg1, callback);
    
    return ok;
}

bool JSB_magic_createCacheDirectory(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    AppDelegate::createCacheDirectory();
    args.rval().setUndefined();
    return true;
}

bool JSB_magic_removeCacheDirectory(JSContext *cx, uint32_t argc, jsval *vp) {
    JSB_PRECONDITION2( argc == 0, cx, false, "Invalid number of arguments" );
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    AppDelegate::removeCacheDirectory();
    args.rval().setUndefined();
    return true;
}

void register_all_magic(JSContext *_cx, JS::HandleObject object) {
    JS::RootedObject magic(_cx, JS_NewObject(_cx, NULL, JS::NullPtr(), JS::NullPtr()));
    JS::RootedValue magicVal(_cx);
    magicVal = OBJECT_TO_JSVAL(magic);
    JS_SetProperty(_cx, object, "magic", magicVal);

    JS_DefineFunction(_cx, magic, "printHoge", JSB_magic_printHoge, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, magic, "doSomethingWithCallback", JSB_magic_doSomethingWithCallback, 1, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, magic, "postFile", JSB_magic_postFile, 3, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, magic, "createCacheDirectory", JSB_magic_createCacheDirectory, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
    JS_DefineFunction(_cx, magic, "removeCacheDirectory", JSB_magic_removeCacheDirectory, 0, JSPROP_READONLY | JSPROP_PERMANENT | JSPROP_ENUMERATE );
}
