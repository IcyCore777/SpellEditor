#include <UnionAfx.h>






namespace UnionFilters
{
	const Common::CString sDefaultSpace					= " \t\n\r";

	const Common::CString sResource_Local				= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
	const Common::CString sResource_Option				= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890:";
	const Common::CString sResource_Number				= "1234567890";
	const Common::CString sResource_Operator			= "+-*/=@<>!,";

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
}

namespace SystemPack
{
	const Common::CString sEngineBlock	[2]  = { "#engine",	"#/engine" };
	const Common::CString sPatchBlock	[2]  = { "#patch",	"#/patch"  };
	const Common::CString sOperators	[ulOperatorNum] =
	{
		"=", "+", "-", "*", "/", "^", "+=", "-=", "*=", "/=", "^=", "!", "==", "!=", "<", "<=", ">", ">=", "@", "NULL", "TRUE", "FALSE"
	};
}






inline int32 inlStringToInt (Common::CString str)
{
	if( str.MatchesMask( UnionFilters::arrNumber[0] ))
		return str.ToInt32(10);

	if( str.MatchesMask( UnionFilters::arrNumber[1] ))
		return str.ToInt32(16);

	return Invalid;
}

inline real32 inlStringToFloat (Common::CString str)
{
	if( str.MatchesMask( UnionFilters::arrNumber[2] ))
		return str.ToReal32();

	return -1.0f;
}




namespace SystemPack
{
	CPatch_Region* CPatch_Region::DefineBlock (Common::CDocument& fileData, const uint32& hash)
	{
		REPORT( ".\tExtracting patch data for current engine version..." );

		if( !fileData.GetNum() )
		{
			return Null;
		}
		CPatch_Region* block = Null;
		CLine* line = &fileData[0];
		while( line )
		{
			Common::CString& lineData = line->GetData();

			if( lineData.GetWord(UnionFilters::sDefaultSpace) == sEngineBlock[0] )
			{
				Common::CString sHash = lineData.GetWord(UnionFilters::sDefaultSpace, 2).GetPattern( UnionFilters::sBrackets_Square[0], UnionFilters::sBrackets_Square[1] ).Shrink();
				if( !sHash.IsEmpty() && inlStringToInt(sHash) == hash )
				{
					REPORT( ".\tBlock " + sHash + " found. Building information..." );

					block = new CPatch_Region;
					while( line )
					{
						block->sRegionData.InsertLines( line->GetData() );
						if( line->GetData().GetWord(UnionFilters::sDefaultSpace) == sEngineBlock[1] )
						{
							REPORT_SUCCESS( ".\tBuilding is done." );

							return block;
						}
						line = line->GetNext();
					}
					ASSERT_PATCH_ERROR( "Не найден конец блока '#engine " + sHash + "'" );
				}
				else
				{
					REPORT_WARN( ".\tFound other engine block " + sHash );

					while( line )
					{
						if( line->GetData().GetWord(UnionFilters::sDefaultSpace) == sEngineBlock[1] )
						{
							break;
						}
						line = line->GetNext();
					}
				}
			}
			line = line->GetNext();
		}
		REPORT_ERROR( ".\tBlock " + Common::CString::Hex32(hash) + " not found :(" ) << endl;

		return Null;
	}


	
}








namespace SystemPack
{
	CPatch_File::CPatch_File (const Common::CString& fileName)
	{
		REPORT( "Loading file '" + fileName + "'" );

		sFileName = fileName;
		Common::CString sData;
		sData.ReadFromFile( fileName );
		if( sData.IsEmpty() )
		{
			REPORT_ERROR( ".\tFile is empty!" );
			return;
		}

		REPORT( ".\tData parsing..." );

		uint32	ulIndex  = 0;
		Common::CString	sComment = NullStr;
		do
		{
			static const uint32 ulComLeftLen  = UnionFilters::sBrackets_Comment[0].Length();
			static const uint32 ulComRightLen = UnionFilters::sBrackets_Comment[1].Length();

			sComment = sData.GetPatternEx( UnionFilters::sBrackets_Comment[0], UnionFilters::sBrackets_Comment[1], 1, ulIndex, &ulIndex );
			if( ulIndex == Invalid )
			{
				break;
			}
			sData.Cut( ulIndex -= ulComLeftLen, sComment.Length() + ulComLeftLen + ulComRightLen );
		}
		while( !sComment.IsEmpty() );
		
		sFileData = sData;
		for (uint32 i = 0; i < sFileData.GetNum(); i++)
		{
			if( sFileData[i].GetData().HasWord( "//" ))
			{
				sFileData[i].GetData() = sFileData[i].GetData().GetPattern( "", "//" );
			}
		}
		REPORT_SUCCESS( ".\tLoading is done." );
	}

	CPatch_File* CPatch_File::LoadFile (const Common::CString& fileName)
	{
		return new CPatch_File( fileName );
	}

	CPatch_Region* CPatch_File::CreateEngineBlock (const uint32& hash)
	{
		if( !sFileData.GetNum() )
		{
			return Null;
		}
		return CPatch_Region::DefineBlock( sFileData, hash );
	}

}