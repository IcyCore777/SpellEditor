// Supported with union (c) 2018 Union team

#ifndef __UNION_THREAD_H__
#define __UNION_THREAD_H__

namespace Common {
	typedef void *HFUNC, *HMEM;
	typedef CRITICAL_SECTION MUTEX;

	enum EThreadPriority
	{
		TRD_TO_BACKGROUND	=  0x00010000,
		TRD_FROM_BACKGROUND	=  0x00020000,
		TRD_IDLE			= -15,
		TRD_LOW				= -2,
		TRD_NORMAL_LOW		= -1,
		TRD_NORMAL			=  0,
		TRD_NORMAL_HIGHT	=  1,
		TRD_HIGHT			=  2,
		TRD_CRITICAL		=  15
	};

	class ASTAPI CThread
	{
		HFUNC	hFunc;
		DWORD	dwThreadID;
		HANDLE	hThread;

	public:
		CThread ();
		CThread (HFUNC f);

		// init thread
		void	Init		(HFUNC);
		DWORD	Detach		(HMEM = NULL);

		// process
		void	Break		();
		void	Suspend		();
		void	Resume		();

		// priority
		void			SetPriority (EThreadPriority);
		EThreadPriority	GetPriority ();

		// properties
		HFUNC	GetFunction ();
		DWORD	GetID		();
		HANDLE	GetHandle	();

		~CThread ();
	};

	class ASTAPI CMutex
	{
		MUTEX mutex;

	public:
		CMutex		();
		void Enter	();
		void Leave	();
		~CMutex		();
	};
} // namespace Common

#endif // __UNION_THREAD_H__