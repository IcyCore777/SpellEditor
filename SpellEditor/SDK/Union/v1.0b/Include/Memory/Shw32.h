// Supported with union (c) 2018 Union team

#ifndef __UNION_MEMORY_H__
#define __UNION_MEMORY_H__

EXTERN_C
{
#define SHIEXT __declspec( dllimport )

  SHIEXT void32 shi_malloc( uint32 sz );
  SHIEXT void32 shi_calloc( uint32 num, uint32 sz );
  SHIEXT void32 shi_realloc( void32 mem, uint32 sz );
  SHIEXT void shi_free( void32 mem );
  SHIEXT void shi_delete( void32 mem );
  SHIEXT uint32 shi_msize( void32 mem );
  SHIEXT bool32 shi_MemInitDefaultPool();
}

void32 operator new (size_t sz);
void32 operator new [] (size_t sz);
void operator delete (void32 mem);
void operator delete [] (void32 mem);

#endif // __UNION_MEMORY_H__