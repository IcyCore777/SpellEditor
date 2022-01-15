// Supported with union (c) 2018 Union team

#ifndef __NEW_ARRAY_H__
#define __NEW_ARRAY_H__
#define __NEW_ARRAY_DEFINITIONS__

namespace Common {
  template <class T>
  class ArrayLocator {
    T*   Vector;
    uint Count;
    uint FullCount;
    uint MemoryUsed;
    uint MemoryAllocated;
    uint AllocMultiplier;

    void AllocArray ( const uint& newCount );
    void ReduceArray( const uint& newCount );
    void InitArray();

  public:

    ArrayLocator();

    T*   AllocEnd  ( const uint& count = 1 );
    T*   AllocFront( const uint& count = 1 );
    T*   AllocAt   ( const uint& index, const uint& count = 1 );
    void FreeEnd   ( const uint& count = 1 );
    void FreeFront ( const uint& count = 1 );
    void FreeAt    ( const uint& index, const uint& count = 1 );
    void FastFreeAt( const uint& index, const uint& count = 1 );

          T& operator [] ( const uint& index );
    const T& operator [] ( const uint& index ) const;

    uint GetNum() const;

    uint GetUsedMemory        () const;
    uint GetAllocatedMemory   () const;
    void SetLocatorMultiplier ( const uint& rate );
    void PrepareToReserveArray( const uint& count );
    void ShrinkToFit();

    ~ArrayLocator();
  };



  template <class T>
  struct TObjectLocator {
    T refObject;
    TObjectLocator() {}
    TObjectLocator( const T& obj );
  
    static void* operator new  ( size_t size, ArrayLocator<T>& allocator );
    static void* operator new  ( size_t size, ArrayLocator<T>& allocator, const uint& index );
    static void* operator new[]( size_t size, ArrayLocator<T>& allocator );
    static void* operator new[]( size_t size, ArrayLocator<T>& allocator, const uint& index );

    static void  operator delete  ( void* mem );
    static void  operator delete  ( void* mem, ArrayLocator<T>& allocator );
    static void  operator delete  ( void* mem, ArrayLocator<T>& allocator, const uint& index );
    static void  operator delete[]( void* mem, ArrayLocator<T>& allocator);
    static void  operator delete[]( void* mem, ArrayLocator<T>& allocator, const uint& index);
  };



  template <class T>
  inline bool operator == ( const T& obj1, const T& obj2 ) {
    return memcmp( &obj1, &obj2, sizeof( T ) ) == 0;
  }




  template <class T>
  class Array {

    typedef bool( *LPARRAYSORTFUNC )(const T& left, const T& right);

    ArrayLocator<T> Allocator;
    LPARRAYSORTFUNC ArraySortFunc;

  public:

    Array();
    Array( T* copy, const uint& count = Invalid );
    Array( const Array& other );

    void InsertEnd     ( const T& obj );
    void Insert        ( const T& obj );
    void InsertAt      ( const T& obj, const uint& index );
    void InsertFront   ( const T& obj );

    void Remove        ( const T& obj );
    void RemoveAt      ( const uint& index );
    void FastRemove    ( const T& obj );
    void FastRemoveAt  ( const uint& index );
    void RemoveAtBounds( const uint& index, const uint& count );
    void Clear         ();

    void Delete        ( const T& obj );
    void DeleteAt      ( const uint& index );
    void FastDelete    ( const T& obj );
    void FastDeleteAt  ( const uint& index );
    void DeleteAtBounds( const uint& index, const uint& count );
    void DeleteData    ();

    void MergeArray  ( const Array& other );
    void MergeArrayAt( const Array& other, const uint& index );

    Array& operator += ( const T& obj );
    Array& operator += ( const Array& other );
    Array& operator |= ( const T& obj );
    Array& operator |= ( const Array& other );
    Array& operator -= ( const T& obj );
    Array& operator -= ( const Array& other );
    Array& operator ^= ( const T& obj );
    Array& operator ^= ( const Array& other );
    Array& operator =  ( const Array& other );
    bool   operator == ( const Array& other ) const;
    bool   operator &  ( const T& obj ) const;

    bool CompareLinear( const Array& other ) const;
    bool CompareInsorted( const Array& other ) const;

    Array& Normalize(); // удалить дубликаты

          T& GetFirst  ();
          T& GetLast   ();
          T& operator[]( const uint& index );
          T* GetSafe   ( const uint& index );
    const T& operator[]( const uint& index ) const;
    const T* GetSafe   ( const uint& index ) const;
    const T& GetFirst  () const;
    const T& GetLast   () const;

    bool HasEqual    ( const T& obj ) const;
    uint SearchEqual ( const T& obj, const uint& begin = 0 ) const;
    uint CountOfEqual( const T& obj ) const;
    void ReleaseData ();
  
    void   InsertSorted      ( const T& obj,       LPARRAYSORTFUNC func = Null );
    void   MergeArraySorted  ( const Array& other, LPARRAYSORTFUNC func = Null );
    bool   HasEqualSorted    ( const T& obj,       LPARRAYSORTFUNC func = Null ) const;
    uint   SearchEqualSorted ( const T& obj,       LPARRAYSORTFUNC func = Null ) const;
    void   RemoveSorted      ( const T& obj,       LPARRAYSORTFUNC func = Null );
    void   DeleteSorted      ( const T& obj,       LPARRAYSORTFUNC func = Null );
    uint   FindIndexForObject( const T& obj,       LPARRAYSORTFUNC func = Null );
    Array& SortByFunc        ( LPARRAYSORTFUNC func );

    void Copy       ( T** ppmem, const uint& index, const uint& count );
    uint GetNum     () const;
    uint GetTypeSize() const;

    void SetDefaultSortFunc( LPARRAYSORTFUNC func );
    void SetLocatorMultiplier( const uint& rate );
    void ShrinkToFit();

    const ArrayLocator<T>& GetArrayLocator() const;
    virtual ~Array();
  };
}

#include "ArrayLocator.inl"
#include "ObjectLocator.inl"
#include "Array.inl"

#undef __NEW_ARRAY_DEFINITIONS__
#endif // __NEW_ARRAY_H__


#if 0

// Numbers sort example
bool SortFunc_Numbers( const uint& l, const uint& r ) {
  return l > r;
}

// Random sort example
bool SortFunc_Random( const uint& l, const uint& r ) {
return rand() % 3 == 0;
}

// Strings sort example
bool SortFunc_Strings( const string& l, const string& r ) {
  uint Length = min( l.Length(), r.Length() );
  for( uint i = 0; i < Length; i++ ) {
    if( l[i] != r[i] )
      return l[i] > r[i];
  }
  return l.Length() > r.Length();
}

#endif