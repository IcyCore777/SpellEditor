#pragma once

namespace SystemPack
{
	class CPatch_Page
	{
		static Common::CArray<CPatch_Page*> arrPages;

		uint32 ulIndex;
		uint32 ulSize;
		uint32 ulAddress;

		 CPatch_Page ();
		~CPatch_Page ();
	public:

		static CPatch_Page*	GetPage  (const uint32& index);
		static CPatch_Page*	Allocate (const uint32& index, const uint32& size);
		static void			Free	 (const uint32& index);
		

		uint32 GetIndex	  ();
		uint32 GetSize	  ();
		uint32 GetAddress ();
	};
}