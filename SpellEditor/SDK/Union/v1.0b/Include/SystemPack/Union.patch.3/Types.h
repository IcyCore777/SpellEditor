#pragma once












namespace SystemPack
{
	class ASTAPI CPatch_Integer : public CPatch_Type
	{
		int32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Type* operator =  (CPatch_Type* symbol);

		virtual CPatch_Type* operator +  (CPatch_Type* symbol);
		virtual CPatch_Type* operator -  (CPatch_Type* symbol);
		virtual CPatch_Type* operator *  (CPatch_Type* symbol);
		virtual CPatch_Type* operator /  (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^  (CPatch_Type* symbol);

		virtual CPatch_Type* operator += (CPatch_Type* symbol);
		virtual CPatch_Type* operator -= (CPatch_Type* symbol);
		virtual CPatch_Type* operator *= (CPatch_Type* symbol);
		virtual CPatch_Type* operator /= (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^= (CPatch_Type* symbol);

		virtual CPatch_Type* operator !  ();
		virtual CPatch_Type* operator == (CPatch_Type* symbol);
		virtual CPatch_Type* operator != (CPatch_Type* symbol);
		virtual CPatch_Type* operator <  (CPatch_Type* symbol);
		virtual CPatch_Type* operator <= (CPatch_Type* symbol);
		virtual CPatch_Type* operator >  (CPatch_Type* symbol);
		virtual CPatch_Type* operator >= (CPatch_Type* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_INTERFACE_DECLARATION( CPatch_Integer );

	public:

		CPatch_Integer (const uint32& value); // pointer

		virtual uint32					GetSizeof		();
		virtual void32					GetData			();
		virtual Common::CString					GetTypeName		();
		virtual TPatch_SymDescriptor&	GetDescriptor	();

		void  SetValue (const int32& val);
		int32 GetValue ();

	};





	class ASTAPI CPatch_Float : public CPatch_Type
	{
		real32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Type* operator =  (CPatch_Type* symbol);

		virtual CPatch_Type* operator +  (CPatch_Type* symbol);
		virtual CPatch_Type* operator -  (CPatch_Type* symbol);
		virtual CPatch_Type* operator *  (CPatch_Type* symbol);
		virtual CPatch_Type* operator /  (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^  (CPatch_Type* symbol);

		virtual CPatch_Type* operator += (CPatch_Type* symbol);
		virtual CPatch_Type* operator -= (CPatch_Type* symbol);
		virtual CPatch_Type* operator *= (CPatch_Type* symbol);
		virtual CPatch_Type* operator /= (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^= (CPatch_Type* symbol);

		virtual CPatch_Type* operator !  ();
		virtual CPatch_Type* operator == (CPatch_Type* symbol);
		virtual CPatch_Type* operator != (CPatch_Type* symbol);
		virtual CPatch_Type* operator <  (CPatch_Type* symbol);
		virtual CPatch_Type* operator <= (CPatch_Type* symbol);
		virtual CPatch_Type* operator >  (CPatch_Type* symbol);
		virtual CPatch_Type* operator >= (CPatch_Type* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_INTERFACE_DECLARATION( CPatch_Float );

	public:

		CPatch_Float (const uint32& value); // pointer

		virtual uint32					GetSizeof		();
		virtual void32					GetData			();
		virtual Common::CString					GetTypeName		();
		virtual TPatch_SymDescriptor&	GetDescriptor	();

		void   SetValue (const real32& val);
		real32 GetValue ();

	};





	class ASTAPI CPatch_Hex : public CPatch_Type
	{
		void32 pValue;
		uint32 ulSize;

	public:

#pragma region VTable
		virtual CPatch_Type* operator =  (CPatch_Type* symbol);

		virtual CPatch_Type* operator +  (CPatch_Type* symbol);
		virtual CPatch_Type* operator -  (CPatch_Type* symbol);
		virtual CPatch_Type* operator *  (CPatch_Type* symbol);
		virtual CPatch_Type* operator /  (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^  (CPatch_Type* symbol);

		virtual CPatch_Type* operator += (CPatch_Type* symbol);
		virtual CPatch_Type* operator -= (CPatch_Type* symbol);
		virtual CPatch_Type* operator *= (CPatch_Type* symbol);
		virtual CPatch_Type* operator /= (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^= (CPatch_Type* symbol);

		virtual CPatch_Type* operator !  ();
		virtual CPatch_Type* operator == (CPatch_Type* symbol);
		virtual CPatch_Type* operator != (CPatch_Type* symbol);
		virtual CPatch_Type* operator <  (CPatch_Type* symbol);
		virtual CPatch_Type* operator <= (CPatch_Type* symbol);
		virtual CPatch_Type* operator >  (CPatch_Type* symbol);
		virtual CPatch_Type* operator >= (CPatch_Type* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_INTERFACE_DECLARATION( CPatch_Hex );

	public:

		CPatch_Hex (const uint32& value); // pointer

		virtual uint32					GetSizeof		();
		virtual void32					GetData			();
		virtual Common::CString					GetTypeName		();
		virtual TPatch_SymDescriptor&	GetDescriptor	();

		void   SetValue (const void32 val, const uint32& size);
		void32 GetValue ();
		void   SetSizeof(const uint32& size);
		void32 GetCopy	();

	};





	class ASTAPI CPatch_Bool : public CPatch_Type
	{
		bool32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Type* operator =  (CPatch_Type* symbol);

		virtual CPatch_Type* operator +  (CPatch_Type* symbol);
		virtual CPatch_Type* operator -  (CPatch_Type* symbol);
		virtual CPatch_Type* operator *  (CPatch_Type* symbol);
		virtual CPatch_Type* operator /  (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^  (CPatch_Type* symbol);

		virtual CPatch_Type* operator += (CPatch_Type* symbol);
		virtual CPatch_Type* operator -= (CPatch_Type* symbol);
		virtual CPatch_Type* operator *= (CPatch_Type* symbol);
		virtual CPatch_Type* operator /= (CPatch_Type* symbol);
		virtual CPatch_Type* operator ^= (CPatch_Type* symbol);

		virtual CPatch_Type* operator !  ();
		virtual CPatch_Type* operator == (CPatch_Type* symbol);
		virtual CPatch_Type* operator != (CPatch_Type* symbol);
		virtual CPatch_Type* operator <  (CPatch_Type* symbol);
		virtual CPatch_Type* operator <= (CPatch_Type* symbol);
		virtual CPatch_Type* operator >  (CPatch_Type* symbol);
		virtual CPatch_Type* operator >= (CPatch_Type* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer  (const uint32& address);
#pragma endregion

		PATCH_INTERFACE_DECLARATION( CPatch_Bool );

	public:

		CPatch_Bool (const uint32& value); // pointer

		virtual uint32					GetSizeof		();
		virtual void32					GetData			();
		virtual Common::CString					GetTypeName		();
		virtual TPatch_SymDescriptor&	GetDescriptor	();

		void   SetValue (const bool32& val);
		bool32 GetValue ();

	};
}