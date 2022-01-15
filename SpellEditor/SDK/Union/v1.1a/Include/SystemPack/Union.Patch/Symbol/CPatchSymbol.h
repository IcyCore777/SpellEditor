#pragma once

namespace SystemPack
{
	enum ESymType
	{
		SYM_TYPE_UNKNOWN,
		SYM_TYPE_STACK,
		SYM_TYPE_POINTER
	};

	class CPatchType;
	class ASTAPI CPatchSymbol
	{
		friend class CPatchOperator;

	protected:
		uint32 ulRef;
		CPatchSymbol();
	public:
		static CPatchSymbol* CreateSymbol(const CString& str);

				void		AddRef ();
				void		Release();
		virtual	CPatchType*	Execute()=0;
		virtual	CString		GetSymbolName()=0;
		virtual ~CPatchSymbol();
	};
}



namespace SystemPack
{
	typedef CPatchSymbol*(*TObjectCreator)();
	class ASTAPI TSymBuilder
	{
		friend class CPatchSymbol;
		friend class CPatchOperator;
		friend class CPatchFunction;
		friend class CPatchStack;

		static CArray<TSymBuilder*> arrBuilders;

		CString			sClassName;
		CString			sSynonym;
		TObjectCreator	pFunction;
	public:
						TSymBuilder	(const CString& className, const CString& synonym, TObjectCreator func);
		CPatchSymbol*	CreateSymbol();
		CString			GetClass();
		CString			GetSynonym();

		static TSymBuilder*	GetByClassName	(const CString& className);
		static TSymBuilder* GetBySynonym	(const CString& synonym);
		static CString		GetSymbolType	(const CString& synonym);
	};
}



#define PATCH_CLASS_DECLARATION(className)			\
public:												\
			 className();							\
	virtual ~className();							\
	static	 CPatchSymbol* CreateObject();			\
	static	 TSymBuilder mSymBuilder;				\
	virtual	 CString	 GetSymbolName();


#define PATCH_CLASS_DEFINITION(className, synonym)	\
	CPatchSymbol* className::CreateObject()			\
	{												\
		return new className;						\
	}												\
	CString	className::GetSymbolName()				\
	{												\
		return mSymBuilder.GetSynonym();			\
	}												\
	TSymBuilder className::mSymBuilder(#className, synonym, className::CreateObject);



#include "Type\CPatchType.h"
#include "Operator\CPatchOperator.h"
#include "Function\CPatchFunction.h"