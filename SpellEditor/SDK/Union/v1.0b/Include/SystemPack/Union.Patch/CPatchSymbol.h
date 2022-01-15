// Supported with union (c) 2018 Union team

#ifndef __SYSTEMPACK_PPATCH_SYMBOL_H__
#define __SYSTEMPACK_PPATCH_SYMBOL_H__

namespace SystemPack
{
  enum ESymType
  {
    SYM_TYPE_UNKNOWN,
    SYM_TYPE_STACK,
    SYM_TYPE_POINTER
  };

  class CPatchType;

  class ASTAPI CPatchSymbol
  {
    friend class CPatchOperator;

  protected:
    uint32 ulRef;
    CPatchSymbol();
  public:
    static CPatchSymbol* CreateSymbol( const Common::CString& str );

    void AddRef();
    void Release();
    virtual CPatchType* Execute() = 0;
    virtual Common::CString GetSymbolName() = 0;
    virtual ~CPatchSymbol();
  };

  typedef CPatchSymbol*( *TObjectCreator )( );

  class ASTAPI TSymBuilder
  {
    friend class CPatchSymbol;
    friend class CPatchOperator;
    friend class CPatchFunction;
    friend class CPatchStack;

    static Common::CArray<TSymBuilder*> arrBuilders;

    Common::CString        sClassName;
    Common::CString        sSynonym;
    TObjectCreator pFunction;
  public:
    TSymBuilder( const Common::CString& className, const Common::CString& synonym, TObjectCreator func );
    CPatchSymbol* CreateSymbol();
    Common::CString GetClass();
    Common::CString GetSynonym();

    static TSymBuilder* GetByClassName( const Common::CString& className );
    static TSymBuilder* GetBySynonym( const Common::CString& synonym );
    static Common::CString GetSymbolType( const Common::CString& synonym );
  };
} // namespace SystemPack

#define PATCH_CLASS_DECLARATION(className) \
public:                                    \
  className();                             \
  virtual ~className();                    \
  static CPatchSymbol* CreateObject();     \
  static TSymBuilder mSymBuilder;          \
  virtual Common::CString GetSymbolName();


#define PATCH_CLASS_DEFINITION(className, synonym) \
  CPatchSymbol* className::CreateObject()          \
  {                                                \
    return new className;                          \
  }                                                \
  Common::CString className::GetSymbolName()               \
  {                                                \
    return mSymBuilder.GetSynonym();               \
  }                                                \
  TSymBuilder className::mSymBuilder(#className, synonym, className::CreateObject);

#include "Types\CPatchType.h"
#include "Operators\CPatchOperator.h"
#include "Functions\CPatchFunction.h"

#endif // __SYSTEMPACK_PARSER_FILTERS_H__