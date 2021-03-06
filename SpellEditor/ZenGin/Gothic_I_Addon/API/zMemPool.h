// Supported with union (c) 2018 Union team

#ifndef __ZMEM_POOL_H__VER1__
#define __ZMEM_POOL_H__VER1__

namespace Gothic_I_Addon {

  typedef enum {
    zVOLATILE_OVERFLOW_FORBID,
    zVOLATILE_OVERFLOW_WRAP,
    zVOLATILE_OVERFLOW_RESIZE
  } zTVolatileOverflowMode;

  class zCMemPoolBlock {
  public:
    zCMemPoolBlock* next;
    void* data;

    zCMemPoolBlock() {}
    //static void operator delete( void* ) zCall( 0x00567830 );
  };

  class zCVolatileMemoryBase {
  public:
    size_t size;
    size_t num;
    size_t nextfree;
    size_t maxAllocated;
    int maxFill;
    zTVolatileOverflowMode overflowMode;
    int overflow;
    void* data;

    zCVolatileMemoryBase() {}
    void zCVolatileMemoryBase_OnInit( unsigned int, unsigned int, zTVolatileOverflowMode ) zCall( 0x005671C0 );
    void zCVolatileMemoryBase_OnInit( unsigned int, zTVolatileOverflowMode )               zCall( 0x00567230 );
    zCVolatileMemoryBase( unsigned int a0, unsigned int a1, zTVolatileOverflowMode a2 )    zInit( zCVolatileMemoryBase_OnInit( a0, a1, a2 ));
    zCVolatileMemoryBase( unsigned int a0, zTVolatileOverflowMode a1 )                     zInit( zCVolatileMemoryBase_OnInit( a0, a1 ));
    ~zCVolatileMemoryBase()                                                                zCall( 0x00567270 );
    void Init( unsigned int )                                                              zCall( 0x005672A0 );
    void* Alloc()                                                                          zCall( 0x005672D0 );
    unsigned int Mark()                                                                    zCall( 0x00567490 );
    void Restore( unsigned int )                                                           zCall( 0x005674A0 );
    void MaxFillPercentage( int )                                                          zCall( 0x00567570 );
    virtual void Destroyed( void* )                                                        zCall( 0x00567220 );
  };

  class zCMemPoolBase {
  public:
    size_t size;
    size_t blocksize;
    zCMemPoolBlock* blocks;
    void* freeList;
    size_t numFree;
    size_t preallocate;
    int forcePrealloc;

    zCMemPoolBase() {}
    void zCMemPoolBase_OnInit( unsigned int )                             zCall( 0x00567580 );
    void zCMemPoolBase_OnInit( unsigned int, unsigned int, unsigned int ) zCall( 0x005675B0 );
    zCMemPoolBase( unsigned int a0 )                                      zInit( zCMemPoolBase_OnInit( a0 ));
    zCMemPoolBase( unsigned int a0, unsigned int a1, unsigned int a2 )    zInit( zCMemPoolBase_OnInit( a0, a1, a2 ));
    ~zCMemPoolBase()                                                      zCall( 0x005675F0 );
    void* Alloc()                                                         zCall( 0x00567690 );
    void Free( void* )                                                    zCall( 0x00567840 );
    void PreAlloc( unsigned int, int )                                    zCall( 0x00567880 );
    void PoolAdd( void*, int, int )                                       zCall( 0x00567A90 );
    static void SetMemDebug( char const*, char const*, int )              zCall( 0x00567BF0 );
    static void DisablePools( int )                                       zCall( 0x00567C10 );

    // static properties
    static const char*& s_className;
    static const char*& s_fileName;
    static int& s_line;
    static int& s_disablePools;
  };

} // namespace Gothic_I_Addon

#endif // __ZMEM_POOL_H__VER1__