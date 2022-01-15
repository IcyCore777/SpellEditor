#pragma once

namespace SystemPack
{
	class ASTAPI CPatchRegion
	{
		friend class CPatchFile;
		friend class CPatchSymbol;
		static Common::CString	  sCurrentPatch;
		static uint32	  ulIterator;
		static uint32	  ulEngineOffset;
		static Common::CDocument* pCurrentRegionData;

	protected:
		
		uint32	  ulOffset;
		Common::CDocument sRegionData;

	public:

		static Common::CString		 GetLastInfo ();
		static CPatchRegion* DefineBlock (Common::CDocument& fileData, const uint32& hash);
		void   ExecuteRegion ();
		uint32 ExecuteOnLine (uint32& iterator);

		~CPatchRegion();
	};
}