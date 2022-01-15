#include <UnionAfx.h>



namespace SystemPack
{
	CPatch_Symbol::~CPatch_Symbol ()
	{
		
	}
}





namespace SystemPack
{
	COBJECT_CLASS_DEFINE( CPatch_Integer );

	uint32 CPatch_Integer::GetSizeof ()
	{
		return sizeof( int32 );
	}

	void32 CPatch_Integer::GetData ()
	{
		return &nValue;
	}

#pragma region VTable

		CPatch_Symbol* CPatch_Integer::operator +  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator -  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator *  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator /  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator ^  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator += (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator -= (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator *= (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator /= (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator ^= (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator !  ()
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator == (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator != (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator <  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator <= (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator >  (CPatch_Symbol* symbol)
		{
			return Null;
		}

		CPatch_Symbol* CPatch_Integer::operator >= (CPatch_Symbol* symbol)
		{
			return Null;
		}

#pragma endregion

	void CPatch_Integer::SetValue (const int32& val)
	{
		nValue = val;
	}

	int32 CPatch_Integer::GetValue ()
	{
		return nValue;
	}
}