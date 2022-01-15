#include <UnionAfx.h>





/* * * * * * * * * * * * * * * * * * * * * * * *

		CParHandler
		Стековый обработчик данных

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	static uint32 UnlockMem (const uint32& address, const uint32& length, const uint32& rule)
	{
		ulong32 oldRule;
		VirtualProtect ((void32)address, length, rule, &oldRule);
		return oldRule;
	}

	CParHandler* CParHandler::CreateHandler (const CString& str)
	{
		CParOperator* op = CParOperator::CreateOperator( str );
		if (op) 
			return op;

		CParSymbol* sym = CParSymbol::CreateSymbol( str );
		if (sym)
			return sym;

		return Null;
	}

	void CParHandler::Release ()
	{
		if (--ulRef == 0)
			delete this;
	}

	void CParHandler::AddRef ()
	{
		++ulRef;
	}
}









/* * * * * * * * * * * * * * * * * * * * * * * *

		CParSymbol
		Носитель информации

* * * * * * * * * * * * * * * * * * * * * * * */


namespace SystemPack
{

	CArray<CParSymbol*> CParSymbol::arrSymbols;


	static const CString sInt10Filter	= "1234567890-";
	static const CString sInt16Filter	= "1234567890xabcdefXABCDEF";
	static const CString sFloatFilter	= "1234567890.-";
	static const CString sHexFilter		= "1234567890abcdefABCDEF ";

	CParSymbol::CParSymbol () : CParHandler ()
	{
		arrSymbols.Insert( this );

		sName		= NullStr;
		lpSymbol	= Null;
		ulSizeof	= 0;
		ulSymType	= VAR_ROOT_UNKNOWN;
		ulRootType	= VAR_ROOT_LOCAL;
		sRoot		= NullStr;
	}

	CParSymbol::CParSymbol (const uint32& type, const CString& name)
	{
		if (!name.IsEmpty())
			for (uint32 i = 0; i < arrSymbols.GetNum(); i++)
				if (arrSymbols[i]->sName == name)
					Say::Fatal( "F: Переопределение '" + name + "'" );

		arrSymbols.Insert( this );
		sName = name;

		if (type == VAR_TYPE_INT)
		{
			ulSizeof	= 4;
			lpSymbol	= shi_malloc( ulSizeof );
			ulSymType	= VAR_TYPE_INT;
			*(int32*)lpSymbol = 0;
		}
		else if (type == VAR_TYPE_FLOAT)
		{
			ulSizeof	= 4;
			lpSymbol	= shi_malloc( ulSizeof );
			ulSymType	= VAR_TYPE_FLOAT;
			*(real32*)lpSymbol = 0.0f;
		}
		else if (type == VAR_TYPE_HEX)
		{
			ulSizeof	= 0;
			lpSymbol	= shi_malloc( 0 );
			ulSymType	= VAR_TYPE_HEX;
		}
		else
		{
			lpSymbol	= Null;
			ulSizeof	= 0;
			ulSymType	= VAR_ROOT_UNKNOWN;
		}
		ulRootType	= VAR_ROOT_LOCAL;
		sRoot		= NullStr;
	}

	CParSymbol::CParSymbol (const CString& type, const CString& name)
	{
		if (!name.IsEmpty())
			for (uint32 i = 0; i < arrSymbols.GetNum(); i++)
				if (arrSymbols[i]->sName == name)
					Say::Fatal( "F: Переопределение '" + name + "'" );

		arrSymbols.Insert( this );
		sName = name;

		if (type == "INT" || type == "BOOL")
		{
			ulSizeof	= 4;
			lpSymbol	= shi_malloc( ulSizeof );
			ulSymType	= VAR_TYPE_INT;
			*(int32*)lpSymbol = 0;
		}
		else if (type == "FLOAT")
		{
			ulSizeof	= 4;
			lpSymbol	= shi_malloc( ulSizeof );
			ulSymType	= VAR_TYPE_FLOAT;
			*(real32*)lpSymbol = 0.0f;
		}
		else if (type == "HEX")
		{
			ulSizeof	= 0;
			lpSymbol	= shi_malloc( 0 );
			ulSymType	= VAR_TYPE_HEX;
		}
		else
		{
			lpSymbol	= Null;
			ulSizeof	= 0;
			ulSymType	= VAR_ROOT_UNKNOWN;
		}
		ulRootType	= VAR_ROOT_LOCAL;
		sRoot		= NullStr;
	}

	void CParSymbol::SetInt	(int32 val)
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
		{
			long32 oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
			**(int32**)lpSymbol = val;
			UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
		}
		else
		{
			lpSymbol = shi_realloc( lpSymbol, ulSizeof );
			*(int32*)lpSymbol = val;
		}
		ulSizeof = 4;
		ulSymType = VAR_TYPE_INT;
	}

	void CParSymbol::SetFloat (real32 val)
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
		{
			long32 oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
			**(real32**)lpSymbol = val;
			UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
		}
		else
		{
			lpSymbol = shi_realloc( lpSymbol, ulSizeof );
			*(real32*)lpSymbol = val;
		}
		ulSizeof = 4;
		ulSymType = VAR_TYPE_FLOAT;
	}

	void CParSymbol::SetHex	(void32 val, const uint32& size)
	{
		ulSizeof = size;
		if (lpSymbol)
			MemDel(lpSymbol);

		if (ulRootType == VAR_ROOT_EXTERNAL)
		{
			long32 oldRoot = UnlockMem( *(int32*)lpSymbol, ulSizeof, PAGE_EXECUTE_READWRITE );
			memcpy( *(void32*)lpSymbol, val, ulSizeof );
			UnlockMem( *(int32*)lpSymbol, ulSizeof, oldRoot );
		}
		else
		{
			lpSymbol = shi_realloc( lpSymbol, ulSizeof );
			memcpy( lpSymbol, val, ulSizeof );
		}
		ulSymType = VAR_TYPE_HEX;
	}

	void CParSymbol::SetRoot (const uint32& type, const CString& root)
	{
		ulRootType = type;
		sRoot	   = root;
		if (ulSymType != VAR_TYPE_UNKNOWN)
		{
			SetOption( root );
		}
	}

	void CParSymbol::SetRoot (const uint32& type, const uint32& address)
	{
		ulRootType = type;
		lpSymbol = shi_realloc(lpSymbol, 4);
		*(uint32*)lpSymbol = address;
	}

	void CParSymbol::SetOption (const CString& str)
	{
		CString sOptionData[3] = { NullStr, NullStr, NullStr };
		for (int32 i = 1; i <= 3; i++)
			sOptionData[3 - i] = str.GetWord( ": \t", -i );

		if (!sOptionData[1].IsEmpty() && !sOptionData[2].IsEmpty())
		{
			COption* opt = Null;
			if (!sOptionData[0].IsEmpty())
			{
				if (sOptionData[0] == "UNION")
					opt = &Union.GetUnionOption();
				else if (sOptionData[0] == "SYSTEMPACK")
					opt = &Union.GetSysPackOption();
				else if (sOptionData[0] == "MOD")
					opt = &Union.GetGameOption();
				else if (sOptionData[0] == "GAME")
					opt = &Union.GetDefaultOption();

				CString val;
				opt->Read( val, sOptionData[1], sOptionData[2] );

				if( ulSymType == VAR_TYPE_INT )
					SetInt( val.ToInt32() );
				if( ulSymType == VAR_TYPE_FLOAT )
					SetFloat( val.ToReal32() );
				if( ulSymType == VAR_TYPE_HEX )
					SetHex( (void32)val.GetVector(), val.Length() );
			}
			else if (Union.OptionIsExists( sOptionData[1], sOptionData[2] ))
			{
				CString val = Union.OptionReadString( sOptionData[1], sOptionData[2] );

				if( ulSymType == VAR_TYPE_INT )
					SetInt( val.ToInt32() );
				if( ulSymType == VAR_TYPE_FLOAT )
					SetFloat( val.ToReal32() );
				if( ulSymType == VAR_TYPE_HEX )
					SetHex( (void32)val.GetVector(), val.Length() );
			}
		}
	}

	static void32 HexToMem (const CString& str, uint32& size)
	{ 
		CArray<byte> arrBytes;
		for (uint32 i = 1;; i++)
		{
			CString sByte = str.GetWord(" '", i);
			
			if (sByte.IsEmpty())
				break;
			arrBytes.Insert( ("0x" + sByte).ToInt32(16) );
		}
		void32 mem = arrBytes.CopyAtBounds(0, arrBytes.GetNum());
		size = arrBytes.GetNum();
		return mem;
	}

	static void32 StringToMem (const CString& str, uint32& size)
	{
		size = str.Length()-2;
		void32 mem = shi_malloc( size );
		memcpy( mem, str.GetVector()+1, size );
		return mem;
	}

	static bool32 IsIncluded (const CString& mask, const CString& object)
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

	inline bool32 bIsInt10 (const CString& str)
	{
		return IsIncluded( sInt10Filter, str );
	}

	inline bool32 bIsInt16 (const CString& str)
	{
		return IsIncluded( sInt16Filter, str );
	}

	inline bool32 bIsFloat (const CString& str)
	{
		return IsIncluded( sFloatFilter, str );
	}

	inline bool32 bIsHex (const CString& str)
	{
		if (str.First() != '\'' || str.Last() != '\'')
			return False;
		return IsIncluded( sHexFilter, CString(&str[1], str.Length()-2) );
	}

	inline bool32 bIsString (const CString& str)
	{
		if (str.First() != '\"' || str.Last() != '\"')
			return False;
		return True;
	}

	ESymbolVarType CParSymbol::DefineSymbolType (const CString& str)
	{
		if (str == "TRUE")
		{
			SetInt( TRUE );
			return VAR_TYPE_INT;
		}
		if (str == "FALSE")
		{
			SetInt( FALSE );
			return VAR_TYPE_INT;
		}
		if (str == "NULL")
		{
			SetInt( NULL );
			return VAR_TYPE_INT;
		}
		if (bIsInt10( str ))
		{
			SetInt( str.ToInt32() );
			return VAR_TYPE_INT;
		}
		if (bIsInt16( str ))
		{
			SetInt( str.ToInt32(16) );
			return VAR_TYPE_INT;
		}
		if (bIsFloat( str ))
		{
			SetFloat( str.ToReal32() );
			return VAR_TYPE_FLOAT;
		}
		if (bIsHex( str ))
		{
			uint32 size = str.Length()-2;
			void32 mem  = HexToMem( str, size );
			SetHex( mem, size );
			return VAR_TYPE_HEX;
		}
		if (bIsString( str ))
		{
			uint32 size = str.Length()-2;
			void32 mem  = StringToMem( str, size );
			SetHex( mem, size );
			return VAR_TYPE_HEX;
		}
		return VAR_TYPE_UNKNOWN;
	}

	void CParSymbol::ConvertToInt ()
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
			ASSERT_PATCH_ERROR( ".patch: Попытка косвенного преобразования типа для внешнего символа. Разрешается использовать только прямой патчинг" );

		if (ulSymType == VAR_TYPE_FLOAT)
		{
			SetInt( *(real32*)lpSymbol );
		}
		else if (ulSymType == VAR_TYPE_HEX)
		{
			CString str( (char*)lpSymbol, 4 );
			SetInt( str.ToInt32() );
		}
		ApplyOption();
	}
	
	void CParSymbol::ConvertToFloat ()
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
			ASSERT_PATCH_ERROR( ".patch: Попытка косвенного преобразования типа для внешнего символа. Разрешается использовать только прямой патчинг" );

		if (ulSymType == VAR_TYPE_INT)
		{
			*(real32*)lpSymbol = *(int32*)lpSymbol;

			ulSymType = VAR_TYPE_FLOAT;
		}
		else if (ulSymType == VAR_TYPE_HEX)
		{
			CString str( (char*)lpSymbol, 4 );
			*(real32*)lpSymbol = str.ToReal32();

			ulSymType = VAR_TYPE_HEX;
		}
		ApplyOption();
	}
		
	void CParSymbol::ConvertToHex ()
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
			ASSERT_PATCH_ERROR( ".patch: Попытка косвенного преобразования типа для внешнего символа. Разрешается использовать только прямой патчинг" );

		if (ulSymType == VAR_TYPE_HEX)
			return;
		ulSymType = VAR_TYPE_HEX;
	}

	void CParSymbol::ConvertToString ()
	{
		if (ulRootType == VAR_ROOT_EXTERNAL)
			ASSERT_PATCH_ERROR( ".patch: Попытка косвенного преобразования типа для внешнего символа. Разрешается использовать только прямой патчинг" );

		if (ulSymType == VAR_TYPE_INT)
		{
			CString sVal = *(int32*)lpSymbol;
			lpSymbol = shi_realloc( lpSymbol, ulSizeof + sVal.Length() );
			memcpy( (void32)((int32)lpSymbol + ulSizeof), sVal.GetVector(), sVal.Length() );
			ulSizeof += sVal.Length();
		}
		else if (ulSymType == VAR_TYPE_FLOAT)
		{
			CString sVal = *(real32*)lpSymbol;
			for (uint32 i = sVal.Length()-1; i != Invalid; i--)
			{
				char c = sVal[i];
				if (c == '.')
				{
					sVal.Cut( i, sVal.Length() - i );
					break;
				}
				if (c != '0')
				{
					sVal.Cut( i+1, sVal.Length() - i+1 );
					break;
				}
			}
			lpSymbol = shi_realloc( lpSymbol, ulSizeof + sVal.Length() );
			memcpy( (void32)((int32)lpSymbol + ulSizeof), sVal.GetVector(), sVal.Length() );
			ulSizeof += sVal.Length();
		}
		ApplyOption();
	}

	void CParSymbol::ApplyOption ()
	{
		if (ulRootType != VAR_ROOT_OPTION || sRoot.IsEmpty())
			return;

		CString sOptionData[3] = { NullStr, NullStr, NullStr };
		for (int32 i = 1; i <= 3; i++)
			sOptionData[3 - i] = sRoot.GetWord( ": \t", -i );

		COption* opt = Null;
		if (!sOptionData[0].IsEmpty())
		{
			if (sOptionData[0] == "UNION")
			{
				opt = &Union.GetUnionOption();
			}
			else if (sOptionData[0] == "SYSTEMPACK")
			{
				opt = &Union.GetSysPackOption();
			}
			else if (sOptionData[0] == "MOD")
			{
				opt = &Union.GetGameOption();
			}
			else if (sOptionData[0] == "GAME")
			{
				opt = &Union.GetDefaultOption();
			}

			if (opt)// && opt->IsExists( sOptionData[1], sOptionData[2] ))
			{
				if (ulSymType == VAR_TYPE_INT)
				{
					opt->Write( *(int32*)lpSymbol, sOptionData[1], sOptionData[2] );
				}
				else if (ulSymType == VAR_TYPE_FLOAT)
				{
					opt->Write( *(real32*)lpSymbol, sOptionData[1], sOptionData[2] );
				}
				else if (ulSymType == VAR_TYPE_HEX)
				{
					opt->Write( CString((char*)lpSymbol, ulSizeof), sOptionData[1], sOptionData[2] );
				}
				else
					ASSERT_PATCH_ERROR( ".patch: Необходимо определить тип ini параметра" );
			}
		}
		else if (Union.OptionIsExists( sOptionData[1], sOptionData[2] ))
		{
			if (ulSymType == VAR_TYPE_INT)
				Union.OptionWriteInt( sOptionData[1], sOptionData[2], *(int32*)lpSymbol );
			else if (ulSymType == VAR_TYPE_FLOAT)
				Union.OptionWriteFloat( sOptionData[1], sOptionData[2], *(real32*)lpSymbol );
			else if (ulSymType == VAR_TYPE_HEX)
				Union.OptionWriteString( sOptionData[1], sOptionData[2], CString((char*)lpSymbol, ulSizeof) );
		}
	}

	CParSymbol& CParSymbol::operator + (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( ulSymType );
		(*newSym)  = (*this);
		(*newSym) +=  sym;
		return *newSym;
	}

	CParSymbol& CParSymbol::operator - (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( ulSymType );
		(*newSym)  = (*this);
		(*newSym) -=  sym;
		return *newSym;
	}

	CParSymbol& CParSymbol::operator * (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( ulSymType );//CreateCopy( &sym );
		(*newSym)  = (*this);
		(*newSym) *=  sym;
		return *newSym;
	}

	CParSymbol& CParSymbol::operator / (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( ulSymType );
		(*newSym)  = (*this);
		(*newSym) /=  sym;
		return *newSym;
	}

	CParSymbol& CParSymbol::operator += (CParSymbol& sym)
	{
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32& left	 = *(int32*)   GetData();
				int32& right = *(int32*)sym.GetData();

				left += right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left += right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для произведения операции над HEX значением, необходимо явное приведение к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				real32& left  =	*(real32*)   GetData();
				int32&  right = *(int32*)sym.GetData();

				left += right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				real32& left  =	*(real32*)    GetData();
				real32& right = *(real32*)sym.GetData();

				left += right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				(*(int32*)lpSymbol) += *(real32*)sym.lpSymbol;
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (ulRootType == VAR_ROOT_EXTERNAL)
				ASSERT_PATCH_ERROR( ".patch: Строковая ссылка не может быть изменена, поскольку невозможно оценить размер строки после преобразования. Разрешается использовать только прямой патчинг" );

			if (sym.ulSymType == VAR_TYPE_INT)
			{
				ASSERT_PATCH_ERROR( ".patch: Для сложения HEX с правым значением, необходимо чтобы оно тот же тип" );

				/*CString sVal = *(int32*)sym.lpSymbol;
				lpSymbol = shi_realloc( lpSymbol, ulSizeof + sVal.Length() );
				memcpy( (void32)((int32)lpSymbol + ulSizeof), sVal.GetVector(), sVal.Length() );
				ulSizeof += sVal.Length();
				
				ApplyOption();
				return *this;*/
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				ASSERT_PATCH_ERROR( ".patch: Для сложения HEX с правым значением, необходимо чтобы оно тот же тип" );

				/*CString sVal = *(real32*)sym.lpSymbol;
				for (uint32 i = sVal.Length()-1; i != Invalid; i--)
				{
					char c = sVal[i];
					if (c == '.')
					{
						sVal.Cut( i, sVal.Length() - i );
						break;
					}
					if (c != '0')
					{
						sVal.Cut( i+1, sVal.Length() - i+1 );
						break;
					}
				}
				lpSymbol = shi_realloc( lpSymbol, ulSizeof + sVal.Length() );
				memcpy( (void32)((int32)lpSymbol + ulSizeof), sVal.GetVector(), sVal.Length() );
				ulSizeof += sVal.Length();

				ApplyOption();
				return *this;*/
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				CString value;
				if (sym.ulRootType == VAR_ROOT_EXTERNAL)
				{
					value = (char*)sym.GetData();
				}
				else
				{
					value = CString( (char*)sym.GetData(), sym.ulSizeof );
				}
				CString source( (char*)lpSymbol, ulSizeof );
				source += value;

				lpSymbol = shi_realloc( lpSymbol, source.Length() );
				memcpy( lpSymbol, source.GetVector(), source.Length() );
				ulSizeof = source.Length();
				Say::Box( ulSizeof );
				
				ApplyOption();
				return *this;
			}
		}
		Say::Fatal ("F: Суммирование одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator -= (CParSymbol& sym)
	{
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				int32& left	 = *(int32*)   GetData();
				int32& right = *(int32*)sym.GetData();

				left -= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left -= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для произведения операции над HEX значением, необходимо явное приведение к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				real32& left  =	*(real32*)   GetData();
				int32&  right = *(int32*)sym.GetData();

				left -= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				real32& left  =	*(real32*)    GetData();
				real32& right = *(real32*)sym.GetData();

				left -= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				(*(int32*)lpSymbol) += *(real32*)sym.lpSymbol;
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (ulRootType == VAR_ROOT_EXTERNAL)
				ASSERT_PATCH_ERROR( ".patch: Строковая ссылка не может быть изменена, поскольку невозможно оценить размер строки после преобразования. Разрешается использовать только прямой патчинг" );

			ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
		}
		Say::Fatal ("F: Вычитание одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator *= (CParSymbol& sym)
	{
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				int32& left	 = *(int32*)   GetData();
				int32& right = *(int32*)sym.GetData();

				left *= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left *= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для произведения операции над HEX значением, необходимо явное приведение к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				real32& left  =	*(real32*)   GetData();
				int32&  right = *(int32*)sym.GetData();

				left *= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				real32& left  =	*(real32*)    GetData();
				real32& right = *(real32*)sym.GetData();

				left *= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				(*(int32*)lpSymbol) += *(real32*)sym.lpSymbol;
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (ulRootType == VAR_ROOT_EXTERNAL)
				ASSERT_PATCH_ERROR( ".patch: Строковая ссылка не может быть изменена, поскольку невозможно оценить размер строки после преобразования. Разрешается использовать только прямой патчинг" );

			ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
		}
		Say::Fatal ("F: Вычитание одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator /= (CParSymbol& sym)
	{
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				int32& left	 = *(int32*)   GetData();
				int32& right = *(int32*)sym.GetData();

				left /= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left /= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для произведения операции над HEX значением, необходимо явное приведение к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				real32& left  =	*(real32*)   GetData();
				int32&  right = *(int32*)sym.GetData();

				left /= right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				real32& left  =	*(real32*)    GetData();
				real32& right = *(real32*)sym.GetData();

				left /= right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				(*(int32*)lpSymbol) += *(real32*)sym.lpSymbol;
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (ulRootType == VAR_ROOT_EXTERNAL)
				ASSERT_PATCH_ERROR( ".patch: Строковая ссылка не может быть изменена, поскольку невозможно оценить размер строки после преобразования. Разрешается использовать только прямой патчинг" );

			ASSERT_PATCH_ERROR(".patch: Для совершения операции с использованием HEX значением необходимо явно привести его к числовому типу" );
		}
		Say::Fatal ("F: Вычитание одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator = (CParSymbol& sym)
	{
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				int32& left	 = *(int32*)   GetData();
				int32& right = *(int32*)sym.GetData();

				left = right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left = right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				cmd << "W: Преобразование из HEX в INT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left = right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );

				real32& left  =	*(real32*)   GetData();
				int32&  right = *(int32*)sym.GetData();

				left = right;
				
				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				cmd << "W: Усечение FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				real32& left  =	*(real32*)    GetData();
				real32& right = *(real32*)sym.GetData();

				left = right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				(*(int32*)lpSymbol) += *(real32*)sym.lpSymbol;
				
				ApplyOption();
				return *this;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				cmd << "W: Преобразование из HEX в FLOAT. Возможна потеря данных." << endl;
				long32 oldRoot;
				if (ulRootType == VAR_ROOT_EXTERNAL)
					oldRoot = UnlockMem( *(int32*)lpSymbol, 4, PAGE_EXECUTE_READWRITE );
				
				int32&  left  =	*(int32*)     GetData();
				real32& right = *(real32*)sym.GetData();

				left = right;

				if (ulRootType == VAR_ROOT_EXTERNAL)
					UnlockMem( *(int32*)lpSymbol, 4, oldRoot );

				ApplyOption();
				return *this;
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			CString value;
			if (sym.ulRootType == VAR_ROOT_EXTERNAL)
			{
				value = (char*)sym.GetData();
			}
			else
			{
				value = CString( (char*)sym.GetData(), sym.ulSizeof );
			}

			CString source;
			if (ulRootType == VAR_ROOT_EXTERNAL)
			{
				source = (char*)GetData();
			}
			else
			{
				source = CString( (char*)GetData(), ulSizeof );
			}

			if (ulRootType == VAR_ROOT_EXTERNAL)
			{
				long32 oldRoot;
				oldRoot = UnlockMem( *(int32*)lpSymbol, value.Length(), PAGE_EXECUTE_READWRITE );
				memcpy( GetData(), value.GetVector(), value.Length() );
				ulSizeof = value.Length();
				UnlockMem( *(int32*)lpSymbol, value.Length(), oldRoot );
			}
			else
			{
				lpSymbol = shi_realloc( lpSymbol, value.Length() );
				memcpy( lpSymbol, value.GetVector(), value.Length() );
				ulSizeof = value.Length();
			}
				
			ApplyOption();
			return *this;
		
		}
		Say::Fatal ("F: Присвоение неопределенному символу!");
	}

	CParSymbol& CParSymbol::operator == (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) == *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) == *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) == *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) == *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				if (ulRootType == VAR_ROOT_EXTERNAL)
				{
					CString str1( (char*)GetData(), sym.ulSizeof );
					CString str2( (char*)sym.GetData(), sym.ulSizeof );
					newSym->SetInt( str1.CompareI( str2 ));
					return *newSym;
				}
				else
				{
					CString str1( (char*)GetData(), ulSizeof );
					CString str2( (char*)sym.GetData(), sym.ulSizeof );
					newSym->SetInt( str1.CompareI( str2 ));
					return *newSym;
				}
			}
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator != (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) != *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) != *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) != *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) != *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				if (ulRootType == VAR_ROOT_EXTERNAL)
				{
					CString str1( (char*)GetData(), sym.ulSizeof );
					CString str2( (char*)sym.GetData(), sym.ulSizeof );
					newSym->SetInt( !str1.CompareI( str2 ));
					return *newSym;
				}
				else
				{
					CString str1( (char*)GetData(), ulSizeof );
					CString str2( (char*)sym.GetData(), sym.ulSizeof );
					newSym->SetInt( !str1.CompareI( str2 ));
					return *newSym;
				}
			}
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator < (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) < *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) < *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) < *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) < *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			ASSERT_PATCH_ERROR( ".patch: Логические операторы не поддерживают HEX значения" );
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator <= (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) <= *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) <= *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) <= *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) <= *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			ASSERT_PATCH_ERROR( ".patch: Логические операторы не поддерживают HEX значения" );
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator > (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) > *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) > *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) > *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) > *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			ASSERT_PATCH_ERROR( ".patch: Логические операторы не поддерживают HEX значения" );
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator >= (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(int32*)GetData()) >= *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(int32*)GetData()) >= *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				newSym->SetInt( (*(real32*)GetData()) >= *(int32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				newSym->SetInt( (*(real32*)GetData()) >= *(real32*)sym.GetData() );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: Сравнение HEX значения допустимо только с другими HEX" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			ASSERT_PATCH_ERROR( ".patch: Логические операторы не поддерживают HEX значения" );
		}
		Say::Fatal ("F: Деление одного или нескольких неопределенных символов!");
	}

	CParSymbol& CParSymbol::operator ^ (CParSymbol& sym)
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				int32 lMult = *(int32*)GetData();
				int32 lPow  = *(int32*)sym.GetData();
				if (lPow == 0)
				{
					lMult = 1;
				}
				else for (int32 i = 1; i < lPow; i++)
				{
					lMult *= *(int32*)GetData();
				}
				newSym->SetInt( lMult );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				int32 lMult = *(int32*)GetData();
				int32 lPow  = *(real32*)sym.GetData();
				if (lPow == 0)
				{
					lMult = 1;
				}
				else for (int32 i = 1; i < lPow; i++)
				{
					lMult *= *(int32*)GetData();
				}
				newSym->SetInt( lMult );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: HEX строка не может быть степенью числа" );
			}
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			if (sym.ulSymType == VAR_TYPE_INT)
			{
				real32 lMult = *(real32*)GetData();
				real32 lPow  = *(int32*)sym.GetData();
				if (lPow == 0)
				{
					lMult = 1;
				}
				else for (uint32 i = 1; i < lPow; i++)
				{
					lMult *= *(int32*)GetData();
				}
				newSym->SetInt( lMult );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_FLOAT)
			{
				real32 lMult = *(real32*)GetData();
				real32 lPow  = *(real32*)sym.GetData();
				if (lPow == 0)
				{
					lMult = 1;
				}
				else for (uint32 i = 1; i < lPow; i++)
				{
					lMult *= *(int32*)GetData();
				}
				newSym->SetInt( lMult );
				return *newSym;
			}
			if (sym.ulSymType == VAR_TYPE_HEX)
			{
				ASSERT_PATCH_ERROR( ".patch: HEX строка не может быть степенью числа" );
			}
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			ASSERT_PATCH_ERROR( ".patch: Невозможно возвести в степерь HEX сторку" );
		}
		ASSERT_PATCH_ERROR( ".patch: Возведение в степень одного или нескольких неопределенных символов!" );
	}

	CParSymbol& CParSymbol::operator ! ()
	{
		CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );
		if (ulSymType == VAR_TYPE_INT)
		{
			newSym->SetInt( !(*(int32*)GetData()) );
			return *newSym;
		}
		if (ulSymType == VAR_TYPE_FLOAT)
		{
			newSym->SetInt( !(*(real32*)GetData()) );
			return *newSym;
		}
		if (ulSymType == VAR_TYPE_HEX)
		{
			Say::Fatal ("F: Невозможно инвертировать строку!");
		}
		Say::Fatal ("F: Инвертирование одного или нескольких неопределенных символов!");
	}

	CParSymbol* CParSymbol::CreateSymbol (const CString& str)
	{
		CParSymbol* sym = new CParSymbol();

		uint32 ulRealType = sym->DefineSymbolType( str );

		if (ulRealType == VAR_TYPE_UNKNOWN)
		{
			uint32 ulOpt = str.HasWord(":");
			if (ulOpt == 1 || ulOpt == 2) 
			{
				sym->sRoot = str;
				return sym;
			}

#if 0
			CString sOptionData[3] = { NullStr, NullStr, NullStr };
			for (int32 i = 1; i <= 3; i++)
				sOptionData[3 - i] = str.GetWord( ": \t", -i );

			if (!sOptionData[1].IsEmpty() && !sOptionData[2].IsEmpty())
			{
				COption* opt = Null;
				if (!sOptionData[0].IsEmpty())
				{
					if (sOptionData[0] == "UNION")
						opt = &Union.GetUnionOption();
					else if (sOptionData[0] == "SYSTEMPACK")
						opt = &Union.GetSysPackOption();
					else if (sOptionData[0] == "MOD")
						opt = &Union.GetGameOption();
					else if (sOptionData[0] == "GAME")
						opt = &Union.GetDefaultOption();

					// if (opt && opt->IsExists( sOptionData[1], sOptionData[2] ))
					{
						//CString val;
						//opt->Read( val, sOptionData[1], sOptionData[2] );
						//CParSymbol* sym = CreateSymbol( val );
						sym->SetRoot( VAR_ROOT_OPTION, str );
						//sym->sName = str;
						return sym;
					}
				}
				else //if (Union.OptionIsExists( sOptionData[1], sOptionData[2] ))
				{
					//CString val = Union.OptionReadString( sOptionData[1], sOptionData[2] );
					//CParSymbol* sym = CreateSymbol( val );
					sym->SetRoot( VAR_ROOT_OPTION, str );
					return sym;
				}
				//Say::Fatal( "F: Option '" + sOptionData[1] + ":" + sOptionData[2] + "' not found." );
			}
#endif
			delete sym;
			for (uint32 i = 0; i < arrSymbols.GetNum(); i++)
			{
				if (arrSymbols[i]->sName == str)
				{
					arrSymbols[i]->AddRef();
					return arrSymbols[i];
				}
			}
			return Null;
		}
		return sym;
	}

	CParSymbol* CParSymbol::CreateCopy (CParSymbol* sym)
	{
		CParSymbol* newSymbol = new CParSymbol();

		newSymbol->ulSizeof		= sym->ulSizeof;
		newSymbol->ulSymType	= sym->ulSymType;
		newSymbol->ulRootType	= sym->ulRootType;
		newSymbol->sRoot		= sym->sRoot;
		newSymbol->lpSymbol		= shi_realloc( newSymbol->lpSymbol, newSymbol->ulSizeof );
		memcpy( newSymbol->lpSymbol, sym->lpSymbol, newSymbol->ulSizeof );

		return newSymbol;
	}

	CString	CParSymbol::GetName	()
	{
		return sName;
	}

	void32 CParSymbol::GetData ()
	{
		return ulRootType == VAR_ROOT_EXTERNAL ? *(void32*)lpSymbol : (void32)lpSymbol;
	}

	uint32 CParSymbol::GetType ()
	{
		return ulSymType;
	}

	bool32 CParSymbol::GetBool ()
	{
		if (ulSymType == VAR_TYPE_INT)
			return (*(uint32*)GetData()) != 0;
		if (ulSymType == VAR_TYPE_FLOAT)
			return (*(real32*)GetData()) != 0.0f;
		if (ulSymType == VAR_TYPE_HEX)
			ASSERT_PATCH_ERROR( ".patch: HEX не может выступать в качестве boolian значения" );
		ASSERT_PATCH_ERROR( ".patch: Неизвестный параметр не может выступать в качестве boolian значения" );
	}

	uint32 CParSymbol::GetSize ()
	{
		if (ulRootType == VAR_ROOT_EXTERNAL && ulSymType == VAR_TYPE_HEX)
		{
			return ulSizeof = strlen( (char*)GetData() );
		}
		return ulSizeof;
	}

	CString CParSymbol::GetRoot ()
	{
		return sRoot;
	}

	CParSymbol* CParSymbol::Execute ()
	{
		AddRef();
		return this;
	}

	void CParSymbol::Print ()
	{
		if (ulSymType == VAR_TYPE_UNKNOWN)
			cmd << "Unknown symbol";
		if (ulSymType == VAR_TYPE_INT)
			cmd << (ulRootType == VAR_ROOT_EXTERNAL ? **(int32**)lpSymbol : *(int32*)lpSymbol);
		if (ulSymType == VAR_TYPE_FLOAT)
			cmd << (ulRootType == VAR_ROOT_EXTERNAL ? **(real32**)lpSymbol : *(real32*)lpSymbol);
		if (ulSymType == VAR_TYPE_HEX)
			cmd << (ulRootType == VAR_ROOT_EXTERNAL ? CString(*(char**)lpSymbol, ulSizeof) : CString((char*)lpSymbol, ulSizeof));
	}

	CParSymbol::~CParSymbol ()
	{
		/*if (ulSymType != VAR_TYPE_UNKNOWN)
		{
			cmd << Col16(CMD_RED | CMD_INTENSITY);
			cmd << "\t~SYM: ";
			Print();
			cmd << endl;
			cmd << Col16();
		}*/
		arrSymbols.Remove( this );
	}
}










/* * * * * * * * * * * * * * * * * * * * * * * *

		CParOperator
		Оператор данных

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	const CString s_sOperators [] = {
		"INT",		// 0
		"FLOAT",	// 1
		"HEX",		// 2
		"BOOL",		// 3
		"+",		// 4
		"-",		// 5
		"*",		// 6
		"/",		// 7

		"^",		// 8

		"=",		// 9

		"==",		// 10
		"!=",		// 11
		"!",		// 12
		"<",		// 13
		"<=",		// 14
		">",		// 15
		">=",		// 16

		"+=",		// 17
		"-=",		// 18
		"*=",		// 19
		"/=",		// 20

		"@",		// 21

		"LIM",		// 22
		"MIN",		// 23
		"MAX",		// 24

		"TOINT",	// 25
		"TOFLOAT",	// 26
		"TOHEX",	// 27
		"TOSTRING",	// 28

		"MODULE_BASE",	// 29
		"PRINT",		// 30
		"MESSAGE",		// 31
		"LOAD_LIBRARY"	// 32
	};

	CParSymbol* CParOperator::Execute ()
	{
		CParStack* pStack = (CParStack*)pOnStack;

		if (sOperator == s_sOperators[0]) // VAR_TYPE_INT
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд от INT" );

			// создаем новую переменную типа int в которую будем записывать число справа
			CParSymbol* newSym		 = new CParSymbol( VAR_TYPE_INT );

			// получаем исходный юнит стека справа от оператора и хендлер
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();

			// вычисляем символ справа от оператора
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			// присваиваем новой переменной данные правого символа
			(*newSym) = (*nextSym);

			// удаляем правый символ и юнит
			// стека, они больше не пригодятся
			nextSym->Release();
			delete pStack->Next();

			// удаляем текущий оператор и 
			// заменяем его полученным символом
			pStack->pHandler->Release();
			pStack->pHandler = newSym;

			return newSym;
		}
		else if (sOperator == s_sOperators[1]) // VAR_TYPE_FLOAT
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд от FLOAT" );

			CParSymbol*  newSym		 = new CParSymbol( VAR_TYPE_FLOAT );
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			(*newSym) = (*nextSym);
			nextSym->Release();

			delete pStack->Next();
			pStack->pHandler->Release();
			pStack->pHandler = newSym;

			return newSym;
		}
		else if (sOperator == s_sOperators[2]) // VAR_TYPE_HEX
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд от HEX" );

			CParSymbol*  newSym		 = new CParSymbol( VAR_TYPE_HEX );
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			(*newSym) = (*nextSym);
			nextSym->Release();
			
			delete pStack->Next();
			pStack->pHandler->Release();
			pStack->pHandler = newSym;

			return newSym;
		}
		else if (sOperator == s_sOperators[3]) // VAR_TYPE_INT (BOOL)
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд от BOOL" );

			CParSymbol* newSym = new CParSymbol( VAR_TYPE_INT );

			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*  zero		 = new CParSymbol( VAR_TYPE_INT );
			zero->SetInt( 0 );

			CParSymbol*	 calcSym	 = nextHandler->Execute();
			CParSymbol*	 nextSym	 = &((*calcSym) > (*zero));

			(*newSym) = (*nextSym);

			nextSym->Release();
			zero->Release();
			
			delete pStack->Next();
			pStack->pHandler->Release();
			pStack->pHandler = newSym;
			return newSym;
		}
		else if (sOperator == s_sOperators[4]) // +
		{
			// обязательно проверяем существуют ли левый и правый симаолы в стеке
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			// получаем исходные юниты стека слева и справа от оператора и хендлеры
			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();

			// вычисляем символы слева и справа от оператора
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			// убеждаемся что символы действительны и их можно обработать
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			// совершаем непосредственную операцию нам символами
			CParSymbol&  newSym		 = (*prevSym) + (*nextSym);

			// удаляем оба символа слева и справа, 
			// они нам больше не понадобятся
			prevSym->Release();
			nextSym->Release();

			// удаляем юниты слева и справа, 
			// поскольку они нам больше не нужны
			delete prevStack;
			delete nextStack;

			// удаляем текущий хендлер оператора 
			// и заменяем его текущим символом
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[5]) // -
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			CParSymbol&  newSym		 = (*prevSym) - (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[6]) // *
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) * (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[7]) // /
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) / (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[8]) // ^
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			CParSymbol&  newSym		 = (*prevSym) ^ (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[9]) // =
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			CParSymbol&  newSym		 = (*prevSym) = (*nextSym);
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[10]) // ==
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			CParSymbol&  newSym		 = (*prevSym) == (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[11]) // !=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) != (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[12]) // !
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = !(*nextSym);
			newSym.Print();
			nextSym->Release();

			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[13]) // <
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) < (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[14]) // <=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) <= (*nextSym);

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[15]) // >
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) > (*nextSym);

			prevSym->Print();
			cmd << " > ";
			nextSym->Print();
			cmd << " is ";
			newSym.Print();
			cmd << endl;

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[16]) // >=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );
			
			CParSymbol&  newSym		 = (*prevSym) >= (*nextSym);

			prevSym->Print();
			cmd << " >= ";
			nextSym->Print();
			cmd << " is ";
			newSym.Print();
			cmd << endl;

			prevSym->Release();
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = &newSym;

			return &newSym;
		}
		else if (sOperator == s_sOperators[17]) // +=
		{
			// обязательно проверяем существуют ли левый и правый симаолы в стеке
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			// получаем исходные юниты стека слева и справа от оператора и хендлеры
			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();

			// вычисляем символы слева и справа от оператора
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			
			// убеждаемся что символы действительны и их можно обработать
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			// совершаем непосредственную операцию нам символами
			(*prevSym) += (*nextSym);

			// поскольку операция представляет присвоение, то и 
			// левый символ оставляем на своем месте, а правый удаляем
			nextSym->Release();

			// удаляем юниты слева и справа, 
			// поскольку они нам больше не нужны
			delete prevStack;
			delete nextStack;

			// удаляем текущий хендлер оператора 
			// и заменяем его текущим символом
			pStack->pHandler->Release();
			pStack->pHandler = prevSym;
			
			return prevSym;
		}
		else if (sOperator == s_sOperators[18]) // -=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			
			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			(*prevSym) - (*nextSym);

			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = prevSym;

			return prevSym;
		}
		else if (sOperator == s_sOperators[19]) // *=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();
			

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			(*prevSym) * (*nextSym);

			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = prevSym;

			return prevSym;
		}
		else if (sOperator == s_sOperators[20]) // /=
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Ожидается левый операнд" );
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParSymbol*	 prevSym	 = prevHandler->Execute();
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( prevSym, ".patch: Левый операнд не является числом" );
			ASSERT_PATCH( nextSym, ".patch: Правый операнд не является числом" );

			(*prevSym) / (*nextSym);
			
			nextSym->Release();

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = prevSym;

			return prevSym;
		}
		else if (sOperator == s_sOperators[21]) // @
		{
			ASSERT_PATCH( pStack->Prev(), ".patch: Для создания ссылки необходимо указать ее тип" );
			ASSERT_PATCH( pStack->Next(), ".patch: Для создания ссылки необходимо указать адрес" );

			CParStack*	 prevStack	 = (CParStack*)pStack->Prev();
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* prevHandler = prevStack->GetData();
			CParHandler* nextHandler = nextStack->GetData();
			CParOperator*prevSym	 = dynamic_cast<CParOperator*>(prevHandler);
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			
			bool32 bIsTypeSymbol = prevSym && ( prevSym->sOperator.Compare("INT") || prevSym->sOperator.Compare("FLOAT") || prevSym->sOperator.Compare("HEX") || prevSym->sOperator.Compare("BOOL"));
			bool32 bIsInteger	 = nextSym && (nextSym->GetType() == VAR_TYPE_INT || nextSym->GetType() == VAR_TYPE_UNKNOWN);
			ASSERT_PATCH( bIsTypeSymbol, ".patch: Левый оператор не найден или не является типом" );
			ASSERT_PATCH( bIsInteger,	 ".patch: Невозможно создать ссылку. Аргумент не является адресом или именем ресурса." );
 
			uint32 ulSymbolType  =	prevSym->sOperator.Compare("INT")	? VAR_TYPE_INT	  : 
									prevSym->sOperator.Compare("FLOAT")	? VAR_TYPE_FLOAT  :
									prevSym->sOperator.Compare("HEX")	? VAR_TYPE_HEX	  :
									prevSym->sOperator.Compare("BOOL")	? VAR_TYPE_INT	  :
																		  VAR_TYPE_UNKNOWN;

			CParSymbol* newSym = new CParSymbol( ulSymbolType );

			if (nextSym->GetType() == VAR_TYPE_INT)
			{
				int32 address = *(int32*)nextSym->GetData();
				newSym->SetRoot( VAR_ROOT_EXTERNAL, address );
			}
			else
			{
				newSym->SetRoot( VAR_ROOT_OPTION, nextSym->GetRoot() );
			}

			delete prevStack;
			delete nextStack;
			pStack->pHandler->Release();
			pStack->pHandler = newSym;

			return newSym;
		}
		else if (sOperator == s_sOperators[22]) // LIM
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается аргумент" );

			// получаем целевой аргумент для загона в предел
			CParStack*	pStack_Argument	= (CParStack*)pStack->Next();
			CParSymbol*	pArgument		= pStack_Argument->GetData()->Execute();

			// ищем операторы ограничения
			bool32 bMinIsCalculated = False;
			bool32 bMaxIsCalculated = False;

			for (uint32 lim = 0; lim < 2; lim++)
			{
				CParStack*  pStack_Operator = (CParStack*)pStack_Argument->Next();
				if (!pStack_Operator)
					break;

				CParOperator* pOperator = dynamic_cast<CParOperator*>(pStack_Operator->pHandler);

				if( pOperator && pOperator->sOperator == "MIN" )
				{
					ASSERT_PATCH( bMinIsCalculated == False, ".patch: Повторяющийся оператор MIN в функции предела" );
					bMinIsCalculated = True;

					CParStack*	pStack_Value = (CParStack*)pStack_Operator->Next();
					CParSymbol*	pValue		 = pStack_Value->GetData()->Execute();

					CParSymbol& pBoolSym = (*pArgument) < (*pValue);
					if( (*(int32*)pBoolSym.GetData()) )
						(*pArgument) = (*pValue);

					pBoolSym.Release();
					pValue->Release();
					delete pStack_Value;
					delete pStack_Operator;
				}
				if( pOperator && pOperator->sOperator == "MAX" )
				{
					ASSERT_PATCH( bMaxIsCalculated == False, ".patch: Повторяющийся оператор MAX в функции предела" );
					bMaxIsCalculated = True;

					CParStack*	pStack_Value = (CParStack*)pStack_Operator->Next();
					CParSymbol*	pValue		 = pStack_Value->GetData()->Execute();

					CParSymbol& pBoolSym = (*pArgument) > (*pValue);
					if( (*(int32*)pBoolSym.GetData()) )
						(*pArgument) = (*pValue);

					pBoolSym.Release();
					pValue->Release();
					delete pStack_Value;
					delete pStack_Operator;
				}
			}

			delete pStack_Argument;
			pStack->pHandler->Release();
			pStack->pHandler = pArgument;

			return pArgument;
		}
		else if (sOperator == s_sOperators[23])
		{
			ASSERT_PATCH_ERROR( ".patch: Найден пустой оператор " + s_sOperators[23] );
		}
		else if (sOperator == s_sOperators[24])
		{
			ASSERT_PATCH_ERROR( ".patch: Найден пустой оператор " + s_sOperators[24] );
		}
		else if (sOperator == s_sOperators[29]) // MODULE_BASE
		{
			ASSERT_PATCH( pStack->Next(), ".patch: Ожидается правый операнд от MODULE_BASE" );

			// создаем новую переменную типа int в которую будем записывать смещение модуля
			CParSymbol* newSym		 = new CParSymbol( VAR_TYPE_INT );

			// получаем исходный юнит стека справа от оператора и хендлер
			CParStack*	 nextStack	 = (CParStack*)pStack->Next();
			CParHandler* nextHandler = nextStack->GetData();

			// вычисляем символ справа от оператора
			CParSymbol*	 nextSym	 = nextHandler->Execute();

			ASSERT_PATCH( nextSym->GetType() == VAR_TYPE_HEX, ".patch: MODULE_BASE принимает HEX строку" );

			MODULEINFO info;
			HANDLE  proc   = GetCurrentProcess();
			HMODULE module = GetModuleHandle( CString( (char*)nextSym->GetData(), nextSym->GetSize() ));
			GetModuleInformation( proc, module, &info, sizeof( MODULEINFO ));

			newSym->SetInt( (uint32)info.lpBaseOfDll );

			// присваиваем новой переменной данные правого символа
			//(*newSym) = (*nextSym);

			// удаляем правый символ и юнит
			// стека, они больше не пригодятся
			nextSym->Release();
			delete pStack->Next();

			// удаляем текущий оператор и 
			// заменяем его полученным символом
			pStack->pHandler->Release();
			pStack->pHandler = newSym;

			return newSym;
		}
		else if (sOperator == s_sOperators[30])
		{
			ASSERT_PATCH_ERROR( ".patch: Функция PRINT не может быть вызвана из выражения");
		}
		else if (sOperator == s_sOperators[31])
		{
			ASSERT_PATCH_ERROR( ".patch: Функция MESSAGE не может быть вызвана из выражения");
		}
		else if (sOperator == s_sOperators[32])
		{
			ASSERT_PATCH_ERROR( ".patch: Функция LOAD_LIBRARY не может быть вызвана из выражения");
		}

		ASSERT_PATCH_ERROR( ".patch: Отсутствует определение оператора '" + ((CParOperator*)pStack->GetData())->sOperator + "'" );
		return Null;
	}

	CParOperator* CParOperator::CreateOperator (const CString& str)
	{
		CParOperator* pOp = Null;
		for (uint32 i = 0; i < 32; i++)
		{
			if (str == s_sOperators[i])
			{
				pOp = new CParOperator();
				pOp->sOperator = str;
				break;
			}
		}
		return pOp;
	}

	void CParOperator::Print ()
	{
		cmd << sOperator;
	}

	CParOperator::~CParOperator ()
	{
		/*cmd << Col16(CMD_PURPLE | CMD_INTENSITY);
		cmd << "\t~OP: ";
		Print();
		cmd << endl;
		cmd << Col16();*/
	}
}