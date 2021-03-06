// Supported with union (c) 2018 Union team

#ifndef __ZMACRO_H__VER3__
#define __ZMACRO_H__VER3__

namespace Gothic_II_Addon {

#define zRELEASE(obj) { if (obj) { obj->Release(); obj=0; }; };
#define zADDREF( obj )  (obj)->AddRef()
#define zNEW( obj ) new obj
#define zDELETE( obj ) delete obj
#ifndef SAFE_DELETE
#define SAFE_DELETE( obj ) if( obj ) { delete obj; obj = 0; }
#endif



#define zCLASS_DECLARATION( className )					\
	static zCClassDef* classDef;						\
														\
public:													\
														\
	static void* operator new(size_t nSize)				\
	{													\
		void* p = ::operator new(nSize);				\
		zCClassDef::ObjectCreated(						\
		(className*)p, classDef);						\
		return p;										\
	}													\


#define zEVENT_INTERFACE
#define zCOLLISION_OBJECT_DECLARATION( classname )
#define zCall( address ) { XCALL( address ); }
#define zInit( call ) { if( Union.GetEngineVersion() == Engine_G2A ) call; }
#define zRTTI( type ) { return type; }
#ifndef __DONT_USE_VTABLE__
#define zPureCall = 0;
#else
#define zPureCall ;
#define virtual
#endif
#define group struct
#define RGBA(r,g,b,a)   ((zUINT32)(zUINT8)(r)|(zUINT32)(zUINT8)(g)<<8|(zUINT32)(zUINT8)(b)<<16|(zUINT32)(zUINT8)(a)<<24)
#define EXTRACT_R(rgba) (rgba		& 0xff)
#define EXTRACT_G(rgba) (rgba >> 8	& 0xff)
#define EXTRACT_B(rgba) (rgba >> 16 & 0xff)
#define EXTRACT_A(rgba) (rgba >> 24 & 0xff)
#define zMEMPOOL_VOLATILE_DECLARATION( className )

#define SafeDiv( a, b ) \
    ( a == 0.0 ? 0.0 : b == 0.0 ? 0.0 : a / b )

#define sqr(a) (a * a)

#define CalcAngle(a, b)                 \
    float angle = atan (SafeDiv(a, b)); \
    if (a >= 0 && b < 0)                \
    angle = 180.0f / DEGREE + angle;    \
    else if (a < 0 && b <= 0)           \
    angle = 180.0f / DEGREE + angle;    \
    else if (a <= 0 && b > 0)           \
    angle = 360.0f / DEGREE + angle;    \
    return angle;

#define RotAngle(a, b, c)                     \
    float radAngle = GetAngle##c();           \
    float length   = sqrt(sqr(a) + sqr(b));   \
    radAngle      += rad;                     \
    a              = sin(radAngle) * length;  \
    b              = cos(radAngle) * length;  \
    return *this;
	
#define zMEMPOOL_DECLARATION_TEMPLATE( classname, address )                                         \
    void *operator new( size_t s ) {                                                                \
      return ((zCMemPoolBase*)address)->Alloc();                                                    \
    }                                                                                               \
    void operator delete( void *p ) {                                                               \
      ((zCMemPoolBase*)address)->Free( p );                                                         \
    }                                                                                               \
    void* operator new( unsigned int size, const char* classn, const char *file, int l ) {          \
      zCMemPoolBase::SetMemDebug( classn, file, l );                                                \
      return operator new( size );                                                                  \
    }                                                                                               \
    void operator delete( void* ptr, const char* classn, const char* file, int line ) {             \
      operator delete( ptr );                                                                       \
    }                                                                                               \
    static void PreAlloc( size_t num, zBOOL force_oneblock = False ){                               \
      ((zCMemPoolBase*)address)->PreAlloc( num, force_oneblock );                                   \
    }

#define zMEMPOOL_DECLARATION( classname, address )                                                  \
    void* operator new( size_t s ){                                                                 \
      return ((zCMemPoolBase*)address)->Alloc();                                                    \
    }                                                                                               \
    void operator delete( void* p ) {                                                               \
      ((zCMemPoolBase*)address)->Free( p );                                                         \
    }                                                                                               \
    void* operator new( unsigned int size, const char* classn, const char* file, int l ) {          \
      zCMemPoolBase::SetMemDebug( classn, file, l);                                                 \
      return operator new(size);                                                                    \
    }                                                                                               \
    void  operator delete( void* ptr,const char *classn,const char *file,int line) {                \
      operator delete(ptr);                                                                         \
    }                                                                                               \
    static void PreAlloc( size_t num, bool32 force_oneblock = False ) {                             \
      ((zCMemPoolBase*)address)->PreAlloc( num, force_oneblock );                                   \
    }                                                                                               \
    static void PoolAdd( classname *mem, int num_objects, bool32 free = False ) {                   \
      ((zCMemPoolBase*)address)->PoolAdd( mem, num_objects, free );                                 \
    }

// class declaration for union zobject classes
#define zCLASS_UNION_DECLARATION( className )                \
  static zCClassDef* className::classDef;                    \
  static zCObject* className::_CreateNewInstance( void );    \
  virtual zCClassDef* className::_GetClassDef( void ) const; \
  void* className::operator new(size_t size);                \
  void className::operator delete(void* mem);


// class definition for union zobject classes
#define zCLASS_UNION_DEFINITION( className, baseClassName, classFlags, archiveVersion )                                                         \
  zCClassDef* className::classDef = new zCClassDef( #className, #baseClassName, className::_CreateNewInstance, sizeof( className ), 0, 0, "" ); \
  zCObject* className::_CreateNewInstance( void ) {                                                                                             \
    return new className;                                                                                                                       \
  }                                                                                                                                             \
  zCClassDef* className::_GetClassDef( void ) const {                                                                                           \
    return className::classDef;                                                                                                                 \
  };                                                                                                                                            \
  void* className::operator new( size_t size ) {                                                                                                \
    void* mem = ::operator new( size );                                                                                                         \
  zCClassDef::ObjectCreated( (zCObject*)mem, className::classDef );                                                                             \
  return mem;                                                                                                                                   \
  };                                                                                                                                            \
  void className::operator delete( void* mem ) {                                                                                                \
    zCClassDef::ObjectDeleted( (zCObject*)mem, className::classDef );                                                                           \
    ::operator delete( mem );                                                                                                                   \
  };

 

} // namespace Gothic_II_Addon

#endif // __ZMACRO_H__VER3__