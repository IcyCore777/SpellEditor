#pragma once

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *



* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */





#include "CParSymbol.h"
#include "CParStack.h"



namespace SystemPack
{
	class CPatch;

	// region of patch commands
	class CPatchRegion
	{
		Common::CString					 sName;
		CPatch*					 pParent;
		Common::CDocument				 sRegion;
		Common::CArray <CParSymbol*>	 arrSymbols;
		
		uint32 CalcLine (uint32 idx);

		CParSymbol* GetVariable	(Common::CString name);

	public:

		CPatchRegion (Common::CString name, CPatch* parent) { 
			sName	= name;
			pParent	= parent; 
		}

		Common::CString GetName  ();
		void PushCommand (const Common::CString& com);
		void Execute	 ();

		~CPatchRegion ();
	};


	// .patch file data
	class CPatch
	{
		friend class CPatchRegion;

		Common::CString					sFileName;
		Common::CArray <CPatchRegion*>	arrPatches;
		Common::CArray <CParSymbol*>	arrGlobals;

	public:

		void Init	 (Common::CString fileName);
		void Execute ();

		static Common::CString sLastFile;
		static Common::CString sLastRegion;
		static uint32  ulLastLine;
	};

};