/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#ifndef _CLDLIBTIMATERIAL_H__
#define _CLDLIBTIMATERIAL_H__

#include "CldLibrary.h"
//#include "TiShaderProgram.h"

namespace ti
{
	struct UniformDef
	{
		ti_string	Name;
		int			Type;
		union
		{
			float	floatValue[4];
			int		intValue[4];
		};
		ti_string	strValue;
		int			sample;
		int			srgb;

		UniformDef()
			: sample(0)
			, srgb(1)
		{
			memset(floatValue, 0, sizeof(float) * 4);
		}
	};

	class CldTiMaterial
	{
	public:
		CldTiMaterial();
		virtual ~CldTiMaterial();

		void		LoadMaterial(FbxMesh* mesh);

		ti_string	Id;
		ti_string	Shader;
		ti_string	Technique;

		ti_vector<UniformDef>	Uniforms;
		ti_string	BindLights;
		int			Flag;

		//void		Load(TiXmlElement* materialRoot);
	};

	//////////////////////////////////////////////////////////////////////////

	class CldMaterial;
	class CldLibTiMaterial : public CldLibrary
	{
	public:
		CldLibTiMaterial();
		virtual ~CldLibTiMaterial();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

				void ConvertDefaultMaterial(CldMaterial* material, bool is_skin_mesh);

		CldTiMaterial*	GetTiMaterialById(const ti_string& material_id);

		int				TotalSets;
		ti_vector< CldTiMaterial* >	Materials;
	};

};

#endif	//_CLDLIBTIMATERIAL_H__