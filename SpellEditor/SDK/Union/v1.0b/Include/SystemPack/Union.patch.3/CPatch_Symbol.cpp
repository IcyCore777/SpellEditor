#include <UnionAfx.h>






using namespace UnionFilters;

namespace SystemPack
{
	Common::CArray<TPatch_SymDescriptor*> TPatch_SymDescriptor::arrSymDescriptors;

	TPatch_SymDescriptor::TPatch_SymDescriptor(const Common::CString& className, TSymConstructor func)
	{
		sClassName = className;
		pSymConstructor = func;
		arrSymDescriptors.Insert( this );
	}
}











namespace SystemPack
{
	Common::CArray<CPatch_Type*>			CPatch_Type::arrVariables;
	Common::CArray<TOperatorCollection*>	CPatch_Type::arrExternalOperators;
	Common::CArray<TAssociation>			CPatch_Type::arrAssociations;
	
	CPatch_Type* CPatch_Type::CreateSymbol (const Common::CString& symbol)
	{
		// * types
		Common::CArray<TPatch_SymDescriptor*>& arrSyms = TPatch_SymDescriptor::arrSymDescriptors;
		for (uint32 i = 0; i < arrSyms.GetNum(); i++)
		{
			if( arrSyms[i]->sClassName == symbol )
			{
				CPatch_Type* sym = arrSyms[i]->CreateSymbol();
				if( sym )
				{
					return sym;
				}
			}
		}

		// * address format
		if( symbol.MatchesMask( UnionFilters::arrNumber[1] ) && symbol.HasWordI("x"))
		{
			Common::CString sPageIndex	=		 symbol.GetWord( UnionFilters::sDefaultSpace, 1 );
			Common::CString sValue		= "0x" + symbol.GetWord( UnionFilters::sDefaultSpace, 2 );

			uint32 ulPageIndex	= sPageIndex.ToInt32( 10 );
			uint32 ulValue		= sValue	.ToInt32( 16 );
			if( ulPageIndex == 0 )
			{
				CPatch_Integer* pInteger = new CPatch_Integer;
				pInteger->SetValue( ulValue );
				return pInteger;
			}

			CPatch_Page* pPage = CPatch_Page::GetPage( ulPageIndex );
			if( !pPage )
			{
				ASSERT_PATCH_ERROR( "Не существует страницы с индексом " + Common::CString(ulPageIndex, 16) );
			}
			uint32 ulPageAddress = pPage->GetAddress() + ulValue;

			CPatch_Integer* pInteger = new CPatch_Integer;
			pInteger->SetValue( ulPageAddress );
			return pInteger;
		}

		// * float format
		if( symbol.MatchesMask( UnionFilters::arrNumber[2] ))
		{
			real32 fValue = symbol.ToReal32();
			CPatch_Float* pFloat = new CPatch_Float;
			pFloat->SetValue( fValue );
			return pFloat;
		}

		// * integer format
		if( symbol.MatchesMask( UnionFilters::arrNumber[0] ))
		{
			uint32 fValue = symbol.ToReal32();
			CPatch_Integer* pInteger = new CPatch_Integer;
			pInteger->SetValue( fValue );
			return pInteger;
		}

		// * text format
		if( symbol.First() == UnionFilters::sBrackets_TextLine[0][0] && symbol.Last() == UnionFilters::sBrackets_TextLine[1][0] )
		{
			CPatch_Hex* pHex = new CPatch_Hex;
			pHex->SetValue( (void32)symbol.GetVector(), symbol.Length()-2 );
			return pHex;
		}

		// * hex format
		if( symbol.First() == UnionFilters::sBrackets_HexLine[0][0] && symbol.Last() == UnionFilters::sBrackets_HexLine[1][0] )
		{
			Common::CArray<byte> arrBytes;
			for (uint32 i = 1;; i++)
			{
				Common::CString sByte = symbol.GetWord(" '", i);
			
				if (sByte.IsEmpty())
					break;
				arrBytes.Insert( (sByte).ToInt32(16) );
			}
			void32 pPtr = arrBytes.CopyAtBounds(0, arrBytes.GetNum());
			uint32 ulSize = arrBytes.GetNum();
			
			CPatch_Hex* pHex = new CPatch_Hex;
			pHex->SetValue( arrBytes.CopyAtBounds(0, arrBytes.GetNum()), arrBytes.GetNum() );
			return pHex;
		}

		// * search in variable list
		for (uint32 i = 0; i < arrVariables.GetNum(); i++)
		{
			if( arrVariables[i]->sObjectName == symbol )
			{
				arrVariables[i]->AddRef();
				return arrVariables[i];
			}
		}

		// * external associations
		for (uint32 i = 0; i < arrAssociations.GetNum(); i++)
		{
			CPatch_Type* pSymbol = arrAssociations[i](symbol);
			if( pSymbol )
			{
				return pSymbol;
			}
		}
		return Null;
	}

	void CPatch_Type::DefineExternalOperators (TOperatorCollection* collection)
	{
		arrExternalOperators.Insert( collection );
	}

	void CPatch_Type::DefineExternalAssociation (TAssociation association)
	{
		arrAssociations.Insert( association );
	}

	CPatch_Type* CPatch_Type::CallExternalOperators (const uint32& index, CPatch_Type* left, CPatch_Type* right)
	{
		for (uint32 i = 0; i < arrExternalOperators.GetNum(); i++)
		{
			if( !arrExternalOperators[i]->operators[index] )
			{
				ASSERT_PATCH_ERROR( "ќператор [" + left->GetTypeName() + "] " + sOperators[index] + " [" + right->GetTypeName() + "] не определен" );
			}
			CPatch_Type* symbol = arrExternalOperators[i]->operators[index]( left, right );
			if( symbol )
			{
				return symbol;
			}
		}
		return Null;
	}

	void CPatch_Type::SetObjectName(const Common::CString& objName)
	{
		sObjectName = objName;
		if( !sObjectName.IsEmpty() )	arrVariables.Insert( this );
		else							arrVariables.Remove( this );
	}

	void CPatch_Type::SetOptionName(const Common::CString& optName)
	{
		sOptionName = optName;
	}

	Common::CString CPatch_Type::GetObjectName()
	{
		return sObjectName;
	}

	Common::CString CPatch_Type::GetOptionName()
	{
		return sOptionName;
	}

	EValueType CPatch_Type::GetValueType()
	{
		return eValueType;
	}

	CPatch_Type::~CPatch_Type()
	{
		arrVariables.Remove( this );
	}
}













namespace SystemPack
{
	PATCH_INTERFACE_DEFINITION( CPatch_Operator );

	CPatch_Operator::CPatch_Operator ()
	{
		
	}

	CPatch_Symbol* CPatch_Operator::CreateSymbol (const Common::CString& name)
	{
		if( name.First() == sBrackets_Round[0][0] && name.Last() == sBrackets_Round[1][0] )
		{
			CPatch_Operator* pOperator = new CPatch_Operator;
			pOperator->SetName( name );
		}
		for (uint32 i = 0; i < ulOperatorNum; i++)
		{
			if (sOperators[i] == name)
			{
				CPatch_Operator* pOperator = new CPatch_Operator;
				pOperator->SetName( name );
			}
		}
		Common::CArray<TPatch_SymDescriptor*>& arrTypes = TPatch_SymDescriptor::arrSymDescriptors;
		for (uint32 i = 0; i < arrTypes.GetNum(); i++)
		{
			if (arrTypes[i]->sClassName == name)
			{
				CPatch_Operator* pOperator = new CPatch_Operator;
				pOperator->SetName( name );
			}
		}
		return Null;
	}

	Common::CString CPatch_Operator::GetName()
	{
		return sOperator;
	}

	CPatch_Operator::~CPatch_Operator ()
	{
		
	}
}