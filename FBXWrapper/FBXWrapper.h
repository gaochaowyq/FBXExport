#pragma once
#include "Exporter.h"
using namespace System;

namespace FBXWrapper {
	public ref class FBXWrapperClass
	{
	public:
		FBXWrapperClass(int a,int b);
		int GetSum();
	private:
		Exporter* eC;
	};
}
