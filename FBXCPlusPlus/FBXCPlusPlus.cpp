// FBXCPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include"FBXCPlusPlus.h"
#include "Exporter.h"
#include "GeometryUtility.h"
#include "Common.h"
#include <iostream>

#define SAMPLE_FILENAME_MC		"ExportScene03_MC.fbx"

// Declare the UV names globally so we can create them on the mesh and then assign them properly
// to our textures when we create them
static const char* gDiffuseElementName = "DiffuseUV";
static const char* gAmbientElementName = "AmbientUV";
static const char* gEmissiveElementName = "EmissiveUV";

int main(int argc, char** argv)
{
	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;
	char* lSampleFileName = (char *)SAMPLE_FILENAME_MC;
	bool lResult;

	// Prepare the FBX SDK.
	InitializeSdkObjects(lSdkManager, lScene);



	// Create the scene.
	lResult = CreateScene(lScene, lSampleFileName);

	if (lResult == false)
	{
		FBXSDK_printf("\n\nAn error occurred while creating the scene...\n");
		DestroySdkObjects(lSdkManager, lResult);
		return 0;
	}

	// Save the scene.
	lResult = SaveScene(lSdkManager, lScene, lSampleFileName);

	if (lResult == false)
	{
		FBXSDK_printf("\n\nAn error occurred while saving the scene...\n");
		DestroySdkObjects(lSdkManager, lResult);
		return 0;
	}

	// Destroy all objects created by the FBX SDK.
	DestroySdkObjects(lSdkManager, lResult);

	return 0;
}

bool CreateScene(FbxScene* pScene, char* pSampleFileName)
{
	FbxNode* lCube = CreateCubeWithTexture(pScene, "Cube");
	int* v;

	int vv[] = 
			{
				50, 0, -50,
				50, 0, 50,
				-50, 0, 50,
				-50, 0, -50
			};

	v = &vv[0];
	
	int f[] = {0,3,1,3,2,1};

	
	vector<FbxVector4> vertices = CreatePoint(v,12);

	vector<vector<int>> face = CreateFace(f,6);
	
	
	FbxNode* lMesh = CreateMesh(pScene, "MyMesh", vertices, face);



	SetCubeDefaultPosition(lCube);

	SetCubeDefaultPosition(lMesh);


	// Build the node tree.
	FbxNode* lRootNode = pScene->GetRootNode();
	lRootNode->AddChild(lCube);

	lRootNode->AddChild(lMesh);

	//Create a simple animated fcurve

	FbxGlobalSettings& lGlobalSettings = pScene->GetGlobalSettings();

	return true;
}

// Create a cube with a texture. 
FbxNode* CreateCubeWithTexture(FbxScene* pScene, const char* pName)
{
	int i, j;
	FbxMesh* lMesh = FbxMesh::Create(pScene, pName);

	FbxVector4 lControlPoint0(-50, 0, 50);
	FbxVector4 lControlPoint1(50, 0, 50);
	FbxVector4 lControlPoint2(50, 100, 50);
	FbxVector4 lControlPoint3(-50, 100, 50);
	FbxVector4 lControlPoint4(-50, 0, -50);
	FbxVector4 lControlPoint5(50, 0, -50);
	FbxVector4 lControlPoint6(50, 100, -50);
	FbxVector4 lControlPoint7(-50, 100, -50);

	FbxVector4 lNormalXPos(1, 0, 0);
	FbxVector4 lNormalXNeg(-1, 0, 0);
	FbxVector4 lNormalYPos(0, 1, 0);
	FbxVector4 lNormalYNeg(0, -1, 0);
	FbxVector4 lNormalZPos(0, 0, 1);
	FbxVector4 lNormalZNeg(0, 0, -1);

	// Create control points.
	lMesh->InitControlPoints(24);
	FbxVector4* lControlPoints = lMesh->GetControlPoints();

	lControlPoints[0] = lControlPoint0;
	lControlPoints[1] = lControlPoint1;
	lControlPoints[2] = lControlPoint2;
	lControlPoints[3] = lControlPoint3;
	lControlPoints[4] = lControlPoint1;
	lControlPoints[5] = lControlPoint5;
	lControlPoints[6] = lControlPoint6;
	lControlPoints[7] = lControlPoint2;
	lControlPoints[8] = lControlPoint5;
	lControlPoints[9] = lControlPoint4;
	lControlPoints[10] = lControlPoint7;
	lControlPoints[11] = lControlPoint6;
	lControlPoints[12] = lControlPoint4;
	lControlPoints[13] = lControlPoint0;
	lControlPoints[14] = lControlPoint3;
	lControlPoints[15] = lControlPoint7;
	lControlPoints[16] = lControlPoint3;
	lControlPoints[17] = lControlPoint2;
	lControlPoints[18] = lControlPoint6;
	lControlPoints[19] = lControlPoint7;
	lControlPoints[20] = lControlPoint1;
	lControlPoints[21] = lControlPoint0;
	lControlPoints[22] = lControlPoint4;
	lControlPoints[23] = lControlPoint5;


	// We want to have one normal for each vertex (or control point),
	// so we set the mapping mode to eByControlPoint.
	FbxGeometryElementNormal* lGeometryElementNormal = lMesh->CreateElementNormal();

	lGeometryElementNormal->SetMappingMode(FbxGeometryElement::eByControlPoint);

	// Here are two different ways to set the normal values.
	bool firstWayNormalCalculations = true;
	if (firstWayNormalCalculations)
	{
		// The first method is to set the actual normal value
		// for every control point.
		lGeometryElementNormal->SetReferenceMode(FbxGeometryElement::eDirect);

		lGeometryElementNormal->GetDirectArray().Add(lNormalZPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYNeg);
	}
	else
	{
		// The second method is to the possible values of the normals
		// in the direct array, and set the index of that value
		// in the index array for every control point.
		lGeometryElementNormal->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

		// Add the 6 different normals to the direct array
		lGeometryElementNormal->GetDirectArray().Add(lNormalZPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalZNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalXNeg);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYPos);
		lGeometryElementNormal->GetDirectArray().Add(lNormalYNeg);

		// Now for each control point, we need to specify which normal to use
		lGeometryElementNormal->GetIndexArray().Add(0); // index of lNormalZPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(0); // index of lNormalZPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(0); // index of lNormalZPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(0); // index of lNormalZPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(1); // index of lNormalXPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(1); // index of lNormalXPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(1); // index of lNormalXPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(1); // index of lNormalXPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(2); // index of lNormalZNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(2); // index of lNormalZNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(2); // index of lNormalZNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(2); // index of lNormalZNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(3); // index of lNormalXNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(3); // index of lNormalXNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(3); // index of lNormalXNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(3); // index of lNormalXNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(4); // index of lNormalYPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(4); // index of lNormalYPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(4); // index of lNormalYPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(4); // index of lNormalYPos in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(5); // index of lNormalYNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(5); // index of lNormalYNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(5); // index of lNormalYNeg in the direct array.
		lGeometryElementNormal->GetIndexArray().Add(5); // index of lNormalYNeg in the direct array.
	}

	// Array of polygon vertices.
	int lPolygonVertices[] = { 0, 1, 2, 3,
		4, 5, 6, 7,
		8, 9, 10, 11,
		12, 13, 14, 15,
		16, 17, 18, 19,
		20, 21, 22, 23 };

	FbxGeometryElementMaterial* lMaterialElement = lMesh->CreateElementMaterial();
	lMaterialElement->SetMappingMode(FbxGeometryElement::eByPolygon);
	lMaterialElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);


	// Create UV for Diffuse channel
	FbxGeometryElementUV* lUVDiffuseElement = lMesh->CreateElementUV(gDiffuseElementName);
	
	FBX_ASSERT(lUVDiffuseElement != NULL);

	lUVDiffuseElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lUVDiffuseElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

	FbxVector2 lVectors0(0, 0);
	FbxVector2 lVectors1(1, 0);
	FbxVector2 lVectors2(1, 1);
	FbxVector2 lVectors3(0, 1);

	lUVDiffuseElement->GetDirectArray().Add(lVectors0);
	lUVDiffuseElement->GetDirectArray().Add(lVectors1);
	lUVDiffuseElement->GetDirectArray().Add(lVectors2);
	lUVDiffuseElement->GetDirectArray().Add(lVectors3);


	// Create UV for Ambient channel
	FbxGeometryElementUV* lUVAmbientElement = lMesh->CreateElementUV(gAmbientElementName);

	lUVAmbientElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lUVAmbientElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

	lVectors0.Set(0, 0);
	lVectors1.Set(1, 0);
	lVectors2.Set(0, 0.418586879968643);
	lVectors3.Set(1, 0.418586879968643);

	lUVAmbientElement->GetDirectArray().Add(lVectors0);
	lUVAmbientElement->GetDirectArray().Add(lVectors1);
	lUVAmbientElement->GetDirectArray().Add(lVectors2);
	lUVAmbientElement->GetDirectArray().Add(lVectors3);

	// Create UV for Emissive channel
	FbxGeometryElementUV* lUVEmissiveElement = lMesh->CreateElementUV(gEmissiveElementName);

	lUVEmissiveElement->SetMappingMode(FbxGeometryElement::eByPolygonVertex);
	lUVEmissiveElement->SetReferenceMode(FbxGeometryElement::eIndexToDirect);

	lVectors0.Set(0.2343, 0);
	lVectors1.Set(1, 0.555);
	lVectors2.Set(0.333, 0.999);
	lVectors3.Set(0.555, 0.666);

	lUVEmissiveElement->GetDirectArray().Add(lVectors0);
	lUVEmissiveElement->GetDirectArray().Add(lVectors1);
	lUVEmissiveElement->GetDirectArray().Add(lVectors2);
	lUVEmissiveElement->GetDirectArray().Add(lVectors3);

	//Now we have set the UVs as eIndexToDirect reference and in eByPolygonVertex  mapping mode
	//we must update the size of the index array.
	lUVDiffuseElement->GetIndexArray().SetCount(24);
	lUVAmbientElement->GetIndexArray().SetCount(24);
	lUVEmissiveElement->GetIndexArray().SetCount(24);



	// Create polygons. Assign texture and texture UV indices.
	for (i = 0; i < 6; i++)
	{
		//we won't use the default way of assigning textures, as we have
		//textures on more than just the default (diffuse) channel.
		lMesh->BeginPolygon(-1, -1, false);



		for (j = 0; j < 4; j++)
		{
			//this function points 
			lMesh->AddPolygon(lPolygonVertices[i * 4 + j] // Control point index. 
			);
			//Now we have to update the index array of the UVs for diffuse, ambient and emissive
			lUVDiffuseElement->GetIndexArray().SetAt(i * 4 + j, j);
			lUVAmbientElement->GetIndexArray().SetAt(i * 4 + j, j);
			lUVEmissiveElement->GetIndexArray().SetAt(i * 4 + j, j);

		}

		lMesh->EndPolygon();
	}

	FbxNode* lNode = FbxNode::Create(pScene, pName);

	lNode->SetNodeAttribute(lMesh);
	lNode->SetShadingMode(FbxNode::eTextureShading);

	CreateMaterials(pScene, lMesh);

	return lNode;
}


// Create texture for cube.
void CreateTexture(FbxScene* pScene, FbxMesh* pMesh)
{
	// A texture need to be connected to a property on the material,
	// so let's use the material (if it exists) or create a new one
	FbxSurfacePhong* lMaterial = NULL;

	//get the node of mesh, add material for it.
	FbxNode* lNode = pMesh->GetNode();
	if (lNode)
	{
		lMaterial = lNode->GetSrcObject<FbxSurfacePhong>(0);
		if (lMaterial == NULL)
		{
			FbxString lMaterialName = "toto";
			FbxString lShadingName = "Phong";
			FbxDouble3 lBlack(0.0, 0.0, 0.0);
			FbxDouble3 lRed(1.0, 0.0, 0.0);
			FbxDouble3 lDiffuseColor(0.75, 0.75, 0.0);

			FbxLayer* lLayer = pMesh->GetLayer(0);

			// Create a layer element material to handle proper mapping.
			FbxLayerElementMaterial* lLayerElementMaterial = FbxLayerElementMaterial::Create(pMesh, lMaterialName.Buffer());

			// This allows us to control where the materials are mapped.  Using eAllSame
			// means that all faces/polygons of the mesh will be assigned the same material.
			lLayerElementMaterial->SetMappingMode(FbxLayerElement::eAllSame);
			lLayerElementMaterial->SetReferenceMode(FbxLayerElement::eIndexToDirect);

			// Save the material on the layer
			lLayer->SetMaterials(lLayerElementMaterial);

			// Add an index to the lLayerElementMaterial.  Since we have only one, and are using eAllSame mapping mode,
			// we only need to add one.
			lLayerElementMaterial->GetIndexArray().Add(0);

			lMaterial = FbxSurfacePhong::Create(pScene, lMaterialName.Buffer());

			// Generate primary and secondary colors.
			lMaterial->Emissive.Set(lBlack);
			lMaterial->Ambient.Set(lRed);
			lMaterial->AmbientFactor.Set(1.);
			// Add texture for diffuse channel
			lMaterial->Diffuse.Set(lDiffuseColor);
			lMaterial->DiffuseFactor.Set(1.);
			lMaterial->TransparencyFactor.Set(0.4);
			lMaterial->ShadingModel.Set(lShadingName);
			lMaterial->Shininess.Set(0.5);
			lMaterial->Specular.Set(lBlack);
			lMaterial->SpecularFactor.Set(0.3);
			lNode->AddMaterial(lMaterial);
		}
	}


}

// Create materials for pyramid.
void CreateMaterials(FbxScene* pScene, FbxMesh* pMesh)
{

		FbxString lMaterialName = "material";
		FbxString lShadingName = "Phong";
		FbxDouble3 lBlack(0.0, 0.0, 0.0);
		FbxDouble3 lRed(1.0, 0.0, 0.0);
		FbxDouble3 lColor;
		FbxSurfacePhong *lMaterial = FbxSurfacePhong::Create(pScene, lMaterialName.Buffer());


		// Generate primary and secondary colors.
		lMaterial->Emissive.Set(lBlack);
		lMaterial->Ambient.Set(lRed);
		lColor = FbxDouble3(1,1,1);

		lMaterial->Diffuse.Set(lColor);
		lMaterial->TransparencyFactor.Set(0.0);
		lMaterial->ShadingModel.Set(lShadingName);
		lMaterial->Shininess.Set(0.5);

		//get the node of mesh, add material for it.
		FbxNode* lNode = pMesh->GetNode();
		lNode->AddMaterial(lMaterial);
}


// Cube is translated to the left.
void SetCubeDefaultPosition(FbxNode* pCube)
{
	pCube->LclTranslation.Set(FbxVector4(-75.0, -50.0, 0.0));
	pCube->LclRotation.Set(FbxVector4(0.0, 0.0, 0.0));
	pCube->LclScaling.Set(FbxVector4(1.0, 1.0, 1.0));
}