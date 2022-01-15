#pragma once

#define PATCH_INTERFACE_DECLARATION(className)										\
	protected:																		\
		CPatch_Symbol* CreateSymbol() { return (CPatch_Symbol*)(new className); };	\
		virtual CPatch_Type* Execute();												\
		static TPatch_SymDescriptor* pSymDescriptor;								\
	public:																			\
		className();																\
		virtual ~className();

#define PATCH_INTERFACE_DEFINITION(className)	\
	

namespace SystemPack
{
	class CPatch_Stack;
	class CPatch_Symbol;
	class CPatch_Type;


	typedef CPatch_Type* (* TAssociation) (const Common::CString&);
	typedef class CPatch_Type* (__cdecl * TExtOperator) (class CPatch_Type* left, class CPatch_Type* right);
	typedef CPatch_Type*(*TSymConstructor)();


	struct TOperatorCollection
	{
		TExtOperator operators[17]; // All operators without '!'
		TOperatorCollection()
		{
			ZeroMemory( this, sizeof(TOperatorCollection) );
		}
	};

	enum EValueType
	{
		SYM_TYPE_STACK,		// при этом значении место хранения данных выделяет парсер
		SYM_TYPE_POINTER,	// поинтер ссылается на участок данных в памяти
	};

	





	
	class TPatch_SymDescriptor
	{
		friend class CPatch_Type;
		friend class CPatch_Operator;
		friend class CPatch_Stack;

		static Common::CArray<TPatch_SymDescriptor*> arrSymDescriptors;

		Common::CString			sClassName;
		TSymConstructor	pSymConstructor;
	public:
		TPatch_SymDescriptor(const Common::CString& className, TSymConstructor func);
		
		static TPatch_SymDescriptor* Search(const Common::CString& className);

		CPatch_Type* CreateSymbol() { return pSymConstructor(); };
		Common::CString GetSymClassName()	{ return sClassName; };
	};











	class CPatch_Symbol
	{
	
		uint32 ulRef;

	protected:
				 CPatch_Symbol() { ulRef = 1; };
		virtual ~CPatch_Symbol() {  };
		
	public:
		void AddRef()  { ulRef++; };
		void Release() { if( --ulRef == 0 ) delete this; };

		virtual CPatch_Type* Execute()=0;
	};

	








	
	



	class CPatch_Type : public CPatch_Symbol
	{
	protected:
		static Common::CArray<CPatch_Type*>			arrVariables;
		static Common::CArray<TOperatorCollection*>	arrExternalOperators;
		static Common::CArray<TAssociation>			arrAssociations;

		Common::CString		sObjectName;
		EValueType	eValueType;
		Common::CString		sOptionName;

	public:
#pragma region VTable
		// дэфолтные операторы. можно "перегрузить" внешними функциями
		virtual CPatch_Type* operator =  (CPatch_Type* symbol)=0;

		virtual CPatch_Type* operator +  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator -  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator *  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator /  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator ^  (CPatch_Type* symbol)=0;

		virtual CPatch_Type* operator += (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator -= (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator *= (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator /= (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator ^= (CPatch_Type* symbol)=0;

		virtual CPatch_Type* operator !  ()=0;
		virtual CPatch_Type* operator == (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator != (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator <  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator <= (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator >  (CPatch_Type* symbol)=0;
		virtual CPatch_Type* operator >= (CPatch_Type* symbol)=0;

		virtual void ReadOption  ()=0;
		virtual void WriteOption ()=0;

		virtual uint32				  GetSizeof	    ()=0;
		virtual void32				  GetData	    ()=0;
		virtual Common::CString				  GetTypeName   ()=0;
		virtual TPatch_SymDescriptor& GetDescriptor ()=0;
		virtual CPatch_Type*		  Execute		()=0;
#pragma endregion

	public:
		static	CPatch_Type* CreateSymbol				(const Common::CString& symbol);
		static	CPatch_Type* CallExternalOperators		(const uint32& index, CPatch_Type* left, CPatch_Type* right);
		static	void		DefineExternalOperators		(TOperatorCollection* collection);
		static	void		DefineExternalAssociation	(TAssociation association);

		virtual void		SetPointer	  (const uint32& address)=0;
				void		SetObjectName (const Common::CString& objName);
				void		SetOptionName (const Common::CString& optName);
				Common::CString		GetObjectName ();
				Common::CString		GetOptionName ();
				EValueType	GetValueType  ();

		virtual ~CPatch_Type();
	};



	class CPatch_Function : public CPatch_Symbol
	{
		CPatch_Stack* pInStack;
		PATCH_INTERFACE_DECLARATION(CPatch_Function)
	public:
		static CPatch_Symbol* CreateSymbol(const Common::CString& funcName);
		void CreateParameters(const Common::CString& parms);

	};



	class CPatch_Operator
	{
		CPatch_Stack* pInStack;
		PATCH_INTERFACE_DECLARATION(CPatch_Operator)

		Common::CString sOperator;
	public:
		static CPatch_Symbol* CreateSymbol(const Common::CString& name);
		Common::CString GetName();
		void SetName(const Common::CString& name);
	};
}

#include "Types.h"