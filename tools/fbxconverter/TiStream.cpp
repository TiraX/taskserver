/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.16
*/

#include "stdafx.h"

#include <stdarg.h>
#include "TiStream.h"

namespace ti
{
	TiStream::TiStream(int buf_size)
		: BufferSize(buf_size)
		, Pos(0)
	{
		Buffer = ti_new char[BufferSize];
	}

	TiStream::TiStream(void* buf, int buf_size)
		: Pos(buf_size)
	{
		BufferSize	= (buf_size + 3) & (~3);
		Buffer		= ti_new char[BufferSize];

		memcpy(Buffer, buf, buf_size);
	}

	TiStream::~TiStream()
	{
		ti_delete[] Buffer;
	}

	void TiStream::Put(const void* buf, int size)
	{
		if (size == 0)
			return;

		if (Pos + size > BufferSize)
		{
			ReallocBuffer(Pos + size);
		}

		memcpy(Buffer + Pos, buf, size);
		Pos				+= size;
	}

	void TiStream::ReallocBuffer(int size)
	{
		if (size < BufferSize * 2)
		{
			size = BufferSize * 2;
		}
		else
		{
			size = (size + 4) & (~3);
		}
		char* newBuffer	= ti_new char[size];
		memcpy(newBuffer, Buffer, Pos);

		char* oldBuffer = Buffer;
		Buffer			= newBuffer;
		ti_delete[] oldBuffer;

		BufferSize		= size;
	}

	void TiStream::Reset()
	{
		Pos				= 0;
	}
}