#include <UnionAfx.h>

namespace SystemPack
{
	const Common::CString sDefaultSpace					= " \t\n\r";

	const Common::CString sResource_Local				= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
	const Common::CString sResource_Option				= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890:";
	const Common::CString sResource_Number				= "1234567890.-";
	const Common::CString sResource_Operator			= "+-*/=@<>!,^&|";

	const Common::CString sNumber_Integer				= "1234567890-";
	const Common::CString sNumber_PureHex				= "1234567890xabcdefXABCDEF";
	const Common::CString sNumber_Float					= "1234567890.-";
	const Common::CString sNumber_LineHex				= "1234567890abcdefABCDEF ";

	const Common::CString sBrackets_Round			[2]	= { "(",	")"	 };
	const Common::CString sBrackets_Square			[2]	= { "[",	"]"	 };
	const Common::CString sBrackets_TextLine		[2]	= { "\"",	"\"" };
	const Common::CString sBrackets_HexLine			[2]	= { "'",	"'"	 };
	const Common::CString sBrackets_Comment			[2]	= { "/*",	"*/" };

	const Common::CString sAssociation_Quote		[2] = { "\\\"",	"\"" };
	const Common::CString sAssociation_EndLine		[2] = { "\\n",	"\n" };
	const Common::CString sAssociation_Tabulation	[2] = { "\\t",	"\t" };


	const Common::CString arrResource [ulResourceNum] =
	{
		sResource_Local,
		sResource_Option,
		sResource_Number,
		sResource_Operator
	};

	const Common::CString arrNumber [ulNumberNum] =
	{
		sNumber_Integer,
		sNumber_PureHex,
		sNumber_Float,
		sNumber_LineHex
	};

	const Common::CString* arrBrackets [ulBracketsNum] =
	{
		sBrackets_Round,
		sBrackets_Square,
		sBrackets_TextLine,
		sBrackets_HexLine,
		sBrackets_Comment
	};

	const Common::CString* arrAssociation [ulAssociationNum] =
	{
		sAssociation_Quote,
		sAssociation_EndLine,
		sAssociation_Tabulation
	};

	const Common::CString sEngineBlock	[2]  = { "#engine",	"#/engine" };
	const Common::CString sPatchBlock	[2]  = { "#patch",	"#/patch"  };
	const Common::CString sOperators	[ulOperatorNum] =
	{
	//	0	 1	  2	   3    4	 5	  6		7	  8		9	  10	11	 12	   13	 14	  15	16	 17	   18	19	  20
		"=", "+", "-", "*", "/", "^", "+=", "-=", "*=", "/=", "^=", "!", "==", "!=", "<", "<=", ">", ">=", "@", "&&", "||"
	};
}