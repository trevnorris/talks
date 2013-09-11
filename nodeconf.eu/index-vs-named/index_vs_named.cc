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


void AccessNamed(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  Local<Object> obj = args[0].As<Object>();
  size_t iter = args[1]->Uint32Value();

  assert(obj->IsObject());

  for (size_t i = 0; i < iter; i++) {
    size_t length = obj->Get(ToLocal(&p_length_sym))->Uint32Value();
    Local<String> type = obj->Get(ToLocal(&p_type_sym)).As<String>();
    bool used = obj->Get(ToLocal(&p_used_sym))->IsTrue();
  }
}


void AccessIndexed(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  Local<Object> obj = args[0].As<Object>();
  size_t iter = args[1]->Uint32Value();

  assert(obj->IsObject());

  for (size_t i = 0; i < iter; i++) {
    size_t length = obj->Get(0)->Uint32Value();
    Local<String> type = obj->Get(1).As<String>();
    bool used = obj->Get(2)->IsTrue();
  }
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  target->Set(String::NewFromUtf8(isolate, "accessNamed"),
              FunctionTemplate::New(AccessNamed)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "accessIndexed"),
              FunctionTemplate::New(AccessIndexed)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "setup"),
              FunctionTemplate::New(Setup)->GetFunction());

  length_sym = reinterpret_cast<const uint8_t*>("length");
  type_sym = reinterpret_cast<const uint8_t*>("type");
  used_sym = reinterpret_cast<const uint8_t*>("used");

  p_length_sym.Reset(isolate, String::NewFromOneByte(isolate, length_sym));
  p_type_sym.Reset(isolate, String::NewFromOneByte(isolate, type_sym));
  p_used_sym.Reset(isolate, String::NewFromOneByte(isolate, used_sym));
}


NODE_MODULE(index_vs_named, Initialize)
