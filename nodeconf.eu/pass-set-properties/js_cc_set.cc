#include <v8.h>
#include <node.h>

#define FN_PREP(args)                    \
  Isolate* isolate = args.GetIsolate();  \
  HandleScope scope(isolate);            \
  do {} while(0)


using v8::Boolean;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Handle;
using v8::HandleScope;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;


Persistent<Function> p_setprop_fn;
Persistent<Function> p_setobj_fn;
Persistent<Object> p_empty_obj;
Persistent<String> p_length_sym;
Persistent<String> p_type_sym;
Persistent<String> p_used_sym;

static const uint8_t* length_sym;
static const uint8_t* type_sym;
static const uint8_t* used_sym;


template<class T>
inline Local<T> ToLocal(Persistent<T>* p_) {
  return *reinterpret_cast<Local<T>*>(p_);
}


void SetInCCSlow(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    obj->Set(String::NewFromOneByte(isolate, length_sym), arg0);
    obj->Set(String::NewFromOneByte(isolate, type_sym), arg1);
    obj->Set(String::NewFromOneByte(isolate, used_sym), arg2);
  }
}


void SetInCCSym(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    obj->Set(ToLocal<String>(&p_length_sym), arg0);
    obj->Set(ToLocal<String>(&p_type_sym), arg1);
    obj->Set(ToLocal<String>(&p_used_sym), arg2);
  }
}


void SetInJS(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    Local<Value> argv[3] = { arg0, arg1, arg2 };
    ToLocal<Function>(&p_setprop_fn)->Call(obj, 3, argv);
  }
}


void SetInJSObj(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  size_t iter = args[0]->Uint32Value();
  Local<Value> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    Local<Value> argv[3] = { arg0, arg1, arg2 };
    Local<Function> fn = ToLocal<Function>(&p_setobj_fn);
    obj = fn->Call(ToLocal<Object>(&p_empty_obj), 3, argv);
  }

  args.GetReturnValue().Set(obj);
}


void SetupCC(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();
  p_setprop_fn.Reset(isolate, args[0].As<Function>());
  p_setobj_fn.Reset(isolate, args[1].As<Function>());
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  target->Set(String::NewFromUtf8(isolate, "setInCCSlow"),
              FunctionTemplate::New(SetInCCSlow)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "setInCCSym"),
              FunctionTemplate::New(SetInCCSym)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "setInJS"),
              FunctionTemplate::New(SetInJS)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "setInJSObj"),
              FunctionTemplate::New(SetInJSObj)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "setupCC"),
              FunctionTemplate::New(SetupCC)->GetFunction());

  length_sym = reinterpret_cast<const uint8_t*>("length");
  type_sym = reinterpret_cast<const uint8_t*>("type");
  used_sym = reinterpret_cast<const uint8_t*>("used");

  p_empty_obj.Reset(isolate, Object::New());
  p_length_sym.Reset(isolate, String::NewFromOneByte(isolate, length_sym));
  p_type_sym.Reset(isolate, String::NewFromOneByte(isolate, type_sym));
  p_used_sym.Reset(isolate, String::NewFromOneByte(isolate, used_sym));
}


NODE_MODULE(js_cc_set, Initialize)
