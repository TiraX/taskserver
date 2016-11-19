/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"
#include "CldLibVisualScene.h"
#include "CldLibImages.h"
#include "CldLibMaterial.h"
#include "CldLibGeometry.h"
#include "Collada.h"

namespace ti
{
	void GetPhysicInfo(PhysicDesc& info, const ti_string& geometry_id)
	{
		CldLibGeometry* libGeom				= (CldLibGeometry*)TiCollada::Get()->ColladaLibraries[ECL_GEOMETRY];
		CldGeometry* geometry				= libGeom->GetGeometryById(geometry_id.c_str() + 1);
		TI_ASSERT(geometry);
		if (info.Type == EPHYT_SPHERE)
		{
			info.Radius						= abs(geometry->Desc.BBox.MaxEdge.Z - geometry->Desc.BBox.MinEdge.Z) * 0.5f;
		}
		else if (info.Type == EPHYT_CYLINDER)
		{
			info.Radius						= abs(geometry->Desc.BBox.MaxEdge.X - geometry->Desc.BBox.MinEdge.X) * 0.5f;
			info.Height						= abs(geometry->Desc.BBox.MaxEdge.Z - geometry->Desc.BBox.MinEdge.Z);
		}
		else if (info.Type == EPHYT_MESH)
		{
		}
		else 
		{
			TI_ASSERT(0);
		}
	}

	CldSceneNode::CldSceneNode()
		: Parent(NULL)
	{
		Position[0]	= 0;
		Position[1]	= 0;
		Position[2]	= 0;

		Rotation[0]	= 0;
		Rotation[1]	= 0;
		Rotation[2]	= 0;
		Rotation[3]	= 1;

		Scale[0]	= 1;
		Scale[1]	= 1;
		Scale[2]	= 1;
	}

	CldSceneNode::~CldSceneNode()
	{
		Parent		= NULL;

		// Delete all children
		for (unsigned int i = 0 ; i < Children.size() ; ++ i)
		{
			SAFE_DELETE(Children[i]);
		}
		Children.clear();
	}
	FbxAMatrix GetNodeGeometryTransform(FbxNode* pNode) 
	{
		FbxAMatrix matrixGeo;
		matrixGeo.SetIdentity();
		if(pNode->GetNodeAttribute())
		{
			const FbxVector4 lT = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
			const FbxVector4 lR = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
			const FbxVector4 lS = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
			matrixGeo.SetT(lT);
			matrixGeo.SetR(lR);
			matrixGeo.SetS(lS);
		}
		return matrixGeo;
	}
	FbxAMatrix GetNodeWorldTransform(FbxNode* pNode)
	{
		FbxAMatrix matrixL2W;
		matrixL2W.SetIdentity();
		if(NULL== pNode)
		{
			return matrixL2W;
		}
		matrixL2W = pNode->EvaluateGlobalTransform();
		FbxAMatrix matrixGeo = GetNodeGeometryTransform(pNode);
		matrixL2W *= matrixGeo;
		return matrixL2W;
	}
	FbxAMatrix GetNodeLocalTransform(FbxNode* pNode)
	{
		FbxAMatrix matrixL;
		matrixL.SetIdentity();
		if(NULL== pNode)
		{
			return matrixL;
		}
		matrixL = pNode->EvaluateLocalTransform();
		FbxAMatrix matrixGeo = GetNodeGeometryTransform(pNode);
		matrixL *= matrixGeo;
		return matrixL;
	}

	bool CldSceneNode::LoadNode(FbxNode *fbx_node)
	{
		// load transform
		FbxAMatrix transform = GetNodeLocalTransform(fbx_node);
		FbxVector4 pos = transform.GetT();
		FbxVector4 rot = transform.GetR();
		FbxVector4 scale = transform.GetS();

		Position[0] = (float)pos[0];
		Position[1] = (float)pos[1];
		Position[2] = (float)pos[2];

		quaternion quat(vector3df((float)(DEG_TO_RAD(rot[0])), (float)(DEG_TO_RAD(rot[1])), (float)(DEG_TO_RAD(rot[2]))));
		Rotation[0] = quat[0];
		Rotation[1] = quat[1];
		Rotation[2] = quat[2];
		Rotation[3] = quat[3];

		Scale[0] = (float)scale[0];
		Scale[1] = (float)scale[1];
		Scale[2] = (float)scale[2];

		if (Type == "MESH")
		{
			InstanceUrl = Id + "-mesh";
			BindMaterialId = Id + "-material";
		}

		return true;
	}

	void CldSceneNode::AddChild(ti::CldSceneNode *node)
	{
		node->Parent	= this;
		Children.push_back(node);
	}

	void CldSceneNode::Remove()
	{
		if (Parent)
		{
			Parent->RemoveChild(this);
		}
	}

	void CldSceneNode::RemoveChild(CldSceneNode* c)
	{
		ti_vector<CldSceneNode*>::iterator it = std::find(Children.begin(), Children.end(), c);
		if (it != Children.end())
		{
			(*it)->Parent = 0;
			Children.erase(it);
		}
	}

	CldSceneNode* CldSceneNode::GetNodeById(const ti_string& _id)
	{
		if (_id == Id)
			return this;

		ti_vector < CldSceneNode* >::iterator it;
		for (it = Children.begin() ; it != Children.end() ; ++ it)
		{
			CldSceneNode* node	= (*it)->GetNodeById(_id);
			if (node)
				return node;
		}

		return NULL;
	}

	CldSceneNode* CldSceneNode::GetNodeByInstanceUrl(const ti_string& _url)
	{
		if (_url == InstanceUrl)
			return this;

		ti_vector < CldSceneNode* >::iterator it;
		for (it = Children.begin() ; it != Children.end() ; ++ it)
		{
			CldSceneNode* node	= (*it)->GetNodeByInstanceUrl(_url);
			if (node)
				return node;
		}

		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////

	CldLibVisualScene::CldLibVisualScene()
		: NodeRoot(NULL)
		, HangNodeOnEmitter(false)
	{
	}

	CldLibVisualScene::~CldLibVisualScene()
	{
		SAFE_DELETE(NodeRoot);
	}

	bool CldLibVisualScene::ConvertFromFbx(FbxNode* node)
	{
		if (NodeRoot == NULL)
		{
			const TiColladaConfig& cfg	= TiCollada::Get()->Config;
			NodeRoot					= new CldSceneNode;
			NodeRoot->Id				= cfg.InputFilename + "-" + node->GetNameOnly().Buffer();
			NodeRoot->Name				= node->GetNameOnly().Buffer();
			NodeRoot->Type				= "MESHROOT";
			NodeList.push_back(NodeRoot);
		}
		LoadNodes(node, NodeRoot);

		//TiColladaConfig& config		= TiCollada::Get()->Config;
		//if (config.OptimizeSkinmesh)
		//{
		//	RemoveUnusedNodes(NodeRoot);
		//}

		//CldLibAnimation* libAnim		= (CldLibAnimation*)TiCollada::Get()->ColladaLibraries[ECL_ANIMATIONS];
		//libAnim->UpdateMorphAnimations(this);

		Loaded	= true;
		return true;
	}

	static const char* fbx_node_type_names[] = {
		"NODE",		//eUnknown,
		"NODE",		//eNull,
		"NODE",		//eMarker,
		"NODE",		//eSkeleton, 
		"MESH",		//eMesh, 
		"NODE",		//eNurbs, 
		"NODE",		//ePatch,
		"CAMERA",	//eCamera, 
		"NODE",		//eCameraStereo,
		"NODE",		//eCameraSwitcher,
		"LIGHT",	//eLight,
		"NODE",		//eOpticalReference,
		"NODE",		//eOpticalMarker,
		"NODE",		//eNurbsCurve,
		"NODE",		//eTrimNurbsSurface,
		"NODE",		//eBoundary,
		"NODE",		//eNurbsSurface,
		"NODE",		//eShape,
		"NODE",		//eLODGroup,
		"NODE",		//eSubDiv,
		"NODE",		//eCachedEffect,
		"NODE",		//eLine
	};

	void CldLibVisualScene::LoadNodes(FbxNode* fbx_node_root, CldSceneNode* node_root)
	{
		for(int i = 0 ; i < fbx_node_root->GetChildCount() ; ++i) 
		{
			FbxNode* fbx_node = fbx_node_root->GetChild(i);
			CldSceneNode* node = new CldSceneNode;
			node->Id = fbx_node->GetNameOnly().Buffer();
			int node_type = fbx_node->GetNodeAttribute() != NULL ? fbx_node->GetNodeAttribute()->GetAttributeType() : 0;
			node->Type = fbx_node_type_names[node_type];

			node->LoadNode(fbx_node);
			
			node_root->AddChild(node);
			NodeList.push_back(node);

			LoadNodes(fbx_node, node);
		}
	}

	int CldLibVisualScene::GetNodeIndex(CldSceneNode* node)
	{
		int i		= 0;
		int size	= NodeList.size();
		for (i = 0 ; i < size ; ++ i)
		{
			if (NodeList[i] == node)
				return i;
		}
		return -1;
	}

	int	GetNodeType(const ti_string& nodeType)
	{
		if (nodeType == "MESH")
			return ENT_MESH;
		else if (nodeType == "SKINMESH")
			return ENT_SKINMESH;
		else if (nodeType == "MORPHMESH")
			return ENT_MORPHMESH;
		else if (nodeType == "PHYSIC")
			return ENT_PHYSIC;
		else if (nodeType == "TRIGGER")
			return ENT_TRIGGER;
		else if (nodeType == "LIGHT")
			return ENT_LIGHT;
		else if (nodeType == "CAMERA")
			return ENT_CAMERA;
		else if (nodeType == "MESHROOT")
			return ENT_GEOMETRY;
		else if (nodeType == "JOINT")
			return ENT_JOINT;
		else if (nodeType == "EMITTER")
			return ENT_EMITTER;
		return ENT_NODE;
	}

	bool CldLibVisualScene::Save(ti_vector<ti_string>& string_list)
	{
		CldLibImage* libImage		= (CldLibImage*)TiCollada::Get()->ColladaLibraries[ECL_IMAGES];
		CldLibMaterial* libMaterial	= (CldLibMaterial*)TiCollada::Get()->ColladaLibraries[ECL_MATERIALS];
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_SCENE;
		header.Version		= TIRES_VERSION_CHUNK_SCEN;
		header.ElementCount	= NodeList.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader) + NodeList.size() * sizeof(NodeDesc);

		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));

		NodeDesc desc;
		for (unsigned int i = 0 ; i < NodeList.size() ; ++ i)
		{
			CldSceneNode* node			= NodeList[i];

			desc.StrIndex_Id			= AddStringToList(node->Id, string_list);
			desc.StrIndex_Sid			= AddStringToList(node->Sid, string_list);
			desc.Type					= GetNodeType(node->Type);
			desc.Flag					= 0;
			desc.StrIndex_InstanceUrl	= AddStringToList(node->InstanceUrl.empty() ? "" : node->InstanceUrl.c_str() + 1, string_list);
			desc.ParentNodeIndex		= GetNodeIndex(node->Parent);

			if (desc.Type == ENT_MESH ||
				desc.Type == ENT_SKINMESH ||
				desc.Type == ENT_MORPHMESH)
			{
				desc.StrIndex_MId		= AddStringToList(node->BindMaterialId.c_str() + 1, string_list);
			}
			else
			{
				desc.StrIndex_MId		= -1;
			}

			// physic info
			//memset(&(desc.Physic), 0, sizeof(PhysicDesc));
			//if (desc.Type == ENT_PHYSIC)
			//{
			//	memcpy(&(desc.Physic), &(node->PhysicInfo), sizeof(PhysicDesc));
			//	if (desc.Physic.Type == EPHYT_MESH)
			//	{
			//		TI_ASSERT(!node->InstanceUrl.empty());
			//		desc.Physic.MeshIdIndex		= desc.StrIndex_InstanceUrl;
			//	}
			//}
			//else
			//{
			//	desc.Physic.Type		= EPHYT_INVALID;
			//}

			// bbox info
			desc.ExtraBBox				= node->ExtraBBox;

			memcpy(desc.Position, node->Position, sizeof(float) * 3);
			memcpy(desc.Rotation, node->Rotation, sizeof(float) * 4);
			memcpy(desc.Scale, node->Scale, sizeof(float) * 3);

			OutputStream.Put(&desc, sizeof(NodeDesc));
		}

		return true;
	}

	CldSceneNode* CldLibVisualScene::GetNodeById(const ti_string& _id)
	{
		return NodeRoot->GetNodeById(_id);
	}

	CldSceneNode* CldLibVisualScene::GetNodeByInstanceUrl(const ti_string& _url)
	{
		return NodeRoot->GetNodeByInstanceUrl(_url);
	}
};