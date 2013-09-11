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
Persistent<Function> with_callback_p;

static struct {
  uint32_t need_to_callback;
} obj_flags;


// This is only safe if the Persistent isn't weak, which none of the
// Handles in here are.
template<class T>
inline Local<T> ToLocal(Persistent<T>& p_) {
  return *reinterpret_cast<Local<T>*>(&p_);
}


void RunWithFlags(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  assert(args[0]->IsNumber());

  uint32_t val = args[0]->Uint32Value() * 2;
  Local<Value> return_val = Integer::NewFromUnsigned(val, isolate);

  if (obj_flags.need_to_callback > 0)
    ToLocal(with_callback_p)->Call(ToLocal(global_context), 1, &return_val);

  obj_flags.need_to_callback = 0;

  args.GetReturnValue().Set(val);
}


void RunWithoutFlags(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  assert(args[0]->IsNumber());

  uint32_t val = args[0]->Uint32Value() * 2;
  Local<Value> return_val = Integer::NewFromUnsigned(val, isolate);

  ToLocal(with_callback_p)->Call(ToLocal(global_context), 1, &return_val);

  args.GetReturnValue().Set(val);
}


void SetupShared(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  Local<Object> flags = args[0].As<Object>();
  flags->SetIndexedPropertiesToExternalArrayData(&obj_flags,
                                                 v8::kExternalUnsignedIntArray,
                                                 1);

  Local<Function> callback = args[1].As<Function>();
  assert(callback->IsFunction());
  with_callback_p.Reset(isolate, callback);
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  target->Set(String::NewFromUtf8(isolate, "runWithFlags"),
              FunctionTemplate::New(RunWithFlags)->GetFunction());
  target->Set(String::NewFromUtf8(isolate, "runWithoutFlags"),
              FunctionTemplate::New(RunWithoutFlags)->GetFunction());

  target->Set(String::NewFromUtf8(isolate, "setupShared"),
              FunctionTemplate::New(SetupShared)->GetFunction());

  global_context.Reset(isolate, Context::GetCurrent()->Global());
}


NODE_MODULE(share_memory, Initialize)
