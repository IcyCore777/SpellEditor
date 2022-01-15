#pragma once

namespace SystemPack
{
	typedef Common::CArray<CPatch_Symbol*> TPatchParameters;
	typedef CPatch_Symbol* (__cdecl * TPatch_ExecutableFunc) (TPatchParameters&);




	struct ASTAPI TPatch_FuncDescriptor
	{
		Common::CString					 sName;
		TPatch_ExecutableFunc	 pFuncExec;
		TTypeDescriptor*		 pFuncType;
		Common::CArray<TTypeDescriptor*> arrParmTypes;

		TPatch_FuncDescriptor (const Common::CString& name, TPatch_ExecutableFunc func, TTypeDescriptor* types);
		void InsertParameter  (TTypeDescriptor* parm);
	};




	class ASTAPI CPatch_Function : public Common::CObject
	{
		friend class CPatch_Stack;
		static Common::CArray<const TPatch_FuncDescriptor*> arrFuncDescriptors;

	protected:

		CPatch_Function();
		void SetDescriptor(const TPatch_FuncDescriptor* desc);

		COBJECT_CLASS_DELARATE( CPatch_Function );
		virtual void Archive	(CArchiver&) { };
		virtual void Unarchive  (CArchiver&) { };

	public:

		const TPatch_FuncDescriptor*	pDescriptor;
		Common::CArray<CPatch_Symbol*>			arrParameters;

		static	CPatch_Function*		CreateFunction	 (const Common::CString& name);
		static	void					RegisterFunction (const Common::CString& name, TPatch_ExecutableFunc func, TTypeDescriptor* types ...); // name, return type, arguments type
				Common::CString					GetName			 ();
				Common::CString					GetFullName		 ();
				TPatch_ExecutableFunc	GetFunction		 ();
				TTypeDescriptor*		GetType			 ();
				void					PushParameter	 (CPatch_Symbol* sym);
				CPatch_Symbol*			Execute			 ();
				void					CreateParameters (const Common::CString& line);
									   ~CPatch_Function	 ();
	};


}