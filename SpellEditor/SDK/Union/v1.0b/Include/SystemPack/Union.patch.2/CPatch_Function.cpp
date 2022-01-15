#include <UnionAfx.h>




namespace SystemPack
{
	TPatch_FuncDescriptor::TPatch_FuncDescriptor (const Common::CString& name, TPatch_ExecutableFunc func, TTypeDescriptor* types)
	{
		sName	  = name;
		pFuncExec = func;
		pFuncType = types;
	}

	void TPatch_FuncDescriptor::InsertParameter(TTypeDescriptor* parm)
	{
		arrParmTypes.Insert( parm );
	}
}



using namespace UnionFilters;

namespace SystemPack
{
	COBJECT_CLASS_DEFINE( CPatch_Function );

	Common::CArray<const TPatch_FuncDescriptor*> CPatch_Function::arrFuncDescriptors;

	CPatch_Function::CPatch_Function()
	{
		
	}

	void CPatch_Function::SetDescriptor(const TPatch_FuncDescriptor* desc)
	{
		pDescriptor = desc;
	}

	CPatch_Function* CPatch_Function::CreateFunction (const Common::CString& name)
	{
		for (uint32 i = 0; i < arrFuncDescriptors.GetNum(); i++)
		{
			if( arrFuncDescriptors[i]->sName == name )
			{
				CPatch_Function* pFunction = new CPatch_Function;
				pFunction->SetDescriptor( arrFuncDescriptors[i] );
				return pFunction;
			}
		}
		return Null;
	}

	void CPatch_Function::RegisterFunction (const Common::CString& name, TPatch_ExecutableFunc func, TTypeDescriptor* types ...)
	{
		TPatch_FuncDescriptor* pDesc = new TPatch_FuncDescriptor( name, func, types );
		TTypeDescriptor** ppParms = (TTypeDescriptor**)(int32(&types) + 4);

		for (uint32 i = 0; ppParms[i]; i++)
		{
			pDesc->InsertParameter( ppParms[i] );
		}
		arrFuncDescriptors.Insert( pDesc );
	}

	Common::CString CPatch_Function::GetName()
	{
		return pDescriptor->sName;
	}

	Common::CString CPatch_Function::GetFullName()
	{
		Common::CString sFullName  = GetType() ? GetType()->sName + " " : "void ";
		sFullName += GetName() + "(";

		if (pDescriptor->arrParmTypes.GetNum() == 0)
		{
			sFullName += "void";
		}
		else for (uint32 i = 0;;)
		{
			sFullName += pDescriptor->arrParmTypes[i]->sName;
			if( ++i >= pDescriptor->arrParmTypes.GetNum() )
				break;
			sFullName += ", ";
		}
		sFullName += ")";

		return sFullName;
	}

	TPatch_ExecutableFunc CPatch_Function::GetFunction()
	{
		return pDescriptor->pFuncExec;
	}

	void CPatch_Function::PushParameter (CPatch_Symbol* sym)
	{
		sym->AddRef();
		arrParameters.Insert( sym );
	}

	TTypeDescriptor* CPatch_Function::GetType ()
	{
		return pDescriptor->pFuncType;
	}

	CPatch_Symbol* CPatch_Function::Execute()
	{
		if( arrParameters.GetNum() != pDescriptor->arrParmTypes.GetNum() )
		{
			ASSERT_PATCH_ERROR( "Количество введенных параметров не соответствует фактическому в функции '" + GetFullName() + "'" );
		}
		for (uint32 i = 0; i < pDescriptor->arrParmTypes.GetNum(); i++)
		{
			if( pDescriptor->arrParmTypes[i] != &arrParameters[i]->GetDescriptor() )
			{
				CPatch_Symbol* pSymbol = dynamic_cast<CPatch_Symbol*>( CClassDef::CreateClass( pDescriptor->arrParmTypes[i]->pClassDef ));
				if( !pSymbol )
				{
					ASSERT_PATCH_ERROR( "Тип " + A (i+1) + "-го параметра функции '" + GetFullName() + "' не определен" );
				}
				if( !((*pSymbol) = arrParameters[i]) )
				{
					ASSERT_PATCH_ERROR( "Не найден соответствующий оператор для преобразования " + A (i+1) + "-й параметра '" + pSymbol->GetTypeName() + "' в '" + arrParameters[i]->GetTypeName() + "' в функции '" + GetFullName() + "'" );
				}
				arrParameters[i]->Release();
				arrParameters.RemoveAt( i );
				arrParameters.InsertAt( i, pSymbol );
			}
		}
		TPatch_ExecutableFunc pFunction = GetFunction();
		CPatch_Symbol* pResult = pFunction( arrParameters );
		if( PATCH_TYPE_CID( pResult ) != GetType() )
		{
			ASSERT_PATCH_ERROR( "Тип возвращаемого значения не соответствует типу функции '" + GetFullName() + "'" );
		}
		while (arrParameters.GetNum())
		{
			arrParameters[0]->Release();
			arrParameters.RemoveAt(0);
		}
		return pResult;
	}

	void CPatch_Function::CreateParameters(const Common::CString& line)
	{
		Common::CString sNormal = line.Copy( 1, line.Length() - 2 );

		Common::CString sCurrentParm;
		for (uint32 i = 1, parm_index = 0;; i++)
		{
			Common::CString sWord = sNormal.GetSymbolEx( arrResource, 4, arrBrackets, 4, i );
			
			if( sWord.IsEmpty() || sWord == "," )
			{
				parm_index++;

				CPatch_Stack*  pStack  = CPatch_Stack::CreateStack( sCurrentParm );
				CPatch_Symbol* pSymbol = pStack->Execute();

				ASSERT( pSymbol, A parm_index + "-й параметр в функции " + pDescriptor->sName + " не представляет ни один тип" );

				pSymbol->AddRef();
				arrParameters.Insert( pSymbol );
				pStack->Destroy();

				if( sWord.IsEmpty() )
				{
					return;
				}
				sCurrentParm.Clear();
			}
			else
			{
				sCurrentParm += sWord;
			}
		}
	}

	CPatch_Function::~CPatch_Function ()
	{
		for (uint32 i = 0; i < arrParameters.GetNum(); i++)
		{
			arrParameters[i]->Release();
		}
		arrParameters.Clear();
	}
}