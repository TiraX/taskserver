/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.10.19
*/

#ifndef _CLDLIBANIMATION_H__
#define _CLDLIBANIMATION_H__

#include "CldLibrary.h"

namespace ti
{
	struct _key_frame
	{
		float	input;
		float	output[16];

		_key_frame()
		{
			input		= 0.0f;
			memset(output, 0, sizeof(output));
		}

		_key_frame(const _key_frame& other)
		{
			input		= other.input;
			for (int i = 0 ; i < 16 ; ++ i)
			{
				output[i]	= other.output[i];
			}
		}

		_key_frame& operator = (const _key_frame& other)
		{
			input		= other.input;
			for (int i = 0 ; i < 16 ; ++ i)
			{
				output[i]	= other.output[i];
			}
			return *this;
		}
	};

	class Channel
	{
	public:
		ti_string			_Source;
		ti_string			_TargetNode;
		ti_string			_TargetAnim;
		int					_Param;

		Channel()
			: _Param(-1)
		{}
	};

	class Sampler
	{
	public:
		ti_string			Id;
		//ti_vector< Input >	Inputs;

		//bool				Load(TiXmlElement* sampler_root);
	};

	//////////////////////////////////////////////////////////////////////////

	class CldAnimation
	{
	public:
		enum
		{
			SEMANTIC_INPUT,
			SEMANTIC_OUTPUT,
			SEMANTIC_INTERPOLATION,
			SEMANTIC_INTANGENT,
			SEMANTIC_OUTTANGENT,

			SEMANTIC_COUNT,
		};
		CldAnimation();
		virtual ~CldAnimation();
		//bool	LoadAnimation(TiXmlElement* animation_root);
		void	GatherKeys();

		//Source*	GetSourceById(const char* source_id);
		//Source*	GetSourceBySemantic(int semantic);

		//bool	IsUnanimous();

		ti_string	Id;

		//ti_vector< Source* >	Sources;
		Sampler					_Sampler;
		Channel					_Channel;

		bool					MorphAnim;

		ti_vector< CldAnimation* >	SubAnims;
	};

	//////////////////////////////////////////////////////////////////////////

	class CldLibAnimation : public CldLibrary
	{
	public:
		CldLibAnimation();
		virtual ~CldLibAnimation();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		void		UpdateMorphAnimations(CldLibVisualScene* libScene);

		void		 ConvertAnimations();
		//// merge RotX, RotY, RotZ animation to rotate
		//// result put into vector Animations
		//void		 MergeRotateAnimations(ti_vector<CldAnimation*>& anims);
		//// merge translation.X, translation.Y, translation.Z animation to translation
		//// result put into vector Animations
		//void		 MergeTranslateAnimations(ti_vector<CldAnimation*>& anims);
		//// merge scale.X, scale.Y, scale.Z animation to scale
		//// result put into vector Animations
		//void		 MergeScaleAnimations(ti_vector<CldAnimation*>& anims);
		//// split transform animation to translate, rotate, scale
		//// result put into vector Animations
		//void		 SplitAnimations(CldAnimation* anim);

		ti_vector< CldAnimation* >	OriginalAnimations;
		ti_vector< CldAnimation* >	Animations;
	};

};

#endif	//_CLDLIBANIMATION_H__