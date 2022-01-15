#include <UnionAfx.h>






using namespace UnionFilters;

namespace SystemPack
{
#if 0
	inline void inlCreateParameters(Common::CString& funcName, Common::CString line, Common::CArray<CPatch_Symbol*>& parms)
	{
		line.First() = ' ';
		line.Last()  = ' ';


		Common::CString sParm;
		for (uint32 i = 1, argument = 0;; i++)
		{
			Common::CString word = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, i );
			if( word.IsEmpty() || word == "," )
			{
				argument++;

				CPatch_Stack    mStack( sParm );
				CPatch_Symbol*  pSymbol = mStack.ExecuteStack();

				if( !pSymbol )
				{
					ASSERT_PATCH_ERROR( A argument + "-й параметр в функции " + funcName + " не представляет ни один тип" );
				}
				pSymbol->AddRef();
				parms.Insert(pSymbol);

				
				if( word.IsEmpty() )
					return;

				sParm.Clear();
			}
			else
			{
				sParm += word;
			}
		}

		Common::CString parm = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, 2 );
		Say::Info( parm );
	}

	CPatch_Stack::CPatch_Stack(const Common::CString& line)
	{
		TPatchStack* list = &lstStack;
		uint32 ulLastIndex = 0;

		for (uint32 i = 1;; i++)
		{
			Common::CString sWord = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, i );
			if( sWord.IsEmpty() )
			{
				break;
			}
			Common::CObject* pSymbol = CPatch_Operator::CreateOperator( sWord );

			if( !pSymbol )
			{
				 pSymbol = CPatch_Symbol::CreateSymbol( sWord );
			}
			if( !pSymbol )
			{
				 pSymbol = CPatch_Function::CreateFunction( sWord );
				 if( pSymbol )
				 {
					CPatch_Function* pFunc = (CPatch_Function*)pSymbol;
					Common::CString sParms = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, ++i );
					inlCreateParameters( pFunc->GetFullName(), sParms, pFunc->arrParameters );
				 }
			}
			if( !pSymbol )
			{
				ASSERT_PATCH_ERROR( "Идентификатор '" + sWord + "' не определен" );
			}
			list->Insert( pSymbol );
			list = list->GetNext();
		}
	}

	inline CPatch_Symbol* inlGetArgument(TPatchStack* stack)
	{
		// Common::CObject*& sData = stack;
	}

	CPatch_Symbol* CPatch_Stack::ExecuteStack()
	{
		// Values
		{
			// CPatch_Symbol* pSymbol = dynamic_cast<CPatch_Symbol*>(  );
		}

		// Functions
		{
			TPatchStack* stack = lstStack.GetNext();

			while (stack)
			{
				Common::CObject*& pObject = stack->GetData();
				CPatch_Function* pFunc = dynamic_cast<CPatch_Function*>( pObject );
				if( pFunc )
				{
					CPatch_Symbol* pSymbol = pFunc->Execute();

					pObject->Release();
					pObject = pSymbol;
				}
				stack = stack->GetNext();
			}
		}

		// Types
		{
			TPatchStack* stack = lstStack.GetNext();

			while (stack)
			{
				Common::CObject*& pObject = stack->GetData();
				CPatch_Operator* pOperator = dynamic_cast<CPatch_Operator*>( pObject );

				if( pOperator )
				{
					Common::CArray<TTypeDescriptor*>& arrSyms = TTypeDescriptor::arrSymbolDescriptors;
					for (uint32 i = 0; i < arrSyms.GetNum(); i++)
					{
						if( arrSyms[i]->sName == pOperator->GetOperatorName() )
						{
							CPatch_Symbol* pSymbol = (CPatch_Symbol*)( CClassDef::CreateClass( arrSyms[i]->pClassDef ));

							TPatchStack* next = stack->GetNext();
							Common::CObject* pArgument;
						}
					}
				}
			}
			/*Common::CArray<TTypeDescriptor*>& arrSyms = TTypeDescriptor::arrSymbolDescriptors;
			for (uint32 i = 0; i < arrSyms.GetNum(); i++)
			{
				if( arrSyms[i]->sName ==  )
				{
					CPatch_Symbol* sym = dynamic_cast<CPatch_Symbol*>( CClassDef::CreateClass( arrSyms[i]->pClassDef ));
					if( sym )
					{
						return sym;
					}
				}
			}*/
		}

		// Operators
		{
			
		}

		// 

		return Null;
	}

	CPatch_Symbol* CPatch_Stack::Execute(TPatchStack* stack)
	{
		Common::CObject*& pObject = stack->GetData();

		CPatch_Symbol* sym = dynamic_cast<CPatch_Symbol*>( pObject );
		if( sym )
		{
			return sym;
		}

		CPatch_Function* func = dynamic_cast<CPatch_Function*>( pObject );
		if( func )
		{
			CPatch_Symbol* result = func->Execute();
			func->Release();
			pObject = result;
			return result;
		}

		CPatch_Operator* op = dynamic_cast<CPatch_Operator*>( pObject );
		if( op )
		{
			
		}

		ASSERT_PATCH_ERROR( "#0" );
		return Null;
	}

	 void CPatch_Stack::Remove (TPatchStack* stack)
	 {
		stack->GetData()->Release();
		lstStack.Remove( stack );
	 }

	CPatch_Stack::~CPatch_Stack()
	{
		TPatchStack* list = lstStack.GetNext();
		while (list)
		{
			list->GetData()->Release();
			list = list->GetNext();
		}
		lstStack.DeleteList();
	}
#endif




	CPatch_Stack::CPatch_Stack()
	{
		pPrev	= Null;
		pNext	= Null;
		pObject	= Null;
	}

	CPatch_Stack* CPatch_Stack::CreateStack (const Common::CString& line)
	{
		ASSERT( !line.IsEmpty(), "Невозможно создать стек из пустой строки" );
		CPatch_Stack* stack = new CPatch_Stack;

		for (uint32 i = 1;; i++)
		{
			Common::CString sWord = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, i );
			if( sWord.IsEmpty() )
			{
				break;
			}
			Common::CObject* pSymbol = CPatch_Operator::CreateOperator( sWord );

			if( !pSymbol )
			{
				pSymbol = CPatch_Symbol::CreateSymbol( sWord );
			}
			if( !pSymbol )
			{
				 pSymbol = CPatch_Function::CreateFunction( sWord );
				 if( pSymbol )
				 {
					Common::CString sParms = line.GetSymbolEx( arrResource, 4, arrBrackets, 4, ++i );

					CPatch_Function* pFunc = (CPatch_Function*)pSymbol;
					pFunc->CreateParameters( sParms );
				 }
				
			}
			CPatch_Stack* elm = new CPatch_Stack;
			elm->SetData( pSymbol );
			stack->PushNext( elm );
			stack = elm;
		}
		return stack;
	}

	void CPatch_Stack::PushNext (CPatch_Stack* stack)
	{
		ASSERT( !stack->pNext && !stack->pPrev, "Попытка вставить элемент одного стека в другой" );
		if( pNext )
			pNext->pPrev = stack;
		stack->pNext = pNext;
		stack->pPrev = this;
		pNext = stack;
	}

	void CPatch_Stack::PushBack (CPatch_Stack* stack)
	{
		ASSERT( !stack->pNext && !stack->pPrev, "Попытка вставить элемент одного стека в другой" );
		if (pPrev)
			pPrev->pNext = stack;
		stack->pPrev = pPrev;
		stack->pNext = this;
		pPrev = stack;
	}

	void CPatch_Stack::Destroy ()
	{
		if (pNext) pNext->Destroy();
		delete this;
	}

	CPatch_Stack* CPatch_Stack::Prev ()
	{
		return pPrev;
	}

	CPatch_Stack* CPatch_Stack::Next ()
	{
		return pNext;
	}

	uint32 CPatch_Stack::Num ()
	{
		CPatch_Stack* stack = pNext;
		uint32 num = 0;
		while (stack)
		{
			num++;
			stack = stack->pNext;
		}
		return num;
	}

	Common::CObject* CPatch_Stack::GetData ()
	{
		return pObject;
	}

	void CPatch_Stack::SetData (Common::CObject* object)
	{
		//object->AddRef();
		pObject = object;
	}

	CPatch_Symbol* CPatch_Stack::Execute ()
	{
		CPatch_Stack* stack = Next();
		while (stack)
		{
			CPatch_Function* func = dynamic_cast<CPatch_Function*>( stack->pObject );
			if( func )
			{
				CPatch_Symbol* result = func->Execute();
				func->Release();
				stack->pObject = result;
			}
			stack = stack->Next();
		}

		CPatch_Stack* stack = Next();
		while (stack)
		{
			CPatch_Operator* op = dynamic_cast<CPatch_Operator*>( stack->pObject );
			if( op )
			{
				Common::CArray<TTypeDescriptor*>& arrSyms = TTypeDescriptor::arrSymbolDescriptors;
				for (uint32 i = 0; i < arrSyms.GetNum(); i++)
				{
					if( arrSyms[i]->sName == op->GetOperatorName() )
					{
						CPatch_Symbol* sym = dynamic_cast<CPatch_Symbol*>( CClassDef::CreateClass( arrSyms[i]->pClassDef ));
						if( sym )
						{
							(*sym) = Next()->ExecuteLocal();
						}
					}
				}
			}
		}

		//CPatch_Integer* val = new CPatch_Integer;
		//val->SetValue( 50 );
		//return val;
	}

	CPatch_Symbol* CPatch_Stack::ExecuteLocal ()
	{
		CPatch_Symbol* sym = dynamic_cast<CPatch_Symbol*>( pObject );
		if( sym )
		{
			return sym;
		}

		CPatch_Function* func = dynamic_cast<CPatch_Function*>( pObject );
		if( func )
		{
			CPatch_Symbol* result = func->Execute();
			func->Release();
			pObject = result;
			return result;
		}

		CPatch_Operator* op = dynamic_cast<CPatch_Operator*>( pObject );
		if( op )
		{
			
		}

		Say::Fatal( "Ожидается оператор" );
	}

	CPatch_Stack::~CPatch_Stack ()
	{
		pObject->Release();
		if (pPrev) pPrev->pNext = pNext;
		if (pNext) pNext->pPrev = pPrev;
	}

}