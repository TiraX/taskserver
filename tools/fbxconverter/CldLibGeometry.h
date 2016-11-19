/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#ifndef _CLDLIBGEOMETRY_H__
#define _CLDLIBGEOMETRY_H__

#include "CldLibrary.h"

namespace ti
{
	class CldGeometry
	{
	public:
		CldGeometry();
		virtual ~CldGeometry();
		bool	LoadFromFbxNode(FbxNode* mesh_node);

		void	GetVertexFormat(FbxMesh* mesh);
		void	GetGeometryData(FbxMesh* mesh);

		ti_string	Id;

		GeometryDesc	Desc;
		TiStream		VertexStream;
		TiStream		IndexStream;

	private:
		void	ReadPosition(FbxMesh* mesh , int ctrlPointIndex , vector3df* pVertex, aabbox3df* bbox, bool init_bbox);
		void	ReadColor(FbxMesh* mesh , int ctrlPointIndex , int vertexCounter , SColorf* pColor);
		bool	ReadUV(FbxMesh* mesh , int ctrlPointIndex , int textureUVIndex , int uvLayer , vector2df* pUV);
		void	ReadNormal(FbxMesh* mesh , int ctrlPointIndex , int vertexCounter , vector3df* pNormal);
		void	ReadTangent(FbxMesh* mesh , int ctrlPointIndex , int vertecCounter , vector3df* pTangent);
	};

	//////////////////////////////////////////////////////////////////////////

	class CldLibGeometry : public CldLibrary
	{
	public:
		CldLibGeometry();
		virtual ~CldLibGeometry();

		virtual bool ConvertFromFbx(FbxNode* node);
		virtual bool Save(ti_vector<ti_string>& string_list);

		CldGeometry*	GetGeometryById(const char* geometry_id);
		void			RemoveGeometryById(const char* geometry_id);

		ti_vector< CldGeometry* >	Geometries;
	};

};

#endif	//_CLDLIBGEOMETRY_H__