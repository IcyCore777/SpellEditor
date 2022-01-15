#pragma once
#pragma warning(disable:4251)

namespace SystemPack
{
#define PATCH_TYPE_DELARATE( className )		\
	COBJECT_CLASS_DELARATE( className );		\
public:											\
	static TTypeDescriptor mTypeDescriptor;

#define PATCH_TYPE_DEFINE( className, typeName )\
	COBJECT_CLASS_DEFINE( className );			\
	TTypeDescriptor className::mTypeDescriptor = TTypeDescriptor(typeName, className::GetClassDef_Class());


#define PATCH_CLASS_CID( className )	\
	&className::mTypeDescriptor

#define PATCH_TYPE_CID( obj )	\
	&obj->GetDescriptor()


	typedef class CPatch_Symbol* (__cdecl * TExtOperator) (class CPatch_Symbol* left, class CPatch_Symbol* right);


	enum EValueType
	{
		SYM_TYPE_STACK,		// при этом значении место хранения данных выделяет парсер
		SYM_TYPE_POINTER,	// поинтер ссылается на участок данных в памяти
	};


	struct ASTAPI TTypeDescriptor
	{
		static Common::CArray<TTypeDescriptor*> arrSymbolDescriptors;

		Common::CString		sName;
		CClassDef*	pClassDef;

		TTypeDescriptor(const Common::CString& name, CClassDef* cdef);
		static TTypeDescriptor* GetByName(const Common::CString& name);
		static TTypeDescriptor* GetByClassDef(CClassDef* cdef);
	};

	class ASTAPI CPatch_Symbol : public Common::CObject
	{
		friend class CPatch_Function;

	public:

		struct TOperatorCollection
		{
			TExtOperator operators[17]; // All operators without '!'
			TOperatorCollection()
			{
				ZeroMemory( this, sizeof(TOperatorCollection) );
			}
		};
		typedef CPatch_Symbol* (* TAssociation) (const Common::CString&);

	protected:

		static Common::CArray<TOperatorCollection*>	arrExternalOperators;
		static Common::CArray<TAssociation>			arrAssociations;
		static Common::CArray<CPatch_Symbol*>		arrSymbols;

		Common::CString		sObjectName;
		EValueType	eValueType;
		Common::CString		sOptionName;

		CPatch_Symbol ();

	public:
#pragma region VTable
		virtual uint32			 GetSizeof	   ()=0;
		virtual void32			 GetData	   ()=0;
		virtual Common::CString			 GetTypeName   ()=0;
		virtual TTypeDescriptor& GetDescriptor ()=0;

		// дэфолтные операторы. можно "перегрузить" внешними функциями
		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol)=0;

		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol)=0;

		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol)=0;

		virtual CPatch_Symbol* operator !  ()=0;
		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol)=0;
		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol)=0;

		virtual void ReadOption  ()=0;
		virtual void WriteOption ()=0;
		virtual void SetPointer (const uint32& address)=0;
#pragma endregion
		void SetOption (const Common::CString& optName);
		void SetObjectName (const Common::CString& name);
		
		Common::CString GetObjectName ();

		static CPatch_Symbol* CreateSymbol				(const Common::CString& association);
		static CPatch_Symbol* CallExternalOperators		(const uint32& index, CPatch_Symbol* left, CPatch_Symbol* right);
		static void			  DefineExternalOperators	(TOperatorCollection* collection);
		static void			  DefineExternalAssociation	(TAssociation association);
		static void			  DefineType				(const Common::CString& name, CClassDef* cid);

		virtual ~CPatch_Symbol();
	};





	class ASTAPI CPatch_Operator : public Common::CObject
	{
		Common::CString sOperator;

		CPatch_Operator();

		COBJECT_CLASS_DELARATE( CPatch_Operator );
		virtual void Archive	(CArchiver&) { };
		virtual void Unarchive  (CArchiver&) { };

	public:

		CPatch_Operator(const Common::CString& name);

		static CPatch_Operator* CreateOperator (const Common::CString& name);
		Common::CString GetOperatorName();

		virtual ~CPatch_Operator();
	};





	class ASTAPI CPatch_Integer : public CPatch_Symbol
	{
		int32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator !  ();
		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_TYPE_DELARATE( CPatch_Integer );

	public:

		CPatch_Integer (); // stack
		CPatch_Integer (const uint32& value); // pointer

		virtual void			 Archive	   (CArchiver&) { };
		virtual void			 Unarchive	   (CArchiver&) { };
		virtual uint32			 GetSizeof	   ();
		virtual void32			 GetData	   ();
		virtual Common::CString			 GetTypeName   ();
		virtual TTypeDescriptor& GetDescriptor ();

		void  SetValue (const int32& val);
		int32 GetValue ();

		virtual ~CPatch_Integer ();
	};





	class ASTAPI CPatch_Float : public CPatch_Symbol
	{
		real32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator !  ();
		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_TYPE_DELARATE( CPatch_Float );

	public:

		CPatch_Float (); // stack
		CPatch_Float (const uint32& value); // pointer

		virtual void			 Archive	   (CArchiver&) { };
		virtual void			 Unarchive	   (CArchiver&) { };
		virtual uint32			 GetSizeof	   ();
		virtual void32			 GetData	   ();
		virtual Common::CString			 GetTypeName   ();
		virtual TTypeDescriptor& GetDescriptor ();

		void   SetValue (const real32& val);
		real32 GetValue ();

		virtual ~CPatch_Float ();
	};





	class ASTAPI CPatch_Hex : public CPatch_Symbol
	{
		void32 pValue;
		uint32 ulSize;

	public:

#pragma region VTable
		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator !  ();
		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer (const uint32& address);
#pragma endregion

		PATCH_TYPE_DELARATE( CPatch_Hex );

	public:

		CPatch_Hex (); // stack
		CPatch_Hex (const uint32& value); // pointer

		virtual void			 Archive	   (CArchiver&) { };
		virtual void			 Unarchive	   (CArchiver&) { };
		virtual uint32			 GetSizeof	   ();
		virtual void32			 GetData	   ();
		virtual Common::CString			 GetTypeName   ();
		virtual TTypeDescriptor& GetDescriptor ();

		void   SetValue (const void32 val, const uint32& size);
		void32 GetValue ();
		void   SetSizeof(const uint32& size);
		void32 GetCopy	();

		virtual ~CPatch_Hex ();
	};





	class ASTAPI CPatch_Bool : public CPatch_Symbol
	{
		bool32* pValue;

	public:

#pragma region VTable
		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol);

		virtual CPatch_Symbol* operator !  ();
		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol);
		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol);

		virtual void ReadOption  ();
		virtual void WriteOption ();
		virtual void SetPointer  (const uint32& address);
#pragma endregion

		PATCH_TYPE_DELARATE( CPatch_Bool );

	public:

		CPatch_Bool (); // stack
		CPatch_Bool (const uint32& value); // pointer

		virtual void			 Archive	   (CArchiver&) { };
		virtual void			 Unarchive	   (CArchiver&) { };
		virtual uint32			 GetSizeof	   ();
		virtual void32			 GetData	   ();
		virtual Common::CString			 GetTypeName   ();
		virtual TTypeDescriptor& GetDescriptor ();

		void   SetValue (const bool32& val);
		bool32 GetValue ();

		virtual ~CPatch_Bool ();
	};



	

//	class ASTAPI CPatch_Hex : public CPatch_Symbol
//	{
//		void32 pMemory;
//		uint32 ulRelativeSize;
//
//	public:
//
//#pragma region VTable
//		virtual CPatch_Symbol* operator =  (CPatch_Symbol* symbol);
//
//		virtual CPatch_Symbol* operator +  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator -  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator *  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator /  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator ^  (CPatch_Symbol* symbol);
//
//		virtual CPatch_Symbol* operator += (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator -= (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator *= (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator /= (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator ^= (CPatch_Symbol* symbol);
//
//		virtual CPatch_Symbol* operator !  ();
//		virtual CPatch_Symbol* operator == (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator != (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator <  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator <= (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator >  (CPatch_Symbol* symbol);
//		virtual CPatch_Symbol* operator >= (CPatch_Symbol* symbol);
//#pragma endregion
//
//		PATCH_TYPE_DELARATE( CPatch_Hex );
//
//	public:
//
//		CPatch_Hex (); // stack
//		CPatch_Hex (const uint32& value); // pointer
//
//		virtual void			 Archive	   (CArchiver&) { };
//		virtual void			 Unarchive	   (CArchiver&) { };
//		virtual uint32			 GetSizeof	   ();
//		virtual void32			 GetData	   ();
//		virtual Common::CString			 GetName	   ();
//		virtual TTypeDescriptor& GetDescriptor ();
//
//		void   SetValue (const void32& val, const uint32& size);
//		void32 GetValue ();
//		uint32 GetSize	(const uint32& size);
//
//		~CPatch_Hex ();
//	};
}