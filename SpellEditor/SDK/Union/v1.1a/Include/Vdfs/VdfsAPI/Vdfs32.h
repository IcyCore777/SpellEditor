#pragma once

#include "CVdf.h"
#include "CHashTable.h"

class Vdfs32
{
	Vdfs32 ();

	static Vdfs32* vdfs;

protected:
	CVdfArraySort	VdfList;
	CHashTable		HashTable_Virtual;
	CHashTable		HashTable_Physical;

private:
	void	InitializeVirtualHash	(CString);
	void	InitializePhysicalHash	(CString);

	VDFAPI CFileBase* GetFileVirtual	(CString&);
	VDFAPI CFileBase* GetFilePhysical	(CString&);

public:
	void	InitSystem	();
	void	ExitSystem	();

	VDFAPI			CHashTable&		GetHashTable_Virtual	();
	VDFAPI			CHashTable&		GetHashTable_Physical	();
	VDFAPI			CFileBase*		GetFile					(CString, CString, const int32&);
	VDFAPI static	Vdfs32&			GetVirtualSpace			();

	~Vdfs32 ();
};