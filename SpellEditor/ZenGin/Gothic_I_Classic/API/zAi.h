// Supported with union (c) 2018 Union team

#ifndef __ZAI_H__VER0__
#define __ZAI_H__VER0__

namespace Gothic_I_Classic {

  class zCAIBase : public zCObject {
  public:
    zCLASS_DECLARATION( zCAIBase )

    zCAIBase() {}
    static void operator delete( void*, char const*, char const*, int ) zCall( 0x004840C0 );
    virtual zCClassDef* _GetClassDef() const                            zCall( 0x004840E0 );
    virtual ~zCAIBase()                                                 zCall( 0x004841F0 );
    virtual void DoAI( zCVob*, int& )                                   zPureCall;
    virtual int CanThisCollideWith( zCVob* )                            zCall( 0x004840F0 );
    virtual void ReportCollisionToAI( zCCollisionReport const& )        zCall( 0x004841A0 );
    virtual int HasAIDetectedCollision()                                zCall( 0x00484100 );
    virtual void AICollisionResponseSelfDetected( zVEC3 const&, int& )  zCall( 0x00484110 );
    virtual void HostVobRemovedFromWorld( zCVob*, zCWorld* )            zCall( 0x00484120 );
    virtual void HostVobAddedToWorld( zCVob*, zCWorld* )                zCall( 0x004841B0 );
  };

  class zCAIBaseSound : public zCAIBase {
  public:
    zCLASS_DECLARATION( zCAIBaseSound )

    int slideSoundHandle;
    char slideSoundOn;

    zCAIBaseSound() {}
    void RemoveSlideSound()                                             zCall( 0x004FC6E0 );
    void CheckSlideSound( zCVob* )                                      zCall( 0x004FC700 );
    void StartDefaultCollisionSound( zCVob*, zCCollisionReport const& ) zCall( 0x004FC790 );
  };

} // namespace Gothic_I_Classic

#endif // __ZAI_H__VER0__