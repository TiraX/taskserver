#include <node.h>
#include <v8.h>
#include "stdafx.h"
#include "fbxasset.h"
#include "Collada.h"
#include <stdarg.h>

using namespace v8;

void ___Log(const char* format, ...)
{
}

void convert(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = Isolate::GetCurrent();
	HandleScope scope(isolate);

	if (args.Length() < 2 || !args[0]->IsString() || !args[1]->IsString()) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong arguments")));
		return;
	}

	v8::String::Utf8Value arg_src(args[0]->ToString());
	v8::String::Utf8Value arg_dst(args[1]->ToString());

	std::string	source_file_name(*arg_src);
	std::string	dest_file_name(*arg_dst);

	FbxAsset::InitSDK();
	{
		FbxAsset* asset = new FbxAsset(source_file_name);
		asset->Load();

		TiStream filestream;
		TiCollada	colladaFile(source_file_name.c_str());
		colladaFile.Config.InputFilename = source_file_name;
		colladaFile.Config.OutputFilename = dest_file_name;

		if (colladaFile.ConvertFrom(asset))
		{
			colladaFile.Save(filestream);

			// write to file
			TiFile f;
			if (f.Open(dest_file_name, EFA_CREATEWRITE))
			{
				TiLodHeader lod_header;
				const int lods = 1;
				lod_header.Lods = lods;
				TiLodDesc* desc = ti_new TiLodDesc[lods];
				desc[0].Start = sizeof(TiLodHeader) + sizeof(TiLodDesc) * lods;
				desc[0].Length = filestream.GetLength();
				f.Write(&lod_header, sizeof(TiLodHeader));
				f.Write(desc, sizeof(TiLodDesc) * lods);
				f.Write(filestream.GetBuffer(), filestream.GetLength());
				ti_delete[] desc;
				f.Close();
			}
		}

		delete asset;
	}
	FbxAsset::DestroySDK();

	// last parameter is callback function
	Local<Value> last_arg = args[args.Length() - 1];
	if (last_arg->IsFunction())
	{
		Local<Function> callback = Local<Function>::Cast(args[args.Length() - 1]);
		Local<Value> argv[1] = {
			String::NewFromUtf8(isolate, "success")
		};
		callback->Call(isolate->GetCurrentContext()->Global(), 1, argv);
	}
}

void init(Handle<Object> exports) {
	NODE_SET_METHOD(exports, "convert", convert);
}

NODE_MODULE(fbxconverter, init);