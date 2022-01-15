// Supported with union (c) 2018 Union team

#ifndef __UNION_CORE_H__
#define __UNION_CORE_H__

namespace UnionCore
{
#define CORE_VERSION 100410

  enum TEngineHash
  {
    Hash_G1    = 0x225BA11E,
    Hash_G1A   = 0xBCA27323,
    Hash_G2    = 0xA2EE682C,
    Hash_G2A   = 0x2BCD7E30,
	Hash_G1AL1 = 0x02648DED,
	Hash_G1AL2 = 0xAC7117A1
  };

  enum TEngineVersion
  {
    Engine_Unknown,
    Engine_G1,  // g1 classic 1.08
    Engine_G1A, // g1 siquel 1.12f
    Engine_G2,  // g2 classic 1.30
    Engine_G2A, // g2 notr 2.6
    Engine_Max
  };

  enum TSystemLangID
  {
    Lang_Other,
    Lang_Rus, // russian
    Lang_Eng, // english
    Lang_Ger, // german
    Lang_Pol, // polish
    Lang_Rou, // romanian
    Lang_Ita, // italian
    Lang_Cze, // czech
    Lang_Esp, // spanish
    Lang_Max
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
    TVersion();
    TVersion( const uint32& major, const uint32& minor, const char& micro = 0 );
    Common::CStringA ToString();
    operator uint64();
  };


  class ASTAPI CUnion
  {
    TVersion       mUnionVersion;
    TEngineVersion mEngineVersion;
    TSystemLangID  mSystemLanguage;
    COption        mUnionOption;
    COption        mGameOption;
    COption        mDefaultOption;
    COption        mSysPackOption;
    uint32         ulGothicHash;
    bool32         bUnionIsInit;

    Common::CStringA sCmdLine;
    Common::CStringA sGameIni;

    void LoadVdfs();
    void LoadOptions();
    void PreLoadPlugins();
    void PostLoadPlugins();
    void LoadGlossaries();
    void InitApp();

    void DefileLanguage();
    void DefineEngine();
    void ApplyHacks();
    void ApplyPatches();
    void InitCore();

  public:

    CUnion();
    void InitGlobal();

    TVersion        GetUnionVersion();
    TEngineVersion  GetEngineVersion();
    TSystemLangID   GetSystemLanguage();
    COption&        GetUnionOption();
    COption&        GetGameOption();
    COption&        GetDefaultOption();
    COption&        GetSysPackOption();
    uint32          GetGothicHash();
    bool32          UnionIsInit();
	const Common::CString&  GetGameDirectory();

    Common::CStringA GetCmdLine();
    Common::CStringA GetGameIni();

    bool    OptionReadBool  ( Common::CString sec, Common::CString val );
    byte    OptionReadByte  ( Common::CString sec, Common::CString val );
    int32   OptionReadInt   ( Common::CString sec, Common::CString val );
    real32  OptionReadFloat ( Common::CString sec, Common::CString val );
    Common::CString OptionReadString( Common::CString sec, Common::CString val );

    void OptionWriteBool  ( Common::CString sec, Common::CString val, bool    par );
    void OptionRWriteByte ( Common::CString sec, Common::CString val, byte    par );
    void OptionWriteInt   ( Common::CString sec, Common::CString val, int32   par );
    void OptionWriteFloat ( Common::CString sec, Common::CString val, real32  par );
    void OptionWriteString( Common::CString sec, Common::CString val, Common::CString par );

    bool32 OptionIsExists( Common::CString sec, Common::CString val );

    void DefineCRTVersion( uint32 major, uint32 minor, uint32 build, uint32 rbuild );

    static  HMODULE __stdcall LoadLibraryA( LPSTR  lpName );
    static  HMODULE __stdcall LoadLibraryW( LPWSTR lpName );

    ~CUnion();
  };

  ASTAPI CUnion Union;

  template <typename T>
  inline T ZenDef( T G1, T G1A, T G2, T G2A ) {
    switch( Union.GetEngineVersion() ) {
    case Engine_G1:  return G1;
    case Engine_G1A: return G1A;
    case Engine_G2:  return G2;
    case Engine_G2A: return G2A;
    };
    return None;
  };
}// namespace UnionCore


#include "CApplication\CApplication.h"
#include "CCallBack\CCallBack.h"
#include "CPlugin\CPlugin.h"

using namespace UnionCore;
 
#endif // __UNION_CORE_H__