// Supported with union (c) 2018 Union team

#pragma once

#ifndef __UNION_AFX_H__
#define __UNION_AFX_H__

#pragma warning(disable:4005)
#pragma warning(disable:4805)
#pragma warning(disable:4800)
#pragma warning(disable:4482)
#pragma warning(disable:4234)
#pragma warning(disable:4099)
#pragma warning(disable:4275)
#pragma warning(disable:4715)
#pragma warning(disable:4244)
#pragma warning(disable:4251)
#pragma warning(disable:4731)
#pragma warning(disable:4166)
#pragma warning(disable:4200)
#pragma warning(disable:4996)
#pragma warning(disable:4305)

#define XCALL(uAddr)			\
	__asm { mov esp, ebp	}	\
	__asm { pop ebp			}	\
	__asm { mov eax, uAddr	}	\
	__asm { jmp eax			}

#ifndef CORE_SECURE_DISABLE
#define UNSAFE_MESSAGE "Unsafe function. Don't call it or use CORE_SECURE_DISABLE"
#define UNSAFE __declspec(deprecated(UNSAFE_MESSAGE)) 
#else
#define UNSAFE
#endif

#define ASTAPI __declspec (dllimport)
#define SHWAPI __declspec (dllimport)
#define VDFAPI __declspec (dllimport)

#define __INLINE inline

#pragma comment (lib, "Psapi.lib")
#pragma comment (lib, "Shw32.lib")
#pragma comment (lib, "Vdfs32g.lib")

extern "C"
{
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
}

#include <Psapi.h>

#include "Common\UnionTypes\Macro.h"
#include "Common\UnionTypes\Types.h"
#include "Common\ArrayNew\Array.h"
#include "Memory\Shw32.h"
#include "Common\Common.h"
#include "Core\Core.h"
#include "Vdfs\Vdfs.h"
#include "SystemPack\Union.Patch\CPatchFile.h"

#include "ZenGin\zGothicAPI.h"

#include "MainFrm.h"
#include "SpellEditor.h"
#include "SpellEditorDoc.h"
#include "SpellEditorView.h"


using namespace std;
using namespace Gothic_II_Addon;

#endif // __UNION_AFX_H__