// Supported with union (c) 2018 Union team

#ifndef __UNION_INVOKE_H__
#define __UNION_INVOKE_H__

#include "..\CHookInfo\CHookInfo.h"
#include "..\CUntyped\CUntyped.h"

#define IvkTargetVer( address, version ) (Union.GetEngineVersion() == version ? address : Null)
#define HOOK auto
#define AS = InvokeAuto
#define NOINLINE __declspec( noinline )
#define THISCALL( a ) ( this->*a )
#define Z (zSTRING)

namespace UnionCore
{
  enum EInterMode
  {
    IVK_DISABLED  = 1 << 1,
    IVK_NORMAL    = 1 << 2,
    IVK_AUTO      = 1 << 3,
    IVK_REDEFINE  = 1 << 4,
    IVK_PROTECTED = 1 << 5,
    IVK_READONLY  = IVK_DISABLED
  };

  template <typename T>
  class CInvoke
  {
    struct THook {
      int References;
      THookInfo HookInfo;

      THook() {
        HookInfo.lpOriginal  = Null;
        HookInfo.lpPointer   = Null;
        HookInfo.lpDetour    = Null;
        HookInfo.ulProtected = False;
        References = 1;
      }

      void AddRef() {
        References++;
      }

      void Release() {
        if( --References == 0 )
          delete this;
      }
    }
    *Hook;

  public:
    CInvoke( const CInvoke<T>& other );

    CInvoke(
      const TInstance&,
      const TInstance& = Null,
      const uint32&    = IVK_AUTO );

    bool32 Attach(
      const TInstance&,
      const TInstance& = Null,
      const uint32&    = IVK_AUTO );

    bool32 Commit();
    bool32 Detach();
    bool32 DetachTree();
    void   Protect();
    void   Unprotect();
    const  THookInfo& GetHookInfo();

    operator T();
    T ReinterpretTo();

    ~CInvoke();
  };
  
  template <class T>
  CInvoke<T>::CInvoke( const CInvoke<T>& other ) {
    Hook = other->Hook;
    Hook->AddRef();
  }

  template <class T>
  CInvoke<T>::CInvoke( const TInstance& from, const TInstance& to, const uint32& flag ) {
    Hook = new THook();
    Attach( from, to, flag );
  }

  template <class T>
  bool32 CInvoke<T>::Attach( const TInstance& from, const TInstance& to, const uint32& flag ) {
    if( !from || CCallBack::IsExist( Hook->HookInfo ) )
      return False;

    if( flag & IVK_PROTECTED )
      Hook->HookInfo.ulProtected = True;

    uint Origin = (uint)from.data;
    if( flag & IVK_AUTO )
      Origin = CCallBack::Auto( Origin );

    Hook->HookInfo.lpOriginal = (void32)Origin;
    Hook->HookInfo.lpPointer  = (void32)Origin;
    Hook->HookInfo.lpDetour   = to;

    if( !to || flag & IVK_DISABLED )
      return False;

    if( flag & IVK_REDEFINE )
      return CCallBack::Redefine( Hook->HookInfo );

    return CCallBack::Attach( Hook->HookInfo );
  }

  template <class T>
  bool32 CInvoke<T>::Commit() {
    return CCallBack::Commit( Hook->HookInfo );
  }

  template <class T>
  bool32 CInvoke<T>::Detach() {
    return CCallBack::Detach( Hook->HookInfo );
  }

  template <class T>
  bool32 CInvoke<T>::DetachTree() {
    return CCallBack::DetachTree( Hook->HookInfo );
  }

  template <class T>
  void CInvoke<T>::Protect() {
    Hook->HookInfo.ulProtected = TRUE;
  }

  template <class T>
  void CInvoke<T>::Unprotect() {
    Hook->HookInfo.ulProtected = FALSE;
  }

  template <class T>
  const THookInfo& CInvoke<T>::GetHookInfo() {
    return Hook->HookInfo;
  }

  template <class T>
  CInvoke<T>::operator T() {
    return *(T*)&Hook->HookInfo.lpPointer;
  }

  template <class T>
  T CInvoke<T>::ReinterpretTo() {
    return *(T*)&Hook->HookInfo.lpPointer;
  }

  template <class T>
  CInvoke<T>::~CInvoke() {
    Hook->Release();
  }

  template <typename T>
  inline CInvoke<T> InvokeAuto( const TInstance& adr, T ptr, const uint32& flag = IVK_AUTO ) {
    return CInvoke<T>( adr, ptr, flag );
  }

} // namespace UnionCore

#endif // __UNION_INVOKE_H__
