#pragma once






namespace SystemPack
{
	class CPatch_Stack
	{
	protected:

		CPatch_Stack	*pPrev, *pNext;
		CPatch_Symbol	*pObject;

	public:

		CPatch_Stack ();
		static CPatch_Stack* CreateStack (const Common::CString& line);

		void PushNext (CPatch_Stack* stack);
		void PushBack (CPatch_Stack* stack);
		void Destroy ();

		CPatch_Stack* Prev ();
		CPatch_Stack* Next ();
		uint32		  Num  ();

		CPatch_Symbol* GetData ();
		void SetData (CPatch_Symbol* object);
		
		CPatch_Type* Execute ();		// ���������� ����� ����� ����� �������
		CPatch_Type* ExecuteLocal ();	// ���������� ����������� ��������

		virtual ~CPatch_Stack ();
	};
}