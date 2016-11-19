/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2013.18
*/

#ifndef _CLDLIBUI_H__
#define _CLDLIBUI_H__

#include "CldLibrary.h"
//#include "TiUString.h"

namespace ti
{
	//enum E_UI_SFX
	//{
	//	EUI_SFX_BUTTON_CLICK,

	//	EUI_SFX_COUNT,
	//	EUI_SFX_INVALID		= -1,
	//};
	//struct UiAnimStringKey
	//{
	//	float		time;
	//	ti_string	key;
	//};
	//class UISymbolAnim
	//{
	//public:

	//	enum
	//	{
	//		ANIM_POSITION,
	//		ANIM_SCALE,
	//		ANIM_SIZE,
	//		ANIM_SFX,
	//		ANIM_ALPHA,
	//		ANIM_BOUNCE,

	//		ANIM_TYPES,
	//	};
	//	enum
	//	{
	//		ANIM_FLAG_LOOP		= 1 << 0,
	//	};
	//	int							Type;
	//	int							Flag;
	//	ti_vector<UiAnimKey>		Keys;
	//	ti_vector<UiAnimStringKey>	StringKeys;
	//};
	//class UISymbol;
	//class UISymbolInstance
	//{
	//public:
	//	ti_string	InstanceId;
	//	UISymbol*	Symbol;
	//	vector2di	Position;
	//	vector2df	Scale;
	//	ti_string	TextId;
	//	ti_string	Script;
	//	ti_string	FontName;
	//	ti_string	Sfx;
	//	ti_string	Anim;
	//	s16			AlignH, AlignV;
	//	SColor		TextColor, BorderColor, GradientColor;
	//	int			FontSize;
	//	s16			FanStart, FanEnd;
	//	int			ScrollDir;
	//	int			MultilineMax;
	//	s16			TextHOffset, TextVOffset;
	//	vector3df	CamPosition, CamTarget;
	//	s16			ScrollChildW, ScrollChildH;
	//	ti_vector<UISymbolAnim*>	Anims;

	//private:
	//	u64			Flag;
	//	u64			Flag1;
	//public:

	//	enum E_FLAG_INSTANCE
	//	{
	//		FLAG_VISIBLE	= 1 << 0,
	//		FLAG_FLIP_H		= 1 << 1,
	//		FLAG_FLIP_V		= 1 << 2,
	//		FLAG_USE_INTERNAL_CHARACTER	= 1 << 3,

	//		FLAG_TEXT_ALIGN_CENTER	= 1 << 4,
	//		FLAG_HAS_BORDER		= 1 << 5,

	//		FLAG_ENABLE_CLIP	= 1 << 6,

	//		FLAG_CHECKABLE		= 1 << 7,
	//		FLAG_CHECKED		= 1 << 8,

	//		FLAG_MULTILINES		= 1 << 9,
	//		FLAG_TEXT_FLUSH		= 1 << 10,
	//		FLAG_FAN_EXTERNAL_IMAGE	= 1 << 11,

	//		FLAG_EVENT_PRESS	= 1 << 17,
	//		FLAG_EVENT_RELEASE	= 1 << 18,
	//		FLAG_EVENT_CLICK	= 1 << 19,
	//		FLAG_EVENT_DRAG		= 1 << 20,

	//		FLAG_TEXT_ALIGN_RIGHT	= 1 << 21,
	//		FLAG_TEXT_LIMIT_LENGTH	= 1 << 22,

	//		FLAG_ICON_GRAY		= 1 << 23,

	//		FLAG_TEXT_ALIGN_VCENTER	= 1 << 24,
	//		FLAG_SCROLL_ALIGN_ITEM	= 1 << 25,

	//		FLAG_HAS_GRADIENT		= 1 << 26,
	//		FLAG_IS_INPUTBOX		= 1 << 27,

	//		FLAG_DEFAULT_ANIMATION	= 1 << 28,
	//		FLAG_SCROLL_ITEM_ALIGN_CENTER	= 1 << 29,

	//		FLAG_EVENTS			= (FLAG_EVENT_PRESS | FLAG_EVENT_RELEASE | FLAG_EVENT_CLICK | FLAG_EVENT_DRAG),

	//		FLAG_AUTO_FIT_HEIGHT	= u64(1 << 30),
	//		FLAG_SCROLL_AUTO_ITEM_HEIGHT = u64(1 << 31),
	//	};

	//	enum E_FLAG_INSTANCE1
	//	{
	//		FLAG_SYSTEM_FONT		= 1 << 0,
	//	};

	//	enum
	//	{
	//		SCROLL_V,
	//		SCROLL_H,
	//	};

	//	bool	GetFlag(E_FLAG_INSTANCE flag)
	//	{
	//		return (Flag & flag) != 0;
	//	}

	//	bool	GetFlag1(E_FLAG_INSTANCE1 flag)
	//	{
	//		return (Flag1 & flag) != 0;
	//	}
	//	void	SetFlag(u64 f)
	//	{
	//		Flag	= f;
	//	}
	//	void	SetFlag1(u64 f)
	//	{
	//		Flag1	= f;
	//	}

	//	UISymbolInstance()
	//		: Symbol(NULL)
	//		, Scale(1, 1)
	//		, Flag(FLAG_VISIBLE)
	//		, Flag1(0)
	//		, FanStart(0)
	//		, FanEnd(360)
	//		, AlignH(EUI_ALIGN_LEFT)
	//		, AlignV(EUI_ALIGN_TOP)
	//		, ScrollDir(SCROLL_V)
	//		, MultilineMax(0)
	//		, TextHOffset(0)
	//		, TextVOffset(0)
	//		, ScrollChildW(0)
	//		, ScrollChildH(0)
	//	{}

	//	~UISymbolInstance()
	//	{
	//		ClearAnims();
	//	}

	//	void ClearAnims()
	//	{
	//		for (u32 i = 0 ; i < Anims.size() ; ++ i)
	//		{
	//			SAFE_DELETE(Anims[i]);
	//		}
	//		Anims.clear();
	//	}

	//	void SaveAnims(UiInstanceDesc& iDesc, TiStream& anim_stream, ti_vector<ti_string>& string_list);
	//};

	//enum
	//{
	//	UISYM_USED	= 1,
	//};

	//class UISymbol
	//{
	//public:
	//	UISymbol(E_UI_TYPE type, const ti_string& name);
	//	~UISymbol();

	//	UISymbolInstance*	AddInstance(UISymbol* sym);
	//	UISymbol*			RemoveInstance(UISymbolInstance* instance);
	//	void				RemoveAllInstances();

	//	virtual void		LoadInstances(TiXmlElement* sym_root);
	//	virtual void		LoadInstanceAnim(TiXmlElement* ins_root, UISymbolInstance* instance);
	//	void				UpdateBoundingRect();

	//	int					GetInstancesCount()
	//	{
	//		return			Instances.size();
	//	}
	//	UISymbolInstance*	GetInstanceAt(int index);
	//	UISymbolInstance*	GetInstanceAt(const vector2di& pos);

	//	E_UI_TYPE	GetType()
	//	{
	//		return	UiType;
	//	}
	//	const ti_string&	GetName()
	//	{
	//		return	Name;
	//	}
	//	const recti&		GetRect()
	//	{
	//		return	BoundRect;
	//	}

	//	E_UI_TYPE				UiType;
	//	u32						UiFlag;
	//	ti_string				Name;
	//	ti_vector<UISymbolInstance*>	Instances;
	//	recti					BoundRect;

	//	// dialog 9
	//	vector2di				SplitPoint;

	//	// image
	//	ti_string				ImagePath;

	//	// button
	//	UISymbol*				Normal;
	//	UISymbol*				Pressed;
	//
	//	vector2di				Offset;		// for image in atlas

	//};

	//class Region : public recti
	//{
	//public:
	//	bool operator < (const Region& other) const
	//	{
	//		if (getHeight() < other.getHeight())
	//			return true;
	//		if (getHeight() == other.getHeight())
	//			return getWidth() < other.getWidth();

	//		return false;
	//	}
	//};

	//struct SorterSymbolImage
	//{
	//	bool operator()(UISymbol const *s1, UISymbol const *s2) const
	//	{
	//		if (s1->BoundRect.getHeight() > s2->BoundRect.getHeight())
	//			return true;

	//		if (s1->BoundRect.getHeight() == s2->BoundRect.getHeight())
	//			return s1->BoundRect.getWidth() > s2->BoundRect.getWidth();

	//		return false;
	//	}
	//};
	////////////////////////////////////////////////////////////////////////////

	//struct UiString
	//{
	//	ti_string	tid;
	//	ti_map<ti_string, TiUString> strings;

	//	UiString()
	//	{}

	//	UiString(const UiString& other)
	//	{
	//		tid			= other.tid;

	//		strings		= other.strings;
	//	}

	//	~UiString()
	//	{
	//	}

	//	UiString& UiString::operator =(const UiString& other)
	//	{
	//		tid			= other.tid;

	//		strings		= other.strings;

	//		return *this;
	//	}

	//	void SetText(const char* lang, const u16* buf)
	//	{
	//		strings[lang]	= buf;
	//	}

	//	TiUString& GetText(const char* lang)
	//	{
	//		if (strings.find(lang) != strings.end())
	//		{
	//			return strings[lang];
	//		}

	//		return strings["en"];
	//	}
	//};

	class CldLibUI : public CldLibrary
	{
	public:
		CldLibUI();
		virtual ~CldLibUI();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

	//	void		LoadStringStandard(TiXmlElement* ui_root);
	//	void		LoadStrings(TiXmlElement* ui_root);
	//	void		SaveStrings(const ti_string& filename, ti_vector<UiString>& strings, const char* lang);
	//	int			GetStringIndex(const ti_string& tid);

	//	void		ExportToCSV(int l);

	//	void		LoadSymbolLibrary(TiXmlElement* lib_root);
	//	void		LoadSymbolRoot(TiXmlElement* lib_root);

	//	UISymbol*	GetSymbolByName(const ti_string& name);

	//	void		CheckSymbols(UISymbol* root);
	//	void		MakeAtlas();
	//	bool		InsertToAtlas(UISymbol* image_symbol);

	//	void		LoadUIStrings();

	//	ti_string				AtlasName;
	//protected:
	//	ti_vector<UISymbol*>	Symbols;
	//	UISymbol*				SceneRoot;

	//	TiImagePtr				Atlas;

	//	ti_vector<Region *>		UsedRegions;
	//	ti_vector<Region *>		AvailableRegions;		
	//	
	//	int						UsefulSymbol;

	//	ti_string				Sfx[EUI_SFX_COUNT];

	//	ti_vector<UiString>		ui_strings;

	//	struct Sorter
	//	{
	//		bool operator()(Region const *s1, Region const *s2) const
	//		{
	//			if (s1->getHeight() < s2->getHeight())
	//				return true;
	//			if (s1->getHeight() == s2->getHeight())
	//				return s1->Upper < s2->Upper;

	//			return false;
	//		}
	//	};
	};

};

#endif	//_CLDLIBUI_H__