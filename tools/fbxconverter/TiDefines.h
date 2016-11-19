/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/


#ifndef _TI_DEFINES_H_
#define _TI_DEFINES_H_

#if defined (DEBUG) || defined (_DEBUG)
#	define TIX_DEBUG
#endif

#if defined(TI_PLATFORM_WIN32)
#   if defined(TIX_DEBUG) && !defined(_XY_EDITOR_)
#       define DEBUG_CLIENTBLOCK	new( _CLIENT_BLOCK, __FILE__, __LINE__)
//#       define new DEBUG_CLIENTBLOCK
#   endif
#endif

#define ti_new new
#define ti_delete delete

#ifndef TI_ASSERT
#	ifdef TIX_DEBUG 
#       if defined (TI_PLATFORM_WIN32)
#           define TI_ASSERT(cond) if (!(cond)) { _asm int 3 }
#       elif defined (TI_PLATFORM_IOS)
#           define TI_ASSERT(cond) assert(cond)
#		elif defined (TI_PLATFORM_ANDROID)
#           define TI_ASSERT(cond)
#       endif
#	else
#		define TI_ASSERT(cond)
#	endif
#endif

#ifndef TI_BREAK
#	define	TI_BREAK	TI_ASSERT(0)
#endif

#ifndef TI_DEBUG
#	ifdef TIX_DEBUG
#		define TI_DEBUG(cond) {int r = cond; TI_ASSERT(r == 0);}
#	else
#		define TI_DEBUG(cond) cond
#	endif
#endif

#ifndef NULL
#	define NULL (0)
#endif

#if defined(TI_PLATFORM_IOS)
//#	ifndef swprintf
//#		define swprintf wprintf
//#	endif
#endif

#define DO_STRINGIZE(x) #x
#define STRINGIZE(x) DO_STRINGIZE(x)
#define TODO_MESSAGE_STRING(msg) __FILE__ "(" STRINGIZE( __LINE__ )") : TODO - " msg " - [ "__FUNCTION__ " ]" 
#if defined TI_PLATFORM_WIN32
#	define TI_TODO(msg) __pragma( message( TODO_MESSAGE_STRING(msg) ) )
#else
#	define TI_TODO
#endif

#ifndef SAFE_DELETE
#	define SAFE_DELETE(x) if(x) { ti_delete x; x = NULL; }
#endif
#ifndef SAFE_DELETE_ARRAY
#	define SAFE_DELETE_ARRAY(x) if(x) { ti_delete[] x; x = NULL; }
#endif


#define TI_INTRUSIVE_PTR(T) boost::intrusive_ptr< T >

#define TI_MAKE_IDENTIFIER(c1, c2, c3, c4) ((c4 << 24) | (c3 << 16) | (c2 << 8) | (c1))

#define TI_CIRCLE_POINTS	(21)

#ifdef TI_PLATFORM_WIN32
#ifdef TI_EXPORTS
#	define TI_API __declspec(dllexport)
#else
#	define TI_API __declspec(dllimport)
#endif
#else
#	define TI_API
#endif


#endif //_TI_DEFINES_H_
