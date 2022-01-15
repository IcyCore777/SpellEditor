// Supported with union (c) 2018 Union team

#ifndef __SYSTEMPACK_PATCH_STACK_H__
#define __SYSTEMPACK_PATCH_STACK_H__

namespace SystemPack
{
  class ASTAPI CPatchStack
  {
    CPatchStack *pPrev, *pNext;
    CPatchSymbol *pObject;

  public:
    CPatchStack();

    static CPatchStack* CreateStack( const CString& line );
    CPatchSymbol* Execute();

    void PushNext( CPatchStack* stack );
    void PushBack( CPatchStack* stack );
    void Destroy();

    CPatchStack* Prev();
    CPatchStack* Next();
    uint32 Num();

    CPatchSymbol* GetData();
    void SetData( CPatchSymbol* object );

    ~CPatchStack();
  };
} // namespace SystemPack

#endif // __SYSTEMPACK_PATCH_STACK_H__