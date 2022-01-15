// Supported with union (c) 2018 Union team

#ifdef __NEW_ARRAY_DEFINITIONS__
#ifndef __NEW_ARRAY_DEFINITION_INL__
#define __NEW_ARRAY_DEFINITION_INL__

namespace Common {
  template <class T>
  Array<T>::Array() {
    ArraySortFunc = Null;
  }



  template <class T>
  Array<T>::Array( T* copy, const uint& count ) {
    ArraySortFunc = Null;

    uint _count = count != Invalid ? count :
      _msize( copy ) / sizeof( T );

    new(Allocator) TObjectLocator<T>[_count];
    for( uint i = 0; i < _count; i++ )
      Allocator[i] = copy[i];
  }



  template <class T>
  Array<T>::Array( const Array& other ) {
    ArraySortFunc = Null;
    MergeArray( other );
  }



  template <class T>
  uint Array<T>::FindIndexForObject( const T& obj, LPARRAYSORTFUNC func ) {
    LPARRAYSORTFUNC SortFunc = func ? func : ArraySortFunc;
    if( !SortFunc )
      return Invalid;

    uint left = 0;
    uint right = GetNum();
    while( true ) {
      uint index = (left + right) / 2;

      T&   Object = Allocator[index];
      bool swap = SortFunc( obj, Object );

      // if object is on range of closest elements
      if( right - left <= 1 )
        return swap ? right : left;

      swap ?
        left  = index :
        right = index;

      // if array belong to group of equal objects
      if( obj == Allocator[index] )
        return index;
    }
  }



  template <class T>
  void Array<T>::InsertEnd( const T& obj ) {
    new(Allocator) TObjectLocator<T>( obj );
  }



  template <class T>
  void Array<T>::Insert( const T& obj ) {
    new(Allocator) TObjectLocator<T>( obj );
  }



  template <class T>
  void Array<T>::InsertSorted( const T& obj, LPARRAYSORTFUNC func ) {
    if( GetNum() == 0 )
      return Insert( obj );

    uint index = FindIndexForObject( obj, func );

    if( index == Invalid ) {
      new(Allocator) TObjectLocator<T>( obj );
      return;
    }
    new(Allocator, index) TObjectLocator<T>( obj );
  }



  template <class T>
  void Array<T>::InsertAt( const T& obj, const uint& index ) {
    new(Allocator, index) TObjectLocator<T>( obj );
  }



  template <class T>
  void Array<T>::InsertFront( const T& obj ) {
    new(Allocator, 0) TObjectLocator<T>( obj );
  }



  template <class T>
  void Array<T>::Remove( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
      delete Locator;
      Allocator.FreeAt( index );
    }
  }



  template <class T>
  void Array<T>::RemoveAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
    delete Locator;
    Allocator.FreeAt( index );
  }



  template <class T>
  void Array<T>::FastRemove( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
      delete Locator;
      Allocator.FastFreeAt( index );
    }
  }



  template <class T>
  void Array<T>::FastRemoveAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
    delete Locator;
    Allocator.FastFreeAt( index );
  }



  template <class T>
  void Array<T>::RemoveAtBounds( const uint& index, const uint& count ) {
    for( uint i = 0; i < count; i++ ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index + i]);
      delete Locator;
    }
    Allocator.FreeAt( index, count );
  }



  template <class T>
  void Array<T>::Clear() {
    RemoveAtBounds( 0, GetNum() );
  }



  template <class T>
  void Array<T>::Delete( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
      delete Locator->refObject;
      delete Locator;
      Allocator.FreeAt( index );
    }
  }



  template <class T>
  void Array<T>::DeleteAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
    delete Locator->refObject;
    delete Locator;
    Allocator.FreeAt( index );
  }



  template <class T>
  void Array<T>::FastDelete( const T& obj ) {
    uint index = SearchEqual( obj );
    if( index != Invalid ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
      delete Locator->refObject;
      delete Locator;
      Allocator.FastFreeAt( index );
    }
  }



  template <class T>
  void Array<T>::FastDeleteAt( const uint& index ) {
    TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index]);
    delete Locator->refObject;
    delete Locator;
    Allocator.FastFreeAt( index );
  }



  template <class T>
  void Array<T>::DeleteAtBounds( const uint& index, const uint& count ) {
    for( uint i = 0; i < count; i++ ) {
      TObjectLocator<T>* Locator = reinterpret_cast<TObjectLocator<T>*>(&Allocator[index + i]);
      delete Locator->refObject;
      delete Locator;
    }
    Allocator.FreeAt( index, count );
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
  void Array<T>::MergeArraySorted( const Array& other, LPARRAYSORTFUNC func ) {
    if( !func && !ArraySortFunc ) {
      uint index = GetNum();
      new(Allocator) TObjectLocator<T>[other.GetNum()];
      for( uint i = 0; i < other.GetNum(); i++ )
        Allocator[index + i] = other[i];
    }
    else for( uint i = 0; i < other.GetNum(); i++ )
      Insert( other[i], func );
  }



  template <class T>
  void Array<T>::MergeArrayAt( const Array& other, const uint& index ) {
    new(Allocator, index) TObjectLocator<T>[other.GetNum()];
    for( uint i = 0; i < other.GetNum(); i++ )
      Allocator[index + i] = other[i];
  }



  template <class T>
  T& Array<T>::operator []( const uint& index ) {
    return Allocator[index];
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
    new(Allocator) TObjectLocator<T>[other.GetNum()];
    for( uint i = 0; i < other.GetNum(); i++ )
      Allocator[i] = other[i];
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
      if( Allocator[i] != other[i] )
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
      T&   Object = Allocator[i];
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
        if( Allocator[i] == Allocator[j] )
          RemoveAt( j-- );
    return *this;
  }



  template <class T>
  Array<T>& Array<T>::SortByFunc( LPARRAYSORTFUNC func ) {
    void* memtmp = malloc( sizeof( T ) );
    for( uint i = 0; i < GetNum() - 1; i++ ) {
      for( uint j = i + 1; j < GetNum(); j++ ) {
        if( func( Allocator[i], Allocator[j] ) ) {
          // swap objects
          memcpy( memtmp,        &Allocator[i], sizeof( T ) );
          memcpy( &Allocator[i], &Allocator[j], sizeof( T ) );
          memcpy( &Allocator[j], memtmp,        sizeof( T ) );
        }
      }
    }
    free( memtmp );
    return *this;
  }



  template <class T>
  T& Array<T>::GetFirst() {
    return Allocator[0];
  }



  template <class T>
  T& Array<T>::GetLast() {
    return Allocator[GetNum() - 1];
  }



  template <class T>
  const T& Array<T>::operator []( const uint& index ) const {
    return Allocator[index];
  }



  template <class T>
  T* Array<T>::GetSafe( const uint& index ) {
    if( index >= GetNum() )
      return Null;
    return &Allocator[index];
  }



  template <class T>
  const T* Array<T>::GetSafe( const uint& index ) const {
    if( index >= GetNum() )
      return Null;
    return &Allocator[index];
  }



  template <class T>
  const T& Array<T>::GetFirst() const {
    return Allocator[0];
  }



  template <class T>
  const T& Array<T>::GetLast() const {
    return Allocator[GetNum() - 1];
  }



  template <class T>
  bool Array<T>::HasEqual( const T& obj ) const {
    return SearchEqual( obj, 0 ) != Invalid;
  }



  template <class T>
  uint Array<T>::SearchEqual( const T& obj, const uint& begin ) const {
    for( uint i = begin; i < GetNum(); i++ )
      if( (T&)Allocator[i] == obj )
        return i;
    return Invalid;
  }



  template <class T>
  uint Array<T>::CountOfEqual( const T& obj ) const {
    uint num = 0;
    for( uint i = 0; i < GetNum(); i++ )
      if( (T&)Allocator[i] == obj )
        num++;
    return num;
  }



  template <class T>
  void Array<T>::ReleaseData() {
    for( uint i = GetNum() - 1; i != Invalid; i-- )
      Allocator[i]->Release();
  }



  template <class T>
  bool Array<T>::HasEqualSorted( const T& obj, LPARRAYSORTFUNC func ) const {
    return SearchEqualSorted( const T& obj, LPARRAYSORTFUNC func ) != Invalid;
  }



  template <class T>
  uint Array<T>::SearchEqualSorted( const T& obj, LPARRAYSORTFUNC func ) const {
    LPARRAYSORTFUNC sortFunc = func ? func : ArraySortFunc;
    if( !sortFunc )
      return SearchEqual( obj );
  
    uint Index = FindIndexForObject( obj, sortFunc );
    if( Allocator[Index] == obj )
      return Index;
    return Invalid;
  }



  template <class T>
  void Array<T>::RemoveSorted( const T& obj, LPARRAYSORTFUNC func ) {
    LPARRAYSORTFUNC sortFunc = func ? func : ArraySortFunc;
    if( !sortFunc )
      return Remove( obj );

    uint Index = FindIndexForObject( obj, sortFunc );
    if( Allocator[Index] == obj )
      RemoveAt( Index );
  }



  template <class T>
  void Array<T>::DeleteSorted( const T& obj, LPARRAYSORTFUNC func ) {
    LPARRAYSORTFUNC sortFunc = func ? func : ArraySortFunc;
    if( !sortFunc )
      return Delete( obj );

    uint Index = FindIndexForObject( obj, sortFunc );
    if( Allocator[Index] == obj )
      DeleteAt( Index );
  }



  template <class T>
  void Array<T>::Copy( T** ppmem, const uint& index, const uint& count ) {
    *ppmem = new T[count];
    for( uint i = 0; i < count; i++ )
      (*ppmem)[i] = Allocator[index + i];
  }



  template <class T>
  uint Array<T>::GetNum() const {
    return Allocator.GetNum();
  }



  template <class T>
  uint Array<T>::GetTypeSize() const {
    return sizeof( T );
  }



  template <class T>
  void Array<T>::SetDefaultSortFunc( LPARRAYSORTFUNC func ) {
    ArraySortFunc = func;
  }



  template <class T>
  void Array<T>::SetLocatorMultiplier( const uint& rate ) {
    Allocator.SetLocatorMultiplier( rate );
  }



  template <class T>
  void Array<T>::ShrinkToFit() {
    Allocator.ShrinkToFit();
  }



  template <class T>
  const ArrayLocator<T>& Array<T>::GetArrayLocator() const {
    return Allocator;
  }



  template <class T>
  Array<T>::~Array() {
    Clear();
  }
}

#endif // __NEW_ARRAY_DEFINITION_INL__
#endif // __NEW_ARRAY_DEFINITIONS__