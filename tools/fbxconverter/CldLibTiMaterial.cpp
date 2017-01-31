/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"
#include "CldLibTiMaterial.h"
#include "CldLibMaterial.h"
#include "CldLibImages.h"
#include "Collada.h"

namespace ti
{
	static const char* k_tag_library_timaterials	= "library_timaterials"; 
	static const char* k_tag_mtrl_set				= "material_set"; 
	static const char* k_tag_timaterial				= "timaterial"; 
	static const char* k_tag_tishader				= "ti_shader"; 
	static const char* k_tag_technique				= "technique";
	static const char* k_attr_src					= "src";
	static const char* k_tag_uniforms				= "uniforms";
	static const char* k_tag_uniform				= "uniform";
	static const char* k_tag_value					= "value";
	static const char* k_attr_sample				= "sample";
	static const char* k_attr_srgb					= "srgb"; 
	static const char* k_tag_flag					= "flag"; 

	static const char* k_uniform_type[] = 
	{

		"float4",	//EUF_VEC4,
		"float3",	//EUF_VEC3,
		"float2",	//EUF_VEC2,
		"float4x4",	//EUF_MAT4,
		"float",	//EUF_FLOAT,
		"int",		//EUF_INT,
		"sampler2d",//EUF_SAMPLER2D,
		"samplerCube",//EUF_SAMPLERCUBE,
	};

	int GetUniformType(const char* name)
	{
		for (int i = 0 ; i < 8 ; ++ i)
		{
			if (strcmp(name, k_uniform_type[i]) == 0)
			{
				return i;
			}
		}

		return 0;
	}
	//////////////////////////////////////////////////////////////////////////

	CldTiMaterial::CldTiMaterial()
		: Flag(0)
	{
	}

	CldTiMaterial::~CldTiMaterial()
	{
	}

	void CldTiMaterial::LoadMaterial(FbxMesh* mesh)
	{
		// set to default pbr material
		Shader = "pbr";
		Technique = "normal";
		Flag = 1;	// pbr flag to bind env cube texture
	}

	//////////////////////////////////////////////////////////////////////////

	CldLibTiMaterial::CldLibTiMaterial()
		: TotalSets(1)
	{
	}

	CldLibTiMaterial::~CldLibTiMaterial()
	{
		// remove all geometries
		for (unsigned int i = 0 ; i < Materials.size() ; ++ i)
		{
			delete Materials[i];
		}
		Materials.clear();
	}

	void CldLibTiMaterial::ConvertDefaultMaterial(CldMaterial* material, bool is_skin_mesh)
	{
		if (GetTiMaterialById(material->Id) == NULL)
		{
			CldLibImage* libImages			= (CldLibImage*)TiCollada::Get()->ColladaLibraries[ECL_IMAGES];
			CldTiMaterial* ti_material		= new CldTiMaterial;

			ti_material->Id					= material->Id;
			ti_material->Shader				= is_skin_mesh ? "LibShader/meshskin_solid.btish" : "LibShader/mesh_solid.btish";
			ti_material->Technique			= "normal";

			UniformDef uniform;
			uniform.Name					= "diffusemap";
			uniform.Type					= EUF_SAMPLER2D;
			CldImage* image					= libImages->GetImageById(material->ChannelTextureIds[CldMaterial::E_CHANNEL_DIFFUSE]);
			if (image)
				uniform.strValue			= image->File;
			ti_material->Uniforms.push_back(uniform);

			Materials.push_back(ti_material);

			TotalSets						= 1;
			Loaded							= true;
		}
	}

	bool CldLibTiMaterial::ConvertFromFbx(FbxNode* node)
	{
		// gather all mesh nodes from fbx
		ti_vector<FbxNode*> nodes;
		GetFbxNodesByType(node, FbxNodeAttribute::eMesh, nodes);

		// remove all materials
		for (unsigned int i = 0 ; i < Materials.size() ; ++ i)
		{
			delete Materials[i];
		}
		Materials.clear();

		// load all meshes
		for (u32 i = 0 ; i < nodes.size() ; ++ i)
		{
			FbxNode* fbx_node = nodes[i];
			FbxMesh* fbx_mesh = fbx_node->GetMesh();
			CldTiMaterial* material = new CldTiMaterial;
			material->Id = fbx_node->GetNameOnly().Buffer();
			material->Id += "-material";

			material->LoadMaterial(fbx_mesh);

			Materials.push_back(material);
		}
		TotalSets = 1;	// only support 1 sets now.

		Loaded	= true;
		return true;
	}

	bool CldLibTiMaterial::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_TIMATERIAL;
		header.Version		= TIRES_VERSION_CHUNK_TIMT;
		header.ElementCount	= Materials.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader);

		TiStream ss;
		ss.Put(&TotalSets, sizeof(int));

		for (u32 m = 0 ; m < Materials.size() ; ++m)
		{
			CldTiMaterial* mtrl	= Materials[m];
			MtrlDesc desc;
			desc.StrIndex_Id		= AddStringToList(mtrl->Id, string_list);
			desc.StrIndex_Shader	= AddStringToList(mtrl->Shader, string_list);
			desc.StrIndex_Tech		= AddStringToList(mtrl->Technique, string_list);
			desc.UniformCount		= mtrl->Uniforms.size();
			desc.Flag				= mtrl->Flag;
			if (mtrl->BindLights != "")
				desc.StrIndex_BindLights = 0;//AddStringToList(mtrl->BindLights, string_list);
			else
				desc.StrIndex_BindLights = -1;

			ss.Put(&desc, sizeof(MtrlDesc));
		}
		for (u32 m = 0 ; m < Materials.size() ; ++m)
		{
			CldTiMaterial* mtrl		= Materials[m];
			MtrlDesc desc;
			desc.UniformCount		= mtrl->Uniforms.size();

			// uniforms
			for (int u = 0 ; u < desc.UniformCount ; ++ u)
			{
				const UniformDef& uniform	= mtrl->Uniforms[u];
				UniformDesc uDesc;
				uDesc.StrIndex_Name			= 0;//AddStringToList(uniform.Name, string_list);
				uDesc.Type					= uniform.Type;
				uDesc.Parameters[0]			= uniform.sample;
				uDesc.Parameters[1]			= uniform.srgb;
				uDesc.Parameters[2]			= 0;
				uDesc.Parameters[3]			= 0;
				if (uDesc.Type == EUF_SAMPLER2D)
				{
					uDesc.intValue[0]		= 0;//AddStringToList(uniform.strValue, string_list);
				}
				else if (uDesc.Type == EUF_SAMPLERCUBE)
				{
					uDesc.intValue[0]		= 0;//AddStringToList(uniform.strValue, string_list);
				}
				else
				{
					memcpy(uDesc.floatValue, uniform.floatValue, sizeof(float) * 4);
				}
				ss.Put(&uDesc, sizeof(UniformDesc));
			}
		}

		header.ChunkSize	+= ss.GetLength();
		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		OutputStream.Put(ss.GetBuffer(), ss.GetLength());

		return true;
	}

	CldTiMaterial* CldLibTiMaterial::GetTiMaterialById(const ti_string& material_id)
	{
		ti_vector< CldTiMaterial* >::iterator it;
		for ( it = Materials.begin() ; it != Materials.end() ; ++ it)
		{
			if ( (*it)->Id == material_id )
			{
				return *it;
			}
		}

		return NULL;
	}
};