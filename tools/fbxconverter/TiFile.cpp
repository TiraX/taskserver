/*
	Copyright (C) 2012
	By Zhao Shuai tirax.cn@gmail.com 2012.7.18
*/

#include "stdafx.h"

#include "TiFile.h"

namespace ti
{
	const char* k_file_access[] =
	{
		"rb",
		"ab",
		"wb",
		"rwb",
	};

	TiFile::TiFile()
		: File(NULL)
		, Size(0)
	{
	}

	TiFile::~TiFile()
	{
		Close();
	}

//#include "direct.h"

	bool TiFile::Open(const ti_string& filename, E_FILE_ACCESS access)
	{

		//char curr_path[256];
		//_getcwd(curr_path, 256);

		Close();
		Filename = filename;

		File	= fopen(filename.c_str(), k_file_access[access]);

		if (File)
		{
			fseek(File, 0, SEEK_END);
			Size = ftell(File);
			fseek(File, 0, SEEK_SET);
			return true;
		}
		return false;
	}

	void TiFile::Close()
	{
		if (File)
		{
			fclose(File);
			File = NULL;
		}
	}

	int TiFile::Read(void* buffer, int buffer_size, int read_size) const
	{
		if (!File)
			return 0;
		if (read_size > buffer_size)
			read_size = buffer_size;
		return fread(buffer, 1, read_size, File);
	}

	int TiFile::Write(const void* buffer, int size)
	{
		if (!File)
			return 0;
		return fwrite(buffer, 1, size, File);
	}

	void TiFile::Seek(int offset, bool relative /* = false */)
	{
		fseek(File, offset, relative ? SEEK_CUR : SEEK_SET);
	}

	int TiFile::Tell() const
	{
		return ftell(File);
	}

	bool TiFile::IsEnd() const
	{
		int pos = ftell(File);
		return pos >= Size;
	}

	int TiFile::BytesLeft() const
	{
		int pos = ftell(File);
		return Size - pos;
	}
	
	char* TiFile::GetMemoryPointer(int size)
	{
		TI_ASSERT(0);	// not supported in TiFile, only in TiFileBuffer;
		return NULL;
	}

	//////////////////////////////////////////////////////////////////////////

	TiFileBuffer::TiFileBuffer(bool delete_buffer)
		: FileBuffer(NULL)
		, ReadPos(0)
		, DeleteBuffer(delete_buffer)
	{
	}

	TiFileBuffer::~TiFileBuffer()
	{
		if (DeleteBuffer)
		{
			ti_delete[] FileBuffer;
		}
	}

	bool TiFileBuffer::Open(const ti_string& filename, char* file_buffer, int size)
	{
		Filename	= filename;
		Size		= size;
		FileBuffer	= file_buffer;
		ReadPos		= 0;
		return true;
	}

	int TiFileBuffer::Read(void* buffer, int buffer_size, int read_size) const
	{
		TI_ASSERT(FileBuffer);
		if (read_size > buffer_size)
			read_size	= buffer_size;

		memcpy(buffer, FileBuffer + ReadPos, read_size);
		ReadPos			+= read_size;
		return read_size;
	}

	char* TiFileBuffer::GetMemoryPointer(int read_size)
	{
		TI_ASSERT(Size - ReadPos >= read_size);
		char* result	= FileBuffer + ReadPos;
		ReadPos			+= read_size;
		return result;
	}

	void TiFileBuffer::Seek(int offset, bool relative /* = false */)
	{
		if (relative)
			ReadPos		+= offset;
		else
			ReadPos		= offset;
	}

	int TiFileBuffer::Tell() const
	{
		return ReadPos;
	}

	bool TiFileBuffer::IsEnd() const
	{
		return ReadPos >= Size;
	}

	int TiFileBuffer::BytesLeft() const
	{
		return Size - ReadPos;
	}
}
