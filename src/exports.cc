#include "exports.h"
#include "utils.h"

NAN_MODULE_INIT(InitAll) {
  Nan::Set(target, Nan::New("scaleFactors").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(ScaleFactors)).ToLocalChecked());
  Nan::Set(target, Nan::New("compressSync").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(CompressSync)).ToLocalChecked());
  Nan::Set(target, Nan::New("decompressSync").ToLocalChecked(),
    Nan::GetFunction(Nan::New<v8::FunctionTemplate>(DecompressSync)).ToLocalChecked());
  Nan::Set(target, Nan::New("FORMAT_RGB").ToLocalChecked(), Nan::New(FORMAT_RGB));
  Nan::Set(target, Nan::New("FORMAT_BGR").ToLocalChecked(), Nan::New(FORMAT_BGR));
  Nan::Set(target, Nan::New("FORMAT_RGBX").ToLocalChecked(), Nan::New(FORMAT_RGBX));
  Nan::Set(target, Nan::New("FORMAT_BGRX").ToLocalChecked(), Nan::New(FORMAT_BGRX));
  Nan::Set(target, Nan::New("FORMAT_XRGB").ToLocalChecked(), Nan::New(FORMAT_XRGB));
  Nan::Set(target, Nan::New("FORMAT_XBGR").ToLocalChecked(), Nan::New(FORMAT_XBGR));
  Nan::Set(target, Nan::New("FORMAT_GRAY").ToLocalChecked(), Nan::New(FORMAT_GRAY));
  Nan::Set(target, Nan::New("FORMAT_RGBA").ToLocalChecked(), Nan::New(FORMAT_RGBA));
  Nan::Set(target, Nan::New("FORMAT_BGRA").ToLocalChecked(), Nan::New(FORMAT_BGRA));
  Nan::Set(target, Nan::New("FORMAT_ABGR").ToLocalChecked(), Nan::New(FORMAT_ABGR));
  Nan::Set(target, Nan::New("FORMAT_ARGB").ToLocalChecked(), Nan::New(FORMAT_ARGB));
}

// There is no semi-colon after NODE_MODULE as it's not a function (see node.h).
// see http://nodejs.org/api/addons.html
NODE_MODULE(jpegturbo, InitAll)
