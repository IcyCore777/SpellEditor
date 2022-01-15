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
		CString					 sName;
		CPatch*					 pParent;
		CDocument				 sRegion;
		CArray <CParSymbol*>	 arrSymbols;
		
		uint32 CalcLine (uint32 idx);

		CParSymbol* GetVariable	(CString name);

	public:

		CPatchRegion (CString name, CPatch* parent) { 
			sName	= name;
			pParent	= parent; 
		}

		CString GetName  ();
		void PushCommand (const CString& com);
		void Execute	 ();

		~CPatchRegion ();
	};


	// .patch file data
	class CPatch
	{
		friend class CPatchRegion;

		CString					sFileName;
		CArray <CPatchRegion*>	arrPatches;
		CArray <CParSymbol*>	arrGlobals;

	public:

		void Init	 (CString fileName);
		void Execute ();

		static CString sLastFile;
		static CString sLastRegion;
		static uint32  ulLastLine;
	};

};