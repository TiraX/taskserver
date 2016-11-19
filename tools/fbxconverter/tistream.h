/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.17
*/

#ifndef _TI_STREAM_H_
#define _TI_STREAM_H_

namespace ti
{
	class TI_API TiStream
	{
	public:
		TiStream(int buf_size = 1024);
		TiStream(void* buf, int buf_size);
		virtual ~TiStream();

		void Put(const void* buf, int size);
		void Reset();

				char* GetBuffer()
				{
					return Buffer;
				}

				int GetLength()
				{
					return Pos;
				}

	protected:
		void	ReallocBuffer(int size);

	protected:
		char*	Buffer;
		int		Pos;
		int		BufferSize;
	};
}

#endif //_TI_STREAM_H_