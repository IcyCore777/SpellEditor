#pragma once

//#include "..\..\UnionAssert.h"
#include "Filters\Filters.h"
#include "MemPage\CMemPage.h"
#include "Symbol\CPatchSymbol.h"
#include "Stack\CPatchStack.h"
#include "Region\CPatchRegion.h"

namespace SystemPack
{
	class ASTAPI CPatchFile
	{
		CString	  sFileName;
		CDocument sFileData;
	protected:
		CPatchFile( const CString& fileName );
	public:
		static CPatchFile* LoadFile( const CString& fileName );
		CPatchRegion* CreateEngineBlock (const uint32& hash);

		void CloseFile();
	};

}






namespace SystemPack
{
	class ASTAPI CPatch
	{
		static CArray<CPatch*> arrPatches;
		CString sName;
	public:
		CPatch(const CString& name);
		void Execute();
		static void ExecuteAll();
		static bool32 HasPatch(const char* name);
	};
}