// fbxconverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fbxasset.h"
#include "Collada.h"
#include <stdarg.h>
#include <Windows.h>

void show_usage() {
	printf("Usage : \n");
	printf("  fbxconverter.exe source_file dest_file \n");
	printf("                                             -texture_path=texture_path \n");
	printf("                                             -reserve_texcoord=0 \n");
	printf("    source_file : input file to be converted.\n");
	printf("    dest_file : output file.\n");
	printf("    -texture_path [optional] : use this path to replace the texture path in the DAE file, texturePath with no '/' ending.\n");
	printf("    -extra_texture_path [optional] : replace the texture path of the extra model in Particle file, texturePath with no '/' ending.\n");
}

bool parse_params(int argc, _TCHAR* argv[], std::string& source, std::string& dest) {
	if (argc < 3) {
		return false;
	}

	for (int i = 1; i < argc; ++i) {
		if (source == _T("")) {
			source = argv[i];
		}
		else if (dest == _T("")) {
			dest = argv[i];
		}
		else if (argv[i][0] == '-') {
			// optional parameters
			std::string param = argv[i] + 1;
			size_t pos = param.find('=');
			std::string key, value;

			if (pos != std::string::npos) {
				key = param.substr(0, pos);
				value = param.substr(pos + 1);
			} else {
				key = param;
			}


			if (key == "texture_path") {
				//_config.TexturePath = value;
			}
		}
	}
	return true;
}

void ___Log(const char* format, ...)
{
	char tmp[1024];
	va_list marker;
	va_start(marker, format);
	vsprintf(tmp, format, marker);
	va_end(marker);

	const char* err_str	= strstr(tmp, "Error:");
	const char* ass_str	= strstr(tmp, "Assert:");
	const char* war_str	= strstr(tmp, "Warning:");
	if (err_str || ass_str)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED);
	}
	else if (war_str)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
			FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}

	printf(tmp);
}

int main(int argc, _TCHAR* argv[]) {
	std::string	source_file_name;
	std::string	dest_file_name;

	if (!parse_params(argc, argv, source_file_name, dest_file_name)) {
		show_usage();
		return 0;
	}

	FbxAsset::InitSDK();
	{
		FbxAsset* asset = new FbxAsset(source_file_name);
		asset->Load();

		TiStream filestream;
		TiCollada	colladaFile(source_file_name.c_str());
		colladaFile.Config.InputFilename	= source_file_name;
		colladaFile.Config.OutputFilename	= dest_file_name;

		if ( colladaFile.ConvertFrom(asset) )
		{
			colladaFile.Save(filestream);

			// write to file
			TiFile f;
			if (f.Open(dest_file_name, EFA_CREATEWRITE))
			{
				TiLodHeader lod_header;
				const int lods					= 1;
				lod_header.Lods					= lods;
				TiLodDesc* desc					= ti_new TiLodDesc[lods];
				desc[0].Start					= sizeof(TiLodHeader) + sizeof(TiLodDesc) * lods;
				desc[0].Length					= filestream.GetLength();
				if (lods > 1)
				{
					//desc[1].Start				= desc[0].Start + desc[0].Length;
					//desc[1].Length				= file_stream_lod.GetLength();
				}
				f.Write(&lod_header, sizeof(TiLodHeader));
				f.Write(desc, sizeof(TiLodDesc) * lods);
				f.Write(filestream.GetBuffer(), filestream.GetLength());
				if (lods > 1)
				{
					//f.Write(file_stream_lod.GetBuffer(), file_stream_lod.GetLength());
				}
				ti_delete[] desc;
				f.Close();
			}
		}

		delete asset;
	}
	FbxAsset::DestroySDK();

    return 0;
}

