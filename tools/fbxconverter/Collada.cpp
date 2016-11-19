/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"
#include "Collada.h"
#include <stdarg.h>
#include "fbxasset.h"

void GetFbxNodesByType(FbxNode* root, int type, ti_vector<FbxNode*>& nodes) {

	if (root->GetNodeAttribute() && root->GetNodeAttribute()->GetAttributeType() == type)
	{
		nodes.push_back(root);
	}

	for(int i = 0 ; i < root->GetChildCount() ; ++i) 
	{ 
		GetFbxNodesByType(root->GetChild(i), type, nodes); 
	} 
}

void SaveStringList(const ti_vector<ti_string>& string_list, TiStream& stream)
{
	char zero[4] = {0};

	int* string_offsets = ti_new int[string_list.size()];
	int offset = 0;
	for (int i = 0 ; i < (int)string_list.size() ; ++ i)
	{
		const ti_string& s = string_list[i];
		offset += ((s.size() + 4) & ~3);
		string_offsets[i] = offset;
	}

	stream.Put(string_offsets, string_list.size() * sizeof(int));
	for (int i = 0 ; i < (int)string_list.size() ; ++ i)
	{
		const ti_string& s = string_list[i];
		int len = ((s.size() + 4) & ~3);
		int real_len = s.size();
		stream.Put(s.c_str(), real_len);
		stream.Put(zero, len - real_len);;
	}
	ti_delete[] string_offsets;
}

int AddStringToList(const ti_string& s, ti_vector<ti_string>& string_list)
{
	int i;
	int size	= (int)string_list.size();
	for (i = 0 ; i < size ; ++ i)
	{
		if (string_list[i] == s)
		{
			return i;
		}
	}
	string_list.push_back(s);
	return size;
}

namespace ti
{
	void TiColladaConfig::AddLog(const char* format, ...)
	{
		char tmp[1024];
		va_list marker;
		va_start(marker, format);
		vsprintf(tmp, format, marker);
		va_end(marker);

		Log			+= tmp;
		Log			+= "\n";
	}


	static const char* k_tag_collada	= "COLLADA";
	static const char* k_tag_asset		= "asset";
	static const char* k_tag_unit		= "unit";
	static const char* k_attr_meter		= "meter";

	TiCollada* TiCollada::s_instance	= NULL;

	TiCollada* TiCollada::Get()
	{
		return s_instance;
	}

	TiCollada::TiCollada(const char* collada_file_name)
		: ColladaFilename(collada_file_name)
	{
		ColladaLibraries[ECL_GEOMETRY]			= new CldLibGeometry;
		ColladaLibraries[ECL_VISUALSCENE]		= new CldLibVisualScene;
		ColladaLibraries[ECL_SHADERS]			= NULL;//new CldLibShaders;

		ColladaLibraries[ECL_IMAGES]			= NULL;//new CldLibImage;
		ColladaLibraries[ECL_MATERIALS]			= NULL;//new CldLibMaterial;

		ColladaLibraries[ECL_ANIMATIONS]		= new CldLibAnimation;
		ColladaLibraries[ECL_CONTROLLERS]		= new CldLibController;

		ColladaLibraries[ECL_PARTICLEEFFECT]	= NULL;//new CldLibParticleEffect;
		ColladaLibraries[ECL_TIMATERIAL]		= new CldLibTiMaterial;

		ColladaLibraries[ECL_UI]				= NULL;//new CldLibUI;

		ColladaLibraries[ECL_RESOURCES]			= NULL;//new CldLibResource;

		s_instance	= this;
	}

	TiCollada::~TiCollada(void)
	{
		for (int i = 0 ; i < ECL_COUNT ; ++ i)
		{
			delete ColladaLibraries[i];
		}

		s_instance	= NULL;
	}

	void TiCollada::Reset()
	{

	}

	bool TiCollada::ConvertFrom(FbxAsset* asset)
	{

		for (int l = 0 ; l < ECL_COUNT ; ++ l)
		{
			if (ColladaLibraries[l] != NULL)
			{
				ColladaLibraries[l]->ConvertFromFbx(asset->GetRoot());
			}
		}
		
		return true;
	}

	bool TiCollada::Save(TiStream& fileStream)
	{
		TiResfileHeader fileHeader;
		ti_vector< ti_string > string_list;
		fileHeader.ID			= TIRES_ID_RESFILE;
		fileHeader.Version		= TIRES_VERSION_MAINFILE;
		fileHeader.ChunkCount	= GetLoadedChunkCount();
		fileHeader.FileSize		= sizeof(TiResfileHeader);

		// save libraries
		for (int l = 0 ; l < ECL_COUNT ; ++ l)
		{
			if (ColladaLibraries[l] && ColladaLibraries[l]->Loaded)
			{
				ColladaLibraries[l]->Save(string_list);
				fileHeader.FileSize	+= ColladaLibraries[l]->OutputStream.GetLength();
			}
		}

		fileHeader.StringCount	= string_list.size();
		fileHeader.StringOffset	= fileHeader.FileSize;

		// stream string list
		TiStream string_stream;
		char zero[4] = {0};

		int* string_offsets = new int[fileHeader.StringCount];
		int offset = 0;
		for (int i = 0 ; i < fileHeader.StringCount ; ++ i)
		{
			const ti_string& s = string_list[i];
			offset += ((s.size() + 4) & ~3);
			string_offsets[i] = offset;
		}

		string_stream.Put(string_offsets, fileHeader.StringCount * sizeof(int));
		for (int i = 0 ; i < fileHeader.StringCount ; ++ i)
		{
			const std::string& s = string_list[i];
			int len = ((s.size() + 4) & ~3);
			int real_len = s.size();
			string_stream.Put(s.c_str(), real_len);
			string_stream.Put(zero, len - real_len);;
		}
		delete[] string_offsets;
		fileHeader.FileSize	+= string_stream.GetLength();


		// write header
		fileStream.Put(&fileHeader, sizeof(TiResfileHeader));

		// write libraries
		for (int l = 0 ; l < ECL_COUNT ; ++ l)
		{
			if (ColladaLibraries[l] && ColladaLibraries[l]->Loaded)
			{
				fileStream.Put( ColladaLibraries[l]->OutputStream.GetBuffer(),
								ColladaLibraries[l]->OutputStream.GetLength());
			}
		}

		// write string list
		fileStream.Put(string_stream.GetBuffer(), string_stream.GetLength());
		return true;
	}

	int TiCollada::GetLoadedChunkCount()
	{
		int count = 0;
		for (int l = 0 ; l < ECL_COUNT ; ++ l)
		{
			if (ColladaLibraries[l] && ColladaLibraries[l]->Loaded)
				++ count;
		}
		return count;
	}
};