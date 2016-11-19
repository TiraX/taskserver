/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibImages.h"

namespace ti
{
	static const char* k_tag_library_images		= "library_images"; 
	static const char* k_tag_image				= "image"; 
	static const char* k_tag_init_from			= "init_from"; 

	CldLibImage::CldLibImage()
	{
	}

	CldLibImage::~CldLibImage()
	{
		// remove all images
		for (unsigned int i = 0 ; i < Images.size() ; ++ i)
		{
			delete Images[i];
		}
		Images.clear();
	}

	bool CldLibImage::ConvertFromFbx(FbxNode* node)
	{
	//	TiXmlElement* lib_images	= colladaRoot->FirstChildElement(k_tag_library_images);
	//	if (!lib_images)
	//	{
	//		return false;
	//	}

	//	// load geometries
	//	TiXmlElement* cldImage		= lib_images->FirstChildElement(k_tag_image);
	//	while (cldImage)
	//	{
	//		CldImage* image				= new CldImage;
	//		image->Id					= cldImage->Attribute(k_attr_id);
	//		image->Name					= cldImage->Attribute(k_attr_name);

	//		TiXmlElement* cld_init_from	= cldImage->FirstChildElement(k_tag_init_from);
	//		TI_ASSERT(cld_init_from);
	//		image->File					= cld_init_from->FirstChild()->ToText()->Value();

	//		const TiColladaConfig& config
	//									= TiCollada::Get()->Config;
	//		if (config.TexturePath != "")
	//		{
	//			//size_t pos				= image->File.rfind("/");
	//			size_t pos				= image->File.find(config.TexturePath);
	//			if (pos != ti_string::npos)
	//			{
	//				pos					+= config.TexturePath.length();
	//				std::string s;
	//				image->File			= config.TexturePath + "/" + image->File.substr(pos + 1);
	//			}
	//			else
	//			{
	//				image->File			= config.TexturePath + "/" + image->File;
	//			}
	//		}

	//		Images.push_back(image);
	//		cldImage					= cldImage->NextSiblingElement(k_tag_image);
	//	}

		Loaded	= true;
		return true;
	}

	bool CldLibImage::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_IMAGES;
		header.Version		= TIRES_VERSION_CHUNK_IMAG;
		header.ElementCount	= Images.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader) + sizeof(int) * Images.size();

		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));

		for (unsigned int i = 0 ; i < Images.size() ; ++ i)
		{
			int str_index	= 0;//AddStringToList(Images[i]->File, string_list);
			OutputStream.Put(&str_index, sizeof(int));
		}

		return true;
	}

	CldImage* CldLibImage::GetImageById(const ti_string& image_id)
	{
		ti_vector<CldImage* >::iterator it;
		for ( it = Images.begin() ; it != Images.end() ; ++ it)
		{
			if ( (*it)->Id == image_id )
			{
				return *it;
			}
		}

		return NULL;
	}
};