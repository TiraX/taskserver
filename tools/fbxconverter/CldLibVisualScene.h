/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#ifndef _CLDLIBVISUALSCENE_H__
#define _CLDLIBVISUALSCENE_H__

#include "CldLibrary.h"

namespace ti
{
	class CldSceneNode
	{
	public:
		CldSceneNode();
		virtual ~CldSceneNode();

		bool	LoadNode(FbxNode* fbx_node);
		void	AddChild(CldSceneNode* node);
		void	Remove();
		void	RemoveChild(CldSceneNode* c);

		CldSceneNode*	GetNodeById(const ti_string& _id);
		CldSceneNode*	GetNodeByInstanceUrl(const ti_string& _url);

		//void	LoadUserProperty(TiXmlElement* cld_tech);
		//void	LoadHelperBBox(TiXmlElement* cld_tech);

		ti_string	Id;
		ti_string	Name;
		ti_string	Sid;
		ti_string	Type;

		ti_string	InstanceUrl;

		float		Position[3];
		float		Rotation[4];
		float		Scale[3];

		ti_string	BindMaterialId;

		CldSceneNode*	Parent;

		ti_vector < CldSceneNode* > Children;

		PhysicDesc		PhysicInfo;
		ti_vector<ti_string>	Props;

		aabbox3df	ExtraBBox;
	};

	//////////////////////////////////////////////////////////////////////////

	class CldLibVisualScene : public CldLibrary
	{
	public:
		CldLibVisualScene();
		virtual ~CldLibVisualScene();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

				void LoadNodes(FbxNode* fbx_node, CldSceneNode* node_root);
				int  GetNodeIndex(CldSceneNode* node);

		CldSceneNode*	GetNodeById(const ti_string& _id);
		CldSceneNode*	GetNodeByInstanceUrl(const ti_string& _url);

		CldSceneNode*	NodeRoot;
		ti_vector< CldSceneNode* > NodeList;

		bool		HangNodeOnEmitter;

		ti_map<ti_string, ti_string>	SidMap;
	};

};

#endif	//_CLDLIBVISUALSCENE_H__