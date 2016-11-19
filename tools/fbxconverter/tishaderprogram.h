/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.18
*/

#ifndef _TI_SHADERPROGRAM_H_
#define _TI_SHADERPROGRAM_H_

#include "TiRenderStates.h"

namespace ti
{

	enum E_SHADER_TYPE
	{
		ESHDT_SM11,
		ESHDT_SM20,
		ESHDT_SM30,
		ESHDT_SM40,
		ESHDT_CG,
		ESHDT_GLSL,
		ESHDT_FIXED,
        ESHDT_METAL,
	};
	enum E_UNIFORM_TYPE
	{
		EUF_VEC4,
		EUF_VEC3,
		EUF_VEC2,
		EUF_MAT4,
		EUF_FLOAT,
		EUF_INT,
		EUF_SAMPLER2D,
		EUF_SAMPLERCUBE,
		EUF_INT4,
		EUF_MAT2,
	};

	struct TiShaderParameterVector
	{
		union
		{
			int		IntValue;
			float	FloatValue;
			float	FloatVec2[2];
			float	FloatVec3[3];
			float	FloatVec4[4];
			float*	FloatPointer;
			int*	IntPointer;
		};
		int			ElementCount;

		TiShaderParameterVector()
			: ElementCount(0)
		{
			memset(FloatVec4, 0, sizeof(float) * 4);
		}

		bool operator == (const TiShaderParameterVector& other) const
		{
			return memcmp(FloatVec4, other.FloatVec4, sizeof(float) * 4) == 0;
		}

		bool operator != (const TiShaderParameterVector& other) const
		{
			return memcmp(FloatVec4, other.FloatVec4, sizeof(float) * 4) != 0;
		}

		bool operator < (const TiShaderParameterVector& other) const
		{
			return memcmp(FloatVec4, other.FloatVec4, sizeof(float) * 4) < 0;
		}
	};
	struct TiShaderParameterMatrix
	{
		float	FloatMatrix[16];
		TiShaderParameterMatrix()
		{
			memset(FloatMatrix, 0, sizeof(float) * 16);
		}

		bool operator == (const TiShaderParameterMatrix& other) const
		{
			return memcmp(FloatMatrix, other.FloatMatrix, sizeof(float) * 16) == 0;
		}

		bool operator != (const TiShaderParameterMatrix& other) const
		{
			return memcmp(FloatMatrix, other.FloatMatrix, sizeof(float) * 16) != 0;
		}

		bool operator < (const TiShaderParameterMatrix& other) const
		{
			return memcmp(FloatMatrix, other.FloatMatrix, sizeof(float) * 16) < 0;
		}
	};
	struct TiShaderParameterTexture
	{
		int TextureSlot;	// ?
	};

	class TiRenderer;

	class TiShaderProgram
	{
	public:
		TiShaderProgram(E_SHADER_TYPE type);
		virtual ~TiShaderProgram();
        
        enum {
            UNIFORM_WVP         = 1 << 0,
            UNIFORM_WORLD       = 1 << 1,
            UNIFORM_WORLDIT     = 1 << 2,
            UNIFORM_LWVP        = 1 << 3,
            UNIFORM_WV          = 1 << 4,
        };
		enum 
		{
			LIGHT_TYPE,
			LIGHT_POS,
			LIGHT_DIR,
			LIGHT_COLOR,
			LIGHT_PARAM,

			LP_COUNT,
		};
        int GetType()
        {
            return Type;
        }
        
		virtual void	LoadShaderProgram(  const ti_string& vertex_shader, 
											const ti_string& fragment_shader,
                                            const TiRenderState& rs, int option);

		int				GetUniformLocation(const ti_string& name);

		virtual void	SetParameter(const ti_string& name, int param) = 0;
		virtual void	SetParameter(const ti_string& name, float param) = 0;
		virtual void	SetParameter(const ti_string& name, const float* param, int elementCount) = 0;

		virtual void	SetParameter(int location, int param) = 0;
		virtual void	SetParameter(int location, float param) = 0;
		virtual void	SetParameter(int location, const float* param, int elementCount) = 0;

		virtual void	ApplyCommonParameter(TiRenderer* renderer) = 0;

		int				GetUniformCount()
		{
			return		(int)Uniforms.size();
		}
        bool            HasShaderFlag(u32 flag)
        {
            return      (Flag & flag) != 0;
        }
		struct Uniform
		{
			ti_string	Name;
			int			Type;
			int			IsCommonParameter;
		};
		TI_API void		GetUniformNames(ti_vector<ti_string>& names);
		TI_API Uniform	GetUniform(const ti_string& name);
		TI_API bool		IsUniformExist(const ti_string& name);
		TI_API bool		IsUniformExist(int location);

		struct	UniformInfo
		{
			int	Size;
			u32	Type;
			int	Location;
			int	IsCommonParameter;
		};
		const ti_string&	GetVsh()
		{
			return Vsh;
		}
		const ti_string&	GetFsh()
		{
			return Fsh;
		}
		bool				IsCompiled()
		{
			return Compiled;
		}
		int					GetLightBindingInfo(int index)
		{
			return LightParamBindings[index];
		}
        void                SetDestFramebufferFormat(int format)
        {
            DestFramebuffer = format;
        }
	protected:

	protected:
		E_SHADER_TYPE		Type;
        u32                 Flag;

        ti_string			Vsh, Fsh;
        TiRenderState       RenderState;
		bool				Compiled;

		typedef ti_map< ti_string, int > MapUniformNames;
		MapUniformNames		UniformNames;

		typedef ti_map< int, UniformInfo >	MapUniforms;
		MapUniforms         Uniforms;

		int					LightParamBindings[LP_COUNT];
        int                 DestFramebuffer;
	};
}


#endif //_TI_SHADERPROGRAM_H_