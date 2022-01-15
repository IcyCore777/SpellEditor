#pragma once

namespace SystemPack
{
	struct ASTAPI TMemUnlocker
	{
		void32  ulAddress;
		ulong32 ulSize;
		ulong32 ulOldRoot;

		 TMemUnlocker(void32 address, const uint32& size, const bool32& condition);
		~TMemUnlocker();
	};

	int32 pow( int32 _val, int32 _pow );
	CPatchType* CallExternalOperators( const uint32&, CPatchType*, CPatchType* );
}

namespace SystemPack
{
	class ASTAPI CPatchType : public CPatchSymbol
	{
		friend class CPatchSymbol;
		friend class CPatchFile;
		friend class CPatch;
	protected:
		static Common::CArray<CPatchType*> arrVariables;
		ESymType eType;
		Common::CString  sObjectName;
		Common::CString	 sOptionName;
	public:
		virtual void		Init(const uint32& address = 0)=0;
		virtual	CPatchType*	Execute()=0;
		virtual void32		GetData()=0;
		virtual uint32		GetSize()=0;

		virtual CPatchType* operator =  (CPatchType* symbol)=0;
		virtual CPatchType* operator +  (CPatchType* symbol)=0;
		virtual CPatchType* operator -  (CPatchType* symbol)=0;
		virtual CPatchType* operator *  (CPatchType* symbol)=0;
		virtual CPatchType* operator /  (CPatchType* symbol)=0;
		virtual CPatchType* operator ^  (CPatchType* symbol)=0;
		virtual CPatchType* operator += (CPatchType* symbol)=0;
		virtual CPatchType* operator -= (CPatchType* symbol)=0;
		virtual CPatchType* operator *= (CPatchType* symbol)=0;
		virtual CPatchType* operator /= (CPatchType* symbol)=0;
		virtual CPatchType* operator ^= (CPatchType* symbol)=0;
		virtual CPatchType* operator !  ()=0;
		virtual CPatchType* operator == (CPatchType* symbol)=0;
		virtual CPatchType* operator != (CPatchType* symbol)=0;
		virtual CPatchType* operator <  (CPatchType* symbol)=0;
		virtual CPatchType* operator <= (CPatchType* symbol)=0;
		virtual CPatchType* operator >  (CPatchType* symbol)=0;
		virtual CPatchType* operator >= (CPatchType* symbol)=0;

		virtual void ReadOption  ()=0;
		virtual void WriteOption ()=0;

		void ReadOptionString (	   Common::CString& result, const Common::CString& optionName, const Common::CString& section, const Common::CString& value);
		void WriteOptionString(const Common::CString& data,	const Common::CString& optionName, const Common::CString& section, const Common::CString& value);

		static CPatchType* GetVariable	 (const Common::CString name);

		void	SetObjectName(const Common::CString& objName);
		void	SetOption	 (const Common::CString& objName);
		Common::CString	GetObjectName();
		Common::CString	GetOption	 ();
		virtual	~CPatchType	 ();
	};
}

#include "BaseTypes\CPatchBaseTypes.h"