#ifndef SIMPLE_CV_UTILS_H
#define SIMPLE_CV_UTILS_H

#include <nan.h>

inline bool has(v8::Local<v8::Object> obj, const char* key) {
  Nan::HandleScope scope;
  return Nan::Has(obj, Nan::New(key).ToLocalChecked()).FromJust();
}

inline bool has(v8::Local<v8::Value> value, const char* key) {
  Nan::HandleScope scope;
  return has(value->ToObject(), key);
}

inline v8::Local<v8::Value> getValue(v8::Local<v8::Object> obj, const char* key) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(Nan::Get(obj, Nan::New(key).ToLocalChecked()).ToLocalChecked());
}

inline v8::Local<v8::Value> getValue(v8::Local<v8::Value> value, const char* key) {
  Nan::EscapableHandleScope scope;
  return scope.Escape(getValue(value->ToObject(), key));
}

template<typename T>
inline T get(v8::Local<v8::Object> obj, const char* key) {
  Nan::HandleScope scope;
  return Nan::To<T>(getValue(obj, key)).FromJust();
}

template<typename T>
inline T get(v8::Local<v8::Value> obj, const char* key) {
  Nan::HandleScope scope;
  return get<T>(obj->ToObject(), key);
}

inline bool isPoint(v8::Local<v8::Value> val) {
  Nan::HandleScope scope;
  return val->IsObject()
     && has(val, "x")
     && has(val, "y")
     && getValue(val, "x")->IsNumber()
     && getValue(val, "y")->IsNumber();
}

template<typename T>
inline cv::Point_<T> getPoint(v8::Local<v8::Value> val) {
  return cv::Point_<T>(get<T>(val, "x"), get<T>(val, "y"));
}

inline bool isRect(v8::Local<v8::Value> val) {
  Nan::HandleScope scope;
  return has(val, "x")
    && has(val, "y")
    && has(val, "width")
    && has(val, "height")
    && getValue(val, "x")->IsNumber()
    && getValue(val, "y")->IsNumber()
    && getValue(val, "width")->IsNumber()
    && getValue(val, "height")->IsNumber();
}

template<typename T>
inline cv::Rect_<T> getRect(v8::Local<v8::Value> val) {
  return cv::Rect_<T>(get<T>(val, "x"), get<T>(val, "y"), get<T>(val, "width"), get<T>(val, "height"));
}

#endif //SIMPLE_CV_UTILS_H
