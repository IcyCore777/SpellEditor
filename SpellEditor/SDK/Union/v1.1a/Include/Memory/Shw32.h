// Supported with union (c) 2018 Union team

#ifndef __UNION_MEMORY_H__
#define __UNION_MEMORY_H__

EXTERN_C
{
#define SHIEXT __declspec( dllimport )

  SHIEXT Common::void32 shi_malloc( Common::uint32 sz );
  SHIEXT Common::void32 shi_calloc( Common::uint32 num, Common::uint32 sz );
  SHIEXT Common::void32 shi_realloc( Common::void32 mem, Common::uint32 sz );
  SHIEXT void shi_free( Common::void32 mem );
  SHIEXT void shi_delete( Common::void32 mem );
  SHIEXT Common::uint32 shi_msize( Common::void32 mem );
  SHIEXT Common::bool32 shi_MemInitDefaultPool();
}

inline Common::void32 operator new ( size_t sz ) {
  return shi_malloc( sz );
}

inline Common::void32 operator new []( size_t sz ) {
  return shi_malloc( sz );
}

inline void operator delete ( Common::void32 mem ) {
  shi_free( mem );
}

inline void operator delete []( Common::void32 mem ) {
  shi_free( mem );
}

#endif // __UNION_MEMORY_H__