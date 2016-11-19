/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.10.19
*/

#ifndef _CLDLIBCONTROLLER_H__
#define _CLDLIBCONTROLLER_H__

#include "CldLibrary.h"

namespace ti
{
	enum
	{
		CONTROLLER_SKIN,
		CONTROLLER_MORPH,
	};

	//class CldController
	//{
	//public:
	//	CldController(int type);
	//	virtual ~CldController();

	//	int						Type;

	//	Source*					GetSourceById(const char* source_id);
	//	virtual bool			Save(TiStream& stream, ti_vector<ti_string>& string_list) = 0;

	//	ti_string				Id;
	//	ti_string				TargetSource;
	//	ti_vector< Source* >	Sources;
	//};
	//
	//class CldJoint
	//{
	//public:
	//	bool				Load(TiXmlElement* joint_root);
	//	ti_vector<Input>	Inputs;
	//	ti_string			GetSourceIdBySemantic(const ti_string& s);
	//};

	//class CldVertexWeight
	//{
	//public:
	//	int					Count;
	//	ti_vector<Input>	Inputs;
	//	ti_vector<int>		BoneCountArray;
	//	ti_vector<int>		BoneWeightIndexArray;
	//	bool				Load(TiXmlElement* vweight_root);
	//	ti_string			GetSourceIdBySemantic(const ti_string& s);
	//};

	//struct VertexBoneInfo
	//{
	//	int					BoneIndex;
	//	float				BoneWeight;
	//};
	//struct VertexSkinInfo
	//{
	//	int							BoneCount;
	//	ti_vector<VertexBoneInfo>	BoneInfo;

	//	VertexSkinInfo()
	//	{
	//		BoneCount		= 0;
	//	}
	//};

	//class CldControllerSkin : public CldController
	//{
	//public:
	//	CldControllerSkin()
	//		: CldController(CONTROLLER_SKIN)
	//		, SkinInfo(NULL)
	//	{}
	//	~CldControllerSkin()
	//	{
	//		SAFE_DELETE_ARRAY(SkinInfo);
	//	}
	//	ti_vector<float>	BindShapeMatrix;
	//	CldJoint			Joint;
	//	CldVertexWeight		VertexWeight;
	//	VertexSkinInfo*		SkinInfo;
	//	bool				LoadSkinController(TiXmlElement* skin_root);
	//	bool				Convert();
	//	virtual bool		Save(TiStream& stream, ti_vector<ti_string>& string_list);
	//};

	////////////////////////////////////////////////////////////////////////////

	//struct MorphTarget
	//{
	//	Input				target;
	//	Input				weight;
	//};

	//class CldControllerMorph : public CldController
	//{
	//public:
	//	CldControllerMorph()
	//		: CldController(CONTROLLER_MORPH)
	//	{}
	//	~CldControllerMorph()
	//	{
	//		for (unsigned int i = 0 ; i < Sources.size() ; ++ i)
	//		{
	//			delete Sources[i];
	//		}
	//		Sources.clear();
	//	}
	//	bool				LoadMorphController(TiXmlElement* morph_root);
	//	bool				Convert();
	//	virtual bool		Save(TiStream& stream, ti_vector<ti_string>& string_list);

	//	MorphTarget				Targets;

	//	struct MorphInfo
	//	{
	//		ti_string		target;
	//		float			weight;
	//	};
	//	ti_vector<MorphInfo>	MorphInfos;
	//};


	//////////////////////////////////////////////////////////////////////////

	class CldLibController : public CldLibrary
	{
	public:
		CldLibController();
		virtual ~CldLibController();

		//CldController*	GetControllerByTargetSource(const ti_string& target_source);
		//CldController*	GetControllerById(const ti_string& target_source);

		bool			IsMorphTarget(const ti_string& mesh_id);

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		//ti_vector< CldController* >	Controllers;
	};

};

#endif	//_CLDLIBCONTROLLER_H__