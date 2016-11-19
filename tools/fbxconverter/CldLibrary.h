/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#ifndef _CLDLIBRARY_H__
#define _CLDLIBRARY_H__

namespace ti
{

	class CldLibrary
	{
	public:
		CldLibrary();
		virtual ~CldLibrary();

		virtual bool ConvertFromFbx(FbxNode* node)	= 0;
		virtual bool Save(ti_vector<ti_string>& string_list)	= 0;

		bool		Loaded;
		TiStream	OutputStream;
	};

};

#endif	//_CLDLIBRARY_H__