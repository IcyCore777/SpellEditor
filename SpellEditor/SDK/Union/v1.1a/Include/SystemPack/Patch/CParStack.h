





/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStackBase
		Абстрактный стек

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	static const uint32 ulHandlerPriority_Brackets	 = 5;
	static const uint32 ulHandlerPriority_External	 = 4;
	static const uint32 ulHandlerPriority_Assignment = 3;
	static const uint32	ulHandlerPriority_Convertor	 = 2;
	static const uint32 ulHandlerPriority_Function	 = 1;
	static const uint32 ulHandlerPriority_Algebra	 = 0;
	

	class CParStackBase
	{
	protected:

		CParStackBase	*pPrev, *pNext;

	public:

		CParStackBase ();
		void PushNext (CParStackBase* sym);
		void PushBack (CParStackBase* sym);
		void Destroy ();	// удаляет текущий и все последующие за собой элементы
		CParStackBase* Prev ();
		CParStackBase* Next ();
		uint32		   Num	();
		virtual ~CParStackBase ();
	};
}








/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStackUncompiled
		Строковый стек данных

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	class CParStackUncompiled : public CParStackBase
	{
		CString sOperation;

	public:

		CParStackUncompiled ();
		CParStackUncompiled (const CString& op);
		CString GetSymbol ();
		void SetSymbol (const CString& op);
		static CParStackUncompiled* CreateStack (const CString& line); // создает некомпилированную очередь операторов
		virtual ~CParStackUncompiled ();
	};
}








/* * * * * * * * * * * * * * * * * * * * * * * *

		CParStack
		Бинарный стек данных

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	class CParStack : public CParStackBase
	{
		friend class CParOperator;
		CParHandler* pHandler;

	public:

		CParStack ();
		CParStack (CParHandler* handler);
		CParHandler* GetData ();
		void SetData (CParHandler* handler);
		CParSymbol* Execute ();
		static CParStack* CreateStack (CParStackUncompiled* stackUncompiled);
		static CParStack* CreateStack (const CString& line);
		virtual ~CParStack ();
	};
}