/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.26
*/

#include "stdafx.h"
#include "CldLibShaders.h"
#include "Collada.h"

namespace ti
{
	//static const char* k_tag_libshaders		= "library_shaders";
	//static const char* k_tag_shader			= "shader";

	//static const char* k_tag_techniques		= "techniques";
	//static const char* k_tag_technique		= "technique";
	//static const char* k_tag_pass			= "pass";
	//static const char* k_tag_vsh			= "vertex_shader";
	//static const char* k_tag_fsh			= "fragment_shader";
	//static const char* k_tag_renderstate	= "render_state";

	//static const char* k_depth_func[8] = 
	//{
	//	"NEVER",			// 1
	//	"LESS",				// 2
	//	"LESS_EQUAL",		// 3
	//	"EQUAL",			// 4
	//	"GREATER",			// 5
	//	"NOT_EQUAL",		// 6
	//	"GREATER_EQUAL",	// 7
	//	"ALWAYS",			// 8
	//};

	//int GetDepthFunc(const ti_string& str)
	//{
	//	for (int i = 0 ; i < 8 ; ++ i)
	//	{
	//		if ( str == k_depth_func[i] )
	//		{
	//			return i + 1;
	//		}
	//	}

	//	return 2;
	//}

	//static const char* k_blend_func[15] =
	//{
	//	"ZERO", 
	//	"ONE", 
	//	"SRC_COLOR", 
	//	"ONE_MINUS_SRC_COLOR", 
	//	"DEST_COLOR", 
	//	"ONE_MINUS_DEST_COLOR",
	//	"SRC_ALPHA", 
	//	"ONE_MINUS_SRC_ALPHA", 
	//	"DST_ALPHA", 
	//	"ONE_MINUS_DST_ALPHA", 
	//	"CONSTANT_COLOR",
	//	"ONE_MINUS_CONSTANT_COLOR", 
	//	"CONSTANT_ALPHA", 
	//	"ONE_MINUS_CONSTANT_ALPHA", 
	//	"SRC_ALPHA_SATURATE",
	//};

	//int GetBlendFunc(const ti_string& str)
	//{
	//	for (int i = 0 ; i < 15 ; ++ i)
	//	{
	//		if ( str == k_blend_func[i] )
	//		{
	//			return i;
	//		}
	//	}

	//	return 1;
	//}

	//static const char* k_cull_mode[2] = 
	//{
	//	"FRONT",
	//	"BACK",
	//};

	//int GetCullMode(const ti_string& str)
	//{
	//	for (int i = 0 ; i < 2 ; ++ i)
	//	{
	//		if ( str == k_cull_mode[i] )
	//		{
	//			return i;
	//		}
	//	}

	//	return 1;
	//}

	//static const char* k_stencil_op[6] = 
	//{
	//	"KEEP",
	//	"ZERO",
	//	"REPLACE",
	//	"INCREASE",
	//	"DECREASE",
	//	"INVERT",
	//};

	//int GetStencilOp(const ti_string& str)
	//{
	//	for (int i = 0 ; i < 6 ; ++ i)
	//	{
	//		if ( str == k_stencil_op[i] )
	//		{
	//			return i + 1;
	//		}
	//	}

	//	return 1;
	//}

	CldLibShaders::CldLibShaders()
	{
	}

	CldLibShaders::~CldLibShaders()
	{
		//for (UINT i = 0 ; i < Shaders.size() ; ++ i)
		//{
		//	delete Shaders[i];
		//	Shaders[i] = 0;
		//}
	}

	//ti_string CldLibShaders::LoadShaderFile(const ti_string& shader_name)
	//{
	//	ti_string full_path	= shader_name;
	//	TiFile file;
	//	if (!file.Open(full_path, EFA_READ))
	//	{
	//		// try remove file path and retry
	//		int mark		= full_path.find('/');
	//		if (mark != ti_string::npos)
	//			full_path	= full_path.substr(mark + 1);
	//		else
	//			return "";
	//	}
	//	if (!file.Open(full_path, EFA_READ))
	//	{
	//		return "";
	//	}

	//	char* text	= ti_new char[file.GetSize() + 1];
	//	file.Read(text, file.GetSize(), file.GetSize());
	//	text[file.GetSize()]	= 0;

	//	ti_string str	= text;
	//	ti_delete[] text;
	//	return str;
	//}

	bool CldLibShaders::ConvertFromFbx(FbxNode* node)
	{
		//TiXmlElement* lib_shaders		= colladaRoot->FirstChildElement(k_tag_libshaders);
		//if (!lib_shaders)
		//{
		//	return false;
		//}

		//const TiColladaConfig& config	= TiCollada::Get()->Config;
		//// load shaders
		//TiXmlElement* shader			= lib_shaders->FirstChildElement(k_tag_shader);
		//TiXmlElement* ele;
		//while (shader)
		//{
		//	CldShader* cld_shader		= new CldShader;
		//	cld_shader->Id				= shader->Attribute(k_attr_id);
		//	ti_string shader_name		= cld_shader->Id.substr(0, cld_shader->Id.rfind(".tish"));

		//	TiXmlElement* options_es3	= shader->FirstChildElement("is_shader_es_30");
		//	if (options_es3)
		//	{
		//		const char* result		= options_es3->FirstChild()->ToText()->Value();
		//		cld_shader->IsES3		= (strcmp(result, "true") == 0);
		//	}
		//	else
		//	{
		//		cld_shader->IsES3		= false;
		//	}

		//	TiXmlElement* options_dlight	= shader->FirstChildElement("with_dynamic_lights");
		//	if (options_dlight)
		//	{
		//		const char* result			= options_dlight->FirstChild()->ToText()->Value();
		//		cld_shader->IsDynamicLight	= (strcmp(result, "true") == 0);
		//	}
		//	else
		//	{
		//		cld_shader->IsDynamicLight	= false;
		//	}


		//	TiXmlElement* techniques	= shader->FirstChildElement(k_tag_techniques);
		//	TiXmlElement* technique		= techniques->FirstChildElement(k_tag_technique);
		//	while (technique)
		//	{
		//		ti_string tech_id		= technique->Attribute(k_attr_id);
		//		if (config.IsIgnoreTech(tech_id))
		//		{
		//			technique			= technique->NextSiblingElement(k_tag_technique);
		//			continue;
		//		}
		//		CldTechnique* cld_tech	= new CldTechnique;
		//		cld_tech->Id			= tech_id;

		//		TiXmlElement* xml_pass	= technique->FirstChildElement(k_tag_pass);
		//		while (xml_pass)
		//		{
		//			CldPass pass;
		//			pass.Id				= xml_pass->Attribute(k_attr_id);
		//			// vertex shader and fragment shader
		//			TiXmlElement* vsh		= xml_pass->FirstChildElement(k_tag_vsh);
		//			TiXmlElement* fsh		= xml_pass->FirstChildElement(k_tag_fsh);
		//			pass.Vsh_Filename	= vsh->Attribute("filename");
		//			pass.VSH			= LoadShaderFile(pass.Vsh_Filename);
		//			if (pass.VSH == "")
		//			{
		//				pass.VSH		= vsh->FirstChild()->ToText()->Value();
		//				_LOG("  Warning: Can not find shader file [%s], use embed shader instead.\n", pass.Vsh_Filename);
		//			}
		//			pass.Fsh_Filename	= fsh->Attribute("filename");
		//			pass.FSH			= LoadShaderFile(pass.Fsh_Filename);
		//			if (pass.FSH == "")
		//			{
		//				pass.FSH		= fsh->FirstChild()->ToText()->Value();
		//				_LOG("  Warning: Can not find shader file [%s], use embed shader instead.\n", pass.Fsh_Filename);
		//			}

		//			pass.MetalVS		= shader_name + "_" + tech_id + "_" + pass.Id + "_vertex";
		//			pass.MetalFS		= shader_name + "_" + tech_id + "_" + pass.Id + "_fragment";

		//			// render state
		//			TiXmlElement* renderstate;
		//			renderstate				= xml_pass->FirstChildElement(k_tag_renderstate);

		//			ele						= renderstate->FirstChildElement("Wireframe");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				// ignore fill mode, deafult to solid
		//				pass.RenderState.SetRenderState(ERSO_FILLMODE, str != "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("Cull");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_CULL, str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("DepthWrite");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_DEPTH, str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("DepthTest");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_DEPTH_TEST, str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("CullMode");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("value");
		//				pass.RenderState.SetCullMode((E_CULL_MODE)GetCullMode(str));
		//			}

		//			ele						= renderstate->FirstChildElement("Blend");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_BLEND, str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("AlphaTest");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				//pass.RenderState.AlphaTest	= str == "TRUE";
		//				// ignore temp
		//			}

		//			ele						= renderstate->FirstChildElement("IgnoreDepthBuffer");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_IGNORE_DEPTH_BUFFER, str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("DepthFunc");
		//			if (ele)
		//			{
		//				ti_string func		= ele->Attribute("value");
		//				pass.RenderState.SetDepthTestFunc((E_COMPARISON_FUNC)GetDepthFunc(func));
		//			}

		//			ele						= renderstate->FirstChildElement("BlendSrc");
		//			if (ele)
		//			{
		//				ti_string func		= ele->Attribute("value");
		//				pass.RenderState.SetBlendSrc((E_BLEND_FUNC)GetBlendFunc(func));
		//			}

		//			ele						= renderstate->FirstChildElement("BlendDest");
		//			if (ele)
		//			{
		//				ti_string func		= ele->Attribute("value");
		//				pass.RenderState.SetBlendDest((E_BLEND_FUNC)GetBlendFunc(func));
		//			}

		//			ele						= renderstate->FirstChildElement("StencilTest");
		//			if (ele)
		//			{
		//				ti_string str		= ele->Attribute("enable");
		//				pass.RenderState.SetRenderState(ERSO_STENCIL_TEST,  str == "TRUE");
		//			}

		//			ele						= renderstate->FirstChildElement("StencilFunc");
		//			if (ele)
		//			{
		//				ti_string func		= ele->Attribute("value");
		//				pass.RenderState.SetStencilFunc((E_COMPARISON_FUNC)GetDepthFunc(func));
		//			}

		//			ele						= renderstate->FirstChildElement("StencilRef");
		//			if (ele)
		//			{
		//				ti_string ref_v		= ele->Attribute("value");
		//				pass.RenderState.SetStencilRef(atoi(ref_v.c_str()));
		//			}

		//			ele						= renderstate->FirstChildElement("StencilOp");
		//			if (ele)
		//			{
		//				ti_string sfail		= ele->Attribute("sfail");
		//				ti_string zfail		= ele->Attribute("zfail");
		//				ti_string zpass		= ele->Attribute("zpass");
		//				pass.RenderState.SetStencilOp((E_STENCIL_OP)GetStencilOp(sfail),
		//											  (E_STENCIL_OP)GetStencilOp(zfail),
		//											  (E_STENCIL_OP)GetStencilOp(zpass));
		//			}

		//			cld_tech->Passes.push_back(pass);

		//			xml_pass			= xml_pass->NextSiblingElement(k_tag_pass);
		//		}

		//		cld_shader->Techniques.push_back(cld_tech);
		//		technique				= technique->NextSiblingElement(k_tag_technique);
		//	}

		//	Shaders.push_back(cld_shader);
		//	shader						= shader->NextSiblingElement(k_tag_shader);
		//}

		Loaded	= true;
		return true;
	}

	bool CldLibShaders::Save(ti_vector<ti_string>& string_list)
	{
		//OutputStream.Reset();

		//TiResfileChunkHeader header;
		//header.ID			= TIRES_ID_CHUNK_SHADER;
		//header.Version		= TIRES_VERSION_CHUNK_SHAD;
		//header.ElementCount	= Shaders.size();
		//header.ChunkSize	= sizeof(TiResfileChunkHeader);

		//TiStream stream;
		//ShaderDesc desc;
		//ShaderTechDesc techDesc;
		//ShaderPassDesc passDesc;
		//for (unsigned int i = 0 ; i < Shaders.size() ; ++ i)
		//{
		//	CldShader* shader			= Shaders[i];
		//	desc.StrIndex_Id			= AddStringToList(shader->Id, string_list);
		//	desc.TechniqueCount			= shader->Techniques.size();
		//	desc.Options				= 0;
		//	if (shader->IsES3)
		//		desc.Options			|= SHADER_OPTION_ESSL30;
		//	if (shader->IsDynamicLight)
		//		desc.Options			|= SHADER_OPTION_DLIGHTS;
		//	stream.Put(&desc, sizeof(ShaderDesc));

		//	for (int t = 0 ; t < desc.TechniqueCount ; ++ t)
		//	{
		//		CldTechnique* tech		= shader->Techniques[t];
		//		techDesc.StrIndex_Id	= AddStringToList(tech->Id, string_list);
		//		techDesc.PassCount		= tech->Passes.size();

		//		stream.Put(&techDesc, sizeof(ShaderTechDesc));

		//		for (int p = 0 ; p < techDesc.PassCount ; ++ p)
		//		{
		//			CldPass& pass			= tech->Passes[p];
		//			passDesc.StrIndex_Id	= AddStringToList(pass.Id, string_list);
		//			passDesc.StrIndex_VSName= AddStringToList(pass.Vsh_Filename, string_list);
		//			passDesc.StrIndex_FSName= AddStringToList(pass.Fsh_Filename, string_list);
		//			if (TiCollada::Get()->Config.EmbedShader)
		//			{
		//				passDesc.StrIndex_VSH	= AddStringToList(pass.VSH, string_list);
		//				passDesc.StrIndex_FSH	= AddStringToList(pass.FSH, string_list);
		//			}
		//			else
		//			{
		//				passDesc.StrIndex_VSH	= -1;
		//				passDesc.StrIndex_FSH	= -1;
		//			}
		//			if (pass.MetalVS != "" &&
		//				pass.MetalFS != "")
		//			{
		//				passDesc.StrIndex_MetalVS	= AddStringToList(pass.MetalVS, string_list);
		//				passDesc.StrIndex_MetalFS	= AddStringToList(pass.MetalFS, string_list);
		//			}
		//			else
		//			{
		//				passDesc.StrIndex_MetalVS	= -1;
		//				passDesc.StrIndex_MetalFS	= -1;
		//			}

		//			passDesc.RenderState	= pass.RenderState;

		//			stream.Put(&passDesc, sizeof(ShaderPassDesc));
		//		}
		//	}
		//}
		//header.ChunkSize	+= stream.GetLength();
		//OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		//OutputStream.Put(stream.GetBuffer(), stream.GetLength());

		return true;
	}
};