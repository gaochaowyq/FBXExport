#ifndef INCLUDE_GEOMETRY_UTILITY_H_
#define INCLUDE_GEOMETRY_UTILITY_H_

#include <fbxsdk.h>
#include<vector>
using std::vector;

FbxNode * CreatePyramid(FbxScene * pScene, const char * pName, double pBottomWidth, double pHeight);

FbxNode* CreateCube(FbxScene* pScene, const char* pName, FbxDouble3& pLclTranslation);



FbxNode* CreateMesh(FbxScene* pScene, const char* pName, vector<FbxVector4> vertices, vector<vector<int>> face);

//void CreateTexture(FbxScene* pScene, FbxMesh* pMesh);

vector<FbxVector4> CreatePoint(int p[], int len);

vector<vector<int>> CreateFace(int f[], int len);

#endif // INCLUDE_GEOMETRY_UTILITY_H_
