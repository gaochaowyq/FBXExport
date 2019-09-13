#pragma once
#include <fbxsdk.h>
class Exporter
{
public:
	Exporter(int a, int b);
	int GetSum();

private:
	int A;
	int B;
};