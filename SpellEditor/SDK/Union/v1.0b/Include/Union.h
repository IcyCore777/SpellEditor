#pragma once



namespace UnionCore
{

	template <typename T>
	inline T ZenDef (T G1, T G1A, T G2, T G2A) {
		switch (Union.GetEngineVersion()) {
			case Engine_G1:		return G1;
			case Engine_G1A:	return G1A;
			case Engine_G2:		return G2;
			case Engine_G2A:	return G2A;
		};
		return None;
	};


struct ASTAPI TVersion
{
	union {
		struct {
			uint64 Micro : 8;
			uint64 Minor : 24;
			uint64 Major : 32;
		};
		uint64 ui64Version;
	};

	TVersion () {
		Major = 1;
		Minor = 0;
		Micro = 0;
	}

	TVersion (const uint32& major, const uint32& minor, const char& micro = 0) {
		Major = major;
		Minor = minor;
		Micro = micro;
	}

	Common::CStringA ToString () { return A Major + '.' + Minor + (char)Micro; }
	operator uint64   () { return ui64Version; }
};


extern "C"
class ASTAPI CUnion
{
	friend uint32 __stdcall _WinMain (HMODULE, HMODULE, text, bool32);
	friend int __stdcall PostWinMain( HINSTANCE a1, HINSTANCE a2, char* a3, int a4 );

	TVersion		mUnionVersion;
	TEngineVersion	mEngineVersion;
	TSystemLangID	mSystemLanguage;
	COption			mUnionOption;
	COption			mGameOption;
	COption			mDefaultOption;
	COption			mSysPackOption;
	uint32			ulGothicHash;
	bool32			bUnionIsInit;

	Common::CStringA sCmdLine;
	Common::CStringA sGameIni;

	// в точке входа двига
	void LoadVdfs		 ();
	void LoadOptions	 ();
	void PreLoadPlugins	 ();
	void PostLoadPlugins ();
	void LoadGlossaries	 ();
	void InitApp		 ();

	// при коннекте к потоку
	void DefileLanguage	();
	void DefineEngine	();
	void ApplyHacks		();
	void ApplyPatches	();
	void InitCore		();

public:

	CUnion ();
	void InitGlobal ();

	TVersion		GetUnionVersion	   ();
	TEngineVersion	GetEngineVersion   ();
	TSystemLangID	GetSystemLanguage  ();
	COption&		GetUnionOption	   ();
	COption&		GetGameOption	   ();
	COption&		GetDefaultOption   ();
	COption&		GetSysPackOption   ();
	uint32			GetGothicHash	   ();
	bool32			UnionIsInit		   ();

	Common::CStringA		GetCmdLine ();
	Common::CStringA		GetGameIni ();

	bool	OptionReadBool	  (Common::CString sec, Common::CString val);
	byte	OptionReadByte	  (Common::CString sec, Common::CString val);
	int32	OptionReadInt	  (Common::CString sec, Common::CString val);
	real32	OptionReadFloat	  (Common::CString sec, Common::CString val);
	Common::CString	OptionReadString  (Common::CString sec, Common::CString val);

	void	OptionWriteBool	  (Common::CString sec, Common::CString val, bool	 par);
	void	OptionRWriteByte  (Common::CString sec, Common::CString val, byte	 par);
	void	OptionWriteInt	  (Common::CString sec, Common::CString val, int32	 par);
	void	OptionWriteFloat  (Common::CString sec, Common::CString val, real32	 par);
	void	OptionWriteString (Common::CString sec, Common::CString val, Common::CString par);

	bool32	OptionIsExists	  (Common::CString sec, Common::CString val);

	void	DefineCRTVersion  (uint32 major, uint32 minor, uint32 build, uint32 rbuild);

	static  HMODULE __stdcall LoadLibraryA(LPSTR  lpName);
	static  HMODULE __stdcall LoadLibraryW(LPWSTR lpName);

	~CUnion ();
};

extern ASTAPI CUnion Union;

}

#include "UnionAssert.h"