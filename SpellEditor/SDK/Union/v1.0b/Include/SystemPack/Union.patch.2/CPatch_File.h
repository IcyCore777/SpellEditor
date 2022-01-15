#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *




 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


namespace UnionFilters
{
	extern const Common::CString sDefaultSpace;

	extern const Common::CString sResource_Local;
	extern const Common::CString sResource_Option;
	extern const Common::CString sResource_Number;
	extern const Common::CString sResource_Operator;

	extern const Common::CString sNumber_Integer;
	extern const Common::CString sNumber_PureHex;
	extern const Common::CString sNumber_Float;
	extern const Common::CString sNumber_LineHex;

	extern const Common::CString sBrackets_Round		 [2];
	extern const Common::CString sBrackets_Square		 [2];
	extern const Common::CString sBrackets_TextLine		 [2];
	extern const Common::CString sBrackets_HexLine		 [2];
	extern const Common::CString sBrackets_Comment		 [2];

	extern const Common::CString sAssociation_Quote		 [2];
	extern const Common::CString sAssociation_EndLine	 [2];
	extern const Common::CString sAssociation_Tabulation [2];

	const uint32  ulResourceNum		= 4;
	const uint32  ulNumberNum		= 4;
	const uint32  ulBracketsNum		= 5;
	const uint32  ulAssociationNum	= 3;

	extern const Common::CString  arrResource	 [ulResourceNum];	   
	extern const Common::CString  arrNumber		 [ulNumberNum];   
	extern const Common::CString* arrBrackets	 [ulBracketsNum];	   
	extern const Common::CString* arrAssociation [ulAssociationNum];
}

namespace SystemPack
{
	const uint32  ulOperatorNum	= 22;

	extern const Common::CString sEngineBlock	[2];
	extern const Common::CString sPatchBlock	[2];
	extern const Common::CString sOperators		[ulOperatorNum];
}

#include "CPatch_Page.h"
#include "CPatch_Symbol.h"
#include "CPatch_Function.h"
#include "CPatch_Stack.h"
#include "CPatch_Region.h"

namespace SystemPack
{
	

	class CPatch_File
	{
		Common::CString	  sFileName;
		Common::CDocument sFileData;
	protected:
		CPatch_File( const Common::CString& fileName );
	public:
		static CPatch_File*	LoadFile( const Common::CString& fileName );
		CPatch_Region*	CreateEngineBlock (const uint32& hash);

		void CloseFile();
	};

}