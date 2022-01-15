#pragma once

namespace SystemPack
{
	class ASTAPI CMemPage
	{
		static Common::CArray<CMemPage*> arrPages;

		uint32 ulIndex;
		uint32 ulSize;
		uint32 ulAddress;

		 CMemPage ();
		~CMemPage ();
	public:

		static CMemPage* GetPage  (const uint32& index);
		static CMemPage* Allocate (const uint32& index, const uint32& size);
		static void		 Free	  (const uint32& index);
		

		uint32 GetIndex	  ();
		uint32 GetSize	  ();
		uint32 GetAddress ();
	};
}