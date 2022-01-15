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
		static CPatchSymbol* CreateSymbol(const Common::CString& str);

				void		AddRef ();
				void		Release();
		virtual	CPatchType*	Execute()=0;
		virtual	Common::CString		GetSymbolName()=0;
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

		static Common::CArray<TSymBuilder*> arrBuilders;

		Common::CString			sClassName;
		Common::CString			sSynonym;
		TObjectCreator	pFunction;
	public:
						TSymBuilder	(const Common::CString& className, const Common::CString& synonym, TObjectCreator func);
		CPatchSymbol*	CreateSymbol();
		Common::CString			GetClass();
		Common::CString			GetSynonym();

		static TSymBuilder*	GetByClassName	(const Common::CString& className);
		static TSymBuilder* GetBySynonym	(const Common::CString& synonym);
		static Common::CString		GetSymbolType	(const Common::CString& synonym);
	};
}



#define PATCH_CLASS_DECLARATION(className)			\
public:												\
			 className();							\
	virtual ~className();							\
	static	 CPatchSymbol* CreateObject();			\
	static	 TSymBuilder mSymBuilder;				\
	virtual	 Common::CString	 GetSymbolName();


#define PATCH_CLASS_DEFINITION(className, synonym)	\
	CPatchSymbol* className::CreateObject()			\
	{												\
		return new className;						\
	}												\
	Common::CString	className::GetSymbolName()				\
	{												\
		return mSymBuilder.GetSynonym();			\
	}												\
	TSymBuilder className::mSymBuilder(#className, synonym, className::CreateObject);



#include "Type\CPatchType.h"
#include "Operator\CPatchOperator.h"
#include "Function\CPatchFunction.h"