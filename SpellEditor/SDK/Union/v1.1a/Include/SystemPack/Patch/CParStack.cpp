#include <UnionAfx.h>








/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStackBase
		Абстрактный стек

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	CParStackBase::CParStackBase ()
	{
		pPrev = Null;
		pNext = Null;
	}

	void CParStackBase::PushNext (CParStackBase* sym)
	{
		if (pNext)
			pNext->pPrev = sym;
		sym->pNext = pNext;
		sym->pPrev = this;
		pNext = sym;
	}

	void CParStackBase::PushBack (CParStackBase* sym)
	{
		if (pPrev)
			pPrev->pNext = sym;
		sym->pPrev = pPrev;
		sym->pNext = this;
		pPrev = sym;
	}

	void CParStackBase::Destroy ()
	{
		if (pNext) pNext->Destroy();
		delete this;
	}

	CParStackBase* CParStackBase::Prev ()
	{
		return pPrev;
	}

	CParStackBase* CParStackBase::Next ()
	{
		return pNext;
	}

	uint32 CParStackBase::Num ()
	{
		CParStackBase* stack = pNext;
		uint32 num = 0;
		while (stack)
		{
			num++;
			stack = stack->pNext;
		}
		return num;
	}

	CParStackBase::~CParStackBase ()
	{
		if (pPrev) pPrev->pNext = pNext;
		if (pNext) pNext->pPrev = pPrev;
	}

}












/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStackUncompiled
		Строковый стек данных

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{

	CParStackUncompiled::CParStackUncompiled () : CParStackBase ()
	{
		sOperation = NullStr;
	}

	CParStackUncompiled::CParStackUncompiled (const CString& op) : CParStackBase ()
	{
		sOperation = op;
	}

	CString CParStackUncompiled::GetSymbol ()
	{
		return sOperation;
	}

	void CParStackUncompiled::SetSymbol (const CString& op)
	{
		sOperation = op;
	}

	
	static const CString s_sNumericalFilter	= "1234567890.xXabcdefABCDEF-";
	static const CString s_sTextFilter		= "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890:";
	static const CString s_sOperatorFilter	= "+-*/=@<>!^";
	static const CString s_sBracketsFilter	= "()[]\"'";

	static const CString s_arrFilters [] = { 
		s_sNumericalFilter,
		s_sTextFilter,
		s_sOperatorFilter,
		s_sBracketsFilter
	};

	static const CString s_sBrackets_Default [2] = { "(",	")"	 };
	static const CString s_sBrackets_Square  [2] = { "[",	"]"	 };
	static const CString s_sBrackets_Text    [2] = { "\"",	"\"" };
	static const CString s_sBrackets_Hex     [2] = { "'",	"'"  };
	static const CString s_sBrackets_Comment [2] = { "/*",	"*/" };

	static const CString* s_arrBrackets [] = {
		s_sBrackets_Default,
		s_sBrackets_Square,
		s_sBrackets_Text,
		s_sBrackets_Hex,
		s_sBrackets_Comment
	};

	CParStackUncompiled* CParStackUncompiled::CreateStack (const CString& line)
	{
		CParStackUncompiled* stack = new CParStackUncompiled;

		for (uint32 i = 1;; i++)
		{
			CString sOp = line.GetSymbolEx( s_arrFilters, 4, s_arrBrackets, 5, i );
			if (sOp.IsEmpty())
				break;

			CParStackUncompiled* sym = new CParStackUncompiled( sOp );
			stack->PushNext( sym );
		}
		return stack;
	}

	CParStackUncompiled::~CParStackUncompiled ()
	{
		//cmd << "~SU: " << sOperation << endl;
	}

}











/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStack
		Бинарный стек данных

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


	CParStack::CParStack () : CParStackBase ()
	{
		pHandler = Null;
	}

	CParStack::CParStack (CParHandler* handler) : CParStackBase ()
	{
		pHandler = handler;
	}

	CParHandler* CParStack::GetData ()
	{
		return pHandler;
	}

	void CParStack::SetData (CParHandler* handler)
	{
		pHandler = handler;
	}

#define DoStackOperations(condition)											\
		stack = (CParStack*)pNext;												\
		while (stack)															\
		{																		\
			CParOperator* op = dynamic_cast<CParOperator*>(stack->GetData());	\
			if (op)																\
				if (condition)													\
					CParSymbol* sym = op->Execute();							\
			stack = (CParStack*)stack->pNext;									\
		}

#define OperatorID(id) op->sOperator == s_sOperators[id]

	CParSymbol* CParStack::Execute ()
	{
		CParStack* stack = (CParStack*)pNext;

		DoStackOperations(OperatorID(21));																												//	Создание ссылочных переменных
		DoStackOperations(OperatorID(0) || OperatorID(1) || OperatorID(2)  || OperatorID(3));															//	Преобразования типов
		DoStackOperations(OperatorID(29));																												//	функция MODULE_BASE
		DoStackOperations(OperatorID(6) || OperatorID(7) || OperatorID(8)  || OperatorID(19) || OperatorID(20));										//	Операторы умножения и деления
		DoStackOperations(OperatorID(4) || OperatorID(5) || OperatorID(17) || OperatorID(18));															//	Операторы сложения и вычитания
		DoStackOperations(OperatorID(22) || OperatorID(23) || OperatorID(24));																			//	функция лимитирования
		DoStackOperations(OperatorID(9));																												//	Присвоение
		DoStackOperations(OperatorID(10) || OperatorID(11) || OperatorID(12) || OperatorID(13) || OperatorID(14) || OperatorID(15) || OperatorID(16));	//	логические операторы
		
		
		if (Num() == 1)
		{
			CParHandler* pHandler = ((CParStack*)pNext)->pHandler;
			ASSERT( dynamic_cast<CParSymbol*>(pHandler), ".patch: Объект не является символом" );
			return (CParSymbol*)pHandler;
		}
		return Null;
	}

	CParStack* CParStack::CreateStack (CParStackUncompiled* _stackUncompiled)
	{
		CParStack*			 stack			 = new CParStack;
		CParStackUncompiled* stackUncompiled = (CParStackUncompiled*)_stackUncompiled->Next();

		while (stackUncompiled)
		{
			CParHandler* pHandler = CParHandler::CreateHandler( stackUncompiled->GetSymbol() );
			if (!pHandler) 
			{
				CString& symValue = stackUncompiled->GetSymbol();
				if (symValue.First() == '(' && symValue.Last() == ')')
				{
					CString sSubStack = symValue.Copy( 1, symValue.Length() - 2 );
					CParStack* pSubStack = CParStack::CreateStack( sSubStack );
					CParSymbol* pSymbol = pSubStack->Execute();

					ASSERT( pSymbol, ".patch: Синтаксическая ошибка при определении скобок" );

					pHandler = pSymbol;
					pHandler->AddRef();
					pSubStack->Destroy();
				}
				ASSERT( pHandler, ".patch: Неизвестная команда: " + stackUncompiled->GetSymbol() );
			}

			CParStack* pStack = new CParStack( pHandler );
			stack->PushNext( pStack );
			CParOperator* pOp = dynamic_cast<CParOperator*>(pHandler);
			if (pOp)
			{
				pOp->pOnStack = pStack;
			}
			stackUncompiled = (CParStackUncompiled*)stackUncompiled->Next();
		}
		return stack;
	}

	CParStack* CParStack::CreateStack (const CString& line)
	{
		CParStackUncompiled* stackUncompiled = CParStackUncompiled::CreateStack( line );
		CParStack* stack = CreateStack( stackUncompiled );
		stackUncompiled->Destroy();
		return stack;
	}

	CParStack::~CParStack ()
	{
		//cmd << "~SC: " << endl;
		if (pHandler)
			pHandler->Release();
	}
}