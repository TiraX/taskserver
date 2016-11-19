/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.10.19
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibAnimation.h"

namespace ti
{

#define ENABLE_MERGE_AND_SPLIT	(1)

	static const char* k_tag_libanimations		= "library_animations"; 
	static const char* k_tag_animation			= "animation";
	static const char* k_tag_sampler			= "sampler";
	static const char* k_tag_channel			= "channel";

	//bool Sampler::Load(TiXmlElement* sampler_root)
	//{
	//	Id						= sampler_root->Attribute(k_attr_id);
	//	Inputs.clear();

	//	// load inputs
	//	TiXmlElement* cld_input	= sampler_root->FirstChildElement(k_tag_input);
	//	while (cld_input)
	//	{
	//		Input input;
	//		input.Semantic		= cld_input->Attribute(k_attr_semantic);
	//		input.Source		= cld_input->Attribute(k_attr_source);

	//		Inputs.push_back(input);
	//		cld_input			= cld_input->NextSiblingElement(k_tag_input);
	//	}

	//	return true;
	//}

	//////////////////////////////////////////////////////////////////////////

	CldAnimation::CldAnimation()
		: MorphAnim(false)
	{
	}

	CldAnimation::~CldAnimation()
	{
		//for (unsigned int i = 0 ; i < Sources.size() ; ++ i)
		//{
		//	delete Sources[i];
		//}
		//Sources.clear();
		TI_ASSERT(SubAnims.size() == 0);
	}

	//Source* CldAnimation::GetSourceById(const char* source_id)
	//{
	//	for (u32 i = 0 ; i < Sources.size() ; ++ i)
	//	{
	//		Source* s	= Sources[i];
	//		if (s->Id == source_id)
	//		{
	//			return s;
	//		}
	//	}
	//	return NULL;
	//}

	//static const char* k_semantic_names[CldAnimation::SEMANTIC_COUNT] =
	//{
	//	"INPUT",
	//	"OUTPUT",
	//	"INTERPOLATION",
	//	"IN_TANGENT",
	//	"OUT_TANGENT",
	//};

	//Source* CldAnimation::GetSourceBySemantic(int semantic)
	//{
	//	TI_ASSERT(semantic >= 0 && semantic < SEMANTIC_COUNT);

	//	// search in samplers
	//	for (u32 i = 0 ; i < _Sampler.Inputs.size() ; ++ i)
	//	{
	//		const Input& input	= _Sampler.Inputs[i];
	//		if (input.Semantic == k_semantic_names[semantic])
	//		{
	//			return GetSourceById(input.Source.c_str() + 1);
	//		}
	//	}
	//	return NULL;
	//}

	//bool CldAnimation::LoadAnimation(TiXmlElement *animation_root)
	//{
	//	// load sources
	//	TiXmlElement* cldSource		= animation_root->FirstChildElement(k_tag_source);
	//	while (cldSource)
	//	{
	//		Source* source			= new Source;
	//		source->Load(cldSource);

	//		Sources.push_back(source);
	//		cldSource				= cldSource->NextSiblingElement(k_tag_source);
	//	}

	//	// load sampler
	//	ti_vector<Sampler> samplers;
	//	TiXmlElement* cldSampler	= animation_root->FirstChildElement(k_tag_sampler);
	//	while (cldSampler)
	//	{
	//		Sampler s;
	//		s.Load(cldSampler);
	//		samplers.push_back(s);
	//		cldSampler				= cldSampler->NextSiblingElement(k_tag_sampler);
	//	}

	//	// load channels
	//	ti_vector<Channel>	channels;
	//	TiXmlElement* cldChannel	= animation_root->FirstChildElement(k_tag_channel);
	//	while (cldChannel)
	//	{
	//		Channel c;
	//		c._Source				= cldChannel->Attribute(k_attr_source);
	//		ti_string target		= cldChannel->Attribute(k_attr_target);
	//		TI_ASSERT (target != "");
	//		u32 pos					= target.find('/');
	//		if (pos != ti_string::npos)
	//		{
	//			c._TargetNode		= target.substr(0, pos);
	//			c._TargetAnim		= target.substr(pos + 1);
	//		}
	//		else
	//		{
	//			// morph animation don't follow 'target/animation' format
	//			// it follow format 'morph_controller-morph_weights(weight_index)'
	//			pos					= target.find('(');
	//			TI_ASSERT(pos != ti_string::npos);
	//			c._TargetNode		= target.substr(0, pos);
	//			u32 pos1			= target.find(')');
	//			TI_ASSERT(pos1 != ti_string::npos);
	//			c._TargetAnim		= target.substr(pos + 1, pos1 - pos - 1);

	//			MorphAnim			= true;
	//		}
	//		channels.push_back(c);
	//		cldChannel				= cldChannel->NextSiblingElement(k_tag_channel);
	//	}

	//	TI_ASSERT(samplers.size() > 0);
	//	TI_ASSERT(channels.size() > 0 &&
	//			  channels.size() == samplers.size());
	//	if (samplers.size() == 1)
	//	{
	//		// animation has only 1 sampler, load to current anim
	//		_Sampler				= samplers[0];
	//		_Channel				= channels[0];
	//	}
	//	else
	//	{
	//		// animation has multi samplers, split into sub anims
	//		for (u32 s = 0 ; s < samplers.size() ; ++ s)
	//		{
	//			CldAnimation* anim			= new CldAnimation;
	//			anim->Id					= Id + "-";
	//			anim->Id					+= '0'+s;
	//			anim->_Sampler				= samplers[s];
	//			anim->_Channel				= channels[s];

	//			const Sampler& sampler		= samplers[s];
	//			// get useful sources
	//			for (u32 i = 0 ; i < sampler.Inputs.size() ; ++ i)
	//			{
	//				const Input& ipt		= sampler.Inputs[i];
	//				Source* useful_source	= GetSourceById(ipt.Source.c_str() + 1);
	//				TI_ASSERT(useful_source);
	//				anim->Sources.push_back(useful_source);
	//			}

	//			SubAnims.push_back(anim);
	//		}
	//		Sources.clear();
	//	}


	//	TiColladaConfig& config		= TiCollada::Get()->Config;
	//	if (config.OptimizeSkinmesh)
	//	{
	//		if (_Channel._TargetNode.find("Footsteps-node") != ti_string::npos)
	//		{
	//			return false;
	//		}
	//	}

	//	// record keys
	//	//GatherKeys();

	//	return true;
	//}

	void CldAnimation::GatherKeys()
	{
		//Keys.clear();

		//Source* s_time				= GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT);
		//Source* s_output			= GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
		//TI_ASSERT(s_time && s_output);
		//TI_ASSERT(s_time->_Accessor.Count == s_output->_Accessor.Count);
		//bool isTranslation			= _Channel._TargetAnim == "translation";
		//int key_count				= s_time->_Accessor.Count;
		//_key_frame key;
		//const float unit			= TiCollada::Get()->Config.UnitParam;
		//for (int k = 0 ; k < key_count ; ++ k)
		//{
		//	key.input				= s_time->ArrayFloat[k];
		//	TI_ASSERT(s_output->_Accessor.Stride <= 16);
		//	for (int stride = 0 ; stride < s_output->_Accessor.Stride ; ++ stride)
		//	{
		//		key.output[stride]	= s_output->ArrayFloat[k * s_output->_Accessor.Stride + stride];
		//		if (isTranslation)
		//		{
		//			key.output[stride]	*= unit;
		//		}
		//	}
		//	Keys.push_back(key);
		//}
	}

	//bool CldAnimation::IsUnanimous()
	//{
	//	// if KeepAllAnimKeys return false directly
	//	TiColladaConfig& config		= TiCollada::Get()->Config;
	//	if (config.KeepAllAnimKeys)
	//		return false;

	//	Source* source_output		= GetSourceBySemantic(SEMANTIC_OUTPUT);
	//	TI_ASSERT(source_output);
	//	const int stride			= source_output->_Accessor.Stride;
	//	for (int i = 1 ; i < source_output->_Accessor.Count ; ++ i)
	//	{
	//		for (int s = 0 ; s < stride ; ++ s)
	//		{
	//			if (!equals(source_output->ArrayFloat[i * stride + s] , source_output->ArrayFloat[s]))
	//			{
	//				return false;
	//			}
	//		}
	//	}
	//	return true;
	//}

	//////////////////////////////////////////////////////////////////////////

	CldLibAnimation::CldLibAnimation()
	{
	}

	CldLibAnimation::~CldLibAnimation()
	{
		// remove all animations
		for (unsigned int i = 0 ; i < Animations.size() ; ++ i)
		{
			delete Animations[i];
		}
		Animations.clear();
		for (unsigned int i = 0 ; i < OriginalAnimations.size() ; ++ i)
		{
			delete OriginalAnimations[i];
		}
		OriginalAnimations.clear();
	}

	bool CldLibAnimation::ConvertFromFbx(FbxNode* node)
	{
		return false;
		//TiXmlElement* lib_animations	= colladaRoot->FirstChildElement(k_tag_libanimations);
		//if (!lib_animations)
		//{
		//	return false;
		//}

		//// load animations
		//TiXmlElement* cldAnimation		= lib_animations->FirstChildElement(k_tag_animation);
		//while (cldAnimation)
		//{
		//	CldAnimation* animation		= new CldAnimation;
		//	animation->Id				= cldAnimation->Attribute(k_attr_id);
		//	if (animation->LoadAnimation(cldAnimation))
		//	{
		//		if (animation->SubAnims.size() > 0)
		//		{
		//			for (u32 sa = 0 ; sa < animation->SubAnims.size() ; ++ sa)
		//			{
		//				OriginalAnimations.push_back(animation->SubAnims[sa]);
		//			}
		//			animation->SubAnims.clear();
		//			delete animation;
		//		}
		//		else
		//		{
		//			OriginalAnimations.push_back(animation);
		//		}
		//	}
		//	else
		//	{
		//		delete animation;
		//	}

		//	cldAnimation				= cldAnimation->NextSiblingElement(k_tag_animation);
		//}

		Loaded	= true;
		ConvertAnimations();
		return true;
	}

	void CldLibAnimation::ConvertAnimations()
	{
//#if ENABLE_MERGE_AND_SPLIT
//		for (u32 oa = 0 ; oa < OriginalAnimations.size() ; ++ oa)
//		{
//			CldAnimation* o_anim	= OriginalAnimations[oa];
//			if (o_anim == NULL)
//				continue;
//
//			if (o_anim->_Channel._TargetAnim == "RotX.ANGLE" ||
//				o_anim->_Channel._TargetAnim == "RotY.ANGLE" ||
//				o_anim->_Channel._TargetAnim == "RotZ.ANGLE")
//			{
//				// merge rotate animations
//				ti_vector<CldAnimation*> anims;
//				for (u32 a = 0 ; a < OriginalAnimations.size() ; ++ a)
//				{
//					CldAnimation* anim	= OriginalAnimations[a];
//					if (anim == NULL)
//						continue;
//					if (anim->_Channel._TargetNode == o_anim->_Channel._TargetNode &&
//						(anim->_Channel._TargetAnim == "RotX.ANGLE" ||
//						 anim->_Channel._TargetAnim == "RotY.ANGLE" ||
//						 anim->_Channel._TargetAnim == "RotZ.ANGLE"))
//					{
//						OriginalAnimations[a]	= NULL;
//						anims.push_back(anim);
//					}
//				}
//				MergeRotateAnimations(anims);
//				// delete these animations to prevent mem leak
//				for (u32 i = 0 ; i < anims.size() ; ++ i)
//				{
//					delete anims[i];
//				}
//			}
//			else if (o_anim->_Channel._TargetAnim == "scale.X" ||
//					 o_anim->_Channel._TargetAnim == "scale.Y" ||
//					 o_anim->_Channel._TargetAnim == "scale.Z")
//			{
//				// merge scale animations
//				ti_vector<CldAnimation*> anims;
//				for (u32 a = 0 ; a < OriginalAnimations.size() ; ++ a)
//				{
//					CldAnimation* anim	= OriginalAnimations[a];
//					if (anim == NULL)
//						continue;
//					if (anim->_Channel._TargetNode == o_anim->_Channel._TargetNode &&
//					   (anim->_Channel._TargetAnim == "scale.X" ||
//						anim->_Channel._TargetAnim == "scale.Y" ||
//						anim->_Channel._TargetAnim == "scale.Z"))
//					{
//						OriginalAnimations[a]	= NULL;
//						anims.push_back(anim);
//					}
//				}
//				MergeScaleAnimations(anims);
//				// delete these animations to prevent mem leak
//				for (u32 i = 0 ; i < anims.size() ; ++ i)
//				{
//					delete anims[i];
//				}
//			}
//			else if (o_anim->_Channel._TargetAnim == "translation.X" ||
//					 o_anim->_Channel._TargetAnim == "translation.Y" ||
//					 o_anim->_Channel._TargetAnim == "translation.Z")
//			{
//				// merge translate animations
//				ti_vector<CldAnimation*> anims;
//				for (u32 a = 0 ; a < OriginalAnimations.size() ; ++ a)
//				{
//					CldAnimation* anim	= OriginalAnimations[a];
//					if (anim == NULL)
//						continue;
//					if (anim->_Channel._TargetNode == o_anim->_Channel._TargetNode &&
//						(anim->_Channel._TargetAnim == "translation.X" ||
//						 anim->_Channel._TargetAnim == "translation.Y" ||
//						 anim->_Channel._TargetAnim == "translation.Z"))
//					{
//						OriginalAnimations[a]	= NULL;
//						anims.push_back(anim);
//					}
//				}
//				MergeTranslateAnimations(anims);
//				// delete these animations to prevent mem leak
//				for (u32 i = 0 ; i < anims.size() ; ++ i)
//				{
//					delete anims[i];
//				}
//			}
//			else if (o_anim->_Channel._TargetAnim == "transform")
//			{
//				// split matrix animations
//				OriginalAnimations[oa]	= NULL;
//				SplitAnimations(o_anim);
//				delete o_anim;
//			}
//			else
//			{
//				OriginalAnimations[oa]	= NULL;
//				Animations.push_back(o_anim);
//			}
//		}
//#else
//		for (u32 oa = 0 ; oa < OriginalAnimations.size() ; ++ oa)
//		{
//			CldAnimation* o_anim	= OriginalAnimations[oa];
//			Animations.push_back(o_anim);
//			OriginalAnimations[oa]	= NULL;
//		}
//#endif
	}

	struct	_SampleOutputCurve
	{
		ti_vector<float>	time;
		ti_vector<float>	vOutput;

		float getValue(float t)
		{
			TI_ASSERT(time.size() > 0);
			TI_ASSERT(vOutput.size() > 0);
			TI_ASSERT(vOutput.size() == time.size());
			if (t <= 0.f)
				return vOutput[0];
			if (t >= time.back())
				return vOutput.back();

			for ( u32 i = 1 ; i < time.size() ; ++ i)
			{
				if (t <= time[i])
				{
					return TI_INTERPOLATE(vOutput[i - 1], vOutput[i], (t - time[i - 1])/(time[i] - time[i - 1]));
				}
			}
			return vOutput[0];
		}
	};

	//void CldLibAnimation::MergeRotateAnimations(ti_vector<CldAnimation*>& anims)
	//{
	//	TI_ASSERT(anims.size() > 0);
	//	CldAnimation* newAnim	= new CldAnimation;

	//	ti_map<float, int> input_map;
	//	_SampleOutputCurve* curves	= new _SampleOutputCurve[anims.size()];
	//	// get max key count in these animations
	//	// get curves
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		CldAnimation* anim	= anims[a];
	//		Source* s_input		= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT);
	//		Source* s_output	= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
	//		TI_ASSERT(s_output->_Accessor.Stride == 1);
	//		int _keys			= s_input->_Accessor.Count;

	//		_SampleOutputCurve& curve	= curves[a];
	//		for (int k = 0 ; k < _keys ; ++ k)
	//		{
	//			input_map[s_input->ArrayFloat[k]]	= 0;
	//			curve.time.push_back(s_input->ArrayFloat[k]);
	//			curve.vOutput.push_back(s_output->ArrayFloat[k]);
	//		}
	//	}
	//	const int key_count				= input_map.size();

	//	CldAnimation* anim				= anims[0];
	//	newAnim->Id						= anim->_Channel._TargetNode + "-rotate";
	//	newAnim->_Channel._TargetNode	= anim->_Channel._TargetNode;
	//	newAnim->_Channel._TargetAnim	= "rotate";
	//	//const int key_count				= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count;
	//	// add input source
	//	Source* source_input			= new Source;
	//	source_input->Id				= anim->_Channel._TargetNode + "-rotate-INPUT"; 
	//	source_input->_Accessor.Count	= key_count;
	//	source_input->_Accessor.Stride	= 1;
	//	source_input->ArrayFloat.Count	= key_count;
	//	ti_map<float, int>::iterator	it_time;
	//	it_time							= input_map.begin();
	//	for (int c = 0 ; c < key_count ; ++ c)
	//	{
	//		source_input->ArrayFloat.ArrayData.push_back(it_time->first);
	//		++ it_time;
	//	}
	//	newAnim->Sources.push_back(source_input);
	//	// add output source
	//	Source* source_output			= new Source;
	//	source_output->Id				= anim->_Channel._TargetNode + "-rotate-OUTPUT";
	//	source_output->_Accessor.Count	= key_count;
	//	source_output->_Accessor.Stride	= 4; // each quaternion has 4 elements
	//	source_output->ArrayFloat.Count		= key_count * 4;
	//	for (int c = 0 ; c < key_count * 4 ; c += 4)
	//	{
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//		source_output->ArrayFloat.ArrayData.push_back(1);
	//	}
	//	newAnim->Sources.push_back(source_output);
	//	Input input, output;
	//	input.Semantic					= "INPUT";
	//	input.Source					= input.Source + "#" + source_input->Id;
	//	newAnim->_Sampler.Inputs.push_back(input);
	//	output.Semantic					= "OUTPUT";
	//	output.Source					= output.Source + "#" + source_output->Id;
	//	newAnim->_Sampler.Inputs.push_back(output);

	//	quaternion q, oq;
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		anim				= anims[a];
	//		TI_ASSERT(anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count <= key_count);

	//		_SampleOutputCurve& curve	= curves[a];

	//		ti_map<float, int>::iterator it_time;
	//		it_time				= input_map.begin();
	//		if (anim->_Channel._TargetAnim == "RotX.ANGLE")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				oq					= quaternion(source_output->ArrayFloat[k * 4], source_output->ArrayFloat[k * 4 + 1],
	//												 source_output->ArrayFloat[k * 4 + 2], source_output->ArrayFloat[k * 4 + 3]);

	//				//q.fromAngleAxis(DEG_TO_RAD(s_output->ArrayFloat[k]), vector3df(1, 0, 0));
	//				q.fromAngleAxis(DEG_TO_RAD(curve.getValue(it_time->first)), vector3df(1, 0, 0));
	//				q.normalize();
	//				oq					= oq * q;
	//				source_output->ArrayFloat[k * 4]		= oq.X;
	//				source_output->ArrayFloat[k * 4 + 1]	= oq.Y;
	//				source_output->ArrayFloat[k * 4 + 2]	= oq.Z;
	//				source_output->ArrayFloat[k * 4 + 3]	= oq.W;

	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "RotY.ANGLE")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				oq					= quaternion(source_output->ArrayFloat[k * 4], source_output->ArrayFloat[k * 4 + 1],
	//												 source_output->ArrayFloat[k * 4 + 2], source_output->ArrayFloat[k * 4 + 3]);
	//				//q.fromAngleAxis(DEG_TO_RAD(s_output->ArrayFloat[k]), vector3df(0, 1, 0));
	//				q.fromAngleAxis(DEG_TO_RAD(curve.getValue(it_time->first)), vector3df(0, 1, 0));
	//				q.normalize();
	//				oq					= oq * q;
	//				source_output->ArrayFloat[k * 4]		= oq.X;
	//				source_output->ArrayFloat[k * 4 + 1]	= oq.Y;
	//				source_output->ArrayFloat[k * 4 + 2]	= oq.Z;
	//				source_output->ArrayFloat[k * 4 + 3]	= oq.W;

	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "RotZ.ANGLE")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				oq					= quaternion(source_output->ArrayFloat[k * 4], source_output->ArrayFloat[k * 4 + 1],
	//												 source_output->ArrayFloat[k * 4 + 2], source_output->ArrayFloat[k * 4 + 3]);
	//				//q.fromAngleAxis(DEG_TO_RAD(s_output->ArrayFloat[k]), vector3df(0, 0, 1));
	//				q.fromAngleAxis(DEG_TO_RAD(curve.getValue(it_time->first)), vector3df(0, 0, 1));
	//				q.normalize();
	//				oq					= oq * q;
	//				source_output->ArrayFloat[k * 4]		= oq.X;
	//				source_output->ArrayFloat[k * 4 + 1]	= oq.Y;
	//				source_output->ArrayFloat[k * 4 + 2]	= oq.Z;
	//				source_output->ArrayFloat[k * 4 + 3]	= oq.W;

	//				++ it_time;
	//			}
	//		}
	//		else
	//		{
	//			TI_ASSERT(0);
	//		}
	//	}
	//	delete[] curves;
	//	if (!newAnim->IsUnanimous())
	//	{
	//		Animations.push_back(newAnim);
	//	}
	//	else
	//	{
	//		delete newAnim;
	//	}
	//}


	//void CldLibAnimation::MergeScaleAnimations(ti_vector<CldAnimation*>& anims)
	//{
	//	TI_ASSERT(anims.size() > 0);
	//	CldAnimation* newAnim	= new CldAnimation;

	//	ti_map<float, int> input_map;
	//	_SampleOutputCurve* curves	= new _SampleOutputCurve[anims.size()];
	//	// get max key count in these animations
	//	// get curves
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		CldAnimation* anim	= anims[a];
	//		Source* s_input		= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT);
	//		Source* s_output	= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
	//		TI_ASSERT(s_output->_Accessor.Stride == 1);
	//		int _keys			= s_input->_Accessor.Count;

	//		_SampleOutputCurve& curve	= curves[a];
	//		for (int k = 0 ; k < _keys ; ++ k)
	//		{
	//			input_map[s_input->ArrayFloat[k]]	= 0;
	//			curve.time.push_back(s_input->ArrayFloat[k]);
	//			curve.vOutput.push_back(s_output->ArrayFloat[k]);
	//		}
	//	}
	//	const int key_count				= input_map.size();

	//	CldAnimation* anim				= anims[0];
	//	newAnim->Id						= anim->_Channel._TargetNode + "-scale";
	//	newAnim->_Channel._TargetNode	= anim->_Channel._TargetNode;
	//	newAnim->_Channel._TargetAnim	= "scale";
	//	//const int key_count				= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count;
	//	// add input source
	//	Source* source_input			= new Source;
	//	source_input->Id				= anim->_Channel._TargetNode + "-scale-INPUT"; 
	//	source_input->_Accessor.Count	= key_count;
	//	source_input->_Accessor.Stride	= 1;
	//	source_input->ArrayFloat.Count	= key_count;
	//	ti_map<float, int>::iterator	it_time;
	//	it_time							= input_map.begin();
	//	for (int c = 0 ; c < key_count ; ++ c)
	//	{
	//		source_input->ArrayFloat.ArrayData.push_back(it_time->first);
	//		++ it_time;
	//	}
	//	newAnim->Sources.push_back(source_input);
	//	// add output source
	//	Source* source_output			= new Source;
	//	source_output->Id				= anim->_Channel._TargetNode + "-scale-OUTPUT";
	//	source_output->_Accessor.Count	= key_count;
	//	source_output->_Accessor.Stride	= 3; // each scale vector has 3 elements
	//	source_output->ArrayFloat.Count	= key_count * 3;
	//	for (int c = 0 ; c < key_count * 3 ; c += 3)
	//	{
	//		source_output->ArrayFloat.ArrayData.push_back(1);
	//		source_output->ArrayFloat.ArrayData.push_back(1);
	//		source_output->ArrayFloat.ArrayData.push_back(1);
	//	}
	//	newAnim->Sources.push_back(source_output);
	//	Input input, output;
	//	input.Semantic					= "INPUT";
	//	input.Source					= input.Source + "#" + source_input->Id;
	//	newAnim->_Sampler.Inputs.push_back(input);
	//	output.Semantic					= "OUTPUT";
	//	output.Source					= output.Source + "#" + source_output->Id;
	//	newAnim->_Sampler.Inputs.push_back(output);

	//	vector3df _s, _os;
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		anim				= anims[a];
	//		TI_ASSERT(anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count <= key_count);

	//		_SampleOutputCurve& curve	= curves[a];

	//		ti_map<float, int>::iterator it_time;
	//		it_time				= input_map.begin();
	//		if (anim->_Channel._TargetAnim == "scale.X")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				source_output->ArrayFloat[k * 3 + 0]	= curve.getValue(it_time->first);
	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "scale.Y")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				source_output->ArrayFloat[k * 3 + 1]	= curve.getValue(it_time->first);
	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "scale.Z")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				source_output->ArrayFloat[k * 3 + 2]	= curve.getValue(it_time->first);
	//				++ it_time;
	//			}
	//		}
	//		else
	//		{
	//			TI_ASSERT(0);
	//		}
	//	}
	//	delete[] curves;
	//	if (!newAnim->IsUnanimous())
	//	{
	//		Animations.push_back(newAnim);
	//	}
	//	else
	//	{
	//		delete newAnim;
	//	}
	//}

	//void CldLibAnimation::MergeTranslateAnimations(ti_vector<CldAnimation*>& anims)
	//{
	//	TI_ASSERT(anims.size() > 0);
	//	CldAnimation* newAnim	= new CldAnimation;

	//	ti_map<float, int> input_map;
	//	_SampleOutputCurve* curves	= new _SampleOutputCurve[anims.size()];
	//	// get max key count in these animations
	//	// get curves
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		CldAnimation* anim	= anims[a];
	//		Source* s_input		= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT);
	//		Source* s_output	= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
	//		TI_ASSERT(s_output->_Accessor.Stride == 1);
	//		int _keys			= s_input->_Accessor.Count;

	//		_SampleOutputCurve& curve	= curves[a];
	//		for (int k = 0 ; k < _keys ; ++ k)
	//		{
	//			input_map[s_input->ArrayFloat[k]]	= 0;
	//			curve.time.push_back(s_input->ArrayFloat[k]);
	//			curve.vOutput.push_back(s_output->ArrayFloat[k]);
	//		}
	//	}
	//	const int key_count				= input_map.size();

	//	CldAnimation* anim				= anims[0];
	//	newAnim->Id						= anim->_Channel._TargetNode + "-translation";
	//	newAnim->_Channel._TargetNode	= anim->_Channel._TargetNode;
	//	newAnim->_Channel._TargetAnim	= "translation";
	//	//const int key_count				= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count;
	//	// add input source
	//	Source* source_input			= new Source;
	//	source_input->Id				= anim->_Channel._TargetNode + "-translation-INPUT"; 
	//	source_input->_Accessor.Count	= key_count;
	//	source_input->_Accessor.Stride	= 1;
	//	source_input->ArrayFloat.Count	= key_count;
	//	ti_map<float, int>::iterator	it_time;
	//	it_time							= input_map.begin();
	//	for (int c = 0 ; c < key_count ; ++ c)
	//	{
	//		source_input->ArrayFloat.ArrayData.push_back(it_time->first);
	//		++ it_time;
	//	}
	//	newAnim->Sources.push_back(source_input);
	//	// add output source
	//	Source* source_output			= new Source;
	//	source_output->Id				= anim->_Channel._TargetNode + "-translation-OUTPUT";
	//	source_output->_Accessor.Count	= key_count;
	//	source_output->_Accessor.Stride	= 3; // each translation has 3 elements
	//	source_output->ArrayFloat.Count	= key_count * 3;
	//	for (int c = 0 ; c < key_count * 3 ; c += 3)
	//	{
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//		source_output->ArrayFloat.ArrayData.push_back(0);
	//	}
	//	newAnim->Sources.push_back(source_output);
	//	Input input, output;
	//	input.Semantic					= "INPUT";
	//	input.Source					= input.Source + "#" + source_input->Id;
	//	newAnim->_Sampler.Inputs.push_back(input);
	//	output.Semantic					= "OUTPUT";
	//	output.Source					= output.Source + "#" + source_output->Id;
	//	newAnim->_Sampler.Inputs.push_back(output);

	//	vector3df t, ot;
	//	for (u32 a = 0 ; a < anims.size() ; ++ a)
	//	{
	//		anim				= anims[a];
	//		TI_ASSERT(anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count <= key_count);

	//		_SampleOutputCurve& curve	= curves[a];

	//		ti_map<float, int>::iterator it_time;
	//		it_time				= input_map.begin();
	//		if (anim->_Channel._TargetAnim == "translation.X")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				ot					= vector3df(source_output->ArrayFloat[k * 3], 
	//												source_output->ArrayFloat[k * 3 + 1],
	//												source_output->ArrayFloat[k * 3 + 2]);

	//				t					= vector3df(curve.getValue(it_time->first), 0, 0);
	//				ot					+= t;
	//				source_output->ArrayFloat[k * 3]		= ot.X;
	//				source_output->ArrayFloat[k * 3 + 1]	= ot.Y;
	//				source_output->ArrayFloat[k * 3 + 2]	= ot.Z;

	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "translation.Y")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				ot					= vector3df(source_output->ArrayFloat[k * 3], 
	//												source_output->ArrayFloat[k * 3 + 1],
	//												source_output->ArrayFloat[k * 3 + 2]);

	//				t					= vector3df(0, curve.getValue(it_time->first), 0);
	//				ot					+= t;
	//				source_output->ArrayFloat[k * 3]		= ot.X;
	//				source_output->ArrayFloat[k * 3 + 1]	= ot.Y;
	//				source_output->ArrayFloat[k * 3 + 2]	= ot.Z;

	//				++ it_time;
	//			}
	//		}
	//		else if (anim->_Channel._TargetAnim == "translation.Z")
	//		{
	//			for (int k = 0 ; k < key_count ; ++ k)
	//			{
	//				ot					= vector3df(source_output->ArrayFloat[k * 3], 
	//												source_output->ArrayFloat[k * 3 + 1],
	//												source_output->ArrayFloat[k * 3 + 2]);

	//				t					= vector3df(0, 0, curve.getValue(it_time->first));
	//				ot					+= t;
	//				source_output->ArrayFloat[k * 3]		= ot.X;
	//				source_output->ArrayFloat[k * 3 + 1]	= ot.Y;
	//				source_output->ArrayFloat[k * 3 + 2]	= ot.Z;

	//				++ it_time;
	//			}
	//		}
	//		else
	//		{
	//			TI_ASSERT(0);
	//		}
	//	}
	//	delete[] curves;
	//	if (!newAnim->IsUnanimous())
	//	{
	//		Animations.push_back(newAnim);
	//	}
	//	else
	//	{
	//		delete newAnim;
	//	}
	//}

	inline float GetFloatAround(float v, float standard_v)
	{
		if (abs(v - standard_v) < 0.0001f)
		{
			return standard_v;
		}
		return v;
	}

	//void CldLibAnimation::SplitAnimations(CldAnimation* anim)
	//{
	//	CldAnimation* animTranslation			= new CldAnimation;
	//	CldAnimation* animRotate				= new CldAnimation;
	//	CldAnimation* animScale					= new CldAnimation;
	//	animTranslation->Id						= anim->_Channel._TargetNode + "-translation";
	//	animTranslation->_Channel._TargetNode	= anim->_Channel._TargetNode;
	//	animTranslation->_Channel._TargetAnim	= "translation";
	//	animRotate->Id							= anim->_Channel._TargetNode + "-rotate";
	//	animRotate->_Channel._TargetNode		= anim->_Channel._TargetNode;
	//	animRotate->_Channel._TargetAnim		= "rotate";
	//	animScale->Id							= anim->_Channel._TargetNode + "-scale";
	//	animScale->_Channel._TargetNode			= anim->_Channel._TargetNode;
	//	animScale->_Channel._TargetAnim			= "scale";

	//	// add input source
	//	Source* source_input[3];
	//	const int key_count						= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->_Accessor.Count;
	//	for (int i = 0 ; i < 3 ;  ++ i)
	//	{
	//		source_input[i]						= new Source;
	//		source_input[i]->_Accessor.Count	= key_count;
	//		source_input[i]->_Accessor.Stride	= 1;
	//		source_input[i]->ArrayFloat.Copy(anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT)->ArrayFloat);
	//	}
	//	source_input[0]->Id						= anim->_Channel._TargetNode + "-translation-INPUT"; 
	//	animTranslation->Sources.push_back(source_input[0]);
	//	source_input[1]->Id						= anim->_Channel._TargetNode + "-rotate-INPUT"; 
	//	animRotate->Sources.push_back(source_input[1]);
	//	source_input[2]->Id						= anim->_Channel._TargetNode + "-scale-INPUT"; 
	//	animScale->Sources.push_back(source_input[2]);

	//	// calc output source
	//	Input input, output;
	//	input.Semantic							= "INPUT";
	//	output.Semantic							= "OUTPUT";
	//	ti_string con							= "#";
	//	Source* translation_output				= new Source;
	//	translation_output->Id					= anim->_Channel._TargetNode + "-translation-OUTPUT";
	//	translation_output->_Accessor.Count		= key_count;
	//	translation_output->_Accessor.Stride		= 3; // each translation is a vector3df has 3 elements
	//	translation_output->ArrayFloat.Count			= key_count * 3;
	//	for (int c = 0 ; c < key_count * 3 ; c ++)
	//		translation_output->ArrayFloat.ArrayData.push_back(0);
	//	animTranslation->Sources.push_back(translation_output);
	//	input.Source							= con + source_input[0]->Id;
	//	animTranslation->_Sampler.Inputs.push_back(input);
	//	output.Source							= con + translation_output->Id;
	//	animTranslation->_Sampler.Inputs.push_back(output);
	//	Source* rotate_output					= new Source;
	//	rotate_output->Id						= anim->_Channel._TargetNode + "-rotate-OUTPUT";
	//	rotate_output->_Accessor.Count			= key_count;
	//	rotate_output->_Accessor.Stride			= 4; // each quaternion has 4 elements
	//	rotate_output->ArrayFloat.Count				= key_count * 4;
	//	for (int c = 0 ; c < key_count * 4 ; c ++)
	//		rotate_output->ArrayFloat.ArrayData.push_back(0);
	//	animRotate->Sources.push_back(rotate_output);
	//	input.Source							= con + source_input[1]->Id;
	//	animRotate->_Sampler.Inputs.push_back(input);
	//	output.Source							= con + rotate_output->Id;
	//	animRotate->_Sampler.Inputs.push_back(output);
	//	Source* scale_output					= new Source;
	//	scale_output->Id						= anim->_Channel._TargetNode + "-scale-OUTPUT";
	//	scale_output->_Accessor.Count			= key_count;
	//	scale_output->_Accessor.Stride			= 3; // scale is a vector3df
	//	scale_output->ArrayFloat.Count				= key_count * 3;
	//	for (int c = 0 ; c < key_count * 3 ; c ++)
	//		scale_output->ArrayFloat.ArrayData.push_back(1);
	//	animScale->Sources.push_back(scale_output);
	//	input.Source							= con + source_input[2]->Id;
	//	animScale->_Sampler.Inputs.push_back(input);
	//	output.Source							= con + scale_output->Id;
	//	animScale->_Sampler.Inputs.push_back(output);

	//	Source* s_output						= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
	//	TI_ASSERT(s_output->_Accessor.Stride == 16);
	//	matrix4 mat_key;
	//	vector3df translation, scale;
	//	quaternion rotation;
	//	for (int k = 0 ; k < key_count ; ++ k)
	//	{
	//		for (int i = 0 ; i < 16 ;  ++ i)
	//		{
	//			mat_key[i]	= s_output->ArrayFloat[k * 16 + i];
	//		}
	//		mat_key						= mat_key.getTransposed();
	//		rotation					= mat_key;
	//		rotation.normalize();
	//		translation.X				= mat_key(3, 0);
	//		translation.Y				= mat_key(3, 1);
	//		translation.Z				= mat_key(3, 2);
	//		scale						= mat_key.getScale();

	//		translation_output->ArrayFloat[k * 3 + 0]	= translation.X;
	//		translation_output->ArrayFloat[k * 3 + 1]	= translation.Y;
	//		translation_output->ArrayFloat[k * 3 + 2]	= translation.Z;

	//		rotate_output->ArrayFloat[k * 4 + 0]			= rotation.X;
	//		rotate_output->ArrayFloat[k * 4 + 1]			= rotation.Y;
	//		rotate_output->ArrayFloat[k * 4 + 2]			= rotation.Z;
	//		rotate_output->ArrayFloat[k * 4 + 3]			= rotation.W;

	//		scale.X			= GetFloatAround(scale.X, 1.f);
	//		scale.Y			= GetFloatAround(scale.Y, 1.f);
	//		scale.Z			= GetFloatAround(scale.Z, 1.f);

	//		scale_output->ArrayFloat[k * 3 + 0]			= scale.X;
	//		scale_output->ArrayFloat[k * 3 + 1]			= scale.Y;
	//		scale_output->ArrayFloat[k * 3 + 2]			= scale.Z;
	//	}

	//	if (!animTranslation->IsUnanimous())
	//	{
	//		Animations.push_back(animTranslation);
	//	}
	//	else
	//	{
	//		delete animTranslation;
	//	}
	//	if (!animRotate->IsUnanimous())
	//	{
	//		Animations.push_back(animRotate);
	//	}
	//	else
	//	{
	//		delete animRotate;
	//	}
	//	if (!animScale->IsUnanimous())
	//	{
	//		Animations.push_back(animScale);
	//	}
	//	else
	//	{
	//		delete animScale;
	//	}
	//}

	bool CldLibAnimation::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		//TiResfileChunkHeader header;
		//header.ID			= TIRES_ID_CHUNK_ANIMS;
		//header.Version		= TIRES_VERSION_CHUNK_ANIM;
		//header.ElementCount	= Animations.size();
		//header.ChunkSize	= sizeof(TiResfileChunkHeader);

		//TiStream buf;
		//// save animations desc
		//for (int i = 0 ; i < header.ElementCount ; ++ i)
		//{
		//	CldAnimation* anim	= Animations[i];
		//	// write descs
		//	AnimDesc desc;
		//	desc.KeyCount			= anim->Sources[0]->_Accessor.Count;
		//	desc.StrTargetNodeIndex	= AddStringToList(anim->_Channel._TargetNode, string_list);
		//	desc.StrTargetAnimIndex	= AddStringToList(anim->_Channel._TargetAnim, string_list);
		//	desc.AnimParam			= anim->_Channel._Param;
		//	buf.Put(&desc, sizeof(AnimDesc));
		//}
		//// save key frames
		//const float unit	= TiCollada::Get()->Config.UnitParam;
		//for (int i = 0 ; i < header.ElementCount ; ++ i)
		//{
		//	CldAnimation* anim	= Animations[i];
		//	AnimKey key;
		//	Source* s_time		= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_INPUT);
		//	Source* s_output	= anim->GetSourceBySemantic(CldAnimation::SEMANTIC_OUTPUT);
		//	TI_ASSERT(s_time && s_output);
		//	TI_ASSERT(s_time->_Accessor.Count == s_output->_Accessor.Count);
		//	bool isTranslation	= anim->_Channel._TargetAnim == "translation";
		//	int key_count		= s_time->_Accessor.Count;
		//	for (int k = 0 ; k < key_count ; ++ k)
		//	{
		//		key.Time		= s_time->ArrayFloat[k];
		//		TI_ASSERT(s_output->_Accessor.Stride <= 4);
		//		for (int stride = 0 ; stride < s_output->_Accessor.Stride ; ++ stride)
		//		{
		//			key.Key[stride]	= s_output->ArrayFloat[k * s_output->_Accessor.Stride + stride];
		//			if (isTranslation)
		//			{
		//				key.Key[stride]	*= unit;
		//			}
		//		}
		//		buf.Put(&key, sizeof(AnimKey));
		//	}
		//}

		//header.ChunkSize	+= buf.GetLength();
		//OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		//OutputStream.Put(buf.GetBuffer(), buf.GetLength());

		return true;
	}

	void CldLibAnimation::UpdateMorphAnimations(CldLibVisualScene* libScene)
	{
		for (u32 a = 0 ; a < Animations.size() ; ++ a)
		{
			CldAnimation* anim	= Animations[a];
			if (anim->MorphAnim)
			{
				u32 pos			= anim->_Channel._TargetNode.find("-morph_weights");
				TI_ASSERT(pos != ti_string::npos);
				ti_string morpher	= "#";
				morpher			+= anim->_Channel._TargetNode.substr(0, pos);
				anim->_Channel._TargetNode	= libScene->GetNodeByInstanceUrl(morpher)->Id;
				anim->_Channel._Param		= atoi(anim->_Channel._TargetAnim.c_str());
				anim->_Channel._TargetAnim	= "morph";
			}
		}
	}
};