#include <v8.h>
#include <node.h>


#define FN_PREP(args)                    \
  Isolate* isolate = args.GetIsolate();  \
  HandleScope scope(isolate);


using v8::Context;
using v8::Function;
using v8::FunctionCallbackInfo;
using v8::FunctionTemplate;
using v8::Handle;
using v8::HandleScope;
using v8::Integer;
using v8::Isolate;
using v8::Local;
using v8::Number;
using v8::Object;
using v8::Persistent;
using v8::String;
using v8::Value;


Persistent<Object> global_context;
Persistent<Object> callbacks_wrap;

enum WrapFlags {
  kError,
  kConnection
};

static struct {
  uint8_t error;
} cb_flags;


// This is only safe if the Persistent isn't weak, which none of the
// Handles in here are.
template<class T>
inline Local<T> ToLocal(Persistent<T>& p_) {
  return *reinterpret_cast<Local<T>*>(&p_);
}


void AccessNamed(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);
}


void AccessIndexed(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);
}


void setup(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  Local<Object> wrap = args[0].As<Object>();
  Local<Object> flags = args[1].As<Object>();
  assert(wrap->IsObject());
  assert(flags->IsObject());

  callbacks_wrap.Reset(isolate, wrap);
  flags->SetIndexedPropertiesToExternalArrayData(&cb_flags,
                                                 v8::kExternalUnsignedByteArray,
                                                 1);
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  target->Set(String::NewFromUtf8(isolate, "accessNamed"),
              FunctionTemplate::New(AccessNamed)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "accessIndexed"),
              FunctionTemplate::New(AccessIndexed)->GetFunction());

  target->Set(String::NewFromUtf8(isolate, "setup"),
              FunctionTemplate::New(setup)->GetFunction());

  global_context.Reset(isolate, Context::GetCurrent()->Global());
}


NODE_MODULE(share_memory, Initialize)
