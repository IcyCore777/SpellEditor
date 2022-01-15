#pragma once

namespace SystemPack
{
	
	class CPatch_Region
	{
		Common::CString sCurrentPatch;

	protected:
		uint32	  ulOffset;
		Common::CDocument sRegionData;

	public:

		static CPatch_Region* DefineBlock (Common::CDocument& fileData, const uint32& hash);
		void   ExecuteRegion ();
		uint32 ExecuteOnLine (uint32 line);

		~CPatch_Region();
	};


}