/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.18
*/

#ifndef _TI_FILE_H_
#define _TI_FILE_H_

namespace ti
{
	enum E_FILE_ACCESS
	{
		EFA_READ,
		EFA_WRITE,
		EFA_CREATEWRITE,
		EFA_READWRITE,
	};

	class TI_API TiFile
	{
	public:
		TiFile();
		virtual ~TiFile();

		virtual bool Open(const ti_string& filename, E_FILE_ACCESS access);
		virtual void Close();

		virtual int  Read(void* buffer, int buffer_size, int read_size) const;
		virtual int  Write(const void* buffer, int size);
		virtual void Seek(int offset, bool relative = false);

		virtual int  Tell() const;
		virtual bool IsEnd() const;
		virtual int  BytesLeft() const;

		virtual char*	GetMemoryPointer(int size);

		int  GetSize() const
		{
			return Size;
		}
		const ti_string& GetFileName() const
		{
			return Filename;
		}
	protected:
		ti_string	Filename;
		FILE*		File;
		int			Size;
	};

	class TI_API TiFileBuffer : public TiFile
	{
	public:
		TiFileBuffer(bool delete_buffer = true);
		virtual ~TiFileBuffer();

		virtual bool	Open(const ti_string& filename, char* file_buffer, int size);
		virtual int		Read(void* buffer, int buffer_size, int read_size) const;
		virtual void	Seek(int offset, bool relative = false);

		virtual int		Tell() const;
		virtual char*	GetMemoryPointer(int size);

		virtual bool	IsEnd() const;
		virtual int		BytesLeft() const;
	protected:
		char*			FileBuffer;
		bool			DeleteBuffer;
		mutable int		ReadPos;
	};
}

#endif //_TI_FILE_H_