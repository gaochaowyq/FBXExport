#pragma once
#include "Exporter.h"

Exporter::Exporter(int a, int b)
{
	A = a;
	B = b;
}

int Exporter::GetSum()
{
	return A+B;
}

