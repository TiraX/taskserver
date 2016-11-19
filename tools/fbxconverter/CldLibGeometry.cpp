/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"
#include "Collada.h"
#include "CldLibGeometry.h"
#include <sstream>
#include <math.h>

using namespace std;

namespace ti
{
	CldGeometry::CldGeometry()
	{
	}

	CldGeometry::~CldGeometry()
	{
	}

	bool CldGeometry::LoadFromFbxNode(FbxNode* mesh_node)
	{
		FbxMesh* mesh = mesh_node->GetMesh();
		GetVertexFormat(mesh);
		GetGeometryData(mesh);
		return true;
	}

	void CldGeometry::GetVertexFormat(FbxMesh* mesh)
	{
		Desc.VertexFormat = 0;
		Desc.VertexFormat |= EVSSEG_POSITION;

		if (mesh->GetElementNormalCount() > 0)
		{
			Desc.VertexFormat |= EVSSEG_NORMAL;
		}
		if (mesh->GetElementVertexColorCount() > 0)
		{
			Desc.VertexFormat |= EVSSEG_COLOR;
		}
		if (mesh->GetElementUVCount() > 0)
		{
			Desc.VertexFormat |= EVSSEG_TEXCOORD0;
		}
		if (mesh->GetElementUVCount() > 1)
		{
			Desc.VertexFormat |= EVSSEG_TEXCOORD1;
		}
		if (mesh->GetElementTangentCount() > 0)
		{
			Desc.VertexFormat |= EVSSEG_TANGENT;
		}
	}

	// Hash ref: http://www.brpreiss.com/books/opus4/html/page217.html
#define HASH_FLOAT( f, exp, bitShift ) ( unsigned int )( !f ? 0 : ( ( ( unsigned int ) (( 2 * fabs( frexp( f, &exp ) ) - 1 ) * ~0U * ( f < 0 ? -1 : 1 ))) << bitShift ) )
#define INIT_HASH_PARAMETERS( hashBitShifts, srcStride ) { unsigned int  hashSize = ( unsigned int ) srcStride; hashBitShifts.reserve(hashSize); for (unsigned int h = 0; h < hashSize; ++h) hashBitShifts.push_back(32 * h / hashSize); }
#define HASH_INT(i, bitShift) ( unsigned int ) ( !i ? 0 :( i << bitShift ))

	inline u32 getHashFrom(const vector2df& v2, ti_vector<int>& shift, int shift_index) {
		u32 h = 0;
		int _e = 0;
		int _s;
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(v2[0], _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(v2[1], _e, _s);
		return h;
	}
	inline u32 getHashFrom(const vector3df& v3, ti_vector<int>& shift, int shift_index) {
		u32 h = 0;
		int _e = 0;
		int _s;
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(v3[0], _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(v3[1], _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(v3[2], _e, _s);
		return h;
	}
	inline u32 getHashFrom(const SColorf& c, ti_vector<int>& shift, int shift_index) {
		u32 h = 0;
		int _e = 0;
		int _s;
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(c.R, _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(c.G, _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(c.B, _e, _s);
		_s = shift[shift_index ++];
		h ^= HASH_FLOAT(c.A, _e, _s);
		return h;
	}

	void CldGeometry::GetGeometryData(FbxMesh* mesh)
	{
		VertexStream.Reset();
		IndexStream.Reset();

		// calculate vertex stride
		int vertex_stride = 0;
		static const int k_seg_stride[] = 
		{
			sizeof(vector3df),	// ESSI_POSITION		= 0,
			sizeof(vector3df),	// ESSI_NORMAL,
			sizeof(SColorf),	// ESSI_COLOR,
			sizeof(vector2df),	// ESSI_TEXCOORD0,
			sizeof(vector2df),	// ESSI_TEXCOORD1,
			sizeof(vector3df),	// ESSI_TANGENT,
			sizeof(SColorf),	// ESSI_BLENDINDEX,
			sizeof(SColorf),	// ESSI_BLENDWEIGHT,
		};
		for (int i = ESSI_POSITION ; i < ESSI_TOTAL ; ++ i)
		{
			if ((Desc.VertexFormat & (1 << i)) != 0)
			{
				vertex_stride += k_seg_stride[i];
			}
		}
		int float_stride = vertex_stride / sizeof(float);

		ti_vector<int>	hashBitShifts;
		INIT_HASH_PARAMETERS(hashBitShifts, float_stride);

		ti_map<unsigned int, int>	IndexMap;
		ti_vector<int>				Indices;

		unsigned int hash_code;
		int	index	= 0;

		// go through every vertex
		vector3df vertex;
		SColorf color;
		vector3df normal;
		vector3df tangent;
		vector2df uv0, uv1;

		int triangleCount = mesh->GetPolygonCount();
		int vertexCounter = 0;

		for(int i = 0 ; i < triangleCount ; ++i)  
		{
			for(int j = 0 ; j < 3 ; j++)  
			{
				hash_code = 0;
				int float_index = 0;

				int ctrlPointIndex = mesh->GetPolygonVertex(i , j);

				// Read the position  
				ReadPosition(mesh , ctrlPointIndex , &vertex, &Desc.BBox, i == 0 && j == 0);
				hash_code ^= getHashFrom(vertex, hashBitShifts, float_index);
				float_index += 3;

				// Read the normal of each vertex
				if (Desc.VertexFormat & EVSSEG_NORMAL)
				{
					ReadNormal(mesh , ctrlPointIndex , vertexCounter , &normal);
					hash_code ^= getHashFrom(normal, hashBitShifts, float_index);
					float_index += 3;
				}

				// Read the color of each vertex  
				if (Desc.VertexFormat & EVSSEG_COLOR)
				{
					ReadColor(mesh , ctrlPointIndex , vertexCounter , &color);
					hash_code ^= getHashFrom(color, hashBitShifts, float_index);
					float_index += 4;
				}

				// Read the UV of each vertex  
				if (Desc.VertexFormat & EVSSEG_TEXCOORD0)
				{
					ReadUV(mesh , ctrlPointIndex , mesh->GetTextureUVIndex(i, j) , 0 , &uv0);
					hash_code ^= getHashFrom(uv0, hashBitShifts, float_index);
					float_index += 2;
				}
				if (Desc.VertexFormat & EVSSEG_TEXCOORD1)
				{
					ReadUV(mesh , ctrlPointIndex , mesh->GetTextureUVIndex(i, j) , 1 , &uv1);
					hash_code ^= getHashFrom(uv1, hashBitShifts, float_index);
					float_index += 2;
				}

				// Read the tangent of each vertex  
				if (Desc.VertexFormat & EVSSEG_TANGENT)
				{
					ReadTangent(mesh , ctrlPointIndex , vertexCounter , &tangent);
					hash_code ^= getHashFrom(tangent, hashBitShifts, float_index);
					float_index += 3;
				}

				vertexCounter++;

				// test if this is a new vertex
				if (IndexMap.find(hash_code) == IndexMap.end())
				{
					// a new vertex, put to stream buffer
					VertexStream.Put(&vertex, sizeof(vector3df));
					if (Desc.VertexFormat & EVSSEG_NORMAL)
					{
						VertexStream.Put(&normal, sizeof(vector3df));
					}

					if (Desc.VertexFormat & EVSSEG_COLOR)
					{
						VertexStream.Put(&color, sizeof(SColorf));
					}

					if (Desc.VertexFormat & EVSSEG_TEXCOORD0)
					{
						VertexStream.Put(&uv0, sizeof(vector2df));
					}

					if (Desc.VertexFormat & EVSSEG_TEXCOORD1)
					{
						VertexStream.Put(&uv1, sizeof(vector2df));
					}

					if (Desc.VertexFormat & EVSSEG_TANGENT)
					{
						VertexStream.Put(&tangent, sizeof(vector3df));
					}

					IndexMap[hash_code] = index;
					Indices.push_back(index);
					++ index;
				}
				else
				{
					// an existed vertex, record index only.
					Indices.push_back(IndexMap[hash_code]);
				}
			}
		}

		Desc.VertexCount	= IndexMap.size();
		Desc.PrimitiveCount	= Indices.size() / 3;
		Desc.IndexType		= index < 65536 ? EIT_16BIT : EIT_32BIT;
		Desc.StrideInByte	= vertex_stride;

		if (Desc.IndexType == EIT_16BIT)
		{
			for (unsigned int i = 0 ; i < Indices.size() ; ++ i)
			{
				unsigned short si	= (unsigned short)Indices[i];
				IndexStream.Put(&si, sizeof(unsigned short));
			}
		}
		else
		{
			for (unsigned int i = 0 ; i < Indices.size() ; ++ i)
			{
				unsigned int ii		= (unsigned int)Indices[i];
				IndexStream.Put(&ii, sizeof(unsigned int));
			}
		}

		// fill up 4 bytes align
		int fill_bit	= (IndexStream.GetLength() + 3) & (~3);
		fill_bit		-= IndexStream.GetLength();
		int zero		= 0;
		IndexStream.Put(&zero, fill_bit);
	}

	void CldGeometry::ReadPosition(FbxMesh* mesh , int ctrlPointIndex , vector3df* pVertex, aabbox3df* bbox, bool init_bbox)  
	{
		FbxVector4* pCtrlPoint = mesh->GetControlPoints();

		const FbxVector4& vec = pCtrlPoint[ctrlPointIndex];
		pVertex->X = (float)vec[0];
		pVertex->Y = (float)vec[1];
		pVertex->Z = (float)vec[2];

		if (init_bbox)
		{
			bbox->reset(*pVertex);
		}
		else
		{
			bbox->addInternalPoint(*pVertex);
		}
	}

	void CldGeometry::ReadColor(FbxMesh* mesh , int ctrlPointIndex , int vertexCounter , SColorf* pColor)  
	{
		if(mesh->GetElementVertexColorCount() < 1)  
		{
			return;
		}

		FbxGeometryElementVertexColor* pVertexColor = mesh->GetElementVertexColor(0);
		switch(pVertexColor->GetMappingMode())  
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(pVertexColor->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pColor->R = (float)pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mRed;
						pColor->G = (float)pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mGreen;
						pColor->B = (float)pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mBlue;
						pColor->A = (float)pVertexColor->GetDirectArray().GetAt(ctrlPointIndex).mAlpha;
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexColor->GetIndexArray().GetAt(ctrlPointIndex);
						pColor->R = (float)pVertexColor->GetDirectArray().GetAt(id).mRed;
						pColor->G = (float)pVertexColor->GetDirectArray().GetAt(id).mGreen;
						pColor->B = (float)pVertexColor->GetDirectArray().GetAt(id).mBlue;
						pColor->A = (float)pVertexColor->GetDirectArray().GetAt(id).mAlpha;
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch (pVertexColor->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pColor->R = (float)pVertexColor->GetDirectArray().GetAt(vertexCounter).mRed;
						pColor->G = (float)pVertexColor->GetDirectArray().GetAt(vertexCounter).mGreen;
						pColor->B = (float)pVertexColor->GetDirectArray().GetAt(vertexCounter).mBlue;
						pColor->A = (float)pVertexColor->GetDirectArray().GetAt(vertexCounter).mAlpha;
					}
					break;
				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexColor->GetIndexArray().GetAt(vertexCounter);
						pColor->R = (float)pVertexColor->GetDirectArray().GetAt(id).mRed;
						pColor->G = (float)pVertexColor->GetDirectArray().GetAt(id).mGreen;
						pColor->B = (float)pVertexColor->GetDirectArray().GetAt(id).mBlue;
						pColor->A = (float)pVertexColor->GetDirectArray().GetAt(id).mAlpha;
					}
					break;
				default:
					break;
				}
			}
			break;
		}
	}

	bool CldGeometry::ReadUV(FbxMesh* mesh , int ctrlPointIndex , int textureUVIndex , int uvLayer , vector2df* pUV)  
	{
		if(uvLayer >= 2 || mesh->GetElementUVCount() <= uvLayer)  
		{
			return false;
		}

		FbxGeometryElementUV* pVertexUV = mesh->GetElementUV(uvLayer);

		switch(pVertexUV->GetMappingMode())  
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(pVertexUV->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pUV->X = (float)pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[0];
						pUV->Y = (float)pVertexUV->GetDirectArray().GetAt(ctrlPointIndex)[1];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = pVertexUV->GetIndexArray().GetAt(ctrlPointIndex);
						pUV->X = (float)pVertexUV->GetDirectArray().GetAt(id)[0];
						pUV->Y = (float)pVertexUV->GetDirectArray().GetAt(id)[1];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch (pVertexUV->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
				case FbxGeometryElement::eIndexToDirect:
					{
						pUV->X = (float)pVertexUV->GetDirectArray().GetAt(textureUVIndex)[0];
						pUV->Y = (float)pVertexUV->GetDirectArray().GetAt(textureUVIndex)[1];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
		return true;
	} 

	void CldGeometry::ReadNormal(FbxMesh* mesh , int ctrlPointIndex , int vertexCounter , vector3df* pNormal)  
	{
		if(mesh->GetElementNormalCount() < 1)  
		{
			return;
		}

		FbxGeometryElementNormal* leNormal = mesh->GetElementNormal(0);
		switch(leNormal->GetMappingMode())  
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(leNormal->GetReferenceMode())
				{
				case FbxGeometryElement::eDirect:
					{
						pNormal->X = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[0];
						pNormal->Y = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[1];
						pNormal->Z = (float)leNormal->GetDirectArray().GetAt(ctrlPointIndex)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leNormal->GetIndexArray().GetAt(ctrlPointIndex);
						pNormal->X = (float)leNormal->GetDirectArray().GetAt(id)[0];
						pNormal->Y = (float)leNormal->GetDirectArray().GetAt(id)[1];
						pNormal->Z = (float)leNormal->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch(leNormal->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pNormal->X = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[0];
						pNormal->Y = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[1];
						pNormal->Z = (float)leNormal->GetDirectArray().GetAt(vertexCounter)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leNormal->GetIndexArray().GetAt(vertexCounter);
						pNormal->X = (float)leNormal->GetDirectArray().GetAt(id)[0];
						pNormal->Y = (float)leNormal->GetDirectArray().GetAt(id)[1];
						pNormal->Z = (float)leNormal->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
	}

	void CldGeometry::ReadTangent(FbxMesh* mesh , int ctrlPointIndex , int vertecCounter , vector3df* pTangent)  
	{
		if(mesh->GetElementTangentCount() < 1)  
		{
			return;
		}

		FbxGeometryElementTangent* leTangent = mesh->GetElementTangent(0);

		switch(leTangent->GetMappingMode())  
		{
		case FbxGeometryElement::eByControlPoint:
			{
				switch(leTangent->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pTangent->X = (float)leTangent->GetDirectArray().GetAt(ctrlPointIndex)[0];
						pTangent->Y = (float)leTangent->GetDirectArray().GetAt(ctrlPointIndex)[1];
						pTangent->Z = (float)leTangent->GetDirectArray().GetAt(ctrlPointIndex)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leTangent->GetIndexArray().GetAt(ctrlPointIndex);
						pTangent->X = (float)leTangent->GetDirectArray().GetAt(id)[0];
						pTangent->Y = (float)leTangent->GetDirectArray().GetAt(id)[1];
						pTangent->Z = (float)leTangent->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;

		case FbxGeometryElement::eByPolygonVertex:
			{
				switch(leTangent->GetReferenceMode())  
				{
				case FbxGeometryElement::eDirect:
					{
						pTangent->X = (float)leTangent->GetDirectArray().GetAt(vertecCounter)[0];
						pTangent->Y = (float)leTangent->GetDirectArray().GetAt(vertecCounter)[1];
						pTangent->Z = (float)leTangent->GetDirectArray().GetAt(vertecCounter)[2];
					}
					break;

				case FbxGeometryElement::eIndexToDirect:
					{
						int id = leTangent->GetIndexArray().GetAt(vertecCounter);
						pTangent->X = (float)leTangent->GetDirectArray().GetAt(id)[0];
						pTangent->Y = (float)leTangent->GetDirectArray().GetAt(id)[1];
						pTangent->Z = (float)leTangent->GetDirectArray().GetAt(id)[2];
					}
					break;

				default:
					break;
				}
			}
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	CldLibGeometry::CldLibGeometry()
	{
	}

	CldLibGeometry::~CldLibGeometry()
	{
		// remove all geometries
		for (unsigned int i = 0 ; i < Geometries.size() ; ++ i)
		{
			delete Geometries[i];
		}
		Geometries.clear();
	}

	bool CldLibGeometry::ConvertFromFbx(FbxNode* node)
	{
		// gather all mesh nodes from fbx
		ti_vector<FbxNode*> nodes;
		GetFbxNodesByType(node, FbxNodeAttribute::eMesh, nodes);

		// remove all geometries
		for (unsigned int i = 0 ; i < Geometries.size() ; ++ i)
		{
			delete Geometries[i];
		}
		Geometries.clear();

		// load all meshes
		for (u32 i = 0 ; i < nodes.size() ; ++ i)
		{
			FbxNode* fbx_node = nodes[i];
			FbxMesh* fbx_mesh = fbx_node->GetMesh();
			CldGeometry* geometry = new CldGeometry;
			geometry->Id = fbx_node->GetNameOnly().Buffer();
			geometry->Id += "-mesh";

			geometry->GetVertexFormat(fbx_mesh);
			geometry->GetGeometryData(fbx_mesh);

			Geometries.push_back(geometry);
		}

		Loaded	= true;
		return true;
	}

	bool CldLibGeometry::Save(ti_vector<ti_string>& string_list)
	{
		OutputStream.Reset();

		TiResfileChunkHeader header;
		header.ID			= TIRES_ID_CHUNK_GEOMETRY;
		header.Version		= TIRES_VERSION_CHUNK_GEOM;
		header.ElementCount	= Geometries.size();
		header.ChunkSize	= sizeof(TiResfileChunkHeader);

		// calc trunk size total
		for ( int i = 0 ; i < header.ElementCount ; ++ i)
		{
			CldGeometry* g		= Geometries[i];
			header.ChunkSize	+= sizeof(GeometryDesc);
			header.ChunkSize	+= g->VertexStream.GetLength();
			header.ChunkSize	+= g->IndexStream.GetLength();
		}

		OutputStream.Put(&header, sizeof(TiResfileChunkHeader));
		// put geodesc data
		for ( int i = 0 ; i < header.ElementCount ; ++ i)
		{
			CldGeometry* g		= Geometries[i];
			g->Desc.StrIndex_Id	= AddStringToList(g->Id, string_list);
			OutputStream.Put(&g->Desc, sizeof(GeometryDesc));
		}
		// put vertex and index data
		for ( int i = 0 ; i < header.ElementCount ; ++ i)
		{
			CldGeometry* g		= Geometries[i];
			OutputStream.Put(g->VertexStream.GetBuffer(), g->VertexStream.GetLength());
			OutputStream.Put(g->IndexStream.GetBuffer(), g->IndexStream.GetLength());
		}

		return true;
	}

	CldGeometry* CldLibGeometry::GetGeometryById(const char* geometry_id)
	{
		for (u32 i = 0 ; i < Geometries.size() ; ++ i)
		{
			if (Geometries[i]->Id == geometry_id)
			{
				return Geometries[i];
			}
		}

		return NULL;
	}

	void CldLibGeometry::RemoveGeometryById(const char* geometry_id)
	{
		ti_vector< CldGeometry* >::iterator it;
		for (it = Geometries.begin() ; it != Geometries.end() ; ++ it)
		{
			if ((*it)->Id == geometry_id)
			{
				ti_delete (*it);
				Geometries.erase(it);

				break;
			}
		}
	}
};