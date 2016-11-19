// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <math.h>

#include <fbxsdk.h>

#define ti_string	std::string
#define ti_wstring	std::wstring
#define ti_vector	std::vector
#define ti_map		std::map

typedef unsigned char		u8;
typedef char				c8;
typedef unsigned short		u16;
typedef short				s16;
typedef unsigned int		UINT;
typedef unsigned int		u32;
typedef int					s32;
typedef unsigned long long	u64;
typedef float				f32;
typedef double				f64;

void ___Log(const char* format, ...);
#ifdef _DEBUG
#	define TI_ASSERT(x) if (!(x)) { _asm int 3 }
#else
#	define TI_ASSERT(cond)	if (!(cond)) {___Log("Assert: %s, line %d, %s.\n", __FILE__, __LINE__, #cond);}
#endif

#define SAFE_DELETE(x) if (x) { delete x; x = NULL; }

//#include "collada/CldTags.h"
//#include "collada/CldElement.h"

// include math file from tix/trunk/include

#define F32_AS_S32(f)		(*((s32 *) &(f)))
#define F32_AS_U32(f)		(*((u32 *) &(f)))
#define F32_AS_U32_POINTER(f)	( ((u32 *) &(f)))

#define F32_VALUE_0		0x00000000
#define F32_VALUE_1		0x3f800000
#define F32_SIGN_BIT		0x80000000U
#define F32_EXPON_MANTISSA	0x7FFFFFFFU

//! code is taken from IceFPU
//! Integer representation of a floating-point value.
#define IR(x)				((u32&)(x))

//! Absolute integer representation of a floating-point value
#define AIR(x)				(IR(x)&0x7fffffff)

//! Floating-point representation of an integer value.
#define FR(x)				((f32&)(x))

//! integer representation of 1.0
#define IEEE_1_0			0x3f800000
//! integer representation of 255.0
#define IEEE_255_0			0x437f0000

#define	F32_LOWER_0(f)		(F32_AS_U32(f) >  F32_SIGN_BIT)
#define	F32_LOWER_EQUAL_0(f)	(F32_AS_S32(f) <= F32_VALUE_0)
#define	F32_GREATER_0(f)	(F32_AS_S32(f) >  F32_VALUE_0)
#define	F32_GREATER_EQUAL_0(f)	(F32_AS_U32(f) <= F32_SIGN_BIT)
#define	F32_EQUAL_1(f)		(F32_AS_U32(f) == F32_VALUE_1)
#define	F32_EQUAL_0(f)		( (F32_AS_U32(f) & F32_EXPON_MANTISSA ) == F32_VALUE_0)

// only same sign
#define	F32_A_GREATER_B(a,b)	(F32_AS_S32((a)) > F32_AS_S32((b)))


const f32 ROUNDING_ERROR_32 = 0.00005f;
const f64 ROUNDING_ERROR_64 = 0.000005;

#ifdef PI // make sure we don't collide with a define
#undef PI
#endif
//! Constant for PI.
const f32 PI		= 3.14159265359f;

//! Constant for reciprocal of PI.
const f32 RECIPROCAL_PI	= 1.0f/PI;

//! Constant for half of PI.
const f32 HALF_PI	= PI/2.0f;

#ifdef PI64 // make sure we don't collide with a define
#undef PI64
#endif
//! Constant for 64bit PI.
const f64 PI64		= 3.1415926535897932384626433832795028841971693993751;

//! Constant for 64bit reciprocal of PI.
const f64 RECIPROCAL_PI64 = 1.0/PI64;

//! 32bit Constant for converting from degrees to radians
const f32 DEGTORAD = PI / 180.0f;

//! 32bit constant for converting from radians to degrees (formally known as GRAD_PI)
const f32 RADTODEG   = 180.0f / PI;

//! 64bit constant for converting from degrees to radians (formally known as GRAD_PI2)
const f64 DEGTORAD64 = PI64 / 180.0;

//! 64bit constant for converting from radians to degrees
const f64 RADTODEG64 = 180.0 / PI64;

#define	RAD_TO_DEG(x)					((x)*RADTODEG)
#define	DEG_TO_RAD(x)					((x)*DEGTORAD)

#define TI_INTERPOLATE(src, dest, t)	((dest - src) * (t) + src)

#define TI_INTERPOLATE(src, dest, t)	((dest - src) * (t) + src)
#define ti_max(a, b) ((a) > (b) ? (a) : (b))
#define ti_min(a, b) ((a) < (b) ? (a) : (b))

inline int CountBitNum(unsigned int value)
{
	int num = 0;
	while(value)
	{
		value &= (value - 1);
		++ num;
	}
	return num;
}


//! returns if a equals b, taking possible rounding errors into account
inline bool equals(const float a, const float b, const float tolerance = ROUNDING_ERROR_32)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

//! returns if a equals zero, taking rounding errors into account
inline bool iszero(const f32 a, const f32 tolerance = ROUNDING_ERROR_32)
{
	return equals(a, 0.0f, tolerance);
}

//! returns if a equals zero, taking rounding errors into account
inline bool iszero(const int a, const int tolerance = 0)
{
	return ( a & 0x7ffffff ) <= tolerance;
}

inline float reciprocal_squareroot(const f32 x)
{
	// comes from Nvidia
	unsigned int tmp = ((unsigned int)(IEEE_1_0 << 1) + IEEE_1_0 - *(u32*)&x) >> 1;
	float y = *(float*)&tmp;
	return y * (1.47f - 0.47f * x * y * y);
}

#define _LOG	___Log

#include "math/Vector2d.h"
#include "math/Vector3d.h"
#include "math/Line2d.h"
#include "math/Rect.h"
#include "math/Line3d.h"
#include "math/Aabbox3d.h"
#include "math/Plane3d.h"
#include "math/Matrix4.h"
#include "math/Quaternion.h"

#include "TiDefines.h"
#include "SColor.h"
#include "TiNodeType.h"
#include "TiMeshType.h"
#include "TiRenderStates.h"
#include "TiResfileDef.h"
#include "TiShaderProgram.h"

//#include <png.h>

#include "TiStream.h"
#include "TiFile.h"
#include "EPixelFormat.h"

int		AddStringToList(const ti_string& s, ti_vector<ti_string>& string_list);
void	SaveStringList(const ti_vector<ti_string>& string_list, ti::TiStream& stream);
void	GetFbxNodesByType(FbxNode* root, int type, ti_vector<FbxNode*>& nodes);

using namespace ti;

// TODO: reference additional headers your program requires here
