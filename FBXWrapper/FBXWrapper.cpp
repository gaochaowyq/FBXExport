#pragma once
#include "stdafx.h"
#include "Exporter.cpp"
#include "FBXWrapper.h"

FBXWrapper::FBXWrapperClass::FBXWrapperClass(int a, int b)
{
	eC = new Exporter(a, b);
}

int FBXWrapper::FBXWrapperClass::GetSum()
{
	return eC->GetSum();
}
