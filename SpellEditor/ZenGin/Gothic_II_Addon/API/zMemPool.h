// Supported with union (c) 2018 Union team

#ifndef __ZMEM_POOL_H__VER3__
#define __ZMEM_POOL_H__VER3__

namespace Gothic_II_Addon {

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
    //static void operator delete( void* ) zCall( 0x00566670 );
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
    void zCVolatileMemoryBase_OnInit( unsigned int, unsigned int, zTVolatileOverflowMode ) zCall( 0x00566070 );
    void zCVolatileMemoryBase_OnInit( unsigned int, zTVolatileOverflowMode )               zCall( 0x005660D0 );
    zCVolatileMemoryBase( unsigned int a0, unsigned int a1, zTVolatileOverflowMode a2 )    zInit( zCVolatileMemoryBase_OnInit( a0, a1, a2 ));
    zCVolatileMemoryBase( unsigned int a0, zTVolatileOverflowMode a1 )                     zInit( zCVolatileMemoryBase_OnInit( a0, a1 ));
    ~zCVolatileMemoryBase()                                                                zCall( 0x00566110 );
    void Init( unsigned int )                                                              zCall( 0x00566140 );
    void* Alloc()                                                                          zCall( 0x00566160 );
    unsigned int Mark()                                                                    zCall( 0x00566300 );
    void Restore( unsigned int )                                                           zCall( 0x00566310 );
    void MaxFillPercentage( int )                                                          zCall( 0x005663C0 );
    virtual void Destroyed( void* )                                                        zCall( 0x005660C0 );
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
    void zCMemPoolBase_OnInit( unsigned int )                             zCall( 0x005663D0 );
    void zCMemPoolBase_OnInit( unsigned int, unsigned int, unsigned int ) zCall( 0x00566400 );
    zCMemPoolBase( unsigned int a0 )                                      zInit( zCMemPoolBase_OnInit( a0 ));
    zCMemPoolBase( unsigned int a0, unsigned int a1, unsigned int a2 )    zInit( zCMemPoolBase_OnInit( a0, a1, a2 ));
    ~zCMemPoolBase()                                                      zCall( 0x00566440 );
    void* Alloc()                                                         zCall( 0x005664E0 );
    void Free( void* )                                                    zCall( 0x00566680 );
    void PreAlloc( unsigned int, int )                                    zCall( 0x005666C0 );
    void PoolAdd( void*, int, int )                                       zCall( 0x005668C0 );
    static void SetMemDebug( char const*, char const*, int )              zCall( 0x00566A80 );
    static void DisablePools( int )                                       zCall( 0x00566AA0 );

    // static properties
    static const char*& s_className;
    static const char*& s_fileName;
    static int& s_line;
    static int& s_disablePools;
  };

} // namespace Gothic_II_Addon

#endif // __ZMEM_POOL_H__VER3__