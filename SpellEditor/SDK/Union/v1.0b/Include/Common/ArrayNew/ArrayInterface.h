#pragma once

namespace Common {
  template <class T>
  Array<T>::Array() {
    Allocator = new ArrayLocator<T>();
    ArrayDefaultSortFunc = Null;
  }

  template <class T>
  Array<T>::Array( T* copy, const uint& count ) {
    Allocator = new ArrayLocator<T>();
    ArrayDefaultSortFunc = Null;

    uint _count = count != Invalid ? count :
      _msize( copy ) / sizeof( T );

    new(GetAllocator()) TObjectLocator<T>[_count];
    for( uint i = 0; i < _count; i++ )
      GetAllocator()[i] = copy[i];
  }

  template <class T>
  Array<T>::Array( Array& other ) {
    Allocator = &other.GetAllocator();
    Allocator->AddReference();
    ArrayDefaultSortFunc = Null;

    /*Allocator = new ArrayLocator<T>();
    ArrayDefaultSortFunc = other.ArrayDefaultSortFunc;
    MergeArray( other );*/
  }

  template <class T>
  Array<T>::Array( const Array& other ) {
    Allocator = new ArrayLocator<T>();
    ArrayDefaultSortFunc = other.ArrayDefaultSortFunc;
    MergeArray( other );
  }

  template <class T>
  ArrayLocator<T>& Array<T>::GetAllocator() {
    return *Allocator;
  }

  template <class T>
  const ArrayLocator<T>& Array<T>::GetAllocator() const {
    return *Allocator;
  }

  template <class T>
  T& Array<T>::Create() {
    return (new(GetAllocator()) TObjectLocator<T>( T() ))->refObject;
  }

  template <class T>
  T& Array<T>::InsertEnd( const T& obj ) {
    return (new(GetAllocator()) TObjectLocator<T>( obj ))->refObject;
  }

  template <class T>
  T& Array<T>::Insert( const T& obj ) {
    return (new(GetAllocator()) TObjectLocator<T>( obj ))->refObject;
  }

  template <class T>
  T& Array<T>::InsertAt( const T& obj, const uint& index ) {
    return (new(GetAllocator(), index) TObjectLocator<T>( obj ))->refObject;
  }

  template <class T>
  T& Array<T>::InsertFront( const T& obj ) {
    return (new(GetAllocator(), 0) TObjectLocator<T>( obj ))->refObject;
  }

  template <class T>
  void Array<T>::Remove( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
      delete Locator;
      GetAllocator().FreeAt( index );
    }
  }

  template <class T>
  void Array<T>::RemoveAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
    delete Locator;
    GetAllocator().FreeAt( index );
  }

  template <class T>
  void Array<T>::FastRemove( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
      delete Locator;
      GetAllocator().FastFreeAt( index );
    }
  }

  template <class T>
  void Array<T>::FastRemoveAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
    delete Locator;
    GetAllocator().FastFreeAt( index );
  }

  template <class T>
  void Array<T>::RemoveAtBounds( const uint& index, const uint& count ) {
    for( uint i = 0; i < count; i++ ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index + i]);
      delete Locator;
    }

    GetAllocator().FreeAt( index, count );
  }

  template <class T>
  void Array<T>::Clear() {
    RemoveAtBounds( 0, GetNum() );
  }

  template <class T>
  void Array<T>::Delete( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
      delete Locator->refObject;
      delete Locator;
      GetAllocator().FreeAt( index );
    }
  }

  template <class T>
  void Array<T>::DeleteAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
    delete Locator->refObject;
    delete Locator;
    GetAllocator().FreeAt( index );
  }
  
  template <class T>
  void Array<T>::FastDelete( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
      delete Locator->refObject;
      delete Locator;
      GetAllocator().FastFreeAt( index );
    }
  }

  template <class T>
  void Array<T>::FastDeleteAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index]);
    delete Locator->refObject;
    delete Locator;
    GetAllocator().FastFreeAt( index );
  }

  template <class T>
  void Array<T>::DeleteAtBounds( const uint& index, const uint& count ) {
    for( uint i = 0; i < count; i++ ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&GetAllocator()[index + i]);
      delete Locator->refObject;
      delete Locator;
    }

    GetAllocator().FreeAt( index, count );
  }

  template <class T>
  void Array<T>::DeleteData() {
    DeleteAtBounds( 0, GetNum() );
  }

  template <class T>
  void Array<T>::MergeArray( const Array& other ) {
    for( uint i = 0; i < other.GetNum(); i++ )
      Insert( other[i] );
  }

  template <class T>
  void Array<T>::MergeArrayAt( const Array& other, const uint& index ) {
    new(GetAllocator(), index) TObjectLocator<T>[other.GetNum()];
    for( uint i = 0; i < other.GetNum(); i++ )
      GetAllocator()[index + i] = other[i];
  }

  template <class T>
  Array<T>& Array<T>::operator += ( const T& obj ) {
    Insert( obj );
    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator += ( const Array& other ) {
    MergeArray( other );
    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator |= ( const T& obj ) {
    if( !HasEqual( obj ) )
      Insert( obj );

    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator |= ( const Array& other ) {
    for( uint i = 0; i < other.GetNum(); i++ )
      (*this) |= other[i];

    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator -= ( const T& obj ) {
    Remove( obj );
    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator -= ( const Array& other ) {
    for( uint i = 0; i < other.GetNum(); i++ )
      Remove( other[i] );

    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator ^= ( const T& obj ) {
    uint index = SearchEqual( obj );
    while( index != Invalid ) {
      RemoveAt( index );
      index = SearchEqual( obj, index );
    }

    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator ^= ( const Array& other ) {
    for( uint i = 0; i < other.GetNum(); i++ )
      (*this) ^= other[i];

    return *this;
  }

  template <class T>
  Array<T>& Array<T>::operator = ( const Array& other ) {
    Clear();
    GetAllocator().PrepareToReserveArray( other.GetNum() );
    for( uint i = 0; i < other.GetNum(); i++ )
      Insert( other[i] );

    return *this;
  }

  template <class T>
  bool Array<T>::operator == ( const Array& other ) const {
    return CompareLinear( other );
  }

  template <class T>
  bool Array<T>::operator & ( const T& obj ) const {
    return HasEqual( obj );
  }

  template <class T>
  bool Array<T>::CompareLinear( const Array& other ) const {
    if( GetNum() != other.GetNum() )
      return false;

    for( uint i = 0; i < GetNum(); i++ ) {
      if( GetAllocator()[i] != other[i] )
        return false;
    }

    return true;
  }

  template <class T>
  bool Array<T>::CompareInsorted( const Array& other ) const {
    uint size1 = GetNum();
    uint size2 = other.GetNum();
    if( size1 != size2 )
      return false;

    for( uint i = 0; i < size1; i++ ) {
      T&   Object  = GetAllocator()[i];
      uint Equals1 = NumberOfEqual( Object );
      uint Equals2 = other.NumberOfEqual( Object );
      if( Equals1 != Equals2 )
        return false;
    }

    return true;
  }

  template <class T>
  Array<T>& Array<T>::Normalize() {
    for( uint i = 0; i < GetNum() - 1; i++ )
      for( uint j = i + 1; j < GetNum(); j++ )
        if( GetAllocator()[i] == GetAllocator()[j] )
          RemoveAt( j-- );

    return *this;
  }

  template <class T>
  T& Array<T>::GetFirst() {
    return GetAllocator()[0];
  }

  template <class T>
  T& Array<T>::GetLast() {
    return GetAllocator()[GetNum() - 1];
  }

  template <class T>
  T& Array<T>::operator []( const uint& index ) {
    return GetAllocator()[index];
  }

  template <class T>
  T* Array<T>::GetSafe( const uint& index ) {
    if( index >= GetNum() )
      return Null;
    return &GetAllocator()[index];
  }

  template <class T>
  const T& Array<T>::operator []( const uint& index ) const {
    return GetAllocator()[index];
  }

  template <class T>
  const T* Array<T>::GetSafe( const uint& index ) const {
    if( index >= GetNum() )
      return Null;
    return &GetAllocator()[index];
  }

  template <class T>
  const T& Array<T>::GetFirst() const {
    return GetAllocator()[0];
  }

  template <class T>
  const T& Array<T>::GetLast() const {
    return GetAllocator()[GetNum() - 1];
  }

  template <class T>
  bool Array<T>::HasEqual( const T& obj ) const {
    return SearchEqual( obj, 0 ) != Invalid;
  }

  template <class T>
  uint Array<T>::SearchEqual( const T& obj, const uint& begin ) const {
    for( uint i = begin; i < GetNum(); i++ )
      if( (T&)GetAllocator()[i] == obj )
        return i;

    return Invalid;
  }

  template <class T>
  uint Array<T>::CountOfEqual( const T& obj ) const {
    uint num = 0;
    for( uint i = 0; i < GetNum(); i++ )
      if( (T&)GetAllocator()[i] == obj )
        num++;

    return num;
  }

  template <class T>
  void Array<T>::ReleaseData() {
    for( uint i = GetNum() - 1; i != Invalid; i-- )
      GetAllocator()[i]->Release();
  }

  template <class T>
  T& Array<T>::InsertSorted( const T& obj, LPARRAYSORTFUNC func ) {
    if( GetNum() == 0 )
      return Insert( obj );

    uint index = FindIndexForObject( obj, func );
    if( index == Invalid )
      return (new(GetAllocator()) TObjectLocator<T>( obj ))->refObject;

    return (new(GetAllocator(), index) TObjectLocator<T>( obj ))->refObject;
  }

  template <class T>
  void Array<T>::MergeArraySorted( const Array& other, LPARRAYSORTFUNC func ) {
    if( !func && !ArrayDefaultSortFunc ) {
      uint index = GetNum();
      new(GetAllocator()) TObjectLocator<T>[other.GetNum()];
      for( uint i = 0; i < other.GetNum(); i++ )
        GetAllocator()[index + i] = other[i];
    }
    else for( uint i = 0; i < other.GetNum(); i++ )
      Insert( other[i], func );
  }

  template <class T>
  bool Array<T>::HasEqualSorted( const T& obj, LPARRAYSORTFUNC func ) const {
    return SearchEqualSorted( obj, func ) != Invalid;
  }

  template <class T>
  uint Array<T>::SearchEqualSorted( const T& obj, LPARRAYSORTFUNC func ) const {
    LPARRAYSORTFUNC sortFunc = func ? func : ArrayDefaultSortFunc;
    if( !sortFunc )
      return SearchEqual( obj );

    uint Index = FindIndexForObject( obj, sortFunc );
    if( GetAllocator()[Index] == obj )
      return Index;
    return Invalid;
  }

  template <class T>
  void Array<T>::RemoveSorted( const T& obj, LPARRAYSORTFUNC func ) {
    LPARRAYSORTFUNC sortFunc = func ? func : ArrayDefaultSortFunc;
    if( !sortFunc )
      return Remove( obj );

    uint Index = FindIndexForObject( obj, sortFunc );
    if( GetAllocator()[Index] == obj )
      RemoveAt( Index );
  }

  template <class T>
  void Array<T>::DeleteSorted( const T& obj, LPARRAYSORTFUNC func ) {
    LPARRAYSORTFUNC sortFunc = func ? func : ArrayDefaultSortFunc;
    if( !sortFunc )
      return Delete( obj );

    uint Index = FindIndexForObject( obj, sortFunc );
    if( GetAllocator()[Index] == obj )
      DeleteAt( Index );
  }

  template <class T>
  uint Array<T>::FindIndexForObject( const T& obj, LPARRAYSORTFUNC func ) const {
    if( GetNum() == 0 )
      return 0;

    LPARRAYSORTFUNC SortFunc = func ? func : ArrayDefaultSortFunc;
    if( !SortFunc )
      return Invalid;

    uint left = 0;
    uint right = GetNum();
    while( true ) {
      uint index = (left + right) / 2;

      const T& Object = GetAllocator()[index];
      bool swap = SortFunc( obj, Object );

      // if object is on range of closest elements
      if( right - left <= 1 )
        return swap ? right : left;

      swap ?
        left = index :
        right = index;

      // if array belong to group of equal objects
      if( obj == GetAllocator()[index] )
        return index;
    }
  }

  template <class T>
  Array<T>& Array<T>::SortByFunc( LPARRAYSORTFUNC func ) {
    if( func == Null ) {
      if( ArrayDefaultSortFunc == Null )
        return *this;

      func = ArrayDefaultSortFunc;
    }

    void* memtmp = malloc( sizeof( T ) );
    for( uint i = 0; i < GetNum() - 1; i++ ) {
      for( uint j = i + 1; j < GetNum(); j++ ) {
        if( func( GetAllocator()[i], GetAllocator()[j] ) ) {
          // swap objects
          memcpy( memtmp,             &GetAllocator()[i], sizeof( T ) );
          memcpy( &GetAllocator()[i], &GetAllocator()[j], sizeof( T ) );
          memcpy( &GetAllocator()[j], memtmp,             sizeof( T ) );
        }
      }
    }
    free( memtmp );
    return *this;
  }

  template <class T>
  void Array<T>::Copy( T** ppmem, const uint& index, const uint& count ) {
    *ppmem = new T[count];
    for( uint i = 0; i < count; i++ )
      (*ppmem)[i] = GetAllocator()[index + i];
  }

  template <class T>
  uint Array<T>::GetNum() const {
    return GetAllocator().GetNum();
  }

  template <class T>
  uint Array<T>::GetTypeSize() const {
    return sizeof( T );
  }

  template <class T>
  void Array<T>::SetDefaultSortFunc( LPARRAYSORTFUNC func ) {
    ArrayDefaultSortFunc = func;
  }

  template <class T>
  void Array<T>::SetLocatorMultiplier( const uint& rate ) {
    GetAllocator().SetLocatorMultiplier( rate );
  }

  template <class T>
  void Array<T>::ShrinkToFit() {
    GetAllocator().ShrinkToFit();
  }

  
  template <class T>
  T* Array<T>::begin() {
    return &GetFirst();
  }

  template <class T>
  const T* Array<T>::begin() const {
    return &GetFirst();
  }
  
  template <class T>
  T* Array<T>::end() {
    return &GetLast() + 1;
  }
  
  template <class T>
  const T* Array<T>::end() const {
    return &GetLast() + 1;
  }

  template <class T>
  const ArrayLocator<T>& Array<T>::GetArrayLocator() const {
    return GetAllocator();
  }

  template <class T>
  Array<T>::~Array() {
    if( GetAllocator().GetRefCrf() == 1 )
      Clear();

    GetAllocator().Release();
  }
}