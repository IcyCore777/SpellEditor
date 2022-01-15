// Supported with union (c) 2018 Union team

#ifndef __UNION_TYPES_H__
#define __UNION_TYPES_H__

namespace Common
{
  typedef          char     int8;
  typedef unsigned char     uint8;
  typedef          short    int16;
  typedef unsigned short    uint16, *bytecode;// , *p_code;
  typedef          int      int32;
  typedef unsigned int      uint32, bool32, uint;
  typedef         long      long32;
  typedef unsigned long     ulong32, uflag32;
  typedef          __int64  int64, long64;
  typedef unsigned __int64  uint64, ulong64, uflag64;
  typedef          float    real32;
  typedef          double   real64;
  typedef          void     *void32;
  typedef          void     *void64;
  typedef          char     *text, *HBuffer;
  typedef          wchar_t  *wtext, *HWBuffer;
  typedef         HINSTANCE HPLUGIN;

  template <typename T>
  T& const_ptr( const T& _Dst_ )
  {
    return const_cast<T&>( _Dst_ );
  }

  template <typename T>
  inline void _swap( T& arg1, T& arg2 )
  {
    T tmp = arg1;
    arg1  = arg2;
    arg2  = tmp;
  }

  struct p_code {
    uint32 address;

    p_code() {
      address = 0U;
    }

    p_code( const int32& addr ) {
      address = addr;
    }

    p_code( const uint32& addr ) {
      address = addr;
    }

    p_code( const void32& addr ) {
      address = (uint32)addr;
    }

    operator void32& () {
      return (void32&)address;
    }

    operator const void32 () const {
      return (void32)address;
    }

    operator uint32& () {
      return address;
    }

    operator const uint32 () const {
      return address;
    }

    p_code& operator += ( const p_code& code ) {
      address += code.address;
      return *this;
    }

    p_code& operator -= ( const p_code& code ) {
      address -= code.address;
      return *this;
    }

    p_code operator + ( const p_code& code ) const {
      return p_code( address + code.address );
    }

    p_code operator - ( const p_code& code ) const {
      return p_code( address - code.address );
    }

    p_code operator + ( const uint32& code ) const {
      return p_code( address + code );
    }

    p_code operator - ( const uint32& code ) const {
      return p_code( address - code );
    }

    p_code operator + ( const int32& code ) const {
      return p_code( address + code );
    }

    p_code operator - ( const int32& code ) const {
      return p_code( address - code );
    }

    p_code operator + ( const void32& code ) const {
      return p_code( address + (uint32)code );
    }

    p_code operator - ( const void32& code ) const {
      return p_code( address - (uint32)code );
    }
  };

} // namespace Common

#endif // __UNION_ALLOCATOR_32_H__