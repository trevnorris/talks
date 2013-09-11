#include <string.h>
#include <v8.h>
#include <node.h>
#include <string_bytes.h>

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


void AfterFill(const FunctionCallbackInfo<Value>& args) {
  FN_PREP(args);

  Local<String> long_string = args[0].As<String>();

  assert(long_string->IsString());
  assert(args[1]->IsString());

  String::Utf8Value fill_char(args[1]);

  char* data = NULL;
  size_t length = 0;
  assert(node::StringBytes::GetExternalParts(
        long_string, const_cast<const char**>(&data), &length));

  memset(data, (*fill_char)[0], length);
}


void Initialize(Handle<Object> target) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  target->Set(String::NewFromUtf8(isolate, "afterFill"),
              FunctionTemplate::New(AfterFill)->GetFunction());
}


NODE_MODULE(mutable_strings, Initialize)
