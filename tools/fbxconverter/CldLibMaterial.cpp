/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"
#include "CldLibMaterial.h"

namespace ti
{
	//static const char* k_tag_library_materials	= "library_materials"; 
	//static const char* k_tag_material			= "material"; 
	//static const char* k_tag_library_effects	= "library_effects"; 
	//static const char* k_tag_effect				= "effect"; 
	//static const char* k_tag_instance_effect	= "instance_effect"; 
	//static const char* k_tag_profile_COMMON		= "profile_COMMON";  
	//static const char* k_tag_newparam			= "newparam";  
	//static const char* k_tag_surface			= "surface"; 
	//static const char* k_tag_init_from			= "init_from"; 
	//static const char* k_tag_sampler2D			= "sampler2D"; 
	//static const char* k_tag_source				= "source";
	//static const char* k_tag_technique			= "technique";
	//static const char* k_tag_blinn				= "blinn";
	//static const char* k_tag_extra				= "extra";
	//static const char* k_tag_diffuse			= "diffuse";
	//static const char* k_tag_specular			= "specular";
	//static const char* k_tag_bump				= "bump";
	//static const char* k_tag_texture			= "texture";
	//static const char* k_attr_texture			= "texture";

	//////////////////////////////////////////////////////////////////////////

	CldMaterial::CldMaterial()
	{
	}

	CldMaterial::~CldMaterial()
	{
	}

	void CldMaterial::LoadMaterial(FbxMesh* mesh)
	{

	}

	//ti_string CldMaterial::GetImageIdFromSampler(TiXmlElement* profile_COMMON, const ti_string& sampler_id)
	//{
	//	ti_string surface_id;
	//	ti_string image_id;
	//	// search surface_id first
	//	TiXmlElement* newparam		= profile_COMMON->FirstChildElement(k_tag_newparam);
	//	while (newparam)
	//	{
	//		ti_string sid			= newparam->Attribute(k_attr_sid);
	//		if (sid == sampler_id)
	//		{
	//			TiXmlElement* sampler2D
	//								= newparam->FirstChildElement(k_tag_sampler2D);
	//			TI_ASSERT(sampler2D);
	//			TiXmlElement* source
	//								= sampler2D->FirstChildElement(k_tag_source);
	//			TI_ASSERT(source);
	//			surface_id			= source->FirstChild()->ToText()->Value();

	//			break;
	//		}
	//		newparam				= newparam->NextSiblingElement(k_tag_newparam);
	//	}
	//	TI_ASSERT(surface_id != "");

	//	newparam					= profile_COMMON->FirstChildElement(k_tag_newparam);
	//	while (newparam)
	//	{
	//		ti_string sid			= newparam->Attribute(k_attr_sid);
	//		if (sid == surface_id)
	//		{
	//			TiXmlElement* surface
	//								= newparam->FirstChildElement(k_tag_surface);
	//			TI_ASSERT(surface);
	//			TiXmlElement* init_from
	//								= surface->FirstChildElement(k_tag_init_from);
	//			TI_ASSERT(init_from);
	//			image_id			= init_from->FirstChild()->ToText()->Value();

	//			break;
	//		}
	//		newparam				= newparam->NextSiblingElement(k_tag_newparam);
	//	}
	//	TI_ASSERT(image_id != "");

	//	return image_id;
	//}

	//void CldMaterial::LoadChannelTextures(TiXmlElement* effect_root)
	//{
	//	TiXmlElement* texture;
	//	ti_string sampler_id;

	//	TiXmlElement* profile_COMMON	= effect_root->FirstChildElement(k_tag_profile_COMMON);
	//	TI_ASSERT(profile_COMMON);
	//	TiXmlElement* technique			= profile_COMMON->FirstChildElement(k_tag_technique);
	//	TI_ASSERT(technique);
	//	TiXmlElement* blinn				= technique->FirstChildElement(k_tag_blinn);
	//	if (blinn)
	//	{
	//		// find diffuse texture
	//		TiXmlElement* diffuse		= blinn->FirstChildElement(k_tag_diffuse);
	//		TI_ASSERT(diffuse);
	//		texture						= diffuse->FirstChildElement(k_tag_texture);
	//		if (texture)
	//		{
	//			sampler_id				= texture->Attribute(k_attr_texture);
	//			ChannelTextureIds[E_CHANNEL_DIFFUSE]
	//									= GetImageIdFromSampler(profile_COMMON, sampler_id);
	//		}
	//		// find specular texture
	//		TiXmlElement* specular		= blinn->FirstChildElement(k_tag_specular);
	//		if (specular)
	//		{
	//			texture						= specular->FirstChildElement(k_tag_texture);
	//			if (texture)
	//			{
	//				sampler_id				= texture->Attribute(k_attr_texture);
	//				ChannelTextureIds[E_CHANNEL_SPECULAR]
	//				= GetImageIdFromSampler(profile_COMMON, sampler_id);
	//			}
	//		}
	//	}
	//	TiXmlElement* extra				= technique->FirstChildElement(k_tag_extra);
	//	if (extra)
	//	{
	//		TiXmlElement* extra_tech	= extra->FirstChildElement(k_tag_technique);
	//		if (extra_tech)
	//		{
	//			TiXmlElement* bump		= extra_tech->FirstChildElement(k_tag_bump);
	//			if (bump)
	//			{
	//				texture				= bump->FirstChildElement(k_tag_texture);
	//				if (texture)
	//				{
	//					sampler_id				= texture->Attribute(k_attr_texture);
	//					ChannelTextureIds[E_CHANNEL_BUMP]
	//					= GetImageIdFromSampler(profile_COMMON, sampler_id);
	//				}
	//			}
	//		}
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////

	CldLibMaterial::CldLibMaterial()
	{
	}

	CldLibMaterial::~CldLibMaterial()
	{
		// remove all geometries
		for (unsigned int i = 0 ; i < Materials.size() ; ++ i)
		{
			delete Materials[i];
		}
		Materials.clear();
	}

	//TiXmlElement* CldLibMaterial::GetEffectInstance(TiXmlElement* effect_lib_root, const ti_string& effect_id)
	//{
	//	// load materials
	//	TiXmlElement* cldEffect			= effect_lib_root->FirstChildElement(k_tag_effect);
	//	while (cldEffect)
	//	{
	//		ti_string eid				= cldEffect->Attribute(k_attr_id);
	//		if (eid == effect_id)
	//		{
	//			return cldEffect;
	//		}
	//		cldEffect					= cldEffect->NextSiblingElement(k_tag_effect);
	//	}

	//	return NULL;
	//}

	bool CldLibMaterial::ConvertFromFbx(FbxNode* node)
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
			CldMaterial* material = new CldMaterial;
			material->Id = fbx_node->GetNameOnly().Buffer();
			material->Id += "-material";

			material->LoadMaterial(fbx_mesh);

			Materials.push_back(material);
		}

		Loaded	= true;
		return true;
	}

	bool CldLibMaterial::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_MATERIAL;
		header.Version		= TIRES_VERSION_CHUNK_MTRL;
		header.ElementCount	= Materials.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader);

		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));

		return true;
	}

	CldMaterial* CldLibMaterial::GetMaterialById(const ti_string& material_id)
	{
		ti_vector< CldMaterial* >::iterator it;
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