#pragma once

#if 0
namespace SystemPack
{
	typedef Common::CList<Common::CObject> TPatchStack;


	class CPatch_Stack
	{
		TPatchStack lstStack;

		 CPatch_Symbol* Execute(TPatchStack* stack);
	public:

		 CPatch_Stack(const Common::CString& line);
		 CPatch_Symbol* ExecuteStack();
		 void Remove (TPatchStack* stack);
		
		~CPatch_Stack();
	};
}
#endif











namespace SystemPack
{
	class CPatch_Stack
	{
	protected:

		CPatch_Stack	*pPrev, *pNext;
		Common::CObject			*pObject;

	public:

		CPatch_Stack ();
		static CPatch_Stack* CreateStack (const Common::CString& line);

		void PushNext (CPatch_Stack* stack);
		void PushBack (CPatch_Stack* stack);
		void Destroy ();

		CPatch_Stack* Prev ();
		CPatch_Stack* Next ();
		uint32		  Num  ();

		Common::CObject* GetData ();
		void	 SetData (Common::CObject* object);
		
		CPatch_Symbol* Execute ();		// выполнение всего стека далее данного
		CPatch_Symbol* ExecuteLocal ();	// выполнение конкретного элемента

		virtual ~CPatch_Stack ();
	};
}