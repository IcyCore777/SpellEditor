












/* * * * * * * * * * * * * * * * * * * * * * * *

		CParHandler
		�������� ���������� ������

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	class CParStack;
	class CParSymbol;

	enum ESymbolVarType
	{
		VAR_TYPE_UNKNOWN,
		VAR_TYPE_INT,	// to float, to hex
		VAR_TYPE_FLOAT,	// to int, to hex
		VAR_TYPE_HEX,	// to int, to float
	};

	enum ESymbolRootType
	{
		VAR_ROOT_UNKNOWN,
		VAR_ROOT_LOCAL,
		VAR_ROOT_EXTERNAL,
		VAR_ROOT_OPTION
	};

	class CParHandler
	{
		friend class CParOperator;
		uint32	ulRef;

	public:
		CParHandler () { ulRef = 1; };

		static CParHandler* CreateHandler (const CString& str);

		void Release ();
		void AddRef  ();

		virtual CParSymbol* Execute ()=0;
		virtual void Print()=0;
		virtual ~CParHandler () {  };
	};
}









/* * * * * * * * * * * * * * * * * * * * * * * *

		CParSymbol
		�������� ����������

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	class CParSymbol : public CParHandler
	{
		//friend class CParOperator;

		static CArray<CParSymbol*> arrSymbols;

		CString sName;			// ���������� ������������ ������� � �����
		void32  lpSymbol;		// ������ �������
		uint32  ulSizeof;		// ������ ������
		uint32  ulSymType;		// ��� �������
		uint32	ulRootType;		// ��� ��������� ������
		CString	sRoot;			// ������� ������ �������

	public:
		void SetInt	   (int32  val);
		void SetFloat  (real32 val);
		void SetHex	   (void32 val, const uint32& size);
		void SetRoot   (const uint32& type, const CString& root);
		void SetRoot   (const uint32& type, const uint32& address);
		void SetOption (const CString& str);
	
		ESymbolVarType DefineSymbolType (const CString& str);

		void ApplyOption ();

				 CParSymbol ();
		virtual ~CParSymbol ();

	public:

		CParSymbol (const uint32&  type, const CString& name = NullStr);
		CParSymbol (const CString& type, const CString& name = NullStr);

		void ConvertToInt	 ();
		void ConvertToFloat  ();
		void ConvertToHex	 ();
		void ConvertToString ();

		CParSymbol& operator +  (CParSymbol& sym);
		CParSymbol& operator -  (CParSymbol& sym);
		CParSymbol& operator *  (CParSymbol& sym);
		CParSymbol& operator /  (CParSymbol& sym);
		CParSymbol& operator += (CParSymbol& sym);
		CParSymbol& operator -= (CParSymbol& sym);
		CParSymbol& operator *= (CParSymbol& sym);
		CParSymbol& operator /= (CParSymbol& sym);
		CParSymbol& operator =  (CParSymbol& sym);
		CParSymbol&	operator == (CParSymbol& sym);
		CParSymbol&	operator != (CParSymbol& sym);
		CParSymbol&	operator <  (CParSymbol& sym);
		CParSymbol&	operator <= (CParSymbol& sym);
		CParSymbol&	operator >  (CParSymbol& sym);
		CParSymbol&	operator >= (CParSymbol& sym);
		CParSymbol&	operator ^  (CParSymbol& sym);
		CParSymbol&	operator !  ();

		static CParSymbol* CreateSymbol (const CString& str);
		static CParSymbol* CreateCopy	(CParSymbol* sym);

		CString	GetName	();
		void32	GetData ();
		uint32	GetType ();
		bool32	GetBool ();
		uint32	GetSize	();
		CString	GetRoot	();

		virtual CParSymbol* Execute ();
		virtual void Print();
	};
}








/* * * * * * * * * * * * * * * * * * * * * * * *

		CParOperator
		�������� ������

* * * * * * * * * * * * * * * * * * * * * * * */

namespace SystemPack
{
	class CParOperator : public CParHandler
	{
		friend class CParStack;
	public:

		CString	   sOperator;
		CParStack* pOnStack;  // ������� � �����

		static CParOperator* CreateOperator (const CString& str);

		virtual CParSymbol* Execute ();
		virtual void Print();

		virtual ~CParOperator ();
	};
}







