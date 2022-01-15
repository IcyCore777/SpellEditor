#include <UnionAfx.h>

#define swsepar " \t\n\r"

#define swoperators	" +-*/=()"

Common::CString* GetSymbolMask ()
{
	static Common::CString StringMask_Parser1 [] = {
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ",
		"1234567890.",
		"+-*/=<>@!:",
		"()[]",
		"abcdefABCDEF0123456789"
	};
	return StringMask_Parser1;
}


namespace SystemPack
{
	/*static Common::CString GetBracketsData (Common::CString formula, uint32* pos = Null, uint32* length = Null)
	{
		uint32 ulBrackets = 0;
		for (uint32 i = 0; i < formula.Length(); i++)
		{
			if (formula[i] == '(') 
				if (!ulBrackets++ && pos) 
					*pos = i;

			if (formula[i] == ')') {
				if (!--ulBrackets) {
					if (length)
						*length = i - *pos + 1;
					return formula.Copy(*pos + 1, *length - 2);
				}
			}
		}
		if (pos)	*pos	= Invalid;
		if (length)	*length	= None;
		return NullStr;
	}*/

	static const Common::CString s_sNumericalFilter	= "1234567890.xXabcdefABCDEF-";
	static const Common::CString s_sTextFilter		= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890:";
	static const Common::CString s_sOperatorFilter	= "+-*/=@<>!";
	static const Common::CString s_sBracketsFilter	= "()[]\"'";

	static const Common::CString s_arrFilters [] = { 
		s_sNumericalFilter,
		s_sTextFilter,
		s_sOperatorFilter,
		s_sBracketsFilter
	};

	static const Common::CString s_sBrackets_Default [2] = { "(",	")"	 };
	static const Common::CString s_sBrackets_Square  [2] = { "[",	"]"	 };
	static const Common::CString s_sBrackets_Text    [2] = { "\"",	"\"" };
	static const Common::CString s_sBrackets_Hex     [2] = { "'",	"'"  };
	static const Common::CString s_sBrackets_Comment [2] = { "/*",	"*/" };

	static const Common::CString* s_arrBrackets [] = {
		s_sBrackets_Default,
		s_sBrackets_Square,
		s_sBrackets_Text,
		s_sBrackets_Hex,
		s_sBrackets_Comment
	};

	CParSymbol* CPatchRegion::GetVariable (Common::CString name)
	{
		for (uint32 i = 0; i < arrSymbols.GetNum(); i++)
		{
			if (arrSymbols[i]->GetName().CompareI(name))
				return arrSymbols[i];
		}
		
		Common::CArray<CParSymbol*>& arrGlobals = pParent->arrGlobals;
		for (uint32 i = 0; i < arrGlobals.GetNum(); i++)
		{
			if (arrGlobals[i]->GetName().CompareI(name))
				return arrGlobals[i];
		}
		return Null;
	}

	static bool32 NameValidation (Common::CString name)
	{
		static const Common::CString sNamesFilter = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
		static const Common::CString sNumsFilter  = "1234567890";

		for (uint32 i = 0; i < sNumsFilter.Length(); i++)
		{
			if (name[0] == sNumsFilter[i])
				return False;
		}
		for (uint32 i = 0; i < name.Length(); i++)
		{
			for (uint32 j = 0; j < sNamesFilter.Length(); j++)
			{
				if (name[i] == sNamesFilter[j])
				{
					goto c;
				}
			}
			return False;
			c:
			continue;
		}
		return True;
	}

	static const Common::CString sInt10Filter	= "1234567890-";
	static const Common::CString sInt16Filter	= "1234567890xabcdefXABCDEF";

	static bool32 IsIncluded (const Common::CString& mask, const Common::CString& object)
	{
		for (uint32 i = 0; i < object.Length(); i++)
		{
			for (uint32 j = 0; j < mask.Length(); j++)
			{
				if (object[i] == mask[j])
					goto g;
			}
			return False;
		g: 
			continue;
		}
		return True;
	}

	inline bool32 bIsInt10 (const Common::CString& str)
	{
		return IsIncluded( sInt10Filter, str );
	}

	inline bool32 bIsInt16 (const Common::CString& str)
	{
		return IsIncluded( sInt16Filter, str );
	}

	uint32 CPatchRegion::CalcLine (uint32 idx)
	{
		CPatch::ulLastLine = idx;
		
		Common::CString& line = sRegion[idx];

		//
		//	Создание новой переменной
		//
		Common::CString sCommand = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 1 );
		if (sCommand == "INT" || sCommand == "BOOL" || sCommand == "FLOAT" || sCommand == "HEX")
		{
			Common::CString sNextCommand = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 2 );
			// создание ссылки
			if (sNextCommand == "@")
			{
				Common::CString sName = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 3 );
				
				if (!bIsInt10( sName ) && !bIsInt16( sName ) && !sName.HasWord(":"))//&& sName.First() != '\"' && sName.Last() != '\"')
				{
					ASSERT_PATCH( NameValidation(sName), ".patch: Имя переменной некорректно: '" + sName + "'" );
				
					Common::CString sAssign = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 4 );
					if (!sAssign.Compare( "=" ))
						ASSERT_PATCH_ERROR( ".patch: Ожидается присвоение адреса" );

					Common::CString		sData    = line.GetPattern( "=", "" );
					CParStack*	pStack   = CParStack::CreateStack( sData );
					CParSymbol*	pAddress = pStack->Execute();

					ASSERT_PATCH( pAddress->GetType() == VAR_TYPE_INT || pAddress->GetType() == VAR_TYPE_UNKNOWN, ".patch: Ссылка должна представлять адрес или имя ini ресурса" );

					if (pAddress->GetType() == VAR_TYPE_INT)
					{
						CParSymbol* pSymbol = new CParSymbol( sCommand, sName );
						pSymbol->SetRoot( VAR_ROOT_EXTERNAL, *(int32*)pAddress->GetData() );
						pStack->Destroy();
						arrSymbols.Insert( pSymbol );
					}
					else
					{
						CParSymbol* pSymbol = new CParSymbol( sCommand, sName );
						pSymbol->SetRoot( VAR_ROOT_OPTION, pAddress->GetRoot() );//Common::CString((char*)pAddress->GetData(), pAddress->GetSize()));
						pStack->Destroy();
						arrSymbols.Insert( pSymbol );
					}

					return idx;
				}
			}
			// создание обычной переменной
			else
			{
				Common::CString sName = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 2 );
				//if (!sName.HasWord(":"))
				{
					ASSERT_PATCH( NameValidation(sName), ".patch: Имя переменной некорректно: '" + sName + "'" );

					Common::CString		sAssign = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 3 );
					CParSymbol*	pSymbol = new CParSymbol( sCommand, sName );

					if (sAssign.Compare( "=" ))
					{
						Common::CString		sData   = line.GetPattern( "=", "" );
						CParStack*	pStack  = CParStack::CreateStack( sData );
						CParSymbol*	pResult = pStack->Execute();

						(*pSymbol) = (*pResult);
						pStack->Destroy();
						arrSymbols.Insert( pSymbol );
					}
					return idx;
				}
			}
			
		}

		if (line.GetWord(" ") == "IF")
		{
			uint32 ulElse	 = Invalid;
			uint32 ulEnd	 = Invalid;
			uint32 ulEntries = 1;
			for (uint32 i = idx + 1; i < sRegion.GetNum(); i++)
			{
				if (sRegion[i].GetData().GetWord(" ") == "IF")
				{
					ulEntries++;
				}
				if (sRegion[i].GetData().GetWord(" ") == "ELSE")
				{
					if (ulEntries == 1)
						ulElse = i;
				}
				if (sRegion[i].GetData().GetWord(" ") == "END")
				{
					if (--ulEntries == 0)
					{
						ulEnd = i;
					}
				}
			}
			ASSERT_PATCH( ulEnd != Invalid, ".patch: Не обнаружен конец блока IF" );

			Common::CString		sCond		= line.GetPattern( "IF", "" );
			CParStack*	pStack		= CParStack::CreateStack( sCond );
			CParSymbol*	pResult		= pStack->Execute();
			bool32		bCondIsTrue	= pResult->GetBool();

			if (ulElse != Invalid)
			{
				CPatchRegion* region = new CPatchRegion(sName + " +", pParent);
				if (bCondIsTrue)
				{
					for (uint32 i = idx + 1; i < ulElse; i++)
						region->PushCommand( sRegion[i] );
				}
				else
				{
					for (uint32 i = ulElse + 1; i < ulEnd; i++)
						region->PushCommand( sRegion[i] );
				}
				region->Execute();
				delete region;
			}
			else
			{
				if (bCondIsTrue)
				{
					CPatchRegion* region = new CPatchRegion(sName + " +", pParent);
					for (uint32 i = idx + 1; i < ulEnd; i++)
						region->PushCommand( sRegion[i] );
					
					region->Execute();
					delete region;
				}
			}
			return ulEnd;
		}

		if (sCommand == "PRINT" || sCommand == "MESSAGE")
		{
			Common::CString sLine = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 2 );

			Common::CString		sData   = line.GetPattern( sCommand, "" );
			CParStack*	pStack  = CParStack::CreateStack( sData );
			CParSymbol*	pResult = pStack->Execute();

			Common::CString sResultStr;
			if (pResult->GetType() == VAR_TYPE_INT)
			{
				sResultStr = *(int32*)pResult->GetData();
			}
			else if (pResult->GetType() == VAR_TYPE_FLOAT)
			{
				sResultStr = *(real32*)pResult->GetData();
			}
			else if (pResult->GetType() == VAR_TYPE_HEX)
			{
				sResultStr = Common::CString( (char*)pResult->GetData(), pResult->GetSize() );
			}
			else
				ASSERT_PATCH_ERROR( ".patch: Невозможно вывести сообщение неопределенного типа" );

			pStack->Destroy();
			if (sCommand == "PRINT")
				cmd << Col16(CMD_GREEN | CMD_INTENSITY) << ".patch >> " << Col16() << sResultStr << endl;
			else
				Say::Info( sResultStr, ".patch" );

			return idx;
		}

		if (sCommand == "LOAD_LIBRARY")
		{
			Common::CString sLine = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, 2 );

			Common::CString		sData   = line.GetPattern( sCommand, "" );
			CParStack*	pStack  = CParStack::CreateStack( sData );
			CParSymbol*	pResult = pStack->Execute();

			ASSERT_PATCH( pResult->GetType() == VAR_TYPE_HEX, ".patch: LOAD_LIBRARY принимает HEX строку" );

			Common::CString sResultStr( (char*)pResult->GetData(), pResult->GetSize() );
			
			LoadLibraryAST( sResultStr );

			return idx;
		}
		
		CParStack* pStack = CParStack::CreateStack( line );
		pStack->Execute();

		return idx;
	}

	void CPatchRegion::Execute ()
	{
		CPatch::sLastRegion = sName;
		for (uint32 i = 0; i < sRegion.GetNum(); i++)
		{
			i = CalcLine( i );
		}
		if (!sName.Compare( "GLOBAL DATA" ))
			arrSymbols.DeleteData();
	}



	void CPatchRegion::PushCommand (const Common::CString& com)
	{
		sRegion.InsertLines(com);
	}


	CPatchRegion::~CPatchRegion ()
	{
		
	}

}
