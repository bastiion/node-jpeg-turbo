
#include "exports.h"

#ifndef TJFLAG_FASTDCT
#define TJFLAG_FASTDCT 0
#endif


NAN_METHOD(CompressSync) {
    int err;
    unsigned char* srcData;
    unsigned char* dstData;
    uint32_t dstLength;
    int width, height, quality, bpp;
    const char* tjErr;

    if (info.Length() < 2) {
        return Nan::ThrowError(Nan::TypeError("Too few arguments"));
      }

      v8::Local<v8::Object> srcObject = info[0].As<v8::Object>();
      if (!node::Buffer::HasInstance(srcObject)) {
        return Nan::ThrowError(Nan::TypeError("Invalid source buffer"));
      }
      srcData = (unsigned char*) node::Buffer::Data(srcObject);

      v8::Local<v8::Object> options = info[1].As<v8::Object>();
        if (!options->IsObject()) {
          return Nan::ThrowError(Nan::TypeError("Options must be an Object"));
      }

      uint32_t format =
        options->Get(Nan::New("format").ToLocalChecked())->Uint32Value();
      
      quality = options->Get(Nan::New("quality").ToLocalChecked())->IntegerValue();

      width = options->Get(Nan::New("width").ToLocalChecked())->IntegerValue();
      height = options->Get(Nan::New("height").ToLocalChecked())->IntegerValue();

      if(quality < 0 || quality > 100) {
        return Nan::ThrowRangeError("Quality parameter must be between 0 (worst) and 100 (best)");
      }

      switch (format) {
        case FORMAT_GRAY:
          bpp = 1;
          break;
        case FORMAT_RGB:
        case FORMAT_BGR:
          bpp = 3;
          break;
        case FORMAT_RGBX:
        case FORMAT_BGRX:
        case FORMAT_XRGB:
        case FORMAT_XBGR:
        case FORMAT_RGBA:
        case FORMAT_BGRA:
        case FORMAT_ABGR:
        case FORMAT_ARGB:
          bpp = 4;
          break;
        default:
          return Nan::ThrowError(Nan::TypeError("Invalid input format"));
        }

        tjhandle ch = tjInitCompress();
      if (ch == NULL) {
      return Nan::ThrowError(tjGetErrorStr());
    }

  v8::Local<v8::Object> dstObject =
    options->Get(Nan::New("out").ToLocalChecked()).As<v8::Object>();

  if (!dstObject->IsUndefined() && !node::Buffer::HasInstance(dstObject)) {
    return Nan::ThrowError(Nan::TypeError("Invalid output buffer"));
  }
  dstLength = tjBufSize(width, height, bpp);
  //dstData = (unsigned char*) node::Buffer::Data(dstObject);

  unsigned char* jpegBuffer = NULL;

  err = tjCompress2( ch, srcData, width, 0, height, format, &jpegBuffer, (unsigned long*)&dstLength, TJSAMP_444, quality, TJFLAG_FASTDCT);

  if (err != 0) {
    tjErr = tjGetErrorStr();
    tjDestroy(ch);
    return Nan::ThrowError(tjErr);
  }
  err = tjDestroy(ch);

  if (err != 0) {
    return Nan::ThrowError(tjGetErrorStr());
  }

  dstObject = Nan::NewBuffer(dstLength).ToLocalChecked();
  memcpy((void*)node::Buffer::Data(dstObject),(const void*) jpegBuffer, dstLength);

  v8::Local<v8::Object> obj = Nan::New<v8::Object>();
  obj->Set(Nan::New("data").ToLocalChecked(), dstObject);
  obj->Set(Nan::New("width").ToLocalChecked(), Nan::New(width));
  obj->Set(Nan::New("height").ToLocalChecked(), Nan::New(height));
  obj->Set(Nan::New("size").ToLocalChecked(), Nan::New(dstLength));
  obj->Set(Nan::New("bpp").ToLocalChecked(), Nan::New(bpp));

  info.GetReturnValue().Set(obj);

}
