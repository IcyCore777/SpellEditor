// Supported with union (c) 2018 Union team

#ifndef __UNION_ALLOCATOR_32_H__
#define __UNION_ALLOCATOR_32_H__

#define untyped_ptr  ...
#define memsize(dst) shi_msize(dst)
#define True         (1)
#define False        (0)
#define Null         (nullptr)
#define None         (0x00000000)
#define Invalid      (0xFFFFFFFF)
#define NotFound     Invalid
#define NullStrA     ((char*)None)
#define NullStrW     ((wchar_t*)None)
#define Success      True
#define Failed       False

#define I32 (int32)
#define I64 (int64)
#define U32 (uint32)
#define U64 (uint64)
#define F32 (real32)
#define F64 (real64)

#define MemDel(obj)       { shi_free(obj); obj = Null; }
#define DeleteObject(obj) { delete obj; obj = Null; }

#ifdef UNICODE
#define NullStr			NullStrW
#else
#define NullStr			NullStrA
#endif

#define zPixelX screen->anx
#define zPixelY screen->any

#define zKeyPressed( a ) zinput->KeyPressed(a)
#define zKeyToggled( a ) zinput->KeyToggled(a)
#define zBindPressed( logic ) zinput->GetState( logic )
#define zBindToggled( logic ) zinput->IsBindedToggled(logic, zinput->GetKey())

#define RGBA(r,g,b,a) ( (zUINT32)(zUINT8)(r)|(zUINT32)(zUINT8)(g)<<8|(zUINT32)(zUINT8)(b)<<16|(zUINT32)(zUINT8)(a)<<24 )
#define EXTRACT_R(rgba) ( rgba		& 0xff  )
#define EXTRACT_G(rgba) ( rgba >> 8	& 0xff  )
#define EXTRACT_B(rgba) ( rgba >> 16 & 0xff )
#define EXTRACT_A(rgba) ( rgba >> 24 & 0xff )

#define VID_MAX_XDIM GetSystemMetrics( SM_CXSCREEN )
#define VID_MAX_YDIM GetSystemMetrics( SM_CYSCREEN )

#endif // __UNION_ALLOCATOR_32_H__