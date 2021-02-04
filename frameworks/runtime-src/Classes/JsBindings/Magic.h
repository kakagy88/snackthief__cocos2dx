#ifndef  _JS_BINDINGS_MAGIC_H_
#define  _JS_BINDINGS_MAGIC_H_

#include "jsapi.h"

extern "C" {
    bool JSB_magic_printHoge(JSContext *cx, uint32_t argc, jsval *vp);
    bool JSB_magic_doSomethingWithCallback(JSContext *cx, uint32_t argc, jsval *vp);
    bool JSB_magic_uploadThumbnail(JSContext *cx, uint32_t argc, jsval *vp);
}

void register_all_magic(JSContext *_cx, JS::HandleObject object);

#endif // _JS_BINDINGS_MAGIC_H_
