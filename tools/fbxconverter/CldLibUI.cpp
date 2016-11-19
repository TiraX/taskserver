/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2013.3.18
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibUI.h"

//static const char* k_symbol_type_names[] = 
//{
//	"ui_root",	//EUIT_UIROOT
//	"symbol",	//EUIT_SYMBOL,
//	"button",	//EUIT_BUTTON,
//	"dialog",	//EUIT_DIALOG,
//	"image",	//EUIT_IMAGE,	
//	"char",		//EUIT_CHARACCTER
//	"textbox",	//EUIT_TEXTBOX
//	"iconbox",	//EUIT_ICONBOX
//	"scrollarea",	//EUIT_SCROLLAREA
//	"fan",			//EUIT_FAN
//	"event_mask",	//EUIT_EVENTMASK
//	"drawbox",		//EUIT_DRAWBOX
//	"dialog9",		//EUIT_DIALOG_9
//	"easybutton",	//EUIT_EZBUTTON
//};
//
//static const char* k_str_align[EUI_ALIGN_COUNT]		= 
//{
//	"left",
//	"hcenter",
//	"right",
//	"relative_left",
//	"relative_hcenter",
//	"relative_right",
//
//	"top",
//	"vcenter",
//	"bottom",
//	"relative_top",
//	"relative_vcenter",
//	"relative_bottom",
//};
//
//static const char* k_sfx_name[EUI_SFX_COUNT] =
//{
//	"sfx_button_click",
//};
//E_UI_SFX GetSfxTypeByName(const char* name)
//{
//	for (int i = 0 ; i < EUI_SFX_COUNT ; ++ i)
//	{
//		if (strcmp(name, k_sfx_name[i]) == 0)
//		{
//			return (E_UI_SFX)i;
//		}
//	}
//	TI_ASSERT(0);
//	return EUI_SFX_INVALID;
//}
//
//E_UINODE_ALIGNMENT GetAlignTypeByName(const char* align)
//{
//	for (int a = 0 ; a < EUI_ALIGN_COUNT ; ++ a)
//	{
//		if (strcmp(k_str_align[a], align) == 0)
//		{
//			return (E_UINODE_ALIGNMENT)a;
//		}
//	}
//	TI_ASSERT(0);
//	return EUI_ALIGN_LEFT;
//}
//
//E_UI_TYPE GetTypeByName(const char* name)
//{
//	if (strcmp(name, "dialog9") == 0)
//	{
//		int bkkk = 0;
//	}
//	for (int i = 0 ; i < EUIT_COUNT ; ++ i)
//	{
//		if (strcmp(k_symbol_type_names[i], name) == 0)
//		{
//			return (E_UI_TYPE)i;
//		}
//	}
//
//	return EUIT_INVALID;
//}
namespace ti
{
	//CldLibUI* s_libui	= NULL;
	//static int	AnimFramesPerSecond	= 30;

	//ti_map<ti_string, int>	useful_strings;

	////////////////////////////////////////////////////////////////////////////

	//void UISymbolInstance::SaveAnims(UiInstanceDesc& iDesc, TiStream& anim_stream, ti_vector<ti_string>& string_list)
	//{
	//	iDesc.AnimCount				= Anims.size();
	//	iDesc.AnimOffset			= anim_stream.GetLength();

	//	// save anims
	//	for (int a = 0 ; a < iDesc.AnimCount ; ++ a)
	//	{
	//		UISymbolAnim* anim		= Anims[a];
	//		UiAnimationDesc aDesc;
	//		aDesc.Type				= anim->Type;
	//		aDesc.Flag				= anim->Flag;
	//		if (anim->Type == UISymbolAnim::ANIM_SFX)
	//		{
	//			aDesc.Keys				= anim->StringKeys.size();
	//			anim_stream.Put(&aDesc, sizeof(UiAnimationDesc));
	//			UiAnimKey key;
	//			for (int k = 0 ; k < aDesc.Keys ; ++ k)
	//			{
	//				UiAnimStringKey& str_key	= anim->StringKeys[k];
	//				key.time		= str_key.time;
	//				key.key.X		= (float)AddStringToList(str_key.key, string_list);
	//				anim_stream.Put(&(key), sizeof(UiAnimKey));
	//			}
	//		}
	//		else
	//		{
	//			aDesc.Keys				= anim->Keys.size();
	//			anim_stream.Put(&aDesc, sizeof(UiAnimationDesc));
	//			for (int k = 0 ; k < aDesc.Keys ; ++ k)
	//			{
	//				anim_stream.Put(&(anim->Keys[k]), sizeof(UiAnimKey));
	//			}
	//		}
	//	}
	//}
	////////////////////////////////////////////////////////////////////////////

	//UISymbol::UISymbol(E_UI_TYPE type, const ti_string& name)
	//	: UiType(type)
	//	, UiFlag(0)
	//{
	//	Name		= name;
	//	ImagePath	= name;

	//	Normal		= NULL;
	//	Pressed		= NULL;
	//}

	//UISymbol::~UISymbol()
	//{
	//	ti_vector<UISymbolInstance*>::iterator it;
	//	for (it = Instances.begin() ; it != Instances.end() ; ++ it)
	//	{
	//		UISymbolInstance* info	= *it;
	//		delete info;
	//	}
	//	Instances.clear();
	//}

	//UISymbolInstance* UISymbol::AddInstance(UISymbol* sym)
	//{
	//	UISymbolInstance* instance	= new UISymbolInstance;
	//	instance->Symbol		= sym;

	//	Instances.push_back(instance);

	//	return instance;
	//}

	//UISymbol* UISymbol::RemoveInstance(UISymbolInstance* instance)
	//{
	//	ti_vector<UISymbolInstance*>::iterator it;
	//	it					= std::find(Instances.begin(), Instances.end(), instance);

	//	UISymbol* symbol	= instance->Symbol;
	//	Instances.erase(it);

	//	return symbol;
	//}

	//void UISymbol::RemoveAllInstances()
	//{
	//	ti_vector<UISymbolInstance*>::iterator it;
	//	for (it = Instances.begin() ; it != Instances.end() ; ++ it)
	//	{
	//		UISymbolInstance* info	= *it;
	//		delete info;
	//	}

	//	Instances.clear();
	//}

	//UISymbolInstance* UISymbol::GetInstanceAt(const vector2di& pos)
	//{
	//	int index;
	//	for (index = Instances.size() - 1; index >= 0 ; -- index)
	//	{
	//		UISymbolInstance* instance	= Instances[index];

	//		recti rc					= instance->Symbol->GetRect();
	//		rc.move(instance->Position.X, instance->Position.Y);

	//		if (rc.isPointInside(pos.X, pos.Y))
	//		{
	//			return instance;
	//		}
	//	}

	//	return NULL;
	//}

	//UISymbolInstance* UISymbol::GetInstanceAt(int index)
	//{
	//	TI_ASSERT(index < (int)Instances.size());

	//	return Instances[index];
	//}

	//void UISymbol::LoadInstances(TiXmlElement* sym_root)
	//{
	//	if (UiType == EUIT_SYMBOL ||
	//		UiType == EUIT_DIALOG ||
	//		UiType == EUIT_BUTTON ||
	//		UiType == EUIT_CHARACTER ||
	//		UiType == EUIT_SCROLLAREA ||
	//		UiType == EUIT_EASYBUTTON)
	//	{
	//		// load instances
	//		TiXmlElement* xml_ins		= sym_root->FirstChildElement("instance");

	//		while (xml_ins)
	//		{
	//			ti_string sym_name		= xml_ins->Attribute("symbol");
	//			UISymbol* symbol		= s_libui->GetSymbolByName(sym_name);
	//			UISymbolInstance* ins	= AddInstance(symbol);

	//			LoadInstanceAnim(xml_ins, ins);

	//			int x, y;
	//			double sx, sy;
	//			xml_ins->Attribute("x", &x);
	//			xml_ins->Attribute("y", &y);
	//			xml_ins->Attribute("sx", &sx);
	//			xml_ins->Attribute("sy", &sy);
	//			ins->InstanceId			= xml_ins->Attribute("id");
	//			ins->Position			= vector2di(x, y);
	//			ins->Scale				= vector2df((float)sx, (float)sy);

	//			TiXmlElement* xml_flag	= xml_ins->FirstChildElement("flag");
	//			if (xml_flag)
	//			{
	//				const char* flag_str	= xml_flag->Attribute("value");
	//				ins->SetFlag(atol(flag_str));
	//				if (xml_flag->Attribute("value1"))
	//				{
	//					ins->SetFlag1(atol(xml_flag->Attribute("value1")));
	//				}
	//			}
	//			else
	//			{
	//				ins->SetFlag(UISymbolInstance::FLAG_VISIBLE);
	//			}

	//			if (xml_ins->Attribute("align_h"))
	//				ins->AlignH			= GetAlignTypeByName(xml_ins->Attribute("align_h"));
	//			else
	//				ins->AlignH			= EUI_ALIGN_LEFT;
	//			if (xml_ins->Attribute("align_v"))
	//				ins->AlignV			= GetAlignTypeByName(xml_ins->Attribute("align_v"));
	//			else
	//				ins->AlignV			= EUI_ALIGN_TOP;

	//			TiXmlElement* xml_scrip	= xml_ins->FirstChildElement("script");
	//			if (xml_scrip)
	//			{
	//				ins->Script			= xml_scrip->FirstChild()->ToText()->Value();
	//			}

	//			TiXmlElement* xml_text	= xml_ins->FirstChildElement("text");
	//			if (xml_text)
	//			{
	//				ti_string text_id;
	//				if (xml_text->Attribute("index"))
	//					text_id			= xml_text->Attribute("index");
	//				ins->TextId			= text_id;
	//				if (ins->TextId != "")
	//				{
	//					useful_strings[ins->TextId]	= 1;
	//				}
	//			}

	//			TiXmlElement* xml_tc	= xml_ins->FirstChildElement("textcolor");
	//			if (xml_tc)
	//			{
	//				ti_vector<int>	int_array;
	//				ReadIntArray(xml_tc->FirstChild()->ToText()->Value(), int_array);
	//				ins->TextColor		= SColor(int_array[0], int_array[1], int_array[2], int_array[3]);
	//			}
	//			TiXmlElement* xml_tbc	= xml_ins->FirstChildElement("bordercolor");
	//			if (xml_tbc)
	//			{
	//				ti_vector<int>	int_array;
	//				ReadIntArray(xml_tbc->FirstChild()->ToText()->Value(), int_array);
	//				ins->BorderColor		= SColor(int_array[0], int_array[1], int_array[2], int_array[3]);
	//			}
	//			TiXmlElement* xml_tgc	= xml_ins->FirstChildElement("gradientcolor");
	//			if (xml_tgc)
	//			{
	//				ti_vector<int>	int_array;
	//				ReadIntArray(xml_tgc->FirstChild()->ToText()->Value(), int_array);
	//				ins->GradientColor		= SColor(int_array[0], int_array[1], int_array[2], int_array[3]);
	//			}
	//			TiXmlElement* xml_fs		= xml_ins->FirstChildElement("font_size");
	//			if (xml_fs)
	//			{
	//				ins->FontSize			= atoi(xml_fs->FirstChild()->ToText()->Value());
	//			}
	//			else
	//				ins->FontSize			= 16;
	//			TiXmlElement* xml_mlm		= xml_ins->FirstChildElement("multi_line_max");
	//			if (xml_mlm)
	//			{
	//				ins->MultilineMax		= atoi(xml_mlm->FirstChild()->ToText()->Value());
	//			}
	//			else
	//				ins->MultilineMax		= 0;

	//			TiXmlElement* xml_text_offset= xml_ins->FirstChildElement("text_offset");
	//			if (xml_text_offset)
	//			{
	//				ti_vector<int> int_array;
	//				ReadIntArray(xml_text_offset->FirstChild()->ToText()->Value(), int_array);
	//				TI_ASSERT(int_array.size() == 2);
	//				ins->TextHOffset		= int_array[0];
	//				ins->TextVOffset		= int_array[1];
	//			}
	//			else
	//			{
	//				ins->TextHOffset	= 0;
	//				ins->TextVOffset	= 0;
	//			}

	//			TiXmlElement* xml_scroll_child= xml_ins->FirstChildElement("scroll_child_size");
	//			if (xml_scroll_child)
	//			{
	//				ti_vector<int> int_array;
	//				ReadIntArray(xml_scroll_child->FirstChild()->ToText()->Value(), int_array);
	//				TI_ASSERT(int_array.size() == 2);
	//				ins->ScrollChildW		= int_array[0];
	//				ins->ScrollChildH		= int_array[1];
	//			}

	//			TiXmlElement* xml_font	= xml_ins->FirstChildElement("font");
	//			if (xml_font)
	//			{
	//				ins->FontName		= xml_font->FirstChild()->ToText()->Value();
	//			}

	//			TiXmlElement* xml_sfx	= xml_ins->FirstChildElement("sfx");
	//			if (xml_sfx)
	//			{
	//				if (xml_sfx->FirstChild())
	//					ins->Sfx		= xml_sfx->FirstChild()->ToText()->Value();
	//			}

	//			TiXmlElement* xml_m_anim	= xml_ins->FirstChildElement("model_anim");
	//			if (xml_m_anim)
	//			{
	//				if (xml_m_anim->FirstChild())
	//					ins->Anim		= xml_m_anim->FirstChild()->ToText()->Value();
	//			}

	//			TiXmlElement* xml_cam_pos = xml_ins->FirstChildElement("cam_position");
	//			if (xml_cam_pos)
	//			{
	//				if (xml_cam_pos->FirstChild())
	//				{
	//					ti_vector<float> arr;
	//					ReadFloatArray(xml_cam_pos->FirstChild()->ToText()->Value(), arr);
	//					ins->CamPosition = vector3df(arr[0], arr[1], arr[2]);
	//				}
	//			}

	//			TiXmlElement* xml_cam_target = xml_ins->FirstChildElement("cam_target");
	//			if (xml_cam_target)
	//			{
	//				if (xml_cam_target->FirstChild())
	//				{
	//					ti_vector<float> arr;
	//					ReadFloatArray(xml_cam_target->FirstChild()->ToText()->Value(), arr);
	//					ins->CamTarget = vector3df(arr[0], arr[1], arr[2]);
	//				}
	//			}

	//			TiXmlElement* xml_fan	= xml_ins->FirstChildElement("fan_range");
	//			if (xml_fan)
	//			{
	//				ti_vector<int> int_array;
	//				ReadIntArray(xml_fan->FirstChild()->ToText()->Value(), int_array);
	//				ins->FanStart		= int_array[0];
	//				ins->FanEnd			= int_array[1];
	//			}

	//			TiXmlElement* xml_scroll	= xml_ins->FirstChildElement("scroll_dir");
	//			if (xml_scroll)
	//			{
	//				const char* sdir	= xml_scroll->FirstChild()->ToText()->Value();
	//				if (strcmp(sdir, "horizontal") == 0)
	//					ins->ScrollDir	= UISymbolInstance::SCROLL_H;
	//				else
	//					ins->ScrollDir	= UISymbolInstance::SCROLL_V;
	//			}
	//			else
	//				ins->ScrollDir		= UISymbolInstance::SCROLL_V;

	//			xml_ins					= xml_ins->NextSiblingElement("instance");
	//		}

	//		if (UiType == EUIT_SCROLLAREA)
	//		{
	//			// load width and height
	//			TiXmlElement* xml_w		= sym_root->FirstChildElement("width");
	//			TI_ASSERT(xml_w);
	//			int w					= atoi(xml_w->FirstChild()->ToText()->Value());

	//			TiXmlElement* xml_h		= sym_root->FirstChildElement("height");
	//			TI_ASSERT(xml_h);
	//			int h					= atoi(xml_h->FirstChild()->ToText()->Value());

	//			BoundRect				= recti(0, 0, w, h);
	//		}
	//		else
	//			UpdateBoundingRect();
	//	}
	//	else if (UiType == EUIT_DIALOG_9)
	//	{
	//		// load width and height
	//		TiXmlElement* xml_w			= sym_root->FirstChildElement("width");
	//		TI_ASSERT(xml_w);
	//		int w						= atoi(xml_w->FirstChild()->ToText()->Value());

	//		TiXmlElement* xml_h			= sym_root->FirstChildElement("height");
	//		TI_ASSERT(xml_h);
	//		int h						= atoi(xml_h->FirstChild()->ToText()->Value());

	//		TiXmlElement* xml_sx		= sym_root->FirstChildElement("split_x");
	//		TI_ASSERT(xml_sx);
	//		int sx						= atoi(xml_sx->FirstChild()->ToText()->Value());

	//		TiXmlElement* xml_sy		= sym_root->FirstChildElement("split_y");
	//		TI_ASSERT(xml_sy);
	//		int sy						= atoi(xml_sy->FirstChild()->ToText()->Value());

	//		SplitPoint.X				= sx;
	//		SplitPoint.Y				= sy;
	//		BoundRect					= recti(0, 0, w, h);

	//		// load instances
	//		TiXmlElement* xml_ins		= sym_root->FirstChildElement("instance");
	//		TI_ASSERT(xml_ins != NULL);	// can have only one instance

	//		ti_string sym_name			= xml_ins->Attribute("symbol");
	//		UISymbol* symbol			= s_libui->GetSymbolByName(sym_name);
	//		UISymbolInstance* ins		= AddInstance(symbol);
	//	}
	//	else if (UiType == EUIT_IMAGE ||
	//			 UiType == EUIT_TEXTBOX ||
	//			 UiType == EUIT_ICONBOX ||
	//			 UiType == EUIT_EVENTMASK ||
	//			 UiType == EUIT_DRAWBOX)
	//	{
	//		// load width and height
	//		TiXmlElement* xml_w			= sym_root->FirstChildElement("width");
	//		TI_ASSERT(xml_w);
	//		int w						= atoi(xml_w->FirstChild()->ToText()->Value());

	//		TiXmlElement* xml_h			= sym_root->FirstChildElement("height");
	//		TI_ASSERT(xml_h);
	//		int h						= atoi(xml_h->FirstChild()->ToText()->Value());

	//		BoundRect					= recti(0, 0, w, h);
	//	}
	//	else if (UiType == EUIT_FAN)
	//	{
	//		// load width and height
	//		TiXmlElement* xml_w			= sym_root->FirstChildElement("width");
	//		TI_ASSERT(xml_w);
	//		int w						= atoi(xml_w->FirstChild()->ToText()->Value());

	//		TiXmlElement* xml_h			= sym_root->FirstChildElement("height");
	//		TI_ASSERT(xml_h);
	//		int h						= atoi(xml_h->FirstChild()->ToText()->Value());

	//		BoundRect					= recti(0, 0, w, h);

	//		// load first instance
	//		TiXmlElement* xml_ins		= sym_root->FirstChildElement("instance");
	//		TI_ASSERT(xml_ins)
	//		if (xml_ins)
	//		{
	//			ti_string sym_name		= xml_ins->Attribute("symbol");
	//			UISymbol* symbol		= s_libui->GetSymbolByName(sym_name);
	//			TI_ASSERT(symbol->GetType() == EUIT_IMAGE);
	//			UISymbolInstance* ins	= AddInstance(symbol);

	//			int x, y;
	//			double sx, sy;
	//			xml_ins->Attribute("x", &x);
	//			xml_ins->Attribute("y", &y);
	//			xml_ins->Attribute("sx", &sx);
	//			xml_ins->Attribute("sy", &sy);
	//			ins->InstanceId			= xml_ins->Attribute("id");
	//			ins->Position			= vector2di(x, y);
	//			ins->Scale				= vector2df((float)sx, (float)sy);

	//			if (xml_ins->Attribute("align_h"))
	//				ins->AlignH			= GetAlignTypeByName(xml_ins->Attribute("align_h"));
	//			else
	//				ins->AlignH			= EUI_ALIGN_LEFT;
	//			if (xml_ins->Attribute("align_v"))
	//				ins->AlignV			= GetAlignTypeByName(xml_ins->Attribute("align_v"));
	//			else
	//				ins->AlignV			= EUI_ALIGN_TOP;

	//			TiXmlElement* xml_flag	= xml_ins->FirstChildElement("flag");
	//			if (xml_flag)
	//			{
	//				const char* flag_str	= xml_flag->Attribute("value");
	//				ins->SetFlag(atol(flag_str));
	//				if (flag_str = xml_flag->Attribute("value1"))
	//				{
	//					ins->SetFlag1(atol(flag_str));
	//				}
	//			}
	//			else
	//			{
	//				ins->SetFlag(UISymbolInstance::FLAG_VISIBLE);
	//			}
	//		}
	//	}
	//}

	//static const char* animation_types[] = 
	//{
	//	"anim_position",
	//	"anim_scale",
	//	"anim_size",
	//	"anim_sfx",
	//	"anim_alpha",
	//	"anim_bounce",
	//};

	//int GetTypeByAnimTypeName(const char* name)
	//{
	//	for (int i = 0 ; i < UISymbolAnim::ANIM_TYPES ; ++ i)
	//	{
	//		if (strcmp(animation_types[i], name) == 0)
	//		{
	//			return i;
	//		}
	//	}
	//	return UISymbolAnim::ANIM_POSITION;
	//}
	//void UISymbol::LoadInstanceAnim(TiXmlElement* ins_root, UISymbolInstance* instance)
	//{
	//	const float fps_inv				= 1.f / AnimFramesPerSecond;
	//	instance->ClearAnims();

	//	TiXmlElement* xml_anim			= ins_root->FirstChildElement("animation");
	//	while (xml_anim)
	//	{
	//		UISymbolAnim* anim			= ti_new UISymbolAnim;
	//		anim->Type					= UISymbolAnim::ANIM_POSITION;
	//		if (xml_anim->Attribute("type"))
	//		{
	//			anim->Type				= GetTypeByAnimTypeName(xml_anim->Attribute("type"));
	//		}
	//		anim->Flag					= 0;
	//		if (xml_anim->Attribute("loop"))
	//		{
	//			if (strcmp(xml_anim->Attribute("loop"), "true") == 0)
	//			{
	//				anim->Flag			|= UISymbolAnim::ANIM_FLAG_LOOP;
	//			}
	//		}

	//		if (anim->Type == UISymbolAnim::ANIM_SFX)
	//		{
	//			TiXmlElement* xml_key		= xml_anim->FirstChildElement("key");
	//			while (xml_key)
	//			{
	//				ti_vector<float> float_array;
	//				UiAnimStringKey key;
	//				TiXmlElement *xml_frame, *xml_value;
	//				xml_frame				= xml_key->FirstChildElement("frame");
	//				xml_value				= xml_key->FirstChildElement("value");
	//				TI_ASSERT(xml_frame && xml_value);

	//				ReadFloatArray(xml_frame->FirstChild()->ToText()->Value(), float_array);
	//				key.time				= float_array[0] * fps_inv;

	//				key.key					= xml_value->FirstChild()->ToText()->Value();
	//				anim->StringKeys.push_back(key);

	//				xml_key					= xml_key->NextSiblingElement("key");
	//			}
	//		}
	//		else
	//		{
	//			ti_vector<float> float_array;
	//			TiXmlElement* xml_key		= xml_anim->FirstChildElement("key");
	//			while (xml_key)
	//			{
	//				UiAnimKey key;
	//				TiXmlElement *xml_frame, *xml_value;
	//				xml_frame				= xml_key->FirstChildElement("frame");
	//				xml_value				= xml_key->FirstChildElement("value");
	//				TI_ASSERT(xml_frame && xml_value);

	//				float_array.clear();
	//				ReadFloatArray(xml_frame->FirstChild()->ToText()->Value(), float_array);
	//				key.time				= float_array[0] * fps_inv;
	//				float_array.clear();
	//				ReadFloatArray(xml_value->FirstChild()->ToText()->Value(), float_array);
	//				TI_ASSERT(float_array.size() == 4);
	//				key.key.X				= float_array[0];
	//				key.key.Y				= float_array[1];
	//				key.key.Z				= float_array[2];
	//				key.key.W				= float_array[3];

	//				anim->Keys.push_back(key);

	//				xml_key					= xml_key->NextSiblingElement("key");
	//			}
	//		}

	//		instance->Anims.push_back(anim);

	//		xml_anim					= xml_anim->NextSiblingElement("animation");
	//	}
	//}

	//void UISymbol::UpdateBoundingRect()
	//{
	//	// calc rect
	//	if (Instances.size() > 0)
	//	{
	//		recti bbox				= Instances[0]->Symbol->BoundRect;
	//		bbox.move(Instances[0]->Position.X, Instances[0]->Position.Y);
	//		BoundRect				= bbox;

	//		for (u32 i = 1 ; i < Instances.size() ; ++ i)
	//		{
	//			bbox				= Instances[i]->Symbol->BoundRect;
	//			bbox.move(Instances[i]->Position.X, Instances[i]->Position.Y);
	//			if (Instances[i]->Symbol->GetType() == EUIT_IMAGE)
	//			{
	//				bbox.Right			= bbox.Left + int(bbox.getWidth() * Instances[i]->Scale.X);
	//				bbox.Lower			= bbox.Upper + int(bbox.getHeight() * Instances[i]->Scale.Y);
	//			}
	//			BoundRect.addInternalRect(bbox);
	//		}
	//	}
	//}

	//////////////////////////////////////////////////////////////////////////

	CldLibUI::CldLibUI()
	{
	}

	CldLibUI::~CldLibUI()
	{
	}

	static const int total_langs			= 13;
	static const char* string_lang_ext[total_langs] = 
	{
		"en",
		"zh",
		"de",
		"ar",
		"es",
		"fr",
		"it",
		"jp",
		"kr",
		"ptbr",
		"pt",
		"ru",
		"tw"
	};

	bool CldLibUI::ConvertFromFbx(FbxNode* node)
	{


		Loaded	= true;
		return true;
	}

	//void CldLibUI::LoadUIStrings()
	//{
	//	const ti_string& string_fn			= "ui_strings.xml";
	//	ti_map<ti_string, UiString> all_strings;

	//	TiXmlDocument doc_strings;
	//	bool result							= doc_strings.LoadFile(string_fn.c_str());
	//	TI_ASSERT(result);

	//	// load all strings
	//	//TiXmlElement* xml_root				= doc_strings.FirstChildElement("COLLADA");
	//	TiXmlElement* xml_strings			= doc_strings.FirstChildElement("strings");
	//	if (xml_strings)
	//	{
	//		TiXmlElement* xml_string		= xml_strings->FirstChildElement("string");
	//		while (xml_string)
	//		{
	//			UiString str;
	//			str.tid						= xml_string->Attribute("id");
	//			if (!str.tid.empty())
	//			{
	//				TiXmlElement* xml_t		= xml_string->FirstChildElement("text");
	//				while (xml_t)
	//				{
	//					const char* lang	= xml_t->Attribute("lang");
	//					if (xml_t->FirstChild())
	//					{
	//						const char* utf_str	= xml_t->FirstChild()->ToText()->Value();
	//						const int str_len	= strlen(utf_str);
	//						int uni_len			= 0;
	//						u16* unicode_str	= TiUString::FromUtf8ToUnicode((const u8*)utf_str, str_len, &uni_len);
	//						TiUString u_str		= unicode_str;
	//						str.strings[lang]	= u_str;
	//						ti_delete[] unicode_str;
	//					}
	//					else
	//					{
	//						str.strings[lang]	= str.strings["en"];
	//						_LOG("  Warning: can not load string [%s] for lang [%s], use EN instead.\n", str.tid.c_str(), lang);
	//					}
	//					xml_t				= xml_t->NextSiblingElement("text");
	//				}

	//				all_strings[str.tid]	= str;
	//			}

	//			xml_string					= xml_string->NextSiblingElement("string");
	//		}
	//	}

	//	ui_strings.clear();
	//	// remove unused strings
	//	ti_map<ti_string, int>::iterator it;
	//	for (it = useful_strings.begin() ; it != useful_strings.end() ; ++ it)
	//	{
	//		const ti_string& ui_str			= it->first;
	//		if (all_strings.find(ui_str) != all_strings.end())
	//		{
	//			ui_strings.push_back(all_strings[ui_str]);
	//		}
	//	}

	//	TiColladaConfig& config				= TiCollada::Get()->Config;

	//	for (int l = 0 ; l < total_langs ; ++ l)
	//	{
	//		ti_string string_file_path		= config.InputFilename;
	//		ti_string string_file_opath		= config.OutputFilename;
	//		size_t ext_pos					= string_file_path.find(".DAE");
	//		if (ext_pos != ti_string::npos)
	//		{
	//			ti_string fn				= string_file_path.substr(0, ext_pos);
	//			string_file_opath			= fn + "_" + string_lang_ext[l] + ".str";
	//		}
	//		else
	//		{
	//			ti_string fn				= string_file_path;
	//			string_file_opath			= fn + "_" + string_lang_ext[l] + ".str";
	//		}

	//		SaveStrings(string_file_opath, ui_strings, string_lang_ext[l]);

	//		if (config.ExportStrToCSV)
	//		{
	//			ExportToCSV(l);
	//		}
	//	}
	//}

	//int CldLibUI::GetStringIndex(const ti_string& tid)
	//{
	//	for (int i = 0 ; i < (int)ui_strings.size() ; ++ i)
	//	{
	//		if (ui_strings[i].tid == tid)
	//			return i;
	//	}
	//	return -1;
	//}

	//void CldLibUI::LoadStringStandard(TiXmlElement* str_root)
	//{
	//	//StringStandard.clear();
	//	//TiXmlElement* ele_str		= str_root->FirstChildElement("string");

	//	//u16* unicode_buffer			= NULL;
	//	//int unicode_size			= 0;

	//	//while (ele_str)
	//	//{
	//	//	UiString ui_str;
	//	//	ui_str.tid				= ele_str->Attribute("id");

	//	//	if (ui_str.tid != "")
	//	//	{
	//	//		TiXmlElement* ele_text	= ele_str->FirstChildElement("text");
	//	//		TI_ASSERT(ele_text);
	//	//		const char* text	= ele_text->FirstChild()->ToText()->Value();

	//	//		utf8_to_unicode((const u8*)text, &unicode_buffer, &unicode_size);

	//	//		ui_str.SetText(unicode_buffer, unicode_size);

	//	//		StringStandard.push_back(ui_str);
	//	//	}
	//	//	if (unicode_buffer)
	//	//	{
	//	//		free(unicode_buffer);
	//	//		unicode_buffer		= NULL;
	//	//	}
	//	//	ele_str					= ele_str->NextSiblingElement("string");
	//	//}
	//}

	//void CldLibUI::LoadStrings(TiXmlElement* str_root)
	//{
	//	//Strings.clear();
	//	//TiXmlElement* ele_str		= str_root->FirstChildElement("string");

	//	//u16* unicode_buffer			= NULL;
	//	//int unicode_size			= 0;

	//	//while (ele_str)
	//	//{
	//	//	UiString ui_str;
	//	//	ui_str.tid				= ele_str->Attribute("id");

	//	//	if (ui_str.tid != "")
	//	//	{
	//	//		TiXmlElement* ele_text	= ele_str->FirstChildElement("text");
	//	//		TI_ASSERT(ele_text);
	//	//		const char* text	= ele_text->FirstChild()->ToText()->Value();

	//	//		utf8_to_unicode((const u8*)text, &unicode_buffer, &unicode_size);

	//	//		ui_str.SetText(unicode_buffer, unicode_size);
	//	//		Strings.push_back(ui_str);
	//	//	}
	//	//	if (unicode_buffer)
	//	//	{
	//	//		free(unicode_buffer);
	//	//		unicode_buffer		= NULL;
	//	//	}
	//	//	ele_str					= ele_str->NextSiblingElement("string");
	//	//}
	//}

	//UiString GetStringById(const ti_vector<UiString>& strings, const ti_string& string_id)
	//{
	//	for (u32 s = 0 ; s < strings.size() ; ++ s)
	//	{
	//		if (strings[s].tid == string_id)
	//		{
	//			return strings[s];
	//		}
	//	}

	//	u16 buf[1];
	//	buf[0]		= 0;
	//	UiString string;
	//	string.tid		= string_id;
	//	//string.SetText(buf, 1 * sizeof(u16));
	//	return string;
	//}

	//void CldLibUI::SaveStrings(const ti_string& filename, ti_vector<UiString>& strings, const char* lang)
	//{
	//	// save strings
	//	TiStream stream;

	//	char zero[4] = {0};

	//	int* string_offsets = ti_new int[strings.size()];
	//	int offset = 0;
	//	for (int i = 0 ; i < (int)strings.size() ; ++ i)
	//	{
	//		UiString& s		= strings[i];
	//		offset += ((s.GetText(lang).Size() * sizeof(u16) + 4) & ~3);
	//		string_offsets[i] = offset;
	//	}

	//	stream.Put(string_offsets, strings.size() * sizeof(int));
	//	for (int i = 0 ; i < (int)strings.size() ; ++ i)
	//	{
	//		UiString& s		= strings[i];
	//		const TiUString& us	= s.GetText(lang);
	//		int len = ((us.Size() * sizeof(u16) + 4) & ~3);
	//		int real_len = us.Size() * sizeof(u16);
	//		stream.Put(us.CStr(), real_len);
	//		stream.Put(zero, len - real_len);;
	//	}
	//	ti_delete[] string_offsets;


	//	u32 fid			= TIRES_ID_CHUNK_STRING;
	//	u32 s_count		= strings.size();

	//	TiFile f;
	//	if (f.Open(filename, EFA_CREATEWRITE))
	//	{
	//		f.Write(&fid, 4);
	//		f.Write(&s_count, 4);
	//		f.Write(stream.GetBuffer(), stream.GetLength());
	//		f.Close();
	//	}
	//}

	//void CldLibUI::ExportToCSV(int l)
	//{
	//	//TiColladaConfig& config			= TiCollada::Get()->Config;
	//	//{
	//	//	ti_string string_file_path		= config.InputFilename;
	//	//	ti_string string_file_opath		= config.OutputFilename;
	//	//	size_t ext_pos					= string_file_path.find(".DAE");

	//	//	if (ext_pos != ti_string::npos)
	//	//	{
	//	//		ti_string fn				= string_file_path.substr(0, ext_pos);
	//	//		string_file_path			= fn + "." + string_lang_ext[l];
	//	//		string_file_opath			= fn + "_" + string_lang_ext[l] + ".txt";
	//	//	}
	//	//	else
	//	//	{
	//	//		ti_string fn				= string_file_path;
	//	//		string_file_path			= fn + "." + string_lang_ext[l];
	//	//		string_file_opath			= fn + "_" + string_lang_ext[l] + ".txt";
	//	//	}


	//	//	// sort strings with standard order
	//	//	ti_vector<UiString> string_sorted;
	//	//	for (u32 s = 0 ; s < StringStandard.size() ; ++ s)
	//	//	{
	//	//		UiString ustr	= GetStringById(Strings, StringStandard[s].tid);
	//	//		if (ustr.text ==  NULL || ustr.text[0] == 0)
	//	//		{
	//	//			ustr		= StringStandard[s];
	//	//		}
	//	//		string_sorted.push_back(ustr);
	//	//	}

	//	//	// save strings
	//	//	TiStream stream;

	//	//	char zero[4] = {0};
	//	//	TiStream utf_buffer;

	//	//	for (int i = 0 ; i < (int)string_sorted.size() ; ++ i)
	//	//	{
	//	//		const UiString& s	= string_sorted[i];
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put(string_file_path.c_str(), string_file_path.length());
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put(";", 1);
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put(s.tid.c_str(), s.tid.length());
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put(";", 1);

	//	//		u8 *result;
	//	//		int size			= unicode_to_utf8(s.text, s.buf_size, &result);
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put(result, size);
	//	//		utf_buffer.Put("\"", 1);
	//	//		utf_buffer.Put("\n", 1);
	//	//		ti_delete result;
	//	//	}

	//	//	TiFile f;
	//	//	if (f.Open(string_file_opath, EFA_CREATEWRITE))
	//	//	{
	//	//		f.Write(utf_buffer.GetBuffer(), utf_buffer.GetLength());
	//	//		f.Close();
	//	//	}
	//	//}
	//}

	//void CldLibUI::CheckSymbols(UISymbol* root)
	//{
	//	for (int i = 0 ; i < root->GetInstancesCount() ; ++ i)
	//	{
	//		UISymbolInstance* instance	= root->GetInstanceAt(i);
	//		if ((instance->Symbol->UiFlag & UISYM_USED) == 0)
	//		{
	//			++ UsefulSymbol;
	//			instance->Symbol->UiFlag	|= UISYM_USED;
	//		}

	//		CheckSymbols(instance->Symbol);
	//	}
	//}

	bool CldLibUI::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		//TiResfileChunkHeader header;
		//header.ID			= TIRES_ID_CHUNK_UI;
		//header.Version		= TIRES_VERSION_CHUNK_TIUI;
		//header.ElementCount	= UsefulSymbol + 1;	// symbols and a root
		//header.ChunkSize	= sizeof(TiResfileChunkHeader);

		//TiColladaConfig& config	= TiCollada::Get()->Config;

		//TiStream stream, anim_stream;

		//UiChunkCommon chunkCommon;
		//chunkCommon.AnimTotal	= 0;
		//chunkCommon.AnimOffset	= 0;
		//chunkCommon.SfxCount	= EUI_SFX_COUNT;

		//// sound fx
		//for (int s = 0 ; s < chunkCommon.SfxCount ; ++ s)
		//{
		//	int index			= AddStringToList(Sfx[s], string_list);
		//	stream.Put(&index, sizeof(int));
		//}

		//// atlas
		//UiAtlasDesc aDesc;
		//ti_string atlas_path	= config.UiAtlas;
		//size_t pos				= atlas_path.rfind("/");
		//if (pos != ti_string::npos)
		//{
		//	atlas_path			= config.TexturePath + "/" + atlas_path.substr(pos + 1);
		//}
		//else
		//{
		//	atlas_path			= config.TexturePath + "/" + atlas_path;
		//}

		//aDesc.FilenameIndex		= AddStringToList(atlas_path, string_list);
		//aDesc.Width				= config.AtlasSize.X;
		//aDesc.Height			= config.AtlasSize.Y;
		//stream.Put(&aDesc, sizeof(UiAtlasDesc));

		//int instance_offset			= 0;

		//// root
		//UiSymbolDesc rDesc;
		//rDesc.NameIndex				= AddStringToList(SceneRoot->GetName(), string_list);
		//rDesc.InstanceCount			= SceneRoot->GetInstancesCount();
		//rDesc.InstanceOffset		= instance_offset;
		//instance_offset				+= rDesc.InstanceCount;
		//stream.Put(&rDesc, sizeof(UiSymbolDesc));

		//// symbols
		//int symbol_saved			= 0;
		//for (u32 i = 0 ; i < Symbols.size() ; ++ i)
		//{
		//	UISymbol* symbol	= Symbols[i];
		//	if (symbol->UiFlag & UISYM_USED)
		//	{
		//		UiSymbolDesc sDesc;
		//		sDesc.NameIndex			= AddStringToList(symbol->GetName(), string_list);
		//		sDesc.InstanceCount		= symbol->GetInstancesCount();
		//		sDesc.InstanceOffset	= instance_offset;
		//		instance_offset			+= sDesc.InstanceCount;
		//		sDesc.Type				= symbol->GetType();
		//		if (sDesc.Type == EUIT_IMAGE ||
		//			sDesc.Type == EUIT_TEXTBOX ||
		//			sDesc.Type == EUIT_ICONBOX ||
		//			sDesc.Type == EUIT_SCROLLAREA ||
		//			sDesc.Type == EUIT_EVENTMASK ||
		//			sDesc.Type == EUIT_FAN ||
		//			sDesc.Type == EUIT_DRAWBOX)
		//		{
		//			sDesc.X				= symbol->Offset.X;
		//			sDesc.Y				= symbol->Offset.Y;
		//			sDesc.W				= symbol->BoundRect.getWidth();
		//			sDesc.H				= symbol->BoundRect.getHeight();
		//		}
		//		else
		//		{
		//			sDesc.X				= symbol->BoundRect.Left;
		//			sDesc.Y				= symbol->BoundRect.Upper;
		//			sDesc.W				= symbol->BoundRect.getWidth();
		//			sDesc.H				= symbol->BoundRect.getHeight();
		//			if (sDesc.Type == EUIT_DIALOG_9)
		//			{
		//				sDesc.splitX	= symbol->SplitPoint.X;
		//				sDesc.splitY	= symbol->SplitPoint.Y;
		//			}
		//		}

		//		stream.Put(&sDesc, sizeof(UiSymbolDesc));
		//		++ symbol_saved;
		//	}
		//}
		//TI_ASSERT(symbol_saved == UsefulSymbol);

		//// root instances
		//for (int i = 0 ; i < SceneRoot->GetInstancesCount() ; ++ i)
		//{
		//	UiInstanceDesc riDesc;
		//	UISymbolInstance* instance	= SceneRoot->GetInstanceAt(i);
		//	riDesc.IdIndex				= AddStringToList(instance->InstanceId, string_list);
		//	riDesc.SymbolNameIndex		= AddStringToList(instance->Symbol->GetName(), string_list);
		//	if (instance->TextId == "")
		//		riDesc.TextIndex		= -1;
		//	else
		//		riDesc.TextIndex		= s_libui->GetStringIndex(instance->TextId);

		//	if (instance->Script == "")
		//		riDesc.ScriptIndex		= -1;
		//	else
		//		riDesc.ScriptIndex		= AddStringToList(instance->Script, string_list);
		//	if (instance->FontName == "")
		//		riDesc.FontIndex		= -1;
		//	else
		//		riDesc.FontIndex		= AddStringToList(instance->FontName, string_list);
		//	riDesc.PosX					= instance->Position.X;
		//	riDesc.PosY					= instance->Position.Y;
		//	riDesc.ScaleX				= instance->Scale.X;
		//	riDesc.ScaleY				= instance->Scale.Y;
		//	riDesc.FanStart				= instance->FanStart;
		//	riDesc.FanEnd				= instance->FanEnd;
		//	riDesc.TextColor			= instance->TextColor;
		//	riDesc.BorderColor			= instance->BorderColor;
		//	riDesc.GradientColor		= instance->GradientColor;
		//	riDesc.ScrollDir			= instance->ScrollDir;
		//	riDesc.FontSize				= instance->FontSize;
		//	riDesc.MultilineMax			= instance->MultilineMax;
		//	riDesc.TextHOffset			= instance->TextHOffset;
		//	riDesc.TextVOffset			= instance->TextVOffset;
		//	riDesc.CamPosition			= instance->CamPosition;
		//	riDesc.CamTarget			= instance->CamTarget;
		//	riDesc.ScrollChildW			= instance->ScrollChildW;
		//	riDesc.ScrollChildH			= instance->ScrollChildH;
		//	instance->SaveAnims(riDesc, anim_stream, string_list);
		//	chunkCommon.AnimTotal		+= instance->Anims.size();

		//	if ((instance->GetFlag(UISymbolInstance::FLAG_VISIBLE)))
		//		riDesc.Flag				|= EUNCF_VISIBLE;
		//	else
		//		riDesc.Flag				&= ~EUNCF_VISIBLE;
		//	if ((instance->GetFlag(UISymbolInstance::FLAG_FLIP_H)))
		//		riDesc.Flag				|= EUNCF_FLIP_H;
		//	else
		//		riDesc.Flag				&= ~EUNCF_FLIP_H;
		//	if ((instance->GetFlag(UISymbolInstance::FLAG_FLIP_V)))
		//		riDesc.Flag				|= EUNCF_FLIP_V;
		//	else
		//		riDesc.Flag				&= ~EUNCF_FLIP_V;
		//	if ((instance->GetFlag(UISymbolInstance::FLAG_ENABLE_CLIP)))
		//		riDesc.Flag				|= EUNCF_ENABLE_CLIP;
		//	else
		//		riDesc.Flag				&= ~EUNCF_ENABLE_CLIP;
		//	if ((instance->GetFlag(UISymbolInstance::FLAG_DEFAULT_ANIMATION)))
		//		riDesc.Flag				|= EUNCF_DEFAULT_ANIMATION;
		//	else
		//		riDesc.Flag				&= ~EUNCF_DEFAULT_ANIMATION;

		//	if (instance->Symbol->GetType() == EUIT_BUTTON ||
		//		instance->Symbol->GetType() == EUIT_EASYBUTTON ||
		//		instance->Symbol->GetType() == EUIT_TEXTBOX)
		//	{
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_LIMIT_LENGTH)))
		//			riDesc.ExtraFlag		|= EUNEF_TEXT_LIMITLENGTH;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_TEXT_LIMITLENGTH;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_USE_INTERNAL_CHARACTER)))
		//			riDesc.ExtraFlag		|= EUNEF_USE_INTERNAL_CHARACTER;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_USE_INTERNAL_CHARACTER;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_HAS_BORDER)))
		//			riDesc.ExtraFlag		|= EUNEF_TEXT_WITH_BORDER;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_TEXT_WITH_BORDER;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_HAS_GRADIENT)))
		//			riDesc.ExtraFlag		|= EUNEF_TEXT_WITH_GRADIENT;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_TEXT_WITH_GRADIENT;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_CHECKABLE)))
		//			riDesc.ExtraFlag		|= EUNEF_CHECKABLE;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_CHECKABLE;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_CHECKED)))
		//			riDesc.ExtraFlag		|= EUNEF_CHECKED;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_CHECKED;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_AUTO_FIT_HEIGHT)))
		//			riDesc.ExtraFlag		|= EUNEF_MULTI_AUTO_HEIGHT;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_MULTI_AUTO_HEIGHT;
		//		if ((instance->GetFlag1(UISymbolInstance::FLAG_SYSTEM_FONT)))
		//			riDesc.ExtraFlag		|= EUNEF_SYSTEM_FONT;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_SYSTEM_FONT;
		//	}

		//	if (instance->Symbol->GetType() == EUIT_SCROLLAREA)
		//	{
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_ALIGN_ITEM)))
		//			riDesc.ExtraFlag		|= EUNEF_SCROLL_ALIGN_ITEM;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_SCROLL_ALIGN_ITEM;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_ITEM_ALIGN_CENTER)))
		//			riDesc.ExtraFlag		|= EUNEF_SCROLL_ALIGN_CENTER;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_SCROLL_ALIGN_CENTER;
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_AUTO_ITEM_HEIGHT)))
		//			riDesc.ExtraFlag		|= EUNEF_SCROLL_AUTO_ITEM_HEIGHT;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_SCROLL_AUTO_ITEM_HEIGHT;
		//	}

		//	if (instance->Symbol->GetType() == EUIT_ICONBOX)
		//	{
		//		if ((instance->GetFlag(UISymbolInstance::FLAG_ICON_GRAY)))
		//			riDesc.ExtraFlag		|= EUNEF_ICONBOX_GRAY;
		//		else
		//			riDesc.ExtraFlag		&= ~EUNEF_ICONBOX_GRAY;
		//	}

		//	riDesc.IsInputBox			= ((instance->GetFlag(UISymbolInstance::FLAG_IS_INPUTBOX))) ? 1 : 0;

		//	// alignment
		//	riDesc.AlignH				= instance->AlignH;
		//	riDesc.AlignV				= instance->AlignV;

		//	// text alignment
		//	if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_CENTER)))
		//		riDesc.TAlignH		= EUI_ALIGN_HCENTER;
		//	else if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_RIGHT)))
		//		riDesc.TAlignH		= EUI_ALIGN_RIGHT;

		//	if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_VCENTER)))
		//		riDesc.TAlignV		= EUI_ALIGN_VCENTER;

		//	stream.Put(&riDesc, sizeof(UiInstanceDesc));
		//}
		//// instances
		//for (u32 s = 0 ; s < Symbols.size() ; ++ s)
		//{
		//	UISymbol* symbol	= Symbols[s];
		//	if (symbol->UiFlag & UISYM_USED)
		//	{
		//		for (int i = 0 ; i < symbol->GetInstancesCount() ; ++ i)
		//		{
		//			UiInstanceDesc iDesc;
		//			UISymbolInstance* instance	= symbol->GetInstanceAt(i);
		//			iDesc.IdIndex				= AddStringToList(instance->InstanceId, string_list);
		//			iDesc.SymbolNameIndex		= AddStringToList(instance->Symbol->GetName(), string_list);
		//			if (instance->TextId == "")
		//				iDesc.TextIndex			= -1;
		//			else
		//				iDesc.TextIndex			= s_libui->GetStringIndex(instance->TextId);

		//			iDesc.FontSize				= instance->FontSize;
		//			if (instance->Script == "")
		//				iDesc.ScriptIndex		= -1;
		//			else
		//				iDesc.ScriptIndex		= AddStringToList(instance->Script, string_list);
		//			if (instance->FontName == "")
		//				iDesc.FontIndex			= -1;
		//			else
		//				iDesc.FontIndex			= AddStringToList(instance->FontName, string_list);
		//			if (instance->Sfx == "")
		//				iDesc.SfxIndex			= -1;
		//			else
		//				iDesc.SfxIndex			= AddStringToList(instance->Sfx, string_list);
		//			if (instance->Anim == "")
		//				iDesc.AnimIndex			= -1;
		//			else
		//				iDesc.AnimIndex			= AddStringToList(instance->Anim, string_list);

		//			iDesc.PosX					= instance->Position.X;
		//			iDesc.PosY					= instance->Position.Y;
		//			iDesc.ScaleX				= instance->Scale.X;
		//			iDesc.ScaleY				= instance->Scale.Y;
		//			iDesc.FanStart				= instance->FanStart;
		//			iDesc.FanEnd				= instance->FanEnd;
		//			iDesc.TextColor				= instance->TextColor;
		//			iDesc.BorderColor			= instance->BorderColor;
		//			iDesc.GradientColor			= instance->GradientColor;
		//			iDesc.ScrollDir				= instance->ScrollDir;
		//			iDesc.MultilineMax			= instance->MultilineMax;
		//			iDesc.TextHOffset			= instance->TextHOffset;
		//			iDesc.TextVOffset			= instance->TextVOffset;
		//			iDesc.CamPosition			= instance->CamPosition;
		//			iDesc.CamTarget				= instance->CamTarget;
		//			iDesc.ScrollChildW			= instance->ScrollChildW;
		//			iDesc.ScrollChildH			= instance->ScrollChildH;
		//			instance->SaveAnims(iDesc, anim_stream, string_list);
		//			chunkCommon.AnimTotal		+= iDesc.AnimCount;

		//			if (instance->Symbol->GetType() == EUIT_BUTTON)
		//			{
		//				if ((!instance->GetFlag(UISymbolInstance::FLAG_EVENTS)))
		//				{
		//					_LOG("  Warning: no events for button [%s].\n", instance->InstanceId.c_str());
		//				}
		//			}
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_VISIBLE)))
		//				iDesc.Flag				|= EUNCF_VISIBLE;
		//			else
		//				iDesc.Flag				&= ~EUNCF_VISIBLE;
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_FLIP_H)))
		//				iDesc.Flag				|= EUNCF_FLIP_H;
		//			else
		//				iDesc.Flag				&= ~EUNCF_FLIP_H;
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_FLIP_V)))
		//				iDesc.Flag				|= EUNCF_FLIP_V;
		//			else
		//				iDesc.Flag				&= ~EUNCF_FLIP_V;
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_ENABLE_CLIP)))
		//				iDesc.Flag				|= EUNCF_ENABLE_CLIP;
		//			else
		//				iDesc.Flag				&= ~EUNCF_ENABLE_CLIP;
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_DEFAULT_ANIMATION)))
		//				iDesc.Flag				|= EUNCF_DEFAULT_ANIMATION;
		//			else
		//				iDesc.Flag				&= ~EUNCF_DEFAULT_ANIMATION;

		//			if (instance->Symbol->GetType() == EUIT_BUTTON ||
		//				instance->Symbol->GetType() == EUIT_EASYBUTTON ||
		//				instance->Symbol->GetType() == EUIT_TEXTBOX)
		//			{
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_LIMIT_LENGTH)))
		//					iDesc.ExtraFlag			|= EUNEF_TEXT_LIMITLENGTH;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_TEXT_LIMITLENGTH;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_USE_INTERNAL_CHARACTER)))
		//					iDesc.ExtraFlag			|= EUNEF_USE_INTERNAL_CHARACTER;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_USE_INTERNAL_CHARACTER;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_HAS_BORDER)))
		//					iDesc.ExtraFlag			|= EUNEF_TEXT_WITH_BORDER;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_TEXT_WITH_BORDER;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_HAS_GRADIENT)))
		//					iDesc.ExtraFlag			|= EUNEF_TEXT_WITH_GRADIENT;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_TEXT_WITH_GRADIENT;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_CHECKABLE)))
		//					iDesc.ExtraFlag			|= EUNEF_CHECKABLE;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_CHECKABLE;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_CHECKED)))
		//					iDesc.ExtraFlag			|= EUNEF_CHECKED;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_CHECKED;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_MULTILINES)))
		//					iDesc.ExtraFlag			|= EUNEF_MULTI_LINES;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_MULTI_LINES;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_FLUSH)))
		//					iDesc.ExtraFlag			|= EUNEF_TEXT_FLUSH;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_TEXT_FLUSH;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_AUTO_FIT_HEIGHT)))
		//					iDesc.ExtraFlag			|= EUNEF_MULTI_AUTO_HEIGHT;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_MULTI_AUTO_HEIGHT;
		//				if ((instance->GetFlag1(UISymbolInstance::FLAG_SYSTEM_FONT)))
		//					iDesc.ExtraFlag			|= EUNEF_SYSTEM_FONT;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_SYSTEM_FONT;
		//				//if ((instance->GetFlag(UISymbolInstance::FLAG_FAN_EXTERNAL_IMAGE)))
		//				//	iDesc.Flag				|= EUNF_FAN_EXTERNAL_IMAGE;
		//				//else
		//				//	iDesc.Flag				&= ~EUNF_FAN_EXTERNAL_IMAGE;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_EVENT_PRESS)))
		//					iDesc.ExtraFlag			|= EUNEF_EVENT_PRESS;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_EVENT_PRESS;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_EVENT_RELEASE)))
		//					iDesc.ExtraFlag			|= EUNEF_EVENT_RELEASE;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_EVENT_RELEASE;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_EVENT_CLICK)))
		//					iDesc.ExtraFlag			|= EUNEF_EVENT_CLICK;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_EVENT_CLICK;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_EVENT_DRAG)))
		//					iDesc.ExtraFlag			|= EUNEF_EVENT_DRAG;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_EVENT_DRAG;
		//			}


		//			if (instance->Symbol->GetType() == EUIT_SCROLLAREA)
		//			{
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_ALIGN_ITEM)))
		//					iDesc.ExtraFlag			|= EUNEF_SCROLL_ALIGN_ITEM;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_SCROLL_ALIGN_ITEM;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_ITEM_ALIGN_CENTER)))
		//					iDesc.ExtraFlag			|= EUNEF_SCROLL_ALIGN_CENTER;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_SCROLL_ALIGN_CENTER;
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_SCROLL_AUTO_ITEM_HEIGHT)))
		//					iDesc.ExtraFlag			|= EUNEF_SCROLL_AUTO_ITEM_HEIGHT;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_SCROLL_AUTO_ITEM_HEIGHT;
		//			}

		//			if (instance->Symbol->GetType() == EUIT_ICONBOX)
		//			{
		//				if ((instance->GetFlag(UISymbolInstance::FLAG_ICON_GRAY)))
		//					iDesc.ExtraFlag			|= EUNEF_ICONBOX_GRAY;
		//				else
		//					iDesc.ExtraFlag			&= ~EUNEF_ICONBOX_GRAY;
		//			}

		//			iDesc.IsInputBox			= ((instance->GetFlag(UISymbolInstance::FLAG_IS_INPUTBOX))) ? 1 : 0;

		//			// alignment
		//			iDesc.AlignH				= instance->AlignH;
		//			iDesc.AlignV				= instance->AlignV;

		//			// text alignment
		//			if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_CENTER)))
		//				iDesc.TAlignH		= EUI_ALIGN_HCENTER;
		//			else if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_RIGHT)))
		//				iDesc.TAlignH		= EUI_ALIGN_RIGHT;

		//			if ((instance->GetFlag(UISymbolInstance::FLAG_TEXT_ALIGN_VCENTER)))
		//				iDesc.TAlignV		= EUI_ALIGN_VCENTER;

		//			stream.Put(&iDesc, sizeof(UiInstanceDesc));
		//		}
		//	}
		//}

		//header.ChunkSize			+= sizeof(UiChunkCommon);
		//header.ChunkSize			+= stream.GetLength();
		//header.ChunkSize			+= anim_stream.GetLength();

		//chunkCommon.AnimOffset	= sizeof(TiResfileChunkHeader) + sizeof(UiChunkCommon) + stream.GetLength();

		//OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		//OutputStream.Put(&chunkCommon, sizeof(UiChunkCommon));
		//OutputStream.Put(stream.GetBuffer(), stream.GetLength());
		//OutputStream.Put(anim_stream.GetBuffer(), anim_stream.GetLength());

		return true;
	}

	//void CldLibUI::LoadSymbolLibrary(TiXmlElement* lib_root)
	//{
	//	TiXmlElement* xml_sym		= lib_root->FirstChildElement("symbol");

	//	ti_vector<TiXmlElement*>	symbol_roots;
	//	// load all symbols first, instances delayed
	//	while (xml_sym)
	//	{
	//		ti_string name			= xml_sym->Attribute("name");
	//		E_UI_TYPE type			= GetTypeByName(xml_sym->Attribute("type"));

	//		UISymbol* symbol		= new UISymbol(type, name);

	//		if (xml_sym->Attribute("x"))
	//			symbol->BoundRect.Left	= atoi(xml_sym->Attribute("x"));
	//		if (xml_sym->Attribute("y"))
	//			symbol->BoundRect.Upper	= atoi(xml_sym->Attribute("y"));
	//		if (xml_sym->Attribute("w"))
	//			symbol->BoundRect.Right	= symbol->BoundRect.Left + atoi(xml_sym->Attribute("w"));
	//		if (xml_sym->Attribute("h"))
	//			symbol->BoundRect.Lower	= symbol->BoundRect.Upper + atoi(xml_sym->Attribute("h"));

	//		Symbols.push_back(symbol);
	//		symbol_roots.push_back(xml_sym);

	//		xml_sym					= xml_sym->NextSiblingElement("symbol");
	//	}

	//	// load instances, delayed
	//	TI_ASSERT(symbol_roots.size() == Symbols.size());
	//	for (u32 i = 0 ; i < Symbols.size() ; ++ i)
	//	{
	//		UISymbol* symbol		= Symbols[i];
	//		symbol->LoadInstances(symbol_roots[i]);
	//	}
	//}

	//void CldLibUI::LoadSymbolRoot(TiXmlElement* lib_root)
	//{
	//	SceneRoot->RemoveAllInstances();
	//	SceneRoot->LoadInstances(lib_root);
	//}

	//UISymbol* CldLibUI::GetSymbolByName(const ti_string& name)
	//{
	//	ti_vector<UISymbol*>::iterator it;
	//	for (it = Symbols.begin() ; it != Symbols.end() ; ++ it)
	//	{
	//		UISymbol* symbol	= *it;
	//		if (symbol->GetName() == name)
	//		{
	//			return symbol;
	//		}
	//	}

	//	return NULL;
	//}

	//TiImagePtr LoadImage(TiFile& file_input)
	//{
	//	// check image type by extension name.
	//	const ti_string& name
	//		= file_input.GetFileName();
	//	ti_string ext	= name.c_str() + name.rfind('.') + 1;

	//	if (ext == "png")
	//	{
	//		return TiImage::LoadImagePNG(file_input, false);
	//	}
	//	else if (ext == "tga")
	//	{
	//		TiImagePtr tga_image	= TiImage::LoadImageTGA(file_input, false);
	//		TiImagePtr flip_image	= ti_new TiImage(tga_image->GetFormat(), tga_image->GetWidth(), tga_image->GetHeight());
	//		// flip v
	//		const int pitch			= tga_image->GetPitch();
	//		char* dst				= (char*)flip_image->Lock();
	//		char* src				= (char*)tga_image->Lock();
	//		src						+= pitch * (tga_image->GetHeight() - 1);
	//		for (int h = 0 ; h < tga_image->GetHeight() ; ++ h)
	//		{
	//			memcpy(dst, src, pitch);
	//			dst					+= pitch;
	//			src					-= pitch;
	//		}
	//		tga_image				= NULL;
	//		return flip_image;
	//	}
	//	else if (ext == "pvr")
	//	{
	//		return 0;//LoadImagePVR(file_input);
	//	}
	//	else
	//	{
	//		TI_ASSERT(0);
	//		_LOG("  Error: not supported image format: %s.\n", name.c_str());
	//	}

	//	return NULL;
	//}

	//void CldLibUI::MakeAtlas()
	//{
	//	TiColladaConfig& config		= TiCollada::Get()->Config;
	//	Region* all = new Region();
	//	all->Left	= 0;
	//	all->Upper	= 0;
	//	all->Right	= config.AtlasSize.X;
	//	all->Lower	= config.AtlasSize.Y;
	//	AvailableRegions.push_back(all);

	//	config.AddLog("ui atlas [%s] (%d, %d):", config.UiAtlas.c_str(), config.AtlasSize, config.AtlasSize);

	//	Atlas		= ti_new TiImage(EPF_R8G8B8A8, config.AtlasSize.X, config.AtlasSize.Y);

	//	ti_vector<UISymbol*>	useful_images;

	//	// find all useful images
	//	ti_vector<UISymbol*>::iterator it;
	//	for (it = Symbols.begin() ; it != Symbols.end() ; ++ it)
	//	{
	//		UISymbol* symbol	= *it;
	//		if (symbol->GetType() == EUIT_IMAGE && ((symbol->UiFlag & UISYM_USED) != 0))
	//		{
	//			useful_images.push_back(symbol);
	//		}
	//	}

	//	std::sort(useful_images.begin(), useful_images.end(), SorterSymbolImage());

	//	for (it = useful_images.begin() ; it != useful_images.end() ; ++ it)
	//	{
	//		UISymbol* symbol		= *it;
	//		InsertToAtlas(symbol);

	//		TiFile image_file;
	//		if (image_file.Open(symbol->ImagePath, EFA_READ))
	//		{
	//			TiImagePtr pImg		= LoadImage(image_file);
	//			config.AddLog("%s, (%d, %d, %d, %d)", symbol->ImagePath.c_str(), symbol->Offset.X, symbol->Offset.Y, symbol->Offset.X + pImg->GetWidth(), symbol->Offset.Y + pImg->GetHeight());
	//			for (int h = 0 ; h < pImg->GetHeight() ; ++ h)
	//			{
	//				for (int w = 0 ; w < pImg->GetWidth() ; ++ w)
	//				{
	//					SColor c	= pImg->GetPixel(w, h);
	//					Atlas->SetPixel((*it)->Offset.X + w, (*it)->Offset.Y + h, c);
	//				}
	//			}
	//			if (config.AtlasSafeUV)
	//			{
	//				// expand image border
	//				int w, h;
	//				// top
	//				h		= 0;
	//				for (int w = 0 ; w < pImg->GetWidth() ; ++ w)
	//				{
	//					SColor c	= pImg->GetPixel(w, h);
	//					Atlas->SetPixel(symbol->Offset.X + w, symbol->Offset.Y - 1 + h, c);
	//				}
	//				// bottom
	//				h		= pImg->GetHeight() - 1;
	//				for (int w = 0 ; w < pImg->GetWidth() ; ++ w)
	//				{
	//					SColor c	= pImg->GetPixel(w, h);
	//					Atlas->SetPixel(symbol->Offset.X + w, symbol->Offset.Y + h + 1, c);
	//				}
	//				// left
	//				w		= 0;
	//				for (int h = 0 ; h < pImg->GetHeight() ; ++ h)
	//				{
	//					SColor c	= pImg->GetPixel(w, h);
	//					Atlas->SetPixel(symbol->Offset.X + w - 1, symbol->Offset.Y + h, c);
	//				}
	//				// right
	//				w		= pImg->GetWidth() - 1;
	//				for (int h = 0 ; h < pImg->GetHeight() ; ++ h)
	//				{
	//					SColor c	= pImg->GetPixel(w, h);
	//					Atlas->SetPixel(symbol->Offset.X + w + 1, symbol->Offset.Y + h, c);
	//				}
	//				// corners
	//				SColor c;
	//				c				= pImg->GetPixel(0, 0);
	//				Atlas->SetPixel(symbol->Offset.X - 1, symbol->Offset.Y - 1, c);
	//				c				= pImg->GetPixel(pImg->GetWidth() - 1, 0);
	//				Atlas->SetPixel(symbol->Offset.X + pImg->GetWidth() - 1 + 1, symbol->Offset.Y - 1, c);
	//				c				= pImg->GetPixel(0, pImg->GetHeight() - 1);
	//				Atlas->SetPixel(symbol->Offset.X - 1, symbol->Offset.Y + pImg->GetHeight() - 1 + 1, c);
	//				c				= pImg->GetPixel(pImg->GetWidth() - 1, pImg->GetHeight() - 1);
	//				Atlas->SetPixel(symbol->Offset.X + pImg->GetWidth() - 1 + 1, symbol->Offset.Y + pImg->GetHeight() - 1 + 1, c);
	//			}
	//		}
	//	}

	//	Atlas->SaveToPng(config.UiAtlas.c_str());
	//	AtlasName		= config.UiAtlas;
	//}

	//bool CldLibUI::InsertToAtlas(UISymbol* image_symbol)
	//{
	//	TiColladaConfig& config			= TiCollada::Get()->Config;
	//	const int gap					= config.AtlasGaps;

	//	// [tirax] add 1 more pixels border to prevent interpolation artifacts when the image was scaled.
	//	int totalWidth	= image_symbol->BoundRect.getWidth() + gap;
	//	int totalHeight	= image_symbol->BoundRect.getHeight() + gap;

	//	if (config.AtlasSafeUV)
	//	{
	//		totalWidth	+= 2;
	//		totalHeight	+= 2;
	//	}

	//	Region* region = NULL;
	//	ti_vector<Region *>::iterator  iterRegion;
	//	for (iterRegion = AvailableRegions.begin(); iterRegion != AvailableRegions.end(); ++iterRegion)
	//	{
	//		if((*iterRegion)->getWidth() >= totalWidth && (*iterRegion)->getHeight() >= totalHeight)
	//		{
	//			region = *iterRegion;
	//			// remove from available region
	//			AvailableRegions.erase(iterRegion);
	//			break;
	//		}
	//	}

	//	// Insert fails...will need to add a new atlas
	//	if(region == NULL)
	//		return false;

	//	// Subdivide region?
	//	if(region->getWidth() > totalWidth || region->getHeight() > totalHeight)
	//	{
	//		// right residue?
	//		if(region->getWidth() - totalWidth > 0)
	//		{
	//			Region* right	= new Region();
	//			right->Left		= region->Left + totalWidth;
	//			right->Right	= region->Right;
	//			right->Upper	= region->Upper;
	//			right->Lower	= region->Upper + totalHeight;
	//			AvailableRegions.push_back(right);
	//		}

	//		// bottom residue?
	//		if(region->getHeight() - totalHeight > 0)
	//		{
	//			Region* bottom	= new Region();
	//			bottom->Left	= region->Left;
	//			bottom->Right	= region->Right;
	//			bottom->Upper	= region->Upper + totalHeight;
	//			bottom->Lower	= region->Lower;
	//			AvailableRegions.push_back(bottom);
	//		}

	//		// resized region
	//		//region->Right	= region->Left + image_symbol->BoundRect.getWidth();
	//		//region->Lower	= region->Upper + image_symbol->BoundRect.getHeight();
	//		region->Right	= region->Left + totalWidth;
	//		region->Lower	= region->Upper + totalHeight;
	//	}

	//	image_symbol->Offset.X		= region->Left;
	//	image_symbol->Offset.Y		= region->Upper;

	//	if (config.AtlasSafeUV)
	//	{
	//		image_symbol->Offset.X	+= 1;
	//		image_symbol->Offset.Y	+= 1;
	//	}

	//	// sort available regions by size so it take best-fit first
	//	std::sort(AvailableRegions.begin(), AvailableRegions.end(), Sorter());

	//	UsedRegions.push_back(region);
	//	return true;
	//}
};