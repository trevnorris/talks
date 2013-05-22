#include <v8.h>
#include <node.h>


using v8::Arguments;
using v8::Boolean;
using v8::Function;
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


Isolate* isolate;
Persistent<Function> p_setprop_fn;
Persistent<Function> p_setobj_fn;
Persistent<Object> p_empty_obj;
Persistent<String> p_length_sym;
Persistent<String> p_type_sym;
Persistent<String> p_used_sym;


Handle<Value> SetInCCSlow(const Arguments& args) {
  HandleScope scope(isolate);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    obj->Set(String::New("length"), arg0);
    obj->Set(String::New("type"), arg1);
    obj->Set(String::New("used"), arg2);
  }

  return scope.Close(obj);
}


Handle<Value> SetInCCSym(const Arguments& args) {
  HandleScope scope(isolate);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    obj->Set(p_length_sym, arg0);
    obj->Set(p_type_sym, arg1);
    obj->Set(p_used_sym, arg2);
  }

  return scope.Close(obj);
}


Handle<Value> SetInJS(const Arguments& args) {
  HandleScope scope(isolate);

  size_t iter = args[0]->Uint32Value();
  Local<Object> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    obj = Object::New();
    Local<Value> argv[3] = { arg0, arg1, arg2 };
    p_setprop_fn->Call(obj, 3, argv);
  }

  return scope.Close(obj);
}


Handle<Value> SetInJSObj(const Arguments& args) {
  HandleScope scope(isolate);

  size_t iter = args[0]->Uint32Value();
  Local<Value> obj;
  Local<Number> arg0 = args[1]->ToNumber();
  Local<String> arg1 = args[2]->ToString();
  Local<Boolean> arg2 = args[3]->ToBoolean();

  for (size_t i = 0; i < iter; i++) {
    Local<Value> argv[3] = { arg0, arg1, arg2 };
    obj = p_setobj_fn->Call(p_empty_obj, 3, argv);
  }

  return scope.Close(obj);
}


Handle<Value> SetupCC(const Arguments& args) {
  p_setprop_fn = Persistent<Function>::New(isolate,
                                           args[0].As<Function>());
  p_setobj_fn = Persistent<Function>::New(isolate,
                                          args[1].As<Function>());
  return Undefined(isolate);
}


void Initialize(Handle<Object> target) {
  isolate = Isolate::GetCurrent();

  HandleScope scope(isolate);

  target->Set(String::New("setInCCSlow"),
              FunctionTemplate::New(SetInCCSlow)->GetFunction());
  target->Set(String::New("setInCCSym"),
              FunctionTemplate::New(SetInCCSym)->GetFunction());
  target->Set(String::New("setInJS"),
              FunctionTemplate::New(SetInJS)->GetFunction());
  target->Set(String::New("setInJSObj"),
              FunctionTemplate::New(SetInJSObj)->GetFunction());
  target->Set(String::New("setupCC"),
              FunctionTemplate::New(SetupCC)->GetFunction());

  p_empty_obj = Persistent<Object>::New(isolate, Object::New());
  p_length_sym = Persistent<String>::New(isolate, String::New("length"));
  p_type_sym = Persistent<String>::New(isolate, String::New("type"));
  p_used_sym = Persistent<String>::New(isolate, String::New("used"));
}


NODE_MODULE(js_cc_set, Initialize)
