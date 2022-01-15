#pragma once

namespace SystemPack
{
	class ASTAPI CPatchRegion
	{
		friend class CPatchFile;
		friend class CPatchSymbol;
		static CString	  sCurrentPatch;
		static uint32	  ulIterator;
		static uint32	  ulEngineOffset;
		static CDocument* pCurrentRegionData;

	protected:
		
		uint32	  ulOffset;
		CDocument sRegionData;

	public:

		static CString		 GetLastInfo ();
		static CPatchRegion* DefineBlock (CDocument& fileData, const uint32& hash);
		void   ExecuteRegion ();
		uint32 ExecuteOnLine (uint32& iterator);

		~CPatchRegion();
	};
}