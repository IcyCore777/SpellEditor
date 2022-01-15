#include <UnionAfx.h>



using namespace UnionFilters;

namespace SystemPack
{
	inline bool32 inlIsNumber (const Common::CString& line)
	{
		bool32 bMatches = line.MatchesMask( sNumber_Float );
		if( bMatches )
		{
			return True;
		}
		bMatches = line.MatchesMask( sNumber_PureHex ) && Common::CString(line[0]).MatchesMask( sNumber_Integer );
		if( bMatches )
		{
			return True;
		}
		return False;
	}

	void CPatch_Region::ExecuteRegion ()
	{
		for (uint32 i = 0; i < sRegionData.GetNum(); i++)
		{
			Common::CString& sLine = sRegionData[i];
			

			if( sLine.GetWord( UnionFilters::sDefaultSpace ) == sPatchBlock[0])
			{
				Common::CString sPatchName = sLine.GetSymbolEx( Null, 0, &UnionFilters::arrBrackets[1], 1);
				Common::CString sName	   = sPatchName.IsEmpty() ? "[Unnamed]" : sPatchName.Shrink();

				REPORT( ".\tExecuting " + sName + " patch..." );
				sCurrentPatch = sName;

				i = ExecuteOnLine( i+1 );
			}
		}
	}

	uint32 CPatch_Region::ExecuteOnLine (uint32 line)
	{
		Common::CArray<CPatch_Symbol*> arrSymbols;

		for (uint32 i = line; i < sRegionData.GetNum(); i++)
		{
			Common::CString& sLineData = sRegionData[i];
			if( sLineData.Shrink() == sPatchBlock[1] )
			{
				line = i;
				break;
			}
			if( sLineData.IsEmpty() )
			{
				continue;
			}
			REPORT( ".\t\t" + sRegionData[i] );


			Common::CString sKeyWord = sLineData.GetSymbolEx( arrResource, 4, arrBrackets, 4, 1 );

			TTypeDescriptor* pType = TTypeDescriptor::GetByName( sKeyWord );

			if( pType )
			{
				bool32 bIsLink = False;
				Common::CString sKeyType = sLineData.GetSymbolEx( arrResource, 4, arrBrackets, 4, 2 );
					
				if( sKeyType == sOperators[18] )
				{
					Common::CString sKeyName = sLineData.GetSymbolEx( arrResource, 4, arrBrackets, 4, 3 );
					if( !inlIsNumber(sKeyName) )
					{
						Common::CString sValue = sLineData.GetPattern( sOperators[0], "" );
						if( sValue.IsEmpty() )
						{
							ASSERT_PATCH_ERROR( "Ссылка должна быть определена" );
						}
						CPatch_Stack*  pStack  = CPatch_Stack::CreateStack( sValue );
						CPatch_Symbol* pSymbol = pStack->Execute();

						CPatch_Integer* pAddress = dynamic_cast<CPatch_Integer*>( pSymbol );
						if( !pAddress )
						{
							ASSERT_PATCH_ERROR( "Определение ссылки должно иметь целочисленный тип" );
						}
						CPatch_Symbol* pLink = CPatch_Symbol::CreateSymbol( sKeyWord );
						pLink->SetObjectName( sKeyName );
						pLink->SetPointer( pAddress->GetValue() );
						arrSymbols.Insert( pLink );
						if( sCurrentPatch == "[GLOBAL DATA]" )
						{
							pLink->AddRef();
						}
						pStack->Destroy();
					}
				}
				else
				{
					Common::CString& sKeyName = sKeyType;
					if( !inlIsNumber( sKeyName ))
					{
						CPatch_Symbol* pVar = CPatch_Symbol::CreateSymbol( sKeyWord );
						pVar->SetObjectName( sKeyName );
						arrSymbols.Insert( pVar );
						if( sCurrentPatch == "[GLOBAL DATA]" )
						{
							pVar->AddRef();
						}
						Common::CString sValue = sLineData.GetPattern( sOperators[0], "" );
						if( !sValue.IsEmpty() )
						{
							CPatch_Stack*  pStack  = CPatch_Stack::CreateStack( sValue );
							CPatch_Symbol* pSymbol = pStack->Execute();
							(*pVar) = pSymbol;
							pStack->Destroy();
						}
					}
				}
				continue;
			}


			static bool32 bConditions = 0;
			if( sKeyWord == "IF" )
			{
				bConditions++;

				Common::CString sCond = sLineData.GetPattern( sKeyWord, "" );
				CPatch_Stack*  pStack  = CPatch_Stack::CreateStack( sCond );
				CPatch_Symbol* pSymbol = pStack->Execute();
				CPatch_Integer pInt; pInt = pSymbol;
				pStack->Destroy();

				bool32 bCond = pInt.GetValue();
				if( bCond )
				{
					i = ExecuteOnLine( i + 1 );
					bConditions--;
					continue;
				}
				else
				{
					for (i += 1; i < sRegionData.GetNum(); i++)
					{
						Common::CString& sPostWord = sRegionData[i].GetData().GetWord( sDefaultSpace );
						if( sPostWord == "ELSE" )
						{
							i = ExecuteOnLine( i + 1 );
							break;
						}
						if( sPostWord == "END" )
						{
							break;
						}
					}
					bConditions--;
					continue;
				}
			}

			if( sKeyWord == "END" )
			{
				if( bConditions == 0 )
				{
					ASSERT_PATCH_ERROR( "Обнаружен 'END' не имеющий предшествующего оператора 'IF'" );
				}
				line = i;
				break;
			}
			if( sKeyWord == "ELSE" )
			{
				if( bConditions == 0 )
				{
					ASSERT_PATCH_ERROR( "Обнаружен 'ELSE' не имеющий предшествующего оператора 'IF'" );
				}
				for (i += 1; i < sRegionData.GetNum(); i++)
				{
					if( sRegionData[i].GetData().GetWord( sDefaultSpace ) == "END" )
						break;
				}
				line = i;
				break;
			}

			CPatch_Stack*  pStack  = CPatch_Stack::CreateStack( sLineData );
			CPatch_Symbol* pSymbol = pStack->Execute();
			if( !pSymbol )
			{
				REPORT_WARN( ".\tResult is not symbol in '" + sLineData + "'" );
				continue;
			}
			pStack->Destroy();
		}


		for (uint32 i = 0; i < arrSymbols.GetNum(); i++)
		{
			arrSymbols[i]->Release();
		}
		arrSymbols.Clear();
		return line;
	}

	CPatch_Region::~CPatch_Region()
	{
		
	}
}












