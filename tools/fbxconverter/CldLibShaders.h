/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.26
*/

#ifndef _CLDLIBSHADERS_H__
#define _CLDLIBSHADERS_H__

#include "CldLibrary.h"

namespace ti
{
	//class CldPass
	//{
	//public:
	//	ti_string	Id;
	//	ti_string	Vsh_Filename;
	//	ti_string	Fsh_Filename;

	//	ti_string	MetalVS;
	//	ti_string	MetalFS;

	//	ti_string	VSH;
	//	ti_string	FSH;

	//	TiRenderState	RenderState;
	//};

	//class CldTechnique
	//{
	//public:
	//	ti_string	Id;
	//	ti_vector<CldPass>	Passes;
	//};

	//class CldShader
	//{
	//public:
	//	~CldShader()
	//	{
	//		for (UINT i = 0 ; i < Techniques.size() ; ++ i)
	//		{
	//			delete Techniques[i];
	//			Techniques[i]	= 0;
	//		}
	//	}

	//	ti_string					Id;
	//	bool						IsES3;
	//	bool						IsDynamicLight;
	//	ti_vector<CldTechnique*>	Techniques;
	//};

	////////////////////////////////////////////////////////////////////////////

	class CldLibShaders : public CldLibrary
	{
	public:
		CldLibShaders();
		virtual ~CldLibShaders();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		//ti_string	LoadShaderFile(const ti_string& shader_name);

		//ti_vector<CldShader*>		Shaders;
	};

};

#endif	//_CLDLIBSHADERS_H__