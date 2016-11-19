/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#ifndef _CLDLIBRESOURCES_H__
#define _CLDLIBRESOURCES_H__

#include "CldLibrary.h"

namespace ti
{
	class CldLibResource : public CldLibrary
	{
	public:
		CldLibResource();
		virtual ~CldLibResource();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		ti_vector<ti_string>	Shaders;
		ti_vector<ti_string>	Textures;
	};

};

#endif	//_CLDLIBRESOURCES_H__