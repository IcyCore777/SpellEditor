// Supported with union (c) 2018 Union team

#ifndef __ZSTRING_H__VER3__
#define __ZSTRING_H__VER3__

namespace Gothic_II_Addon {


	char spaceChar = ' ';

  enum zTSTR_KIND {
    zSTR_ONLY,
    zSTR_BEFORE,
    zSTR_AFTER,
    zSTR_TO,
    zSTR_FROM
  };

  enum zTSTR_ALIGN {
    zSTR_RIGHT,
    zSTR_CENTER,
    zSTR_LEFT
  };

  class zSTRING {
  public:
    int allocater;
    char* vector;
    int length;
    int reserved;
  public:
	  //zMEMPOOL_DECLARATION(zSTRING, 0x008CDC98)
	
    zSTRING( char const* a0 )                                                     zCall( 0x004010C0 );
    zSTRING()                                                                     zCall( 0x00402AF0 );
    zSTRING( zSTRING const& )                                                     zCall( 0x00416500 );
    zSTRING( int )                                                                zCall( 0x00435870 );
    zSTRING( float xWert, int digits = 20)                                                         zCall( 0x00435970 );
    char& operator[]( unsigned int )                                              zCall( 0x00445A20 );

    zSTRING( double, int )                                                        zCall( 0x00454680 );
    zSTRING( unsigned long )                                                      zCall( 0x00461E90 );
    char* ToChar() const                                                          zCall( 0x004639D0 );
    zSTRING& Lower()                                                              zCall( 0x0046A9F0 );
    zSTRING& Upper()                                                              zCall( 0x0046AB00 );
    zSTRING& UpperFirstLowerRest()                                                zCall( 0x0046AC10 );
    zSTRING& Align(const zTSTR_ALIGN align, int room, const char c = spaceChar)                                      zCall( 0x0046AD60 );
    zSTRING PickWord( unsigned int, zSTRING const&, zSTRING const& ) const        zCall( 0x0046AF80 );
    char const* PickWordPos( unsigned int, zSTRING const&, zSTRING const& ) const zCall( 0x0046B1D0 );
    zSTRING PickWord_Old( int, zSTRING const& ) const                             zCall( 0x0046B340 );
    int Insert( unsigned int, zSTRING const& )                                    zCall( 0x0046B400 );
    zSTRING Inserted( unsigned int, zSTRING const& ) const                        zCall( 0x0046B520 );
    int Overwrite( unsigned int, zSTRING const& )                                 zCall( 0x0046B6A0 );
    zSTRING Overwritten( unsigned int, zSTRING const& ) const                     zCall( 0x0046B890 );
    int DeleteRight( unsigned int )                                               zCall( 0x0046B990 );
    int Delete( unsigned int, unsigned long )                                     zCall( 0x0046BAA0 );
    zSTRING Deleted( unsigned int, unsigned long ) const                          zCall( 0x0046BBB0 );
    int Delete(const zSTRING& xStr, const zTSTR_KIND kind = zSTR_ONLY)            zCall( 0x0046BCF0 );
    zSTRING Deleted( zSTRING const&, zTSTR_KIND ) const                           zCall( 0x0046BEE0 );
    int Copy( unsigned int, unsigned long )                                       zCall( 0x0046BFC0 );
    zSTRING Copied(unsigned int pos, unsigned long length =-1) const                           zCall( 0x0046C170 );
    int Copy( zSTRING const&, zTSTR_KIND const& )                                 zCall( 0x0046C2D0 );
    zSTRING Copied( zSTRING const&, zTSTR_KIND const& ) const                     zCall( 0x0046C550 );
    void TrimLeft(char ch = ' ')                                                         zCall( 0x0046C630 );
    void TrimRight(char ch = ' ')                                                        zCall( 0x0046C770 );
    int Search( int, char const*, unsigned int ) const                            zCall( 0x0046C920 );
    int SearchRev(const zSTRING& substr, unsigned int num = 1) const                           zCall( 0x0046CA20 );
    bool __cdecl Sprintf( char const*, ... )                                      zCall( 0x0046CC60 );
    int Search( zSTRING const&, unsigned int p2 = 1) const                              zCall( 0x00492680 );
    float ToFloat() const                                                         zCall( 0x004936C0 );
    zSTRING& operator =( char const* )                                            zCall( 0x004CFAF0 );
    zSTRING( char )                                                               zCall( 0x0051AC80 );
    zSTRING& operator =( zSTRING const& )                                         zCall( 0x0059CEB0 );
    void Clear()                                                                  zCall( 0x0059D010 );
    int Length() const                                                            zCall( 0x0059D0E0 );
    long ToInt() const                                                            zCall( 0x0059D0F0 );
    int Search( char const*, unsigned int ) const                                 zCall( 0x0059D110 );
    bool IsEmpty() const                                                          zCall( 0x00674210 );
    zSTRING& operator+= ( char const* )                                           zCall( 0x0067A7B0 );
	zSTRING& operator+=(zSTRING& s) { *this += s.ToChar(); return *this;};


    zSTRING( long )                                                               zCall( 0x006CFE50 );
    void Init()                                                                   zCall( 0x006D9B80 );
    zSTRING( zSTRING const* )                                                     zCall( 0x007928D0 );
    virtual ~zSTRING()                                                            zCall( 0x00401160 );  // scalar:0x00401140 vector:0x0041C760 destructor:0x00401160
	void assign(char const *);
	inline operator Common::CString() {
		return ToChar();
	}
	inline operator const Common::CString() const {
		return ToChar();
	}


	inline zSTRING Characters(char ch, int anzahl)
	{
		return zSTRING((float)anzahl, ch);
	}




	friend int operator!=(const zSTRING& xStr1, const zSTRING& xStr2) { return strcmp(xStr1.ToChar(),xStr2.ToChar()) != 0; }

	friend int operator!=(const zSTRING& xStr1, const char* const xStr2) { return strcmp(xStr1.ToChar(), xStr2) != 0; }


	friend int operator!=(const char* xStr1, const zSTRING& xStr2) { return strcmp(xStr1, xStr2.ToChar()) != 0; }

  };



  inline zSTRING operator+(zSTRING const &, zSTRING const &)
  {
	  XCALL(0x004045C0);
  };

  inline zSTRING operator+(char const *, zSTRING const &)
  {
	  XCALL(0x00404710);
  };

  inline zSTRING operator+(zSTRING const &, char const *)
  {
	  XCALL(0x00404880);
  };

  inline zSTRING operator+(zSTRING const &, char)
  {
	  XCALL(0x00445DD0);
  };

  inline zSTRING operator+(char, class zSTRING const &)
  {
	  XCALL(0x0044A190);
  };
  inline BOOL operator==(zSTRING const &, char const * const)
  {
	  XCALL(0x006CFF50);
  };

  inline BOOL operator==(zSTRING const &, zSTRING const &)
  {
	  XCALL(0x00674220);
  };
  inline zSTRING Characters(char,int)  zCall(0x0046A8F0);
} // namespace Gothic_II_Addon



#endif // __ZSTRING_H__VER3__