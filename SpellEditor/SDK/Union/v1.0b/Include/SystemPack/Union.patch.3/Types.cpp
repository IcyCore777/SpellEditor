#include <UnionAfx.h>

namespace SystemPack
{
	static int32 pow( int32 _val, int32 _pow )
	{
		if( _pow == 0 )
			return 1;

		int32 newVal = _val;
		for (int32 i = 1; i < _pow; i++)
		{
			newVal *= _val;
		}
		return newVal;
	}
}


using namespace UnionFilters;




namespace SystemPack
{
	struct TMemUnlocker
	{
		void32* ulAddress;
		ulong32 ulSize, ulOldRoot;
		TMemUnlocker( void32* address, const uint32& size, const bool32& condition )
		{
			if( condition && address && size )
			{
				ulAddress = address;
				ulSize	  = size;
				ulOldRoot = VirtualProtect (*ulAddress, ulSize, PAGE_EXECUTE_READWRITE, &ulOldRoot);
			}
			else
			{
				ulAddress = Null;
				ulSize	  = 0;
			}
			//Say::Box( "Unlock" );
		}
		~TMemUnlocker()
		{
			if( ulAddress )
				VirtualProtect (*ulAddress, ulSize, ulOldRoot, &ulOldRoot);

			//Say::Box( "Lock" );
		}
	};
}





namespace SystemPack
{
	PATCH_INTERFACE_DEFINITION( CPatch_Integer, "int" );

	CPatch_Integer::CPatch_Integer ()
	{
		pValue = new int32;
		eValueType = SYM_TYPE_STACK;
	}

	CPatch_Integer::CPatch_Integer (const uint32& address)
	{
		pValue = (int32*)address;
		eValueType = SYM_TYPE_POINTER;
	}

	CPatch_Integer::~CPatch_Integer ()
	{
		if( eValueType == SYM_TYPE_STACK )
		{
			delete pValue;
		}
	}

	uint32 CPatch_Integer::GetSizeof ()
	{
		return sizeof( int32 );
	}

	void32 CPatch_Integer::GetData ()
	{
		return pValue;
	}

#pragma region VTable

		CPatch_Type* CPatch_Integer::operator = (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( (int32)symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 0, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator +  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() + symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() + (int32)symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 1, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator -  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() - symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() - symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 2, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator *  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() * symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() * symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 3, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator /  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() / symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() / symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 4, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator ^ (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( pow( GetValue(), symInt->GetValue() ));
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( pow( (real32)GetValue(), symFloat->GetValue() ));
					return resultInt;
				}
			}
			return CallExternalOperators( 5, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator += (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() + symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() + symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 6, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator -= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() - symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() - symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 7, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator *= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() * symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() * symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 8, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator /= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() / symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() / symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 9, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator ^= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( pow( GetValue(), symInt->GetValue() ));
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( pow( GetValue(), (int32)symFloat->GetValue() ));
					return this;
				}
			}
			return CallExternalOperators( 10, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator ! ()
		{
			CPatch_Bool* resultInt = new CPatch_Bool;
			resultInt->SetValue( GetValue() != 0 ? FALSE : TRUE );
			return resultInt;
		}

		CPatch_Type* CPatch_Integer::operator == (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() == symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() == symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 11, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator != (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() != symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() != symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 12, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator <  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() < symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() < symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 13, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator <= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() <= symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() <= symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 14, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator >  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() > symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() > symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 15, this, symbol );
		}

		CPatch_Type* CPatch_Integer::operator >= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() >= symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() >= symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 16, this, symbol );
		}

		void CPatch_Integer::ReadOption ()
		{
		
		}

		void CPatch_Integer::WriteOption ()
		{
			
		}

		void CPatch_Integer::SetPointer (const uint32& address)
		{
			//Say::Box( "SetPointer " + A address );
			if( pValue )
			{
				delete pValue;
			}
			pValue = (int32*)address;
			eValueType = SYM_TYPE_POINTER;
		}

#pragma endregion

	void CPatch_Integer::SetValue (const int32& val)
	{
		TMemUnlocker unlocker( (void32*)&pValue, GetSizeof(), eValueType == SYM_TYPE_POINTER );
		memcpy( pValue, &val, 4 );
	}

	int32 CPatch_Integer::GetValue ()
	{
		return *pValue;
	}

	Common::CString CPatch_Integer::GetTypeName()
	{
		return pSymDescriptor->GetSymClassName();
	}
}









namespace SystemPack
{
	PATCH_INTERFACE_DEFINITION( CPatch_Float, "float" );

	CPatch_Float::CPatch_Float ()
	{
		pValue = new real32;
		eValueType = SYM_TYPE_STACK;
	}

	CPatch_Float::CPatch_Float (const uint32& address)
	{
		pValue = (real32*)address;
		eValueType = SYM_TYPE_POINTER;
	}

	CPatch_Float::~CPatch_Float ()
	{
		if( eValueType == SYM_TYPE_STACK )
		{
			delete pValue;
		}
	}

	uint32 CPatch_Float::GetSizeof ()
	{
		return sizeof( real32 );
	}

	void32 CPatch_Float::GetData ()
	{
		return pValue;
	}

#pragma region VTable

		CPatch_Type* CPatch_Float::operator = (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 0, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator +  (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() + symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Float* resultFloat = new CPatch_Float;
					resultFloat->SetValue( GetValue() + symFloat->GetValue() );
					return resultFloat;
				}
			}
			return CallExternalOperators( 1, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator -  (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() - symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Float* resultFloat = new CPatch_Float;
					resultFloat->SetValue( GetValue() - symFloat->GetValue() );
					return resultFloat;
				}
			}
			return CallExternalOperators( 2, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator *  (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() * symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Float* resultFloat = new CPatch_Float;
					resultFloat->SetValue( GetValue() * symFloat->GetValue() );
					return resultFloat;
				}
			}
			return CallExternalOperators( 3, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator /  (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( GetValue() / symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Float* resultFloat = new CPatch_Float;
					resultFloat->SetValue( GetValue() / symFloat->GetValue() );
					return resultFloat;
				}
			}
			return CallExternalOperators( 4, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator ^ (CPatch_Type* symbol)
		{
			// Int
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Integer* resultInt = new CPatch_Integer;
					resultInt->SetValue( pow( GetValue(), symInt->GetValue() ));
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Float* resultFloat = new CPatch_Float;
					resultFloat->SetValue( pow( GetValue(), symFloat->GetValue() ));
					return resultFloat;
				}
			}
			return CallExternalOperators( 5, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator += (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() + symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() + symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 6, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator -= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() - symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() - symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 7, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator *= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() * symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() * symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 8, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator /= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( GetValue() / symInt->GetValue() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( GetValue() / symFloat->GetValue() );
					return this;
				}
			}
			return CallExternalOperators( 9, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator ^= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( pow( GetValue(), symInt->GetValue() ));
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( pow( GetValue(), symFloat->GetValue() ));
					return this;
				}
			}
			return CallExternalOperators( 10, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator ! ()
		{
			CPatch_Bool* resultInt = new CPatch_Bool;
			resultInt->SetValue( GetValue() != 0.0f ? FALSE : TRUE );
			return resultInt;
		}

		CPatch_Type* CPatch_Float::operator == (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() == symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() == symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 11, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator != (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() != symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() != symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 12, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator <  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() < symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() < symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 13, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator <= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() <= symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() <= symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 14, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator >  (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() > symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() > symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 15, this, symbol );
		}

		CPatch_Type* CPatch_Float::operator >= (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() >= symInt->GetValue() );
					return resultInt;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					CPatch_Bool* resultInt = new CPatch_Bool;
					resultInt->SetValue( GetValue() >= symFloat->GetValue() );
					return resultInt;
				}
			}
			return CallExternalOperators( 16, this, symbol );
		}

		void CPatch_Float::ReadOption ()
		{
		
		}

		void CPatch_Float::WriteOption ()
		{
			
		}

		void CPatch_Float::SetPointer (const uint32& address)
		{
			if( pValue )
			{
				delete pValue;
			}
			pValue = (real32*)address;
			eValueType = SYM_TYPE_POINTER;
		}

#pragma endregion

	void CPatch_Float::SetValue (const real32& val)
	{
		(*pValue) = val;
	}

	real32 CPatch_Float::GetValue ()
	{
		return *pValue;
	}

	Common::CString CPatch_Float::GetTypeName()
	{
		return pSymDescriptor->GetSymClassName();
	}
}








namespace SystemPack
{
	PATCH_INTERFACE_DEFINITION( CPatch_Hex, "hex" );

	CPatch_Hex::CPatch_Hex ()
	{
		pValue = shi_malloc( 0 );
		ulSize = 0;
		eValueType = SYM_TYPE_STACK;
	}

	CPatch_Hex::CPatch_Hex (const uint32& value)
	{
		ulSize = 0;
		eValueType = SYM_TYPE_POINTER;
	}

	CPatch_Hex::~CPatch_Hex ()
	{
		if( eValueType == SYM_TYPE_STACK )
		{
			shi_free( pValue );
		}
	}

#pragma region VTable

		CPatch_Type* CPatch_Hex::operator = (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue ( symInt->GetData(), symInt->GetSizeof() );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue ( symFloat->GetData(), symFloat->GetSizeof() );
					return this;
				}
			}
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					SetValue ( symHex->GetData(), symHex->GetSizeof() );
					return this;
				}
			}
			return CallExternalOperators( 0, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator + (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Hex*	resultHex = new CPatch_Hex;
					Common::CString		sLeft  ( (char*)		GetData(),		   GetSizeof() );
					Common::CString		sRight ( (char*)symHex->GetData(), symHex->GetSizeof() );

					sLeft += sRight;

					resultHex->SetValue( (void32)sLeft.GetVector(), sLeft.Length() );
					return resultHex;
				}
			}
			return CallExternalOperators( 1, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator -  (CPatch_Type* symbol)
		{

			return CallExternalOperators( 2, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator *  (CPatch_Type* symbol)
		{

			return CallExternalOperators( 3, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator /  (CPatch_Type* symbol)
		{

			return CallExternalOperators( 4, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator ^ (CPatch_Type* symbol)
		{

			return CallExternalOperators( 5, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator += (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					Common::CString		sLeft  ( (char*)		GetData(),		   GetSizeof() );
					Common::CString		sRight ( (char*)symHex->GetData(), symHex->GetSizeof() );

					sLeft += sRight;

					SetValue( (void32)sLeft.GetVector(), sLeft.Length() );
					return this;
				}
			}
			return CallExternalOperators( 6, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator -= (CPatch_Type* symbol)
		{

			return CallExternalOperators( 7, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator *= (CPatch_Type* symbol)
		{

			return CallExternalOperators( 8, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator /= (CPatch_Type* symbol)
		{

			return CallExternalOperators( 9, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator ^= (CPatch_Type* symbol)
		{

			return CallExternalOperators( 10, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator ! ()
		{

			return 0;
		}

		CPatch_Type* CPatch_Hex::operator == (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					Common::CString		sLeft  ( (char*)		GetData(),		   GetSizeof() );
					Common::CString		sRight ( (char*)symHex->GetData(), symHex->GetSizeof() );

					resultInteger->SetValue( sLeft.Compare(sRight) );
					return resultInteger;
				}
			}
			return CallExternalOperators( 11, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator != (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					Common::CString		sLeft  ( (char*)		GetData(),		   GetSizeof() );
					Common::CString		sRight ( (char*)symHex->GetData(), symHex->GetSizeof() );

					resultInteger->SetValue( sLeft.Compare(sRight) );
					return resultInteger;
				}
			}
			return CallExternalOperators( 12, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator <  (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					bool32 bCmp = memcmp( GetData(), symHex->GetData(), min(GetSizeof(), symHex->GetSizeof()) );

					resultInteger->SetValue( bCmp < 0 );
					return resultInteger;
				}
			}
			return CallExternalOperators( 13, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator <= (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					bool32 bCmp = memcmp( GetData(), symHex->GetData(), min(GetSizeof(), symHex->GetSizeof()) );

					resultInteger->SetValue( bCmp <= 0 );
					return resultInteger;
				}
			}
			return CallExternalOperators( 14, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator >  (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					bool32 bCmp = memcmp( GetData(), symHex->GetData(), min(GetSizeof(), symHex->GetSizeof()) );

					resultInteger->SetValue( bCmp > 0 );
					return resultInteger;
				}
			}
			return CallExternalOperators( 15, this, symbol );
		}

		CPatch_Type* CPatch_Hex::operator >= (CPatch_Type* symbol)
		{
			// Hex
			{
				CPatch_Hex* symHex = dynamic_cast<CPatch_Hex*>( symbol );
				if( symHex )
				{
					CPatch_Bool*	resultInteger = new CPatch_Bool;
					bool32 bCmp = memcmp( GetData(), symHex->GetData(), min(GetSizeof(), symHex->GetSizeof()) );

					resultInteger->SetValue( bCmp >= 0 );
					return resultInteger;
				}
			}
			return CallExternalOperators( 16, this, symbol );
		}

		void CPatch_Hex::ReadOption ()
		{
		
		}

		void CPatch_Hex::WriteOption ()
		{
			
		}

		void CPatch_Hex::SetPointer (const uint32& address)
		{
			Say::Box( "SetPointer " + A address );
			if( pValue )
			{
				delete pValue;
			}
			pValue = (int32*)address;
			eValueType = SYM_TYPE_POINTER;
		}

#pragma endregion

		uint32 CPatch_Hex::GetSizeof ()
		{
			return ulSize;
		}

		void32 CPatch_Hex::GetData ()
		{
			return pValue;
		}

		Common::CString CPatch_Hex::GetTypeName ()
		{
			return pSymDescriptor->GetSymClassName();
		}

		void CPatch_Hex::SetValue (const void32 val, const uint32& size)
		{
			TMemUnlocker unlocker( (void32*)&pValue, GetSizeof(), eValueType == SYM_TYPE_POINTER );

			SetSizeof( size );
			memcpy( GetData(), val, size );
		}

		void32 CPatch_Hex::GetValue ()
		{
			return pValue;
		}

		void CPatch_Hex::SetSizeof (const uint32& size)
		{
			ulSize = size;
			if( eValueType == SYM_TYPE_STACK )
			{
				pValue = shi_realloc( pValue, size );
			}
		}

		void32 CPatch_Hex::GetCopy ()
		{
			void32 pCopy = shi_malloc( ulSize );
			memcpy( pCopy, pValue, ulSize );
			return pCopy;
		}


}















namespace SystemPack
{
	PATCH_INTERFACE_DEFINITION( CPatch_Bool, "bool" );

	CPatch_Bool::CPatch_Bool ()
	{
		pValue = new bool32;
		eValueType = SYM_TYPE_STACK;
	}

	CPatch_Bool::CPatch_Bool (const uint32& address)
	{
		pValue = (bool32*)address;
		eValueType = SYM_TYPE_POINTER;
	}

	CPatch_Bool::~CPatch_Bool ()
	{
		if( eValueType == SYM_TYPE_STACK )
		{
			delete pValue;
		}
	}

	uint32 CPatch_Bool::GetSizeof ()
	{
		return sizeof( int32 );
	}

	void32 CPatch_Bool::GetData ()
	{
		return pValue;
	}

#pragma region VTable

		CPatch_Type* CPatch_Bool::operator = (CPatch_Type* symbol)
		{
			// Integer
			{
				CPatch_Integer* symInt = dynamic_cast<CPatch_Integer*>( symbol );
				if( symInt )
				{
					SetValue( symInt->GetValue() != 0 );
					return this;
				}
			}
			// Float
			{
				CPatch_Float* symFloat = dynamic_cast<CPatch_Float*>( symbol );
				if( symFloat )
				{
					SetValue( symFloat->GetValue() != 0.0f );
					return this;
				}
			}
			return CallExternalOperators( 0, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator +  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 1, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator -  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 2, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator *  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 3, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator /  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 4, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator ^ (CPatch_Type* symbol)
		{
			return CallExternalOperators( 5, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator += (CPatch_Type* symbol)
		{
			return CallExternalOperators( 6, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator -= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 7, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator *= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 8, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator /= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 9, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator ^= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 10, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator ! ()
		{
			CPatch_Bool* resultInt = new CPatch_Bool;
			resultInt->SetValue( GetValue() != 0 ? FALSE : TRUE );
			return resultInt;
		}

		CPatch_Type* CPatch_Bool::operator == (CPatch_Type* symbol)
		{
			{
				CPatch_Bool symBool;
				bool32 symIsConverted = (bool32)(symBool = symbol);
				if( symIsConverted )
				{
					CPatch_Bool* symResult = new CPatch_Bool;
					symResult->SetValue( GetValue() == symBool.GetValue() );
					return symResult;
				}
			}
			return CallExternalOperators( 11, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator != (CPatch_Type* symbol)
		{
			{
				CPatch_Bool symBool;
				bool32 symIsConverted = (bool32)(symBool = symbol);
				if( symIsConverted )
				{
					CPatch_Bool* symResult = new CPatch_Bool;
					symResult->SetValue( GetValue() != symBool.GetValue() );
					return symResult;
				}
			}
			return CallExternalOperators( 12, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator <  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 13, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator <= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 14, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator >  (CPatch_Type* symbol)
		{
			return CallExternalOperators( 15, this, symbol );
		}

		CPatch_Type* CPatch_Bool::operator >= (CPatch_Type* symbol)
		{
			return CallExternalOperators( 16, this, symbol );
		}

		void CPatch_Bool::ReadOption ()
		{
			
		}

		void CPatch_Bool::WriteOption ()
		{
			
		}

		void CPatch_Bool::SetPointer (const uint32& address)
		{
			if( pValue )
			{
				delete pValue;
			}
			pValue = (bool32*)address;
			eValueType = SYM_TYPE_POINTER;
		}

#pragma endregion

	void CPatch_Bool::SetValue (const bool32& val)
	{
		TMemUnlocker unlocker( (void32*)&pValue, GetSizeof(), eValueType == SYM_TYPE_POINTER );
		memcpy( pValue, &val, 4 );
	}

	bool32 CPatch_Bool::GetValue ()
	{
		return *pValue;
	}

	Common::CString CPatch_Bool::GetTypeName()
	{
		return pSymDescriptor->GetSymClassName();
	}
}