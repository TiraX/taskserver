/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.9.14
*/

#ifndef _CLDLIBIMAGES_H__
#define _CLDLIBIMAGES_H__

#include "CldLibrary.h"

namespace ti
{
	class CldImage
	{
	public:
		ti_string	Id;
		ti_string	Name;

		ti_string	File;
	};

	//////////////////////////////////////////////////////////////////////////

	class CldLibImage : public CldLibrary
	{
	public:
		CldLibImage();
		virtual ~CldLibImage();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		CldImage*		GetImageById(const ti_string& image_id);

		ti_vector< CldImage* >	Images;
	};

};

#endif	//_CLDLIBIMAGES_H__