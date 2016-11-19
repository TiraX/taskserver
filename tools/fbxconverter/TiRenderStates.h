/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.18
*/

#ifndef _TI_RENDERSTATES_H_
#define _TI_RENDERSTATES_H_

namespace ti
{

	enum E_RENDER_STATES_OPTION	//This is the enable/disable options
	{
		ERS0_START		= 1,

		ERSO_FILLMODE	= 1 << 0,
		ERSO_CULL		= 1 << 1,
		ERSO_DEPTH		= 1 << 2,
		ERSO_DEPTH_TEST	= 1 << 3,
		//ERSO_STENCIL	= 1 << 4,
		ERSO_STENCIL_TEST= 1<< 5,
		ERSO_BLEND		= 1 << 6,
		ERSO_FOG		= 1 << 7,
		ERSO_SCISSOR	= 1 << 8,
		ERSO_ALPHA_TEST	= 1 << 9,
		ERSO_IGNORE_DEPTH_BUFFER = 1 << 10,	// for metal, some shaders do not need depth buffer
	};

	//////////////////////////////////////////////////////////////////////////
	// Rasterizer definition
	
	enum E_FILL_MODE
	{
		EFM_WIREFRAME	= 0,
		EFM_SOLID		= 1,
	};

	enum E_FRONT_FACE
	{
		EFF_CW, 
		EFF_CCW
	};

	enum E_CULL_MODE
	{
		ECM_FRONT		= 0,
		ECM_BACK		= 1
	};

	enum E_FOG_MODE
	{
		EFM_FASTEST	= 0,
		EFM_NICEST	= 1,
		EFM_DONT_CARE = 2,
	};

	enum E_BLEND_FUNC
	{
		EBF_ZERO, 
		EBF_ONE, 
		EBF_SRC_COLOR, 
		EBF_ONE_MINUS_SRC_COLOR, 
		EBF_DEST_COLOR, 
		EBF_ONE_MINUS_DEST_COLOR,
		EBF_SRC_ALPHA, 
		EBF_ONE_MINUS_SRC_ALPHA, 
		EBF_DST_ALPHA, 
		EBF_ONE_MINUS_DST_ALPHA, 
		EBF_CONSTANT_COLOR,
		EBF_ONE_MINUS_CONSTANT_COLOR, 
		EBF_CONSTANT_ALPHA, 
		EBF_ONE_MINUS_CONSTANT_ALPHA, 
		EBF_SRC_ALPHA_SATURATE
	};

	enum E_BLEND_EQUATION
	{
		EBE_FUNC_ADD, 
		EBE_FUNC_SUBTRACT, 
		EBE_FUNC_REVERSE_SUBTRACT, 
		EBE_MIN, 
		EBE_MAX
	};

	//////////////////////////////////////////////////////////////////////////
	// Depth and Stencil definition
	enum E_COMPARISON_FUNC
	{
		ECF_NEVER		= 1,
		ECF_LESS		= 2,
		ECF_LESS_EQUAL	= 3,
		ECF_EQUAL		= 4,
		ECF_GREATER		= 5,
		ECF_NOT_EQUAL	= 6,
		ECF_GREATER_EQUAL= 7,
		ECF_ALWAYS		= 8
	};

	enum E_STENCIL_OP
	{
		ESO_KEEP		= 1,
		ESO_ZERO		= 2,
		ESO_REPLACE		= 3,
		ESO_INCR_SAT	= 4,
		ESO_DECR_SAT	= 5,
		ESO_INVERT		= 6,
		ESO_INCR		= 7,
		ESO_DECR		= 8
	};

	struct RenderStatesValue
	{
		u8	CullMode;	//front face default to CCW
		u8	FogMode;
		u8	BlendSrc;
		u8	BlendDest;
		union
		{
			u32	ColorMaski;
			u8	ColorMask[4];
		};
		u8	StencilOp[3];
		u8	DepthTestFunc;
		u8	StencilFunc;
		u8	AlphaTestFunc;
		u8	StencilRef;
		u8	_pad;	//for 4 bytes align

		RenderStatesValue& operator = (const RenderStatesValue& otherRSV)
		{
			CullMode		= otherRSV.CullMode;
			FogMode			= otherRSV.FogMode;
			BlendDest		= otherRSV.BlendDest;
			BlendSrc		= otherRSV.BlendSrc;
			DepthTestFunc	= otherRSV.DepthTestFunc;
			StencilFunc		= otherRSV.StencilFunc;
			ColorMaski		= otherRSV.ColorMaski;
			StencilOp[0]	= otherRSV.StencilOp[0];
			StencilOp[1]	= otherRSV.StencilOp[1];
			StencilOp[2]	= otherRSV.StencilOp[2];
			StencilRef		= otherRSV.StencilRef;
			AlphaTestFunc	= otherRSV.AlphaTestFunc;
			_pad			= otherRSV._pad;
			return *this;
		}

		bool operator == (const RenderStatesValue& otherRSV) const
		{
			return memcmp(this, &otherRSV, sizeof(RenderStatesValue)) == 0;
		}
	};

	class TI_API TiRenderState
	{
	public:
		TiRenderState();
		~TiRenderState();

		TiRenderState& operator = (const TiRenderState& otherRS)
		{
			RSOptions		= otherRS.RSOptions;
			RSValues		= otherRS.RSValues;
			return *this;
		}

		bool operator == (const TiRenderState& otherRS) const
		{
			return (RSOptions == otherRS.RSOptions) &&
				   (RSValues == otherRS.RSValues);
		}

		void SetRenderState(E_RENDER_STATES_OPTION op, bool enable)
		{
			if (enable)
			{
				RSOptions |= op;
			}
			else
			{
				RSOptions &= ~op;
			}
		}

		bool GetRenderState(E_RENDER_STATES_OPTION op) const
		{
			return (RSOptions & op) != 0;
		}

		void SetCullMode(E_CULL_MODE mode)
		{
			RSValues.CullMode = mode;
		}

		void SetFogMode(E_FOG_MODE mode)
		{
			RSValues.FogMode = mode;
		}

		void SetBlendSrc(E_BLEND_FUNC func)
		{
			RSValues.BlendSrc = func;
		}

		void SetBlendDest(E_BLEND_FUNC func)
		{
			RSValues.BlendDest		= func;
		}

		void SetDepthTestFunc(E_COMPARISON_FUNC func)
		{
			RSValues.DepthTestFunc	= func;
		}

		void SetStencilFunc(E_COMPARISON_FUNC func)
		{
			RSValues.StencilFunc	= func;
		}

		void SetStencilRef(int s_ref)
		{
			RSValues.StencilRef		= s_ref;
		}

		void SetStencilOp(E_STENCIL_OP sfail, E_STENCIL_OP dpfail, E_STENCIL_OP dppass)
		{
			RSValues.StencilOp[0]	= sfail;
			RSValues.StencilOp[1]	= dpfail;
			RSValues.StencilOp[2]	= dppass;
		}

		void SetColorMask(u8 r, u8 g, u8 b, u8 a)
		{
			RSValues.ColorMask[0]	= r;
			RSValues.ColorMask[1]	= g;
			RSValues.ColorMask[2]	= b;
			RSValues.ColorMask[3]	= a;
		}

		u8	GetColorMask(int index) const
		{
			return	RSValues.ColorMask[index];
		}

		u32	GetColorMaski() const
		{
			return	RSValues.ColorMaski;
		}

		u8	GetFillMode() const
		{
			return (RSOptions & ERSO_FILLMODE);
		}

		u8	GetDepthTestFunc() const
		{
			return RSValues.DepthTestFunc;
		}

		u8	GetStencilFunc() const
		{
			return RSValues.StencilFunc;
		}

		u8	GetStencilRef() const
		{
			return RSValues.StencilRef;
		}

		u8	GetCullMode() const
		{
			return RSValues.CullMode;
		}

		u8	GetBlendSrc() const
		{
			return RSValues.BlendSrc;
		}

		u8	GetBlendDst() const
		{
			return RSValues.BlendDest;
		}

		u8	GetStencilOp(int index) const
		{
			return RSValues.StencilOp[index];
		}

		u8	GetAlphaTestFunc() const
		{
			return RSValues.AlphaTestFunc;
		}

		bool IsDepthWriteEnable() const
		{
			return (RSOptions & ERSO_DEPTH) != 0;
		}

		bool IsDepthTestEnable() const
		{
			return (RSOptions & ERSO_DEPTH_TEST) != 0;
		}
        
        bool IsIgnoreDepthBuffer() const
        {
            return (RSOptions & ERSO_IGNORE_DEPTH_BUFFER) != 0;
        }

		bool IsCullEnable() const
		{
			return (RSOptions & ERSO_CULL) != 0;
		}
        
        bool IsBlendEnable() const
        {
            return (RSOptions & ERSO_BLEND) != 0;
        }

	protected:
		UINT	RSOptions;
		RenderStatesValue	RSValues;
	};

}
#endif //_TI_RENDERSTATES_H_