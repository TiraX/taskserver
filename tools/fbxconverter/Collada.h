/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#ifndef _COLLADA_H__
#define _COLLADA_H__

#include "CldLibGeometry.h"
#include "CldLibVisualScene.h"
#include "CldLibShaders.h"
#include "CldLibImages.h"
#include "CldLibMaterial.h"
#include "CldLibTiMaterial.h"
#include "CldLibAnimation.h"
#include "CldLibController.h"
#include "CldLibParticleEffect.h"
#include "CldLibUI.h"
#include "CldLibResources.h"

class FbxAsset;

namespace ti
{

	struct TiColladaConfig
	{
		TiColladaConfig()
			: UnitParam(1.0f)
			, AtlasSize(512, 512)
			, ReserveTexcoord(false)
			, AnimationOnly(false)
			, KeepAllAnimKeys(false)
			, OptimizeSkinmesh(false)
			, EmbedShader(false)
			, AtlasGaps(1)
			, AtlasSafeUV(false)
			, ExportStrToCSV(false)
			, DisableShrinkVertex(false)
			, GenerateTangent(false)
			, ExportVertexData(false)
		{
			UiAtlas	= "atlas.png";
		}
		ti_string	InputFilename;
		ti_string	OutputFilename;
		ti_string	TexturePath;
		ti_string	UiAtlas;
		ti_string	ExtraModelTexturePath;
		ti_string	Log;
		float		UnitParam;
		bool		ReserveTexcoord;
		bool		AnimationOnly;
		bool		KeepAllAnimKeys;
		bool		OptimizeSkinmesh;
		bool		DisableShrinkVertex;
		bool		EmbedShader;
		bool		GenerateTangent;
		bool		ExportVertexData;
		ti_vector<ti_string>	IgnoreTechs;
		vector2di	AtlasSize;
		int			AtlasGaps;
		bool		AtlasSafeUV;
		bool		ExportStrToCSV;

		bool IsIgnoreTech(const ti_string& tech_name) const
		{
			for (u32 i = 0 ; i < IgnoreTechs.size() ; ++ i)
			{
				if (IgnoreTechs[i] == tech_name)
				{
					return true;
				}
			}
			return false;
		}

		void AddLog(const char* format, ...);
	};

	class TiCollada
	{
	protected:
		static TiCollada* s_instance;
	public:
		static TiCollada*	Get();
		TiCollada(const char* collada_file_name);
		~TiCollada();

		void		Reset();
		bool		ConvertFrom(FbxAsset* asset);
		bool		Save(TiStream& file_stream);

		int			GetLoadedChunkCount();

		ti_string	ColladaFilename;
		CldLibrary*	ColladaLibraries[ECL_COUNT];
		TiColladaConfig	Config;
	};

};

#endif	//_COLLADA_H__