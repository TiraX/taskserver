/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.11.13
*/

#ifndef _CLDLIBPARTICLEEFFECT_H__
#define _CLDLIBPARTICLEEFFECT_H__

#include "CldLibrary.h"

namespace ti
{
	//class CldAffector
	//{
	//public:
	//	int			Type;

	//	float		Data[20];

	//	CldAffector()
	//	{
	//		memset(Data, 0, sizeof(Data));
	//	}
	//};

	//class CldEmitter
	//{
	//public:
	//	CldEmitter();
	//	virtual ~CldEmitter();

	//	bool		LoadEmitter(TiXmlElement* emitter_root);
	//	void		LoadAffectors(TiXmlElement* affector_root);

	//	ti_string	Id;
	//	ti_string	ParentName;

	//	EmitterDesc	Desc;
	//	ti_string	Sfx;
	//	ti_string	ParticleTexture;
	//	ti_vector<CldAffector*>	Affectors;
	//};

	//////////////////////////////////////////////////////////////////////////

	class CldLibParticleEffect : public CldLibrary
	{
	public:
		CldLibParticleEffect();
		virtual ~CldLibParticleEffect();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		//		CldEmitter* GetEmitterById(const char* __id);

		//ti_vector< CldEmitter* >	Emitters;

		//ti_string					ExtraModel;
	};

};

#endif	//_CLDLIBPARTICLEEFFECT_H__