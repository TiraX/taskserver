/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#ifndef _CLDLIBMATERIAL_H__
#define _CLDLIBMATERIAL_H__

#include "CldLibrary.h"

namespace ti
{
	class CldMaterial
	{
	public:
		enum
		{
			E_CHANNEL_DIFFUSE,
			E_CHANNEL_SPECULAR,
			E_CHANNEL_BUMP,
			E_CHANNEL_RESERVE,

			E_CHANNEL_COUNT,
		};

		CldMaterial();
		virtual ~CldMaterial();

		void		LoadMaterial(FbxMesh* mesh);

		ti_string	Id;
		ti_string	Name;

		ti_string	ChannelTextureIds[E_CHANNEL_COUNT];
	};

	//////////////////////////////////////////////////////////////////////////

	class CldLibMaterial : public CldLibrary
	{
	public:
		CldLibMaterial();
		virtual ~CldLibMaterial();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		CldMaterial*	GetMaterialById(const ti_string& material_id);

		//TiXmlElement*	GetEffectInstance(TiXmlElement* effect_lib_root, const ti_string& effect_id);

		ti_vector< CldMaterial* >	Materials;
	};

};

#endif	//_CLDLIBMATERIAL_H__