#pragma once

namespace Common {
#pragma pack( push, 1 )
  // A clear dynamic array class
  template <class T>
  class ArrayLocator {
    T*   Vector;
    uint Count;
    uint FullCount;
    uint MemoryUsed;
    uint MemoryAllocated;
    uint AllocMultiplier;
    uint refCrt;
  protected:

    void AllocArray ( const uint& newCount );
    void ReduceArray( const uint& newCount );
    void InitArray  ();
  public:

    uint AddReference();
    uint Release() ;
    const uint GetRefCrf() const;

    ArrayLocator   ();
    T* AllocEnd    ( const uint& count = 1 );
    T* AllocFront  ( const uint& count = 1 );
    T* AllocAt     ( const uint& index, const uint& count = 1 );
    void FreeEnd   ( const uint& count = 1 );
    void FreeFront ( const uint& count = 1 );
    void FreeAt    ( const uint& index, const uint& count = 1 );
    void FastFreeAt( const uint& index, const uint& count = 1 );

          T& operator [] ( const uint& index );
    const T& operator [] ( const uint& index ) const;

    uint GetNum               () const;
    uint GetUsedMemory        () const;
    uint GetAllocatedMemory   () const;
    void SetLocatorMultiplier ( const uint& rate );
    void PrepareToReserveArray( const uint& count );
    void ShrinkToFit          ();
    ~ArrayLocator             ();
  };


  // A dynamic object constructor for arrays
  template <class T>
  struct TObjectLocator {
    T refObject;

    TObjectLocator() {}
    TObjectLocator( const T& obj );

    static void* operator new    ( size_t size, ArrayLocator<T>& allocator );
    static void* operator new    ( size_t size, ArrayLocator<T>& allocator, const uint& index );
    static void* operator new[]  ( size_t size, ArrayLocator<T>& allocator );
    static void* operator new[]  ( size_t size, ArrayLocator<T>& allocator, const uint& index );
    static void operator delete  ( void* mem);
    static void operator delete  ( void* mem, ArrayLocator<T>& allocator );
    static void operator delete  ( void* mem, ArrayLocator<T>& allocator, const uint& index );
    static void operator delete[]( void* mem, ArrayLocator<T>& allocator );
    static void operator delete[]( void* mem, ArrayLocator<T>& allocator, const uint& index );
  };


#pragma warning(disable:4521)
  // A dynamic array interface
  template <class T>
  class Array {
    typedef bool( *LPARRAYSORTFUNC )(const T& left, const T& right);

    ArrayLocator<T>* Allocator;
    LPARRAYSORTFUNC ArrayDefaultSortFunc;
    ArrayLocator<T>& GetAllocator();
    const ArrayLocator<T>& GetAllocator() const;
  public:

    Array();

    // Copy data from memory
    Array( T* copy, const uint& count = Invalid );

    // Copy data from other array
    Array( Array& other );       // !!! Reference
    Array( const Array& other ); // !!! Copy




    // Create new empty object
    T& Create();




    // Include object to array as last
    T& InsertEnd( const T& obj );

    // Include object to array as last
    T& Insert( const T& obj );

    // Include object to array to index
    T& InsertAt( const T& obj, const uint& index );

    // Include object to array as first
    T& InsertFront( const T& obj );




    // Remove element from array
    void Remove( const T& obj );

    // Remove element from array
    void RemoveAt( const uint& index );

    // Remove element from array and move last element to intex of deleted element
    void FastRemove( const T& obj );

    // Remove element from array and move last element to this intex
    void FastRemoveAt( const uint& index );

    // Remove elements from array in bounds
    void RemoveAtBounds( const uint& index, const uint& count );

    // Remove all elements from array
    void Clear();




    // Remove element from array (with free memory)
    void Delete( const T& obj );

    // Remove element from array (with free memory)
    void DeleteAt( const uint& index );

    // Remove element from array and move last element to intex of deleted element (with free memory)
    void FastDelete( const T& obj );

    // Remove element from array and move last element to this intex (with free memory)
    void FastDeleteAt( const uint& index );

    // Remove elements from array in bounds (with free memory)
    void DeleteAtBounds( const uint& index, const uint& count );
    
    // Remove elements from array (with free memory)
    void DeleteData();




    // Include all elements of other array to this array
    void MergeArray( const Array& other );

    // Include all elements of other array to this array in position
    void MergeArrayAt( const Array& other, const uint& index );




    // include object to array
    Array& operator += ( const T&     obj );
    Array& operator += ( const Array& other );

    // Include object if array NOT has equal objects
    Array& operator |= ( const T&     obj );
    Array& operator |= ( const Array& other );

    // Exclude first equal object from this array
    Array& operator -= ( const T&     obj );
    Array& operator -= ( const Array& other );

    // Exclude all equal objects from this array
    Array& operator ^= ( const T&     obj );
    Array& operator ^= ( const Array& other );

    // Copy data from other array to this array
    Array& operator = ( const Array& other );

    // Return true if arrays is equal
    bool operator == ( const Array& other ) const;

    // Returt true if array has equal object
    bool operator & ( const T& obj ) const;




    // Ordered comparing arrays contents
    bool CompareLinear  ( const Array& other ) const;

    // Inordered comparing arrays contents
    bool CompareInsorted( const Array& other ) const;

    // Remove all dubles
    Array& Normalize();




    // Return reference to object by index
    const T& operator[]( const uint& index ) const;
          T& operator[]( const uint& index );
    
    // Return pointer to object by index. Return Null if inexists. 
    const T* GetSafe( const uint& index ) const;
          T* GetSafe( const uint& index );

    // Return first element from this array
    const T& GetFirst() const;
          T& GetFirst  ();

    // Return last element from this array
    const T& GetLast() const;
          T& GetLast();




    // Has first equal element in this array
    bool HasEqual( const T& obj ) const;

    // Search first index of qeual element after 'begin' index
    uint SearchEqual( const T& obj, const uint& begin = 0 ) const;

    // Calculate num of equal objects in this array
    uint CountOfEqual( const T& obj ) const;

    // Call 'Release' function for all elements of array
    void ReleaseData ();




    // Sorted insert function
    T& InsertSorted( const T& obj, LPARRAYSORTFUNC func = Null );

    // Sorted copy contents from other array and past to this array
    void MergeArraySorted( const Array& other, LPARRAYSORTFUNC func = Null );

    // Sorted search equal object
    bool HasEqualSorted( const T& obj, LPARRAYSORTFUNC func = Null ) const;

    // Sorted search index of equal object
    uint SearchEqualSorted( const T& obj, LPARRAYSORTFUNC func = Null ) const;

    // Remove object with sorted search algorithm
    void RemoveSorted( const T& obj, LPARRAYSORTFUNC func = Null );

    // Remove with free object memory with sorted search algorithm
    void DeleteSorted( const T& obj, LPARRAYSORTFUNC func = Null );

    // Find best index for object by sort func
    uint FindIndexForObject( const T& obj, LPARRAYSORTFUNC func = Null ) const;

    // Sorting all elements of array
    Array& SortByFunc( LPARRAYSORTFUNC func = Null );




    // Copy this array to other memory
    void Copy( T** ppmem, const uint& index, const uint& count );

    // Num elements in array
    uint GetNum() const;

    // Size of T type
    uint GetTypeSize() const;




    // Set default sort func...
    void SetDefaultSortFunc( LPARRAYSORTFUNC func );

    // Multiplier of next preallocated array size
    void SetLocatorMultiplier( const uint& rate );

    // Realloc array size as used memory bounds
    void ShrinkToFit();




    //
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;
    



    // Dynamic array oject
    const ArrayLocator<T>& GetArrayLocator() const;

    virtual ~Array();
  };
#pragma warning(default:4521)
#pragma pack( pop )
}

#include "ArrayLocator.h"
#include "ObjectLocator.h"
#include "ArrayInterface.h"