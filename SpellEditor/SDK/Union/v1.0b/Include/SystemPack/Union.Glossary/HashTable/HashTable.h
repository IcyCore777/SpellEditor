#pragma once

namespace SystemPack
{
	class CFilterBase
	{

	public:
		virtual void			Push  (CGlossaryWord*)=0;
		virtual void			Pop	  (CGlossaryWord*)=0;
		virtual CGlossaryWord*	Get	  (const Common::CString& name)=0;
		virtual CGlossaryWord*	Get	  (uint32)=0;
		virtual uint32			Num	  ()=0;
		virtual void			Clear ()=0;
	};

	class CFirstSymbolFilter : CFilterBase
	{
		friend class CLengthFilter;
		Common::CArray <CGlossaryWord*> arrData;
		char symbol;

	public:
		CFirstSymbolFilter (const char& sym);

		virtual void			Push  (CGlossaryWord*);
		virtual void			Pop	  (CGlossaryWord*);
		virtual CGlossaryWord*	Get   (const Common::CString& name);
		virtual CGlossaryWord*	Get	  (uint32);
		virtual uint32			Num	  ();
		virtual void			Clear ();

		~CFirstSymbolFilter ();
	};

	class CLengthFilter : CFilterBase
	{
		friend class CHashTable;
		Common::CArray <CFirstSymbolFilter*> arrData;
		uint32 length;

	public:
		CLengthFilter (const uint32& len);

		virtual void			Push  (CGlossaryWord*);
		virtual void			Pop	  (CGlossaryWord*);
		virtual CGlossaryWord*	Get   (const Common::CString& name);
		virtual CGlossaryWord*	Get	  (uint32);
		virtual uint32			Num	  ();
		virtual void			Clear ();
				uint32			GetLength();

		~CLengthFilter ();
	};

	class CHashTable : CFilterBase
	{
		Common::CArray <CLengthFilter*> arrData;
	
	public:
		virtual void			Push  (CGlossaryWord*);
		virtual void			Pop	  (CGlossaryWord*);
		virtual CGlossaryWord*	Get   (const Common::CString& name);
		virtual CGlossaryWord*	Get	  (uint32);
		virtual uint32			Num	  ();
		virtual void			Clear ();

		~CHashTable ();
	};
};