#pragma once

namespace SystemPack
{
	class ASTAPI CPatchStack
	{
		CPatchStack	*pPrev, *pNext;
		CPatchSymbol		*pObject;

	public:
		CPatchStack();

		static CPatchStack* CreateStack(const Common::CString& line);
		CPatchSymbol* Execute();

		void PushNext (CPatchStack* stack);
		void PushBack (CPatchStack* stack);
		void Destroy  ();

		CPatchStack* Prev ();
		CPatchStack* Next ();
		uint32		 Num  ();

		CPatchSymbol* GetData ();
		void		  SetData (CPatchSymbol* object);

		~CPatchStack();
	};
}