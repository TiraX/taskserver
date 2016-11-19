/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.10.19
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibController.h"

namespace ti
{
	//static const char* k_tag_libcontrollers		= "library_controllers"; 
	//static const char* k_tag_controller			= "controller"; 
	//static const char* k_tag_skin				= "skin";  
	//static const char* k_tag_morph				= "morph"; 
	//static const char* k_tag_joints				= "joints"; 
	//static const char* k_tag_vertex_weights		= "vertex_weights"; 
	//static const char* k_tag_vcount				= "vcount"; 
	//static const char* k_tag_v					= "v"; 
	//static const char* k_tag_bsm				= "bind_shape_matrix"; 

	////////////////////////////////////////////////////////////////////////////

	//CldController::CldController(int type)
	//	: Type(type)
	//{
	//}

	//CldController::~CldController()
	//{
	//	for (unsigned int i = 0 ; i < Sources.size() ; ++ i)
	//	{
	//		delete Sources[i];
	//	}
	//	Sources.clear();
	//}

	//Source* CldController::GetSourceById(const char* source_id)
	//{
	//	for (u32 i = 0 ; i < Sources.size() ; ++ i)
	//	{
	//		if (Sources[i]->Id == source_id)
	//		{
	//			return Sources[i];
	//		}
	//	}
	//	return NULL;
	//}

	//bool CldJoint::Load(TiXmlElement* joint_root)
	//{
	//	Inputs.clear();

	//	// load inputs
	//	TiXmlElement* cld_input	= joint_root->FirstChildElement(k_tag_input);
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

	//ti_string CldJoint::GetSourceIdBySemantic(const ti_string& s)
	//{
	//	for (u32 i = 0 ; i < Inputs.size() ; ++ i)
	//	{
	//		if (Inputs[i].Semantic == s)
	//		{
	//			return Inputs[i].Source;
	//		}
	//	}

	//	return "";
	//}

	//bool CldVertexWeight::Load(TiXmlElement* vweight_root)
	//{
	//	vweight_root->Attribute(k_attr_count, &Count);

	//	// load inputs
	//	Inputs.clear();
	//	TiXmlElement* eleInput	= vweight_root->FirstChildElement(k_tag_input);
	//	while (eleInput)
	//	{
	//		Input input;
	//		input.Semantic		= eleInput->Attribute(k_attr_semantic);
	//		input.Source		= eleInput->Attribute(k_attr_source);
	//		eleInput->Attribute(k_attr_offset, &input.Offset);

	//		Inputs.push_back(input);
	//		eleInput			= eleInput->NextSiblingElement(k_tag_input);
	//	}

	//	// load bone count array
	//	TiXmlElement* eleBoneCount	= vweight_root->FirstChildElement(k_tag_vcount);
	//	TI_ASSERT(eleBoneCount);
	//	TiXmlElement* eleBoneWeightIndex
	//								= vweight_root->FirstChildElement(k_tag_v);
	//	TI_ASSERT(eleBoneWeightIndex);
	//	BoneCountArray.clear();
	//	BoneWeightIndexArray.clear();
	//	ReadIntArray(eleBoneCount->FirstChild()->ToText()->Value(), BoneCountArray);
	//	ReadIntArray(eleBoneWeightIndex->FirstChild()->ToText()->Value(), BoneWeightIndexArray);

	//	TI_ASSERT(Count == BoneCountArray.size());
	//	return true;
	//}

	//ti_string CldVertexWeight::GetSourceIdBySemantic(const ti_string& s)
	//{
	//	for (u32 i = 0 ; i < Inputs.size() ; ++ i)
	//	{
	//		if (Inputs[i].Semantic == s)
	//		{
	//			return Inputs[i].Source;
	//		}
	//	}

	//	return "";
	//}

	//bool CldControllerSkin::LoadSkinController(TiXmlElement* skin_root)
	//{
	//	// load bind shape matrix
	//	TiXmlElement* bsm			= skin_root->FirstChildElement(k_tag_bsm);
	//	TI_ASSERT(bsm);
	//	BindShapeMatrix.clear();
	//	ReadFloatArray(bsm->FirstChild()->ToText()->Value(), BindShapeMatrix);

	//	TargetSource				= skin_root->Attribute(k_attr_source);
	//	// load sources
	//	TiXmlElement* eleSource		= skin_root->FirstChildElement(k_tag_source);
	//	while (eleSource)
	//	{
	//		Source* source			= new Source;
	//		source->Load(eleSource);

	//		Sources.push_back(source);
	//		eleSource				= eleSource->NextSiblingElement(k_tag_source);
	//	}
	//	// load joint
	//	TiXmlElement* eleJoint		= skin_root->FirstChildElement(k_tag_joints);
	//	TI_ASSERT(eleJoint);
	//	Joint.Load(eleJoint);

	//	// load vertex weights
	//	TiXmlElement* eleVWeights	= skin_root->FirstChildElement(k_tag_vertex_weights);
	//	TI_ASSERT(eleVWeights);
	//	VertexWeight.Load(eleVWeights);

	//	return Convert();
	//}

	//bool CldControllerSkin::Convert()
	//{
	//	// convert VertexWeight.BoneCountArray and VertexWeight.BoneWeightIndexArray to SkinInfo array.
	//	SAFE_DELETE_ARRAY(SkinInfo);
	//	SkinInfo					= new VertexSkinInfo[VertexWeight.Count];
	//	ti_string source_id			= VertexWeight.GetSourceIdBySemantic("WEIGHT");
	//	TI_ASSERT(source_id != "");
	//	Source* weight_source		= GetSourceById(source_id.c_str() + 1);
	//	TI_ASSERT(weight_source);
	//	int weight_offset			= 0;
	//	for (int i = 0 ; i < VertexWeight.Count ; ++ i)
	//	{
	//		VertexSkinInfo& info	= SkinInfo[i];
	//		info.BoneCount			= VertexWeight.BoneCountArray[i];
	//		TI_ASSERT(info.BoneCount > 0);
	//		for (int b = 0 ; b < info.BoneCount ; ++ b)
	//		{
	//			VertexBoneInfo bInfo;
	//			bInfo.BoneIndex		= VertexWeight.BoneWeightIndexArray[weight_offset + 0];
	//			int weight_index	= VertexWeight.BoneWeightIndexArray[weight_offset + 1];
	//			bInfo.BoneWeight	= weight_source->ArrayFloat[weight_index];
	//			info.BoneInfo.push_back(bInfo);
	//			weight_offset		+= 2;
	//		}

	//		// trim info, remove the 0 weight components
	//		ti_vector<VertexBoneInfo>::iterator it;
	//		for (it = info.BoneInfo.begin() ; it != info.BoneInfo.end() ; )
	//		{
	//			if (it->BoneWeight == 0.0f)
	//			{
	//				it	= info.BoneInfo.erase(it);
	//			}
	//			else
	//			{
	//				it ++;
	//			}
	//		}
	//		info.BoneCount	= info.BoneInfo.size();
	//		//TI_ASSERT(info.BoneCount > 0 && info.BoneCount <= 4);
	//		//if (info.BoneCount <= 0 || info.BoneCount > 4)
	//		//{
	//		//	_LOG("  Error: %s - Current [%d].\n", Id.c_str(), info.BoneCount);
	//		//	ti_string j_source_id		= VertexWeight.GetSourceIdBySemantic("JOINT");
	//		//	TI_ASSERT(j_source_id != "");
	//		//	Source* joint_source		= GetSourceById(j_source_id.c_str() + 1);
	//		//	TI_ASSERT(joint_source);
	//		//	for (int b = 0 ; b < info.BoneCount ; ++ b)
	//		//	{
	//		//		_LOG("    - %d, %s.\n", info.BoneInfo[b].BoneIndex, joint_source->ArrayString[info.BoneInfo[b].BoneIndex].c_str());
	//		//	}
	//		//}
	//		TI_ASSERT(info.BoneCount > 0);
	//		if (info.BoneCount > 4)
	//		{
	//			// sort weights
	//			ti_vector<float> weights;
	//			for (it = info.BoneInfo.begin() ; it != info.BoneInfo.end() ; ++ it )
	//			{
	//				weights.push_back(it->BoneWeight);
	//			}
	//			std::sort(weights.begin(), weights.end());
	//			// remove the lowest
	//			int small_counts = weights.size() - 4;
	//			ti_vector<float>::iterator itw;
	//			for (it = info.BoneInfo.begin() ; it != info.BoneInfo.end() ; )
	//			{
	//				itw = std::find(weights.begin(), weights.end(), it->BoneWeight);
	//				int dis = std::distance(weights.begin(), itw);
	//				if (dis < small_counts)
	//				{
	//					// remove this
	//					it = info.BoneInfo.erase(it);
	//				}
	//				else
	//				{
	//					++ it;
	//				}
	//			}

	//			// normalize it
	//			float weights_total = 0.f;
	//			for (it = info.BoneInfo.begin() ; it != info.BoneInfo.end() ; ++ it)
	//			{
	//				weights_total += it->BoneWeight;
	//			}
	//			float weights_total_inv = 1.f / weights_total;
	//			for (it = info.BoneInfo.begin() ; it != info.BoneInfo.end() ; ++ it)
	//			{
	//				it->BoneWeight	*= weights_total_inv;
	//			}
	//			info.BoneCount	= info.BoneInfo.size();
	//		}
	//		TI_ASSERT(info.BoneCount > 0 && info.BoneCount <= 4);
	//		if (info.BoneCount <= 0)
	//		{
	//			_LOG("  Error: %s - Current [%d].\n", Id.c_str(), info.BoneCount);
	//		}
	//	}

	//	return true;
	//}

	//bool CldControllerSkin::Save(TiStream& stream, ti_vector<ti_string>& string_list)
	//{
	//	const float unit			= TiCollada::Get()->Config.UnitParam;
	//	// get bone source
	//	ti_string joint_source_name	= VertexWeight.GetSourceIdBySemantic("JOINT");
	//	TI_ASSERT(joint_source_name != "");
	//	Source* joint_source		= GetSourceById(joint_source_name.c_str() + 1);
	//	TI_ASSERT(joint_source);
	//	ti_string bp_source_name	= Joint.GetSourceIdBySemantic("INV_BIND_MATRIX");
	//	TI_ASSERT(bp_source_name != "");
	//	Source* bp_source			= GetSourceById(bp_source_name.c_str() + 1);
	//	TI_ASSERT(bp_source);

	//	// bone name map from sid to bone id
	//	CldLibVisualScene* lib_scene	= (CldLibVisualScene*)TiCollada::Get()->ColladaLibraries[ECL_VISUALSCENE];
	//	ti_map<ti_string, ti_string>& sid_map = lib_scene->SidMap;

	//	for (int b = 0 ; b < joint_source->_Accessor.Count ; ++ b)
	//	{
	//		BoneDesc bDesc;
	//		TI_ASSERT(sid_map.find(joint_source->ArrayString[b]) != sid_map.end());
	//		bDesc.BoneName_StrIndex		= AddStringToList(sid_map[joint_source->ArrayString[b]], string_list);
	//		TI_ASSERT(bp_source->_Accessor.Stride == 16);
	//		TI_ASSERT(bp_source->_Accessor.Count == joint_source->_Accessor.Count);
	//		for (int bm = 0 ; bm < 16 ; ++ bm)
	//		{
	//			bDesc.InvertBindMatrix[bm]	= bp_source->ArrayFloat[b * 16 + bm];
	//		}
	//		bDesc.InvertBindMatrix[3]		*= unit;
	//		bDesc.InvertBindMatrix[7]		*= unit;
	//		bDesc.InvertBindMatrix[11]		*= unit;
	//		stream.Put(&bDesc, sizeof(BoneDesc));
	//	}
	//	return true;
	//}

	////////////////////////////////////////////////////////////////////////////

	//bool CldControllerMorph::LoadMorphController(TiXmlElement* morph_root)
	//{
	//	TargetSource				= morph_root->Attribute(k_attr_source);
	//	// load sources
	//	TiXmlElement* cldSource		= morph_root->FirstChildElement(k_tag_source);
	//	while (cldSource)
	//	{
	//		Source* source			= new Source;
	//		source->Load(cldSource);

	//		Sources.push_back(source);
	//		cldSource				= cldSource->NextSiblingElement(k_tag_source);
	//	}

	//	// load target
	//	TiXmlElement* cldTarget		= morph_root->FirstChildElement("targets");
	//	TI_ASSERT(cldTarget);
	//	TiXmlElement* cldInput		= cldTarget->FirstChildElement("input");
	//	while (cldInput)
	//	{
	//		ti_string semantic		= cldInput->Attribute(k_attr_semantic);
	//		if (semantic == "MORPH_TARGET")
	//		{
	//			Targets.target.Semantic	= semantic;
	//			Targets.target.Source	= cldInput->Attribute(k_attr_source);
	//		}
	//		else if (semantic == "MORPH_WEIGHT")
	//		{
	//			Targets.weight.Semantic	= semantic;
	//			Targets.weight.Source	= cldInput->Attribute(k_attr_source);
	//		}
	//		cldInput				= cldInput->NextSiblingElement("input");
	//	}

	//	return Convert();
	//}

	//bool CldControllerMorph::Convert()
	//{
	//	// fill morph info array
	//	Source* target_source		= GetSourceById(Targets.target.Source.c_str() + 1);
	//	Source* weight_source		= GetSourceById(Targets.weight.Source.c_str() + 1);
	//	TI_ASSERT(target_source && weight_source);
	//	TI_ASSERT(target_source->ArrayIDRef.Count == weight_source->ArrayFloat.Count);

	//	MorphInfos.clear();
	//	for (int i = 0 ; i < target_source->ArrayIDRef.Count ; ++ i)
	//	{
	//		MorphInfo info;
	//		info.target				= target_source->ArrayIDRef.ArrayData[i];
	//		info.weight				= weight_source->ArrayFloat.ArrayData[i];
	//		MorphInfos.push_back(info);
	//	}

	//	return true;
	//}

	//bool CldControllerMorph::Save(TiStream& stream, ti_vector<ti_string>& string_list)
	//{
	//	for (u32 m = 0 ; m < MorphInfos.size() ; ++ m)
	//	{
	//		const MorphInfo& info	= MorphInfos[m];
	//		MorphTargetDesc mtDesc;
	//		mtDesc.TargetName		= AddStringToList(info.target, string_list);
	//		mtDesc.Weight			= info.weight;

	//		stream.Put(&mtDesc, sizeof(MorphInfo));
	//	}
	//	return true;
	//}


	//////////////////////////////////////////////////////////////////////////

	CldLibController::CldLibController()
	{
	}

	CldLibController::~CldLibController()
	{
		//// remove all geometries
		//for (unsigned int i = 0 ; i < Controllers.size() ; ++ i)
		//{
		//	delete Controllers[i];
		//}
		//Controllers.clear();
	}

	bool CldLibController::ConvertFromFbx(FbxNode* node)
	{
		return false;
		//TiXmlElement* lib_controllers	= colladaRoot->FirstChildElement(k_tag_libcontrollers);
		//if (!lib_controllers)
		//{
		//	return false;
		//}

		//// load geometries
		//TiXmlElement* eleController		= lib_controllers->FirstChildElement(k_tag_controller);
		//TiXmlElement *eleSkin, *eleMorph;
		//while (eleController)
		//{
		//	CldController* controller	= NULL;
		//	eleSkin						= eleController->FirstChildElement(k_tag_skin);
		//	eleMorph					= eleController->FirstChildElement(k_tag_morph);
		//	if (eleSkin)
		//	{
		//		CldControllerSkin* skinController;
		//		skinController			= new CldControllerSkin;
		//		skinController->Id		= eleController->Attribute(k_attr_id);
		//		skinController->LoadSkinController(eleSkin);
		//		controller				= skinController;
		//	}
		//	else if (eleMorph)
		//	{
		//		CldControllerMorph* morphController;
		//		morphController			= new CldControllerMorph;
		//		morphController->Id		= eleController->Attribute(k_attr_id);
		//		morphController->LoadMorphController(eleMorph);
		//		controller				= morphController;
		//	}

		//	Controllers.push_back(controller);
		//	eleController				= eleController->NextSiblingElement(k_tag_controller);
		//}

		Loaded	= true;
		return true;
	}

	bool CldLibController::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		//TiResfileChunkHeader header;
		//header.ID			= TIRES_ID_CHUNK_CONTROLLER;
		//header.Version		= TIRES_VERSION_CHUNK_CTRL;
		//header.ElementCount	= Controllers.size();
		//header.ChunkSize	= sizeof(TiResfileChunkHeader);

		//TiStream buf, data_stream;
		//// write desc
		//for (u32 i = 0 ; i < Controllers.size() ; ++ i)
		//{
		//	CldController* controller
		//					= Controllers[i];
		//	if (controller->Type == CONTROLLER_SKIN)
		//	{
		//		CldControllerSkin* skinController
		//									= (CldControllerSkin*)controller;

		//		// get bone source
		//		ControllerDesc	desc;
		//		ti_string joint_source_name	= skinController->VertexWeight.GetSourceIdBySemantic("JOINT");
		//		TI_ASSERT(joint_source_name != "");
		//		Source* joint_source		= skinController->GetSourceById(joint_source_name.c_str() + 1);
		//		TI_ASSERT(joint_source);

		//		desc.Id_StrIndex			= AddStringToList(controller->Id, string_list);
		//		desc.TargetSource_StrIndex	= AddStringToList(controller->TargetSource.c_str() + 1, string_list);
		//		desc.ControllerType			= controller->Type;
		//		desc.TotalBones				= joint_source->_Accessor.Count;
		//		desc.DataOffset				= data_stream.GetLength();
		//		// save data
		//		controller->Save(data_stream, string_list);
		//		buf.Put(&desc, sizeof(ControllerDesc));
		//	}
		//	else if (controller->Type == CONTROLLER_MORPH)
		//	{
		//		CldControllerMorph* morphController
		//									= (CldControllerMorph*)controller;
		//		ControllerDesc	desc;
		//		desc.Id_StrIndex			= AddStringToList(controller->Id, string_list);
		//		desc.TargetSource_StrIndex	= AddStringToList(controller->TargetSource.c_str() + 1, string_list);
		//		desc.ControllerType			= controller->Type;
		//		desc.TotalMorphTargets		= morphController->MorphInfos.size();
		//		desc.DataOffset				= data_stream.GetLength();
		//		controller->Save(data_stream, string_list);
		//		buf.Put(&desc, sizeof(ControllerDesc));
		//	}
		//	else
		//	{
		//		TI_ASSERT(0);
		//	}
		//}

		//header.ChunkSize			+= buf.GetLength();
		//header.ChunkSize			+= data_stream.GetLength();
		//OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		//OutputStream.Put(buf.GetBuffer(), buf.GetLength());
		//OutputStream.Put(data_stream.GetBuffer(), data_stream.GetLength());

		return true;
	}

	//CldController* CldLibController::GetControllerByTargetSource(const ti_string& target_source)
	//{
	//	ti_vector<CldController*>::iterator it;
	//	for (it = Controllers.begin() ; it != Controllers.end() ; ++ it)
	//	{
	//		if (target_source == (*it)->TargetSource.c_str() + 1)
	//		{
	//			return *it;
	//		}
	//	}
	//	return NULL;
	//}

	//CldController* CldLibController::GetControllerById(const ti_string& _id)
	//{
	//	ti_vector<CldController*>::iterator it;
	//	for (it = Controllers.begin() ; it != Controllers.end() ; ++ it)
	//	{
	//		if ((*it)->Id == _id)
	//		{
	//			return *it;
	//		}
	//	}
	//	return NULL;
	//}

	//bool CldLibController::IsMorphTarget(const ti_string& mesh_id)
	//{
	//	for (u32 c = 0 ; c < Controllers.size() ; ++ c)
	//	{
	//		CldController* controller	= Controllers[c];
	//		if (controller->Type == CONTROLLER_MORPH)
	//		{
	//			CldControllerMorph* morph	= (CldControllerMorph*)controller;
	//			for (u32 m = 0 ; m < morph->MorphInfos.size() ; ++ m)
	//			{
	//				if (morph->MorphInfos[m].target == mesh_id)
	//				{
	//					return true;
	//				}
	//			}
	//		}
	//	}
	//	return false;
	//}
};