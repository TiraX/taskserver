
#pragma once

class FbxAsset
{
public:
	FbxAsset(const std::string& filename);
	~FbxAsset();

	static bool	InitSDK();
	static void	DestroySDK();

	bool Load();
	FbxNode* GetRoot();
private:
	void ProcessNode(FbxNode* pNode);

private:
	std::string	_filename;

	FbxImporter* _importer;
	FbxScene* _scene;
};