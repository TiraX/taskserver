/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibResources.h"
#include "CldLibVisualScene.h"
#include "CldLibTiMaterial.h"
#include "CldLibParticleEffect.h"
#include "CldLibUI.h"

namespace ti
{
	static const char* k_tag_library_images		= "library_images"; 
	static const char* k_tag_image				= "image"; 
	static const char* k_tag_init_from			= "init_from"; 

	CldLibResource::CldLibResource()
	{
	}

	CldLibResource::~CldLibResource()
	{
	}

	bool CldLibResource::ConvertFromFbx(FbxNode* node)
	{
		// do not need resource lib now.
		Loaded		= false;
		return true;
	}



	bool CldLibResource::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_RESOURCES;
		header.Version		= TIRES_VERSION_CHUNK_RES;
		header.ElementCount	= Shaders.size() + Textures.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader) + sizeof(ResourceDesc) * header.ElementCount;

		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));

		for (u32 i = 0 ; i < Shaders.size() ; ++ i)
		{
			ResourceDesc desc;
			desc.Type		= ERT_SHADER;
			desc.Name		= 0;//AddStringToList(Shaders[i], string_list);
			OutputStream.Put(&desc, sizeof(ResourceDesc));
		}
		for (u32 i = 0 ; i < Textures.size() ; ++ i)
		{
			ResourceDesc desc;
			desc.Type		= ERT_TEXTURE;
			desc.Name		= 0;//AddStringToList(Textures[i], string_list);
			OutputStream.Put(&desc, sizeof(ResourceDesc));
		}

		return true;
	}
};