// Supported with union (c) 2018 Union team

#ifndef __OCS_TRIGGER_H__VER1__
#define __OCS_TRIGGER_H__VER1__

#include "zVobMisc.h"

namespace Gothic_I_Addon {

  class oCCSTrigger : public zCTrigger {
  public:
    zCLASS_DECLARATION( oCCSTrigger )

    oCCSTrigger() {}
    static zCObject* _CreateNewInstance()                               zCall( 0x00404840 );
    static void operator delete( void*, char const*, char const*, int ) zCall( 0x00404960 );
    virtual zCClassDef* _GetClassDef() const                            zCall( 0x00404980 );
    virtual void Archive( zCArchiver& )                                 zCall( 0x00405330 );
    virtual void Unarchive( zCArchiver& )                               zCall( 0x00405340 );
    virtual ~oCCSTrigger()                                              zCall( 0x004049C0 );
    virtual void TriggerTarget( zCVob* )                                zCall( 0x004049D0 );
    virtual void UntriggerTarget( zCVob* )                              zCall( 0x004050B0 );
  };

} // namespace Gothic_I_Addon

#endif // __OCS_TRIGGER_H__VER1__