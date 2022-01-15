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
		Common::CString	  sFileName;
		Common::CDocument sFileData;
	protected:
		CPatchFile( const Common::CString& fileName );
	public:
		static CPatchFile* LoadFile( const Common::CString& fileName );
		CPatchRegion* CreateEngineBlock (const uint32& hash);

		void CloseFile();
	};

}






namespace SystemPack
{
	class ASTAPI CPatch
	{
		static Common::CArray<CPatch*> arrPatches;
		Common::CString sName;
	public:
		CPatch(const Common::CString& name);
		void Execute();
		static void ExecuteAll();
		static bool32 HasPatch(const char* name);
	};
}