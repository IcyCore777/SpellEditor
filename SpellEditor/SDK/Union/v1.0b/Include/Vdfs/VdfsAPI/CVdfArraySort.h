#pragma once

typedef void (CVdf::*TArrayCallFunction) ();

class CVdfArraySort : CArray <CVdf*>
{
public:

	VDFAPI void Sort			();
	VDFAPI void Optimize		();
	VDFAPI void CallFunctions	(TArrayCallFunction);
};