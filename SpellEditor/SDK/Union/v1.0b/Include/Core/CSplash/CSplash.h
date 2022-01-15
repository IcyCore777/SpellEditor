#pragma once



namespace UnionCore
{
	typedef uint32		IRESOURCE;
	typedef HANDLE		HTHREAD;
	typedef WNDCLASS	TWndClass;
	typedef HWND		TWindow;
	typedef void32		Bitmap;

	class CSplash
	{
		friend LRESULT CALLBACK WindProc (TWindow, UINT, WPARAM, LPARAM);

		static CSplash* lpDefaultSplash;

		
		struct
		{
			Bitmap hBitmap;
			bool32 bUseAlpha;
			uint32 ulHexColor;

		} Image;

		struct
		{
			TWndClass	Class;
			TWindow		Handle;
			Common::CThread		Thread;

		} Window;

		static Common::CArray<CSplash*> arrSplash;

	public:

		ASTAPI CSplash ();

		ASTAPI void Show ();
		ASTAPI void Hide ();

		ASTAPI static Bitmap LoadBitmapRC	(HMODULE, IRESOURCE);
		ASTAPI static Bitmap LoadBitmapFILE	(Common::CString);

		ASTAPI bool32 SetImage	 (Bitmap);
		ASTAPI bool32 Init		 ();

		ASTAPI void SetAlpha	 (bool32, uint32 = RGB(255, 0, 255));
		ASTAPI void SetAsDefault ();

		ASTAPI static CSplash* FindIdentity (TWindow);
		ASTAPI static CSplash* GetDefault	();

		ASTAPI ~CSplash ();
	};
}

#ifdef __FORCE_DEFINITION
#include "CSplash.inl"
#endif
