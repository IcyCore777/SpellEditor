#pragma once

#include "ztypes.h"


static zDWORD	__cdecl		sysGetTime						()				{XCALL(0x00505280)}
static void	__cdecl		sysExit							()				{XCALL(0x005052F0)}
static void	__cdecl		sysEvent						()				{XCALL(0x005053E0)}
static void	__cdecl		sysIdle							(int Time)		{XCALL(0x00505870)}
static void	__cdecl		sysSetFocus						()				{XCALL(0x00506010)}
static zBOOL	__cdecl		sysGotDebugger					()				{XCALL(0x005091E0)}
static zBOOL	__cdecl		sysHandleExceptions				()				{XCALL(0x00502AA0)}
static bool	__cdecl		sysKillWindowsKeys				(bool doit)		{XCALL(0x005019B0)}
static void	__cdecl		sysParseCommandLine				(char *Cmd)		{XCALL(0x00505A50)}
static bool	__cdecl		SetForegroundWindowEx			(HWND Wnd)		{XCALL(0x00501F30)}

static int		WINAPI		HandledWinMain					(HINSTANCE hInst,
													 HINSTANCE hPrev,
													 LPSTR szCmdLine,
													 int sw)		{XCALL(0x00502ED0)}

static int		__cdecl		initializeSystemMFC				()				{XCALL(0x00503280)}

static void	__cdecl		sysSetWindowMode				(zBOOL FullScreen,
													 zBOOL Show)	{XCALL(0x00502000)}




static void	__cdecl		inCreateMouseMessage			(zULONG,zULONG) {XCALL(0x00509220)}
static void	__cdecl		sysProcessIdle					()				{XCALL(0x00505320)}
static void	__cdecl		sysHardExit						(char *,...)	{XCALL(0x00504A80)}
//static void	__stdcall	InitCommonControls				()				{XCALL(0x007B468A)}
static void	__cdecl		winCreateMenu					()				{XCALL(0x00503620)}
static void	__cdecl		winCalcSizes					()				{XCALL(0x00505240)}
static void	__cdecl		winDoInstanceCheck				()				{XCALL(0x005035C0)}
static void	__fastcall	vidMinimize						(int)			{XCALL(0x004FF070)}
static int		__cdecl		MainProg						()				{XCALL(0x00781840)}
static void	__cdecl		libExit							()				{XCALL(0x00502AB0)}
static void	__cdecl		HandleFocusLoose				()				{XCALL(0x00503630)}



#define ENTER_PROC(proc)			((void)(0))
#define EXIT_PROC() 				{ return; }
#define memZero(x,y)		memset((x), 0, (y))
#define RETURN(f)					{ return (f); }