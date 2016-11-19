/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.17
*/

#ifndef _TI_RESFILE_DEFINE_H_
#define _TI_RESFILE_DEFINE_H_

namespace ti
{
	enum 
	{
		TIRES_VERSION_MAINFILE		= 1,
		TIRES_VERSION_CHUNK_GEOM	= 2,	// add Geometry Mesh flag, for morph target mesh buffer
		TIRES_VERSION_CHUNK_SCEN	= 4,	// add TiMaterial in DAE converting, remove Material, use default TiMaterial instead;added trigger node
		TIRES_VERSION_CHUNK_IMAG	= 1,
		TIRES_VERSION_CHUNK_ANIM	= 2,	// add morph animation support
		TIRES_VERSION_CHUNK_CTRL	= 2,	// add morph controller support
		TIRES_VERSION_CHUNK_LIT		= 1,
		TIRES_VERSION_CHUNK_CAM		= 1,
		TIRES_VERSION_CHUNK_SHAD	= 5,	
		// in v4: add stencil options, add support for metal shader functions
		// in v5: add flag options for OpenGLES 3.0 shader
		TIRES_VERSION_CHUNK_MTRL	= 1,
		TIRES_VERSION_CHUNK_EMIT	= 14,	
		// in v14: add particle frame animation interval
		// add particle default fade time; add Particle Color Boost, add Emitter's BBox, add emitter param 'EmitLife' & 'EmitDelay', and GEOMETRY particle type, add Particle Life random and Particle Size random
		TIRES_VERSION_CHUNK_TIMT	= 5,
		// in v2: add material set, each model can have max to 5 material sets
		// in v3: add bind lights for material. to bind specified lights by names
		// in v4: add material texture sample method
		// in v5: add material flag for pbr materials
		TIRES_VERSION_CHUNK_TIUI	= 20,	
		// in v14: add scroll direction for UiScrollArea
		// add anim flag in AnimDesc; add a new symbol: event_mask; upgrade animation version; add default sfx and button sfx; add node alignment by viewport; add FAN ui node
		// in v15: add text gradient in ui fonts
		// in v16: add multi lines count limitation
		// in v17: add dialog 9 symbol
		// in v18: add text offset in easy button
		// in v19: add Camera info for draw box to render extra geometries; add child width and height for scroll area; add input box flag for text box
		// in v20: re-factor node flags for more usage

		TIRES_VERSION_CHUNK_RES		= 1,
	};

	enum 
	{
		TIRES_ID_RESFILE			= TI_MAKE_IDENTIFIER('T', 'I', 'R', 'S'),
		TIRES_ID_CHUNK_GEOMETRY		= TI_MAKE_IDENTIFIER('G', 'E', 'O', 'S'),
		TIRES_ID_CHUNK_SCENE		= TI_MAKE_IDENTIFIER('S', 'C', 'E', 'N'),
		TIRES_ID_CHUNK_IMAGES		= TI_MAKE_IDENTIFIER('I', 'M', 'A', 'G'),
		TIRES_ID_CHUNK_ANIMS		= TI_MAKE_IDENTIFIER('A', 'N', 'I', 'M'),
		TIRES_ID_CHUNK_CONTROLLER	= TI_MAKE_IDENTIFIER('C', 'T', 'R', 'L'),
		TIRES_ID_CHUNK_LIGHT		= TI_MAKE_IDENTIFIER('L', 'I', 'T', '.'),
		TIRES_ID_CHUNK_CAMERA		= TI_MAKE_IDENTIFIER('C', 'A', 'M', 'E'), 
		TIRES_ID_CHUNK_SHADER		= TI_MAKE_IDENTIFIER('S', 'H', 'A', 'D'), 
		TIRES_ID_CHUNK_MATERIAL		= TI_MAKE_IDENTIFIER('M', 'T', 'R', 'L'), 
		TIRES_ID_CHUNK_TIMATERIAL	= TI_MAKE_IDENTIFIER('T', 'I', 'M', 'T'), 
		TIRES_ID_CHUNK_EMITTER		= TI_MAKE_IDENTIFIER('E', 'M', 'I', 'T'), 
		TIRES_ID_CHUNK_UI			= TI_MAKE_IDENTIFIER('T', 'I', 'U', 'I'), 
		TIRES_ID_CHUNK_STRING		= TI_MAKE_IDENTIFIER('S', 'T', 'R', '.'), 
		TIRES_ID_CHUNK_RESOURCES	= TI_MAKE_IDENTIFIER('R', 'E', 'S', '.'), 
		TIRES_ID_TILEZONE			= TI_MAKE_IDENTIFIER('Z', 'O', 'N', 'E'), 
	};

	enum E_COLLADA_LIB
	{
		ECL_IMAGES,
		ECL_MATERIALS,
		ECL_CONTROLLERS,
		ECL_GEOMETRY,
		ECL_SHADERS,
		ECL_ANIMATIONS,
		ECL_PARTICLEEFFECT,
		ECL_TIMATERIAL,
		ECL_UI,
		ECL_VISUALSCENE,

		ECL_RESOURCES,	// this is the last one

		ECL_COUNT,
	};

	struct TiLodHeader
	{
		int		Lods;
	};
	struct TiLodDesc
	{
		int		Start;
		int		Length;
	};


	struct TiResfileHeader
	{
		union 
		{
			UINT	ID;
			char	IDNAME[4];
		};
		int		Version;
		int		ChunkCount;
		int		FileSize;
		int		StringCount;
		int		StringOffset;

		TiResfileHeader()
			: ID(TIRES_ID_RESFILE)
			, Version(TIRES_VERSION_MAINFILE)
			, ChunkCount(0)
			, FileSize(0)
			, StringCount(0)
			, StringOffset(0)
		{}
	};

	struct TiResfileChunkHeader
	{
		union 
		{
			UINT	ID;
			char	IDNAME[4];
		};
		int		Version;
		int		ChunkSize;
		int		ElementCount;

		TiResfileChunkHeader()
			: ID(0)
			, Version(0)
			, ChunkSize(0)
			, ElementCount(0)
		{}
	};

	static const int k_reszone_version = 3;
	struct ResZone
	{
		SColor		MainLightDiffuse;
		SColor		MainLightAmbient;
		float		MainLightIntensity;
		vector3df	MainLightDir;

		vector3df	ShadowDir;
		float		WindStrength;

		float		WaterLevel;
		SColor		WaterColor;
		SColor		WaterSpecular;
		int			WaterPbr;

		SColor		FogColor;
		vector2df	FogRange;

		float		Exposure;
		float		BloomWidth;
		float		BloomIntensity;
		float		Defocus;
		float		Threshold;

		int			SkyboxName;
		int			EnvMap;
		int			EnvLight;
		float		EnvRot;
	};

	static const int	k_actor_version	= 2;	// add linked actor
	struct ActorHeader
	{
		union
		{
			UINT	ID;
			char	IDNAME[4];
		};
		int			Version;
		int			ActorCount;
		int			StringCount;
		int			StringOffset;
	};

	struct ActorDesc
	{
		int				NameStr;
		int				TypeStr;
		int				LinkIndex;
		vector3df		Position;
		quaternion		Rotation;
	};

	static const int k_camera_track_version	= 3;	
	// add near / far plane in tracks
	// add fog info in camera keys
	struct CameraTrackHeader
	{
		union
		{
			UINT	ID;
			char	IDNAME[4];
		};
		int			Version;
		int			TrackCount;
		int			StringCount;
		int			StringOffset;
	};

	struct CameraTrackDesc
	{
		float		TotalTime;
		int			KeyCount;
	};

	struct CameraKeyDesc
	{
		int				Frame;
		vector3df		Position;
		vector3df		Target;
		float			Fov;
		float			NearPlane;
		float			FarPlane;

		SColor			FogColor;
		float			FogNear;
		float			FogFar;
	};

	struct TiCameraTrack
	{
		float						TotalTime;
		ti_vector<CameraKeyDesc>	Keys;
	};

	//////////////////////////////////////////////////////////////////////////

	struct GeometryDesc
	{
		int				StrIndex_Id;
		u32				VertexFormat;
		int				VertexCount;
		int				StrideInByte;
		int				PrimitiveCount;	//triangle count, means (index count) / 3. (triangle list)
		int				IndexType;
		aabbox3df		BBox;
		u32				Flag;

		enum
		{
			FLAG_MORPH_SOURCE	= 1 << 0,
			FLAG_MORPH_TARGET	= 1 << 1,
		};

		GeometryDesc()
			: StrIndex_Id(-1)
			, VertexFormat(0)
			, VertexCount(0)
			, StrideInByte(0)
			, PrimitiveCount(0)
			, IndexType(0)
			, Flag(0)
		{
		}
	};

	struct ObjectDescV3
	{
		int			Filename_index;
		u32			NodeType;
		u32			NodeFlag;
		vector3df	Position;
		quaternion	Rotation;
		vector3df	Scale;

		union
		{
			// geometry
			struct
			{
				int		UVIndex;
				int		MaterialSet;
			};
			// grass
			struct
			{
				float	Radius;
				float	Density;
			};
		};
		int			Children;
		u8			GroupID[8];
		ObjectDescV3()
			: Children(0)
		{
			UVIndex		= 0;
			MaterialSet	= 0;
		}
	};

	struct ObjectDescV4
	{
		int			NodeId_Index;
		int			Filename_index;
		u32			NodeType;
		u32			NodeFlag;
		vector3df	Position;
		quaternion	Rotation;
		vector3df	Scale;

		union
		{
			// geometry
			struct
			{
				int		UVIndex;
				int		MaterialSet;
			};
			// grass
			struct
			{
				float	Radius;
				float	Density;
			};
		};
		int			Children;
		u8			GroupID[8];
		ObjectDescV4()
			: Children(0)
			, NodeId_Index(-1)
		{
			UVIndex		= 0;
			MaterialSet	= 0;
		}
	};

	struct GroupDummyDesc
	{
		vector3df	Position;
	};

	struct UVHeader
	{
		u32			Flag;
		int			VertexCount;
		int			IndexCount;
	};
	struct UVDesc
	{
		int			VertexIndex;
		vector2df	UV;
	};

	struct LightDesc
	{
		int			Filename_index;
		int			Type;
		u32			Flag;
		float		Intensity;
		SColor		Diffuse;
		vector3df	Position;
		vector3df	Target;
		float		Attenuation[2];
		float		Cone[2];
	};

	struct PhysicDesc
	{
		int		Type;
        
		// sphere
        float	Radius;
        float	Height;
		// mesh
		int			MeshIdIndex;
		
		PhysicDesc()
			: Type(EPHYT_INVALID)
            , Radius(0.f)
            , Height(0.f)
			, MeshIdIndex(0)
		{
		}
	};

	struct NodeDesc
	{
		int		StrIndex_Id;
		int		StrIndex_Sid;
		int		Type;
		int		Flag;
		int		StrIndex_InstanceUrl;

		float	Position[3];	// vector3df
		float	Rotation[4];	// quaternion
		float	Scale[3];		// vector3df

		int		StrIndex_MId;	// material id

		PhysicDesc	Physic;
		aabbox3df	ExtraBBox;

		int		ParentNodeIndex;// node index in node list. -1 means no parent
		int		PropString[2];

		NodeDesc()
			: StrIndex_Id(-1)
			, StrIndex_Sid(-1)
			, Type(0)
			, Flag(0)
			, StrIndex_InstanceUrl(-1)
			, StrIndex_MId(-1)
			, ParentNodeIndex(-1)
		{
			Position[0] = 0.f;
			Position[1] = 0.f;
			Position[2] = 0.f;

			Rotation[0] = 0.f;
			Rotation[1] = 0.f;
			Rotation[2] = 0.f;
			Rotation[3] = 1.f;

			Scale[0] = 1.f;
			Scale[1] = 1.f;
			Scale[2] = 1.f;

			PropString[0] = -1;
			PropString[1] = -1;
		}
	};

	enum{
		SHADER_OPTION_ESSL30	= 1 << 0,
		SHADER_OPTION_DLIGHTS	= 1 << 1,
	};
	struct ShaderDesc
	{
		int		StrIndex_Id;
		int		TechniqueCount;
		int		Options;
	};

	struct ShaderPassDesc
	{
		int		StrIndex_Id;
		int		StrIndex_VSName;
		int		StrIndex_FSName;
		int		StrIndex_VSH;
		int		StrIndex_FSH;
		int		StrIndex_MetalVS;
		int		StrIndex_MetalFS;

		TiRenderState	RenderState;
	};

	struct ShaderTechDesc
	{
		int		StrIndex_Id;
		int		PassCount;
	};

	struct AnimDesc
	{
		int		KeyCount;
		u16		StrTargetNodeIndex;
		u16		StrTargetAnimIndex;
		int		AnimParam;
	};

	struct AnimKey
	{
		float	Time;
		float	Key[4];

		AnimKey()
			: Time(0.f)
		{
			Key[0]	= 0;
			Key[1]	= 0;
			Key[2]	= 0;
			Key[3]	= 0;
		}
	};

	struct ControllerDesc
	{
		int		Id_StrIndex;
		int		TargetSource_StrIndex;
		int		ControllerType;
		int		DataOffset;
		union
		{
			int	TotalBones;
			int	TotalMorphTargets;
		};
	};

	struct BoneDesc
	{
		int		BoneName_StrIndex;
		float	InvertBindMatrix[16];
	};

	struct MorphTargetDesc
	{
		int		TargetName;
		float	Weight;
	};

	struct UniformDesc
	{
		int		StrIndex_Name;
		int		Type;
		union
		{
			float	floatValue[4];
			int		intValue[4];
		};
		u8		Parameters[4];
	};

	enum
	{
		MATERIAL_FLAG_ISPBR = 1 << 0,
		MATERIAL_FLAG_ISTRANSPARENT = 1 << 1,
		MATERIAL_FLAG_PBR_NOTEX = 1 << 2,
	};

	struct MtrlDesc
	{
		int		StrIndex_Id;
		int		StrIndex_Shader;
		int		StrIndex_Tech;
		int		UniformCount;
		int		StrIndex_BindLights;
		int		Flag;
	};

	struct EmitterDesc
	{
		int			Id_StrIndex;

		int			EmitterType;
		int			ParticleType;

		u32			EmitterFlag;

		vector3df	Position;
		float		EmitDelay;
		float		EmitLife;
		float		Interval;
		int			EmitCount;
		float		Radius;
		float		Angle;
		int			Section;
		float		Height;
		vector3df	Dir;
		vector3df	EndPoint;
		float		ParticleLife;
		float		ParticleLifeRandom;
		float		ParticleSpeed;
		float		ParticleColorBoost;
		float		DefaultFadeTime;
		int			BlendType;
		vector2df	ParticleSize;
		float		ParticleSizeRandom;
		SColorf		ParticleColor;
		int			Texture_StrIndex;
		int			AffectorCount;
		u16			Demension[2];
		float		FrameInterval;
		int			Sfx_StrIndex;
		aabbox3df	BBox;
		EmitterDesc()
			: EmitterType(0)
			, ParticleType(0)
			, EmitterFlag(0)
			, EmitLife(0.f)
			, EmitDelay(0.f)
			, Interval(0.f)
			, EmitCount(1)
			, Radius(1.f)
			, EndPoint(0, 0, 1)
			, Angle(0.f)
			, Section(1)
			, Height(1.f)
			, ParticleLife(1.f)
			, ParticleSpeed(1.f)
			, ParticleColorBoost(1.f)
			, BlendType(0)
			, Texture_StrIndex(0)
			, AffectorCount(0)
			, Sfx_StrIndex(0)
			, DefaultFadeTime(0.1f)
			, ParticleLifeRandom(0.f)
			, ParticleSizeRandom(0.f)
			, FrameInterval(0.1f)
		{
			Demension[0]	= 1;
			Demension[1]	= 1;
		}
	};

	struct AffectorDesc
	{
		int			AffectorType;
		float		Data[20];
		AffectorDesc()
			: AffectorType(-1)
		{
			memset(Data, 0, sizeof(Data));
		}
	};

	struct UiChunkCommon
	{
		int			AnimOffset;
		int			AnimTotal;
		int			SfxCount;
	};

	struct UiAtlasDesc
	{
		int			FilenameIndex;
		s16			Width;
		s16			Height;
	};

	struct UiAnimKey
	{
		float		time;
		quaternion	key;

		inline UiAnimKey& operator=(const UiAnimKey& other)
		{
			time	= other.time;
			key		= other.key;
			return *this;
		}
	};

	struct UiAnimationDesc
	{
		u16			Type;
		u16			Flag;
		int			Keys;
	};

	struct UiInstanceDesc
	{
		s16			IdIndex;
		s16			SymbolNameIndex;
		s16			ScriptIndex;
		s16			FontIndex;
		int			TextIndex;
		s16			PosX, PosY;
		float		ScaleX, ScaleY;
		s16			FanStart, FanEnd;
		int			FontSize;
		int			IsInputBox;
		SColor		TextColor;
		SColor		BorderColor;
		SColor		GradientColor;
		u32			Flag;			// Flag for common symbol
		u32			ExtraFlag;		// Flag for specified symbol
		s16			AlignH, AlignV;	// Instance Alignment 
		s16			TAlignH, TAlignV;	// Text Alignment
		int			AnimCount;
		int			AnimOffset;
		int			SfxIndex;
		int			AnimIndex;
		int			ScrollDir;
		int			MultilineMax;
		s16			TextHOffset, TextVOffset;
		s16			ScrollChildW, ScrollChildH;
		vector3df	CamPosition, CamTarget;

		UiInstanceDesc()
			: PosX(0)
			, PosY(0)
			, ScaleX(1)
			, ScaleY(1)
			, Flag(EUNCF_VISIBLE)
			, ExtraFlag(0)
			, FontSize(16)
			, IsInputBox(0)
			, AnimCount(0)
			, AnimOffset(0)
			, AnimIndex(-1)
			, FanStart(0)
			, FanEnd(360)
			, AlignH(EUI_ALIGN_LEFT)
			, AlignV(EUI_ALIGN_TOP)
			, TAlignH(EUI_ALIGN_LEFT)
			, TAlignV(EUI_ALIGN_TOP)
			, SfxIndex(-1)
			, ScrollDir(0)
			, MultilineMax(0)
			, TextHOffset(0)
			, TextVOffset(0)
			, ScrollChildW(0)
			, ScrollChildH(0)
		{}
	};
	struct UiSymbolDesc
	{
		UiSymbolDesc()
			: InstanceCount(0)
			, InstanceOffset(0)
			, Type(EUIT_SYMBOL)
			, X(0), Y(0), W(0), H(0)
			, splitX(0)
			, splitY(0)
		{
		}
		s16		NameIndex;
		s16		Type;
		s16		InstanceCount;
		s16		InstanceOffset;

		s16		X, Y, W, H;
		s16		splitX, splitY;
	};

	enum E_RESOURCE_TYPE
	{
		ERT_SHADER,
		ERT_TEXTURE,
	};

	struct ResourceDesc
	{
		int		Type;
		int		Name;
	};
}

#endif //_TI_RESFILE_DEFINE_H_