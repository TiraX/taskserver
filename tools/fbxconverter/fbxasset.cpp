
#include "stdafx.h"
#include "fbxasset.h"

static FbxManager* s_sdkManager = NULL;

bool FbxAsset::InitSDK() {
	// Initialize the SDK manager. This object handles memory management.
	s_sdkManager = FbxManager::Create();

	// Create the IO settings object.
	FbxIOSettings *ios = FbxIOSettings::Create(s_sdkManager, IOSROOT);
	s_sdkManager->SetIOSettings(ios);

	return true;
}

void FbxAsset::DestroySDK() {
	if (s_sdkManager) {
		s_sdkManager->Destroy();
	}
}

FbxAsset::FbxAsset(const std::string& filename) 
	: _filename(filename)
	, _importer(NULL)
	, _scene(NULL)
{
}

FbxAsset::~FbxAsset() {
}

bool FbxAsset::Load() {
	// Create an importer using the SDK manager.
	_importer = FbxImporter::Create(s_sdkManager, "");

	// Use the first argument as the filename for the importer.
	if (!_importer->Initialize(_filename.c_str(), -1, s_sdkManager->GetIOSettings())) {
		printf("Call to FbxImporter::Initialize() failed.\n");
		printf("Error returned: %s\n\n", _importer->GetStatus().GetErrorString());
		return false;
	}

	// Create a new scene so that it can be populated by the imported file.
	_scene = FbxScene::Create(s_sdkManager, "myScene");

	// Import the contents of the file into the scene.
	_importer->Import(_scene);

	//ProcessNode(_scene->GetRootNode());

	// The file is imported, so get rid of the importer.
	_importer->Destroy();

	return true;
}

FbxNode* FbxAsset::GetRoot() {
	if (_scene)
	{
		return _scene->GetRootNode();
	}
	return NULL;
}

void FbxAsset::ProcessNode(FbxNode* pNode) {

	printf("node name : [%s]", pNode->GetName());

	if(pNode->GetNodeAttribute()) 
	{
		printf(" - node type [%d].\n", pNode->GetNodeAttribute()->GetAttributeType());
		switch(pNode->GetNodeAttribute()->GetAttributeType()) 
		{ 
		case FbxNodeAttribute::eMesh: 
			//ProcessMesh(pNode); 
			break; 
		case FbxNodeAttribute::eSkeleton: 
			//ProcessSkeleton(pNode); 
			break; 
		case FbxNodeAttribute::eLight: 
			//ProcessLight(pNode); 
			break; 
		case FbxNodeAttribute::eCamera: 
			//ProcessCamera(); 
			break; 
		} 
	}
	else {
		printf("\n");
	}

	for(int i = 0 ; i < pNode->GetChildCount() ; ++i) 
	{ 
		ProcessNode(pNode->GetChild(i)); 
	} 
}
