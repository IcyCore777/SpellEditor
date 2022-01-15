#pragma once

#include "CFile.h"

class CVdf
{
protected:
	FILE*		hVdf;
	VDFHEADER	mHeader;
	CString		sName;

public:
	CVdf (const CString&);

	VDFAPI CString	Name	();
	VDFAPI uint32	Size	();
	VDFAPI uint32	Files	();
	VDFAPI uint32	Dirs	();
			void	Init	();

	~CVdf ();
};

#include "CVdfArraySort.h"