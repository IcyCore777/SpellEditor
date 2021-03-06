// Supported with union (c) 2018 Union team

#ifndef __OCS_PROPS_H__VER1__
#define __OCS_PROPS_H__VER1__

#include "zCCsProps.h"

namespace Gothic_I_Addon {

  class oCCSProps : public zCCSProps {
  public:
    zCLASS_DECLARATION( oCCSProps )

    int resultReaction;

    void oCCSProps_OnInit()                                             zCall( 0x00404510 );
    oCCSProps()                                                         zInit( oCCSProps_OnInit() );
    static void operator delete( void*, char const*, char const*, int ) zCall( 0x00403020 );
    static zCObject* _CreateNewInstance()                               zCall( 0x00404480 );
    virtual zCClassDef* _GetClassDef() const                            zCall( 0x00404500 );
    virtual void Archive( zCArchiver& )                                 zCall( 0x00404570 );
    virtual void Unarchive( zCArchiver& )                               zCall( 0x00404580 );
    virtual ~oCCSProps()                                                zCall( 0x00404560 );
    virtual int AcceptRole( zCCSRole*, zCVob* )                         zCall( 0x00404590 );
    virtual int CheckRole( zCCSRole*, zCVob* )                          zCall( 0x004045B0 );
    virtual int CheckRoleResult()                                       zCall( 0x00404600 );
  };

} // namespace Gothic_I_Addon

#endif // __OCS_PROPS_H__VER1__