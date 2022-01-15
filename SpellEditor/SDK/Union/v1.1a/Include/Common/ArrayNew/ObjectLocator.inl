// Supported with union (c) 2018 Union team

#ifdef __NEW_ARRAY_DEFINITIONS__
#ifndef __NEW_ARRAY_OBJECT_LOCATOR_INL__
#define __NEW_ARRAY_OBJECT_LOCATOR_INL__

namespace Common {
  template <class T>
  TObjectLocator<T>::TObjectLocator( const T& obj ) {
    refObject = obj;
  }



  template <class T>
  void* TObjectLocator<T>::operator new(size_t size, ArrayLocator<T>& allocator){
    return allocator.AllocEnd();
  }



  template <class T>
  void* TObjectLocator<T>::operator new(size_t size, ArrayLocator<T>& allocator, const uint& index) {
    return allocator.AllocAt( index );
  }



  template <class T>
  void* TObjectLocator<T>::operator new[](size_t size, ArrayLocator<T>& allocator){
    return allocator.AllocEnd( size / sizeof( T ) );
  }



  template <class T>
  void* TObjectLocator<T>::operator new[](size_t size, ArrayLocator<T>& allocator, const uint& index){
    return allocator.AllocAt( index, size / sizeof( T ) );
  }



  template <class T>
  void TObjectLocator<T>::operator delete(void* mem) {
    // ~refObject
  }



  template <class T>
  void TObjectLocator<T>::operator delete(void* mem, ArrayLocator<T>& allocator) {
    allocator.FreeAt( allocator.GetNum() - 1 );
  }



  template <class T>
  void TObjectLocator<T>::operator delete(void* mem, ArrayLocator<T>& allocator, const uint& index) {
    allocator.FreeAt( index );
  }



  template <class T>
  void TObjectLocator<T>::operator delete[](void* mem, ArrayLocator<T>& allocator) {
    allocator.FreeAt( allocator.GetNum() - 1 ); // ??
  }



  template <class T>
  void TObjectLocator<T>::operator delete[](void* mem, ArrayLocator<T>& allocator, const uint& index) {
    allocator.FreeAt( index ); // ??
  }
}

#endif // __NEW_ARRAY_OBJECT_LOCATOR_INL__
#endif // __NEW_ARRAY_DEFINITIONS__