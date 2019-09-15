#pragma once
#include <vector>
#include <fbxsdk.h>
using std::vector;

class Exporter
{
public:
	Exporter(int a, int b);
	int GetSum();

private:
	int A;
	int B;
};


class FBXExporter
{
public:
	FBXExporter();

	FBXExporter( char* pFile);

	bool CreateScene(FbxScene* pScene, char* pSampleFileName);

	FbxNode* CreateCubeWithTexture(FbxScene* pScene, const char* pName);
	FbxNode* CreateTriangle(FbxScene* pScene, const char* pName);

	void CreateTexture(FbxScene* pScene, FbxMesh* pMesh);
	void CreateMaterials(FbxScene* pScene, FbxMesh* pMesh);

	void SetCubeDefaultPosition(FbxNode* pCube);

	bool Run();

	~FBXExporter()
	{

	}
private:

	char* lSampleFileName;


	int* vertices [];
};




class FBXVertic
{
};

class FBXMaterial
{
public:
	FBXMaterial();

	~FBXMaterial() {};
private:

};

