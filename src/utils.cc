#include "utils.h"
#include <turbojpeg.h>

#ifndef TJFLAG_FASTDCT
#define TJFLAG_FASTDCT 0
#endif

NAN_METHOD(ScaleFactors) {
    v8::Local<v8::Array> arr = Nan::New<v8::Array>();
    int num;
    tjscalingfactor* factors = tjGetScalingFactors(&num);
    for(int i = 0; i < num; i++) {
        v8::Local<v8::Object> obj = Nan::New<v8::Object>();
        obj->Set(Nan::New("num").ToLocalChecked(), Nan::New(factors[i].num));
        obj->Set(Nan::New("denom").ToLocalChecked(), Nan::New(factors[i].denom));
        arr->Set(i, obj);
    }
    info.GetReturnValue().Set(arr);

}

