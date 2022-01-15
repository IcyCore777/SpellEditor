#include <UnionAfx.h>




namespace SystemPack
{
	Common::CArray<CPatch_Page*> CPatch_Page::arrPages;

	CPatch_Page::CPatch_Page ()
	{
		arrPages.Insert( this );
	}

	CPatch_Page* CPatch_Page::GetPage (const uint32& index)
	{
		for (uint32 i = 0; i < arrPages.GetNum(); i++)
		{
			if( arrPages[i]->ulIndex == index )
			{
				return arrPages[i];
			}
		}
		return Null;
	}

	CPatch_Page* CPatch_Page::Allocate (const uint32& index, const uint32& size)
	{
		uint32 ulAddress = (uint32)VirtualAlloc( Null, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE );
		if( !ulAddress )
		{
			ASSERT_PATCH_ERROR( "Ќевозможно получить страницу пам€ти index[" + Common::CString(index, 16) + "] size[" + Common::CString(size, 16) + "]" );
		}
		CPatch_Page* pPage = new CPatch_Page;
		pPage->ulAddress = ulAddress;
		pPage->ulIndex	 = index;
		pPage->ulSize	 = size;

		return pPage;
	}

	void CPatch_Page::Free (const uint32& index)
	{
		for (uint32 i = 0; i < arrPages.GetNum(); i++)
		{
			if( arrPages[i]->ulIndex == index )
			{
				delete arrPages[i];
			}
		}
	}

	uint32 CPatch_Page::GetIndex ()
	{
		return ulIndex;
	}

	uint32 CPatch_Page::GetSize ()
	{
		return ulSize;
	}

	uint32 CPatch_Page::GetAddress ()
	{
		return ulAddress;
	}


	CPatch_Page::~CPatch_Page ()
	{
		VirtualFree( (void32)ulAddress, 0, MEM_RELEASE );
		arrPages.Remove( this );
	}
}