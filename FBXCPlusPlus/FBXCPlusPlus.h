#pragma once
#include <fbxsdk.h>
// Function prototypes.
bool CreateScene(FbxScene* pScene, char* pSampleFileName);
FbxNode* CreateCubeWithTexture(FbxScene* pScene, const char* pName);
void CreateTexture(FbxScene* pScene, FbxMesh* pMesh);
void CreateMaterials(FbxScene* pScene, FbxMesh* pMesh);
void SetCubeDefaultPosition(FbxNode* pCube);