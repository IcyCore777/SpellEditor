#include "stdafx.h"


//Moving interface
extern "C" __declspec(dllexport) zCVob* PickSingle()
{
	return NULL;
};

extern "C" __declspec(dllexport) zVEC2 PickCursor()
{
	return zVEC2(0, 0);
};