#include <node.h>
#include <v8.h>

using namespace v8;

// ����������������args[0] �ַ�����args[1] �ص�����
void hello(const FunctionCallbackInfo<Value>& args) {
  // ʹ�� HandleScope ��������������
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  // �жϲ�����ʽ�͸�ʽ
  if (args.Length() < 2 || !args[0]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "Wrong arguments")));
    return;
  }

  // callback, ʹ��Cast������ת��
  Local<Function> callback = Local<Function>::Cast(args[1]);
  Local<Value> argv[1] = {
    // ƴ��String
    String::Concat(Local<String>::Cast(args[0]), String::NewFromUtf8(isolate, " world"))
  };
  // ���ûص�, ����: ��ǰ�����ģ����������������б�
  callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);
}

// �൱���� exports ��������� { hello: hello }
void init(Handle<Object> exports) {
  NODE_SET_METHOD(exports, "hello", hello);
}

// �� export ����¶��ȥ
// ԭ�� `NODE_MODULE(module_name, Initialize)`
NODE_MODULE(test, init);