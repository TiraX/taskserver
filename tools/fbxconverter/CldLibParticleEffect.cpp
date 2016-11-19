/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.11.13
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibParticleEffect.h"

enum E_EMITTER_TYPE
{
	EEMIT_POINT,
	EEMIT_DISC,
	EEMIT_SPHERE,
	EEMIT_CYLINDER,
	EEMIT_BILLBOARD,
	EEMIT_STICK,
	EEMIT_LINE,

	EEMIT_COUNT,
};

enum E_PARTICLE_TYPE
{
	EPT_DIRX,
	EPT_DIRY,
	EPT_DIRZ,
	EPT_BILLBOARD_SPEED,
	EPT_BILLBOARD,
	EPT_STRIPE,
	EPT_LINE_STRIPE,
	EPT_SPEED,
	EPT_GEOMETRY,

	EPT_COUNT,
};

enum E_PARTICLE_BLEND
{
	EPB_ADDITIVE,
	EPB_ALPHA,
	EPB_ADDTIVE_NODEPTH,
	EPB_ALPHA_NODEPTH,

	EPB_COUNT,
};

namespace ti
{
	//static const char* k_tag_libparticleeffect		= "library_particle_effects"; 
	//static const char* k_tag_particleeffect			= "particle_effect"; 
	//static const char* k_tag_emitter				= "emitter";
	//static const char* k_attr_relative				= "relative";
	//static const char* k_attr_emitonce				= "emit_once";
	//static const char* k_attr_random_speed			= "random_speed";

	//static const char* k_emitter_type_name[EEMIT_COUNT] = 
	//{
	//	"Point",
	//	"Disc",
	//	"Sphere",
	//	"Cylinder",
	//	"Billboard",
	//	"Stick",
	//	"Line",
	//};
	//static const char* k_particle_type_name[EPT_COUNT] = 
	//{
	//	"DirX",
	//	"DirY",
	//	"DirZ",
	//	"BillboardSpeed",
	//	"Billboard",
	//	"Stripe",
	//	"LineStripe",
	//	"Speed",
	//	"Geometry",
	//};
	//static const char* k_particle_blend_name[EPB_COUNT] = 
	//{
	//	"additive",
	//	"alpha",
	//	"additive_nodepth",
	//	"alpha_nodepth",
	//};

	//E_EMITTER_TYPE GetEmitterTypeByName(const ti_string& name)
	//{
	//	for (int i = 0 ; i < EEMIT_COUNT ; ++ i)
	//	{
	//		if (name == k_emitter_type_name[i])
	//		{
	//			return (E_EMITTER_TYPE)i;
	//		}
	//	}

	//	return EEMIT_POINT;
	//}
	//E_PARTICLE_TYPE GetParticleTypeByName(const ti_string& name)
	//{
	//	for (int i = 0 ; i < EPT_COUNT ; ++ i)
	//	{
	//		if (name == k_particle_type_name[i])
	//		{
	//			return (E_PARTICLE_TYPE)i;
	//		}
	//	}

	//	return EPT_BILLBOARD;
	//}
	//E_PARTICLE_BLEND GetParticleBlendByName(const ti_string& name)
	//{
	//	for (int i = 0 ; i < EPB_COUNT ; ++ i)
	//	{
	//		if (name == k_particle_blend_name[i])
	//		{
	//			return (E_PARTICLE_BLEND)i;
	//		}
	//	}

	//	return EPB_ADDITIVE;
	//}

	//CldEmitter::CldEmitter()
	//{
	//}

	//CldEmitter::~CldEmitter()
	//{
	//	for (u32 a  = 0 ; a < Affectors.size() ; ++ a)
	//	{
	//		delete Affectors[a];
	//		Affectors[a] = NULL;
	//	}
	//	Affectors.clear();
	//}

	//enum 
	//{
	//	EMITF_RELATIVE_PARTICLE		= 1 << 0,
	//	EMITF_EMIT_ONCE				= 1 << 1,
	//	EMITF_RANDOM_SPEED_DIR		= 1 << 2,
	//	EMITF_RANDOM_ROTATE			= 1 << 3,
	//	EMITF_EMIT_INSIDE			= 1 << 4,
	//	EMITF_RANDOM_FRAME			= 1 << 5,
	//	EMITF_AUTO_DESTROY			= 1 << 6,
	//	EMITF_FRAME_ANIMATION		= 1 << 7,
	//	EMITF_SHOW_BBOX				= 1 << 8,
	//	EMITF_SHOW_EDITOR_HELPER	= 1 << 9,
	//	EMITF_INTERPORLATE_TRACK	= 1 << 10,
	//	EMITF_UV_FLIP_X				= 1 << 11,
	//	EMITF_UV_FLIP_Y				= 1 << 12,
	//	EMITF_FIXED_EMIT_DIR		= 1 << 13,
	//	EMITF_SFX_DISABLE_DISTANCE	= 1 << 14,

	//	EMITF_EMITTED				= 1 << 16,
	//};


	//bool LoadParam(TiXmlElement* root, const char* name)
	//{
	//	TiXmlElement* param		= root->FirstChildElement(name);
	//	if (param)
	//	{
	//		return strcmp(param->Attribute("value"), "true") == 0;
	//	}

	//	return false;
	//}

	//bool CldEmitter::LoadEmitter(TiXmlElement* emitter_root)
	//{
	//	double number;
	//	ti_vector<float> numArray;

	//	TiXmlElement* xml_eType		= emitter_root->FirstChildElement("emitter_type");
	//	ti_string e_type_str		= xml_eType->Attribute("value");
	//	Desc.EmitterType			= (int)GetEmitterTypeByName(e_type_str);

	//	TiXmlElement* xml_params	= emitter_root->FirstChildElement("params");
	//	TI_ASSERT(xml_params);
	//	// flags
	//	if (LoadParam(xml_params, "relative"))
	//		Desc.EmitterFlag		|= EMITF_RELATIVE_PARTICLE;
	//	if (LoadParam(xml_params, "emit_once"))
	//		Desc.EmitterFlag		|= EMITF_EMIT_ONCE;
	//	if (LoadParam(xml_params, "random_speed"))
	//		Desc.EmitterFlag		|= EMITF_RANDOM_SPEED_DIR;
	//	if (LoadParam(xml_params, "random_rotate"))
	//		Desc.EmitterFlag		|= EMITF_RANDOM_ROTATE;
	//	if (LoadParam(xml_params, "emit_inside"))
	//		Desc.EmitterFlag		|= EMITF_EMIT_INSIDE;
	//	if (LoadParam(xml_params, "random_frame"))
	//		Desc.EmitterFlag		|= EMITF_RANDOM_FRAME;
	//	if (LoadParam(xml_params, "auto_destroy"))
	//		Desc.EmitterFlag		|= EMITF_AUTO_DESTROY;
	//	if (LoadParam(xml_params, "frame_animation"))
	//		Desc.EmitterFlag		|= EMITF_FRAME_ANIMATION;
	//	if (LoadParam(xml_params, "interporlate_track"))
	//		Desc.EmitterFlag		|= EMITF_INTERPORLATE_TRACK;
	//	if (LoadParam(xml_params, "texture_flip_x"))
	//		Desc.EmitterFlag		|= EMITF_UV_FLIP_X;
	//	if (LoadParam(xml_params, "texture_flip_y"))
	//		Desc.EmitterFlag		|= EMITF_UV_FLIP_Y;
	//	if (LoadParam(xml_params, "fixed_dir"))
	//		Desc.EmitterFlag		|= EMITF_FIXED_EMIT_DIR;
	//	if (LoadParam(xml_params, "sfx_disable_distance"))
	//		Desc.EmitterFlag		|= EMITF_SFX_DISABLE_DISTANCE;

	//	TiXmlElement* xml_parent	= emitter_root->FirstChildElement("parent_node");
	//	if (xml_parent)
	//	{
	//		ParentName				= xml_parent->FirstChild()->ToText()->Value();
	//	}

	//	TiXmlElement* xml_position	= emitter_root->FirstChildElement("position");
	//	if (xml_position)
	//	{
	//		numArray.clear();
	//		ReadFloatArray(xml_position->FirstChild()->ToText()->Value(), numArray);
	//		vector3df pos(numArray[0], numArray[1], numArray[2]);
	//		Desc.Position			= pos;
	//	}

	//	TiXmlElement* radius		= xml_eType->FirstChildElement("radius");
	//	if (radius)
	//	{
	//		radius->Attribute("value", &number);
	//		Desc.Radius			= (float)number;
	//	}

	//	TiXmlElement* angle			= xml_eType->FirstChildElement("angle");
	//	if (angle)
	//	{
	//		angle->Attribute("value", &number);
	//		Desc.Angle				= (float)number;
	//	}
	//	TiXmlElement* section		= xml_eType->FirstChildElement("section");
	//	if (section)
	//	{
	//		int int_num;
	//		section->Attribute("value", &int_num);
	//		Desc.Section			= int_num;
	//	}

	//	TiXmlElement* dir			= xml_eType->FirstChildElement("dir");
	//	if (dir)
	//	{
	//		numArray.clear();
	//		ReadFloatArray(dir->FirstChild()->ToText()->Value(), numArray);
	//		vector3df vDir(numArray[0], numArray[1], numArray[2]);
	//		vDir.normalize();
	//		Desc.Dir				= vDir;
	//	}

	//	TiXmlElement* height		= xml_eType->FirstChildElement("height");
	//	if (height)
	//	{
	//		height->Attribute("value", &number);
	//		Desc.Height				= (float)number;;
	//	}

	//	TiXmlElement* end_point		= xml_eType->FirstChildElement("end_point");
	//	if (end_point)
	//	{
	//		numArray.clear();
	//		ReadFloatArray(end_point->FirstChild()->ToText()->Value(), numArray);
	//		vector3df endPoint(numArray[0], numArray[1], numArray[2]);
	//		Desc.EndPoint			= endPoint;
	//	}

	//	TiXmlElement* emit_interval		= emitter_root->FirstChildElement("interval");
	//	TI_ASSERT(emit_interval);
	//	emit_interval->Attribute("value", &number);
	//	Desc.Interval					= (float)number;

	//	TiXmlElement* emit_life			= emitter_root->FirstChildElement("emit_life");
	//	if (emit_life)
	//	{
	//		double c;
	//		emit_life->Attribute("value", &c);
	//		Desc.EmitLife				= (float)c;
	//	}
	//	TiXmlElement* emit_delay		= emitter_root->FirstChildElement("emit_delay");
	//	if (emit_delay)
	//	{
	//		double c;
	//		emit_delay->Attribute("value", &c);
	//		Desc.EmitDelay				= (float)c;
	//	}
	//	TiXmlElement* emit_count		= emitter_root->FirstChildElement("emit_count");
	//	if (emit_count)
	//	{
	//		int c;
	//		emit_count->Attribute("value", &c);
	//		Desc.EmitCount				= c;
	//	}

	//	TiXmlElement* emit_bbox			= emitter_root->FirstChildElement("bbox");
	//	if (emit_bbox)
	//	{
	//		TiXmlElement* bbox_min		= emit_bbox->FirstChildElement("min");
	//		TI_ASSERT(bbox_min);
	//		numArray.clear();
	//		ReadFloatArray(bbox_min->FirstChild()->ToText()->Value(), numArray);
	//		Desc.BBox.MinEdge			= vector3df(numArray[0], numArray[1], numArray[2]);
	//		TiXmlElement* bbox_max		= emit_bbox->FirstChildElement("max");
	//		TI_ASSERT(bbox_max);
	//		numArray.clear();
	//		ReadFloatArray(bbox_max->FirstChild()->ToText()->Value(), numArray);
	//		Desc.BBox.MaxEdge			= vector3df(numArray[0], numArray[1], numArray[2]);
	//	}

	//	TiXmlElement* emit_sfx			= emitter_root->FirstChildElement("sfx");
	//	if (emit_sfx)
	//	{
	//		if (emit_sfx->FirstChild())
	//		{
	//			Sfx						= emit_sfx->FirstChild()->ToText()->Value();
	//		}
	//	}

	//	TiXmlElement* particle_type		= emitter_root->FirstChildElement("particle_type");
	//	TI_ASSERT(particle_type);
	//	Desc.ParticleType				= GetParticleTypeByName(particle_type->Attribute("value"));

	//	TiXmlElement* particle_life		= emitter_root->FirstChildElement("particle_life");
	//	TI_ASSERT(particle_life);
	//	particle_life->Attribute("value", &number);
	//	Desc.ParticleLife				= (float)number;

	//	TiXmlElement* par_life_random	= emitter_root->FirstChildElement("particle_life_random");
	//	if (par_life_random)
	//	{
	//		par_life_random->Attribute("value", &number);
	//		Desc.ParticleLifeRandom		= (float)number;
	//	}
	//	else
	//		Desc.ParticleLifeRandom		= 0.f;

	//	TiXmlElement* particle_speed	= emitter_root->FirstChildElement("particle_speed");
	//	TI_ASSERT(particle_speed);
	//	particle_speed->Attribute("value", &number);
	//	Desc.ParticleSpeed				= (float)number;

	//	TiXmlElement* particle_cb		= emitter_root->FirstChildElement("particle_color_boost");
	//	if (particle_cb)
	//	{
	//		particle_cb->Attribute("value", &number);
	//		Desc.ParticleColorBoost		= (float)number;
	//	}
	//	else
	//		Desc.ParticleColorBoost		= 1.f;

	//	TiXmlElement* particle_fadetime	= emitter_root->FirstChildElement("particle_fadetime");
	//	if (particle_fadetime)
	//	{
	//		particle_fadetime->Attribute("value", &number);
	//		Desc.DefaultFadeTime		= (float)number;
	//	}
	//	else
	//		Desc.DefaultFadeTime		= 0.1f;

	//	TiXmlElement* particle_size		= emitter_root->FirstChildElement("particle_size");
	//	TI_ASSERT(particle_size);
	//	vector2df p_size;
	//	particle_size->Attribute("width", &number);
	//	p_size.X						= (float)number;
	//	particle_size->Attribute("height", &number);
	//	p_size.Y						= (float)number;
	//	Desc.ParticleSize				= p_size;

	//	TiXmlElement* par_size_random	= emitter_root->FirstChildElement("particle_size_random");
	//	if (par_size_random)
	//	{
	//		par_size_random->Attribute("value", &number);
	//		Desc.ParticleSizeRandom		= (float)number;
	//	}
	//	else
	//		Desc.ParticleSizeRandom		= 0.f;

	//	TiXmlElement* particle_fi		= emitter_root->FirstChildElement("frame_anim_interval");
	//	if (particle_fi)
	//	{
	//		particle_fi->Attribute("value", &number);
	//		Desc.FrameInterval			= (float)number;
	//	}
	//	else
	//		Desc.FrameInterval			= 0.1f;

	//	TiXmlElement* particle_blend	= emitter_root->FirstChildElement("particle_blend");
	//	if (particle_blend != NULL)
	//	{
	//		TI_ASSERT(particle_blend->FirstChild());
	//		const char* blend_type		= particle_blend->FirstChild()->ToText()->Value();
	//		int bt						= GetParticleBlendByName(blend_type);
	//		Desc.BlendType				= bt;
	//	}
	//	else
	//		Desc.BlendType				= EPB_ADDITIVE;

	//	TiXmlElement* particle_color		= emitter_root->FirstChildElement("particle_color");
	//	TI_ASSERT(particle_color);
	//	numArray.clear();
	//	ReadFloatArray(particle_color->FirstChild()->ToText()->Value(), numArray);
	//	SColorf c;
	//	c.R									= numArray[0] / 255.f;
	//	c.G									= numArray[1] / 255.f;
	//	c.B									= numArray[2] / 255.f;
	//	c.A									= numArray[3] / 255.f;
	//	Desc.ParticleColor						= c;

	//	TiXmlElement* particle_texture		= emitter_root->FirstChildElement("particle_texture");
	//	TI_ASSERT(particle_texture);
	//	ParticleTexture						= particle_texture->Attribute("value");

	//	TiXmlElement* texture_demension		= emitter_root->FirstChildElement("texture_demension");
	//	if (texture_demension)
	//	{
	//		vector2di d;
	//		texture_demension->Attribute("x", &d.X);
	//		texture_demension->Attribute("y", &d.Y);
	//		Desc.Demension[0]				= (u16)d.X;
	//		Desc.Demension[1]				= (u16)d.Y;
	//	}

	//	TiXmlElement* xml_affectors			= emitter_root->FirstChildElement("affectors");
	//	if (xml_affectors)
	//	{
	//		LoadAffectors(xml_affectors);
	//	}
	//	Desc.AffectorCount					= Affectors.size();

	//	return true;
	//}

	//enum E_AFFECTOR_TYPE
	//{
	//	EAT_ROTATE,
	//	EAT_COLOR,
	//	EAT_COLOR_ANIM,
	//	EAT_SIZE,
	//	EAT_SPEED_ANIM,
	//	EAT_SIZE_ANIM,
	//	EAT_FORCE,
	//	EAT_SPEED_ANIM_NON_LINEAR,
	//	EAT_VORTEX,
	//	EAT_MAGNET,

	//	EAT_COUNT,
	//};
	//static const char* k_affector_tag_name[EAT_COUNT] = 
	//{
	//	"affector_rotate",	//EAT_ROTATE,
	//	"affector_color",	//EAT_COLOR,
	//	"affector_color_anim",	//EAT_COLOR_ANIM,
	//	"affector_size",	//EAT_SIZE,
	//	"affector_speed_anim",	//EAT_SPEED_ANIM,
	//	"affector_size_anim",	//EAT_SIZE_ANIM,
	//	"affector_forcefield",	//EAT_FORCE,
	//	"affector_speed_anim_non_linear",	//EAT_SPEED_ANIM_NON_LINEAR,vor
	//	"affector_vortex",		//EAT_VORTEX
	//	"affector_magnet",		//EAT_MAGNET
	//};
	//int GetTypeByAffectType(const char* type_name)
	//{
	//	for (int i = 0 ; i < EAT_COUNT ; ++ i)
	//	{
	//		if (strcmp(type_name, k_affector_tag_name[i]) == 0)
	//		{
	//			return i;
	//		}
	//	}

	//	return -1;
	//}

	//void CldEmitter::LoadAffectors(TiXmlElement* affector_root)
	//{
	//	TiXmlElement* xml_affector		= affector_root->FirstChildElement("affector");
	//	while (xml_affector != NULL)
	//	{
	//		int affector_type			= GetTypeByAffectType(xml_affector->Attribute("type"));
	//		TI_ASSERT(affector_type != -1);

	//		CldAffector* affector		= new CldAffector;
	//		affector->Type				= affector_type;
	//		if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_ROTATE]) == 0)
	//		{
	//			// affector rotate
	//			TiXmlElement* xml_speed		= xml_affector->FirstChildElement("rotate_speed");
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_speed->FirstChild()->ToText()->Value(), num_array);
	//			affector->Data[0]			= num_array[0];
	//			affector->Data[1]			= num_array[1];
	//			affector->Data[2]			= num_array[2];
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_COLOR]) == 0)
	//		{
	//			// affector color
	//			TiXmlElement* xml_speed		= xml_affector->FirstChildElement("color_speed");
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_speed->FirstChild()->ToText()->Value(), num_array);
	//			affector->Data[0]			= num_array[0];
	//			affector->Data[1]			= num_array[1];
	//			affector->Data[2]			= num_array[2];
	//			affector->Data[3]			= num_array[3];
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_COLOR_ANIM]) == 0)
	//		{
	//			// affector color anim
	//			TiXmlElement* xml_keys		= xml_affector->FirstChildElement("color_keys");
	//			TI_ASSERT(xml_keys);
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_keys->FirstChild()->ToText()->Value(), num_array);
	//			TI_ASSERT(num_array.size() == 20);
	//			for (int i = 0 ; i < 20 ; ++ i)
	//			{
	//				affector->Data[i]		= num_array[i];
	//			}
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_SPEED_ANIM]) == 0 ||
	//				 strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_SPEED_ANIM_NON_LINEAR]) == 0)
	//		{
	//			// affector color anim
	//			TiXmlElement* xml_keys		= xml_affector->FirstChildElement("speed_keys");
	//			TI_ASSERT(xml_keys);
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_keys->FirstChild()->ToText()->Value(), num_array);
	//			TI_ASSERT(num_array.size() == 5);
	//			for (int i = 0 ; i < 5 ; ++ i)
	//			{
	//				affector->Data[i]		= num_array[i];
	//			}
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_SIZE_ANIM]) == 0)
	//		{
	//			// affector color anim
	//			TiXmlElement* xml_keys		= xml_affector->FirstChildElement("size_keys");
	//			TI_ASSERT(xml_keys);
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_keys->FirstChild()->ToText()->Value(), num_array);
	//			TI_ASSERT(num_array.size() == 10);
	//			for (int i = 0 ; i < 10 ; ++ i)
	//			{
	//				affector->Data[i]		= num_array[i];
	//			}
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_SIZE]) == 0)
	//		{
	//			TiXmlElement* xml_speed		= xml_affector->FirstChildElement("size_speed");
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_speed->FirstChild()->ToText()->Value(), num_array);
	//			affector->Data[0]			= num_array[0];
	//			affector->Data[1]			= num_array[1];
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_FORCE]) == 0)
	//		{
	//			TiXmlElement* xml_dir		= xml_affector->FirstChildElement("force_dir");
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_dir->FirstChild()->ToText()->Value(), num_array);
	//			affector->Data[0]			= num_array[0];
	//			affector->Data[1]			= num_array[1];
	//			affector->Data[2]			= num_array[2];

	//			TiXmlElement* xml_strength	= xml_affector->FirstChildElement("strength");
	//			affector->Data[3]			= (float)atof(xml_strength->FirstChild()->ToText()->Value());
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_MAGNET]) == 0)
	//		{
	//			TiXmlElement* xml_strength	= xml_affector->FirstChildElement("strength");
	//			affector->Data[0]			= (float)atof(xml_strength->FirstChild()->ToText()->Value());
	//		}
	//		else if (strcmp(xml_affector->Attribute("type"), k_affector_tag_name[EAT_VORTEX]) == 0)
	//		{
	//			TiXmlElement* xml_dir		= xml_affector->FirstChildElement("vortex_dir");
	//			ti_vector<float> num_array;
	//			ReadFloatArray(xml_dir->FirstChild()->ToText()->Value(), num_array);
	//			affector->Data[0]			= num_array[0];
	//			affector->Data[1]			= num_array[1];
	//			affector->Data[2]			= num_array[2];

	//			TiXmlElement* xml_strength	= xml_affector->FirstChildElement("strength");
	//			affector->Data[3]			= (float)atof(xml_strength->FirstChild()->ToText()->Value());
	//		}
	//		else
	//		{
	//			TI_ASSERT(0);
	//		}
	//		Affectors.push_back(affector);
	//		xml_affector				= xml_affector->NextSiblingElement("affector");
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////

	CldLibParticleEffect::CldLibParticleEffect()
	{
	}

	CldLibParticleEffect::~CldLibParticleEffect()
	{
		//for (unsigned int i = 0 ; i < Emitters.size() ; ++ i)
		//{
		//	delete Emitters[i];
		//}
		//Emitters.clear();
	}

	bool CldLibParticleEffect::ConvertFromFbx(FbxNode* node)
	{
		//TiXmlElement* lib_particleeffect	= colladaRoot->FirstChildElement(k_tag_libparticleeffect);
		//if (!lib_particleeffect)
		//{
		//	return false;
		//}

		//// extra models
		//TiXmlElement* xml_model			= lib_particleeffect->FirstChildElement("model");
		//if (xml_model)
		//{
		//	ExtraModel					= xml_model->FirstChild()->ToText()->Value();
		//	size_t pos					= ExtraModel.find(".tidae");
		//	TI_ASSERT(pos != ti_string::npos);
		//	ExtraModel					= ExtraModel.substr(0, pos);
		//	ExtraModel					+= ".DAE";

		//	TiColladaConfig& config		= TiCollada::Get()->Config;
		//	ti_string texture_path_bak	= config.TexturePath;
		//	config.TexturePath			= config.ExtraModelTexturePath;

		//	ti_string file_name_bak		= config.InputFilename;
		//	config.InputFilename		= ExtraModel;
		//	if (TiCollada::Get()->Load(ExtraModel.c_str()))
		//	{
		//		CldLibVisualScene* lib_scene	= (CldLibVisualScene*)TiCollada::Get()->ColladaLibraries[ECL_VISUALSCENE];
		//		lib_scene->HangNodeOnEmitter	= true;
		//	}
		//	config.InputFilename		= file_name_bak;
		//	config.TexturePath			= texture_path_bak;
		//}

		//// load emitters
		//TiXmlElement* xml_emitter		= lib_particleeffect->FirstChildElement(k_tag_emitter);
		//while (xml_emitter)
		//{
		//	CldEmitter* cld_emitter		= new CldEmitter;
		//	cld_emitter->Id				= xml_emitter->Attribute("id");
		//	cld_emitter->LoadEmitter(xml_emitter);

		//	Emitters.push_back(cld_emitter);
		//	xml_emitter					= xml_emitter->NextSiblingElement(k_tag_emitter);
		//}

		Loaded	= true;
		return true;
	}

	//CldEmitter* CldLibParticleEffect::GetEmitterById(const char* __id)
	//{
	//	for (u32 e = 0 ; e < Emitters.size() ; ++ e)
	//	{
	//		if (Emitters[e]->Id == __id)
	//		{
	//			return Emitters[e];
	//		}
	//	}
	//	return NULL;
	//}

	bool CldLibParticleEffect::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		//TiResfileChunkHeader header;
		//header.ID			= TIRES_ID_CHUNK_EMITTER;
		//header.Version		= TIRES_VERSION_CHUNK_EMIT;
		//header.ElementCount	= Emitters.size();
		//header.ChunkSize	= sizeof(TiResfileChunkHeader);

		//TiStream buf;
		//// save emitter desc
		//for (int i = 0 ; i < header.ElementCount ; ++ i)
		//{
		//	CldEmitter* emitter	= Emitters[i];
		//	
		//	emitter->Desc.Id_StrIndex		= AddStringToList(emitter->Id, string_list);
		//	emitter->Desc.Texture_StrIndex	= AddStringToList(emitter->ParticleTexture, string_list);
		//	emitter->Desc.Sfx_StrIndex		= AddStringToList(emitter->Sfx, string_list);
		//	buf.Put(&(emitter->Desc), sizeof(EmitterDesc));
		//}
		//// affectors
		//for (int i = 0 ; i < header.ElementCount ; ++ i)
		//{
		//	CldEmitter* emitter	= Emitters[i];

		//	for (u32 a = 0 ; a < emitter->Affectors.size() ; ++ a)
		//	{
		//		CldAffector* aff	= emitter->Affectors[a];
		//		AffectorDesc aDesc;
		//		aDesc.AffectorType	= aff->Type;
		//		memcpy(aDesc.Data, aff->Data, sizeof(aff->Data));
		//		buf.Put(&aDesc, sizeof(AffectorDesc));
		//	}
		//}

		//header.ChunkSize	+= buf.GetLength();
		//OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		//OutputStream.Put(buf.GetBuffer(), buf.GetLength());

		return true;
	}
};