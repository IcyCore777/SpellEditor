#include "stdafx.h"

// ESC key crashfix
int __fastcall Ivk_CGameManager_HandleEvent(CGameManager*, void*, int);
CInvoke <int(__thiscall *) (CGameManager*, int)> pIvk_CGameManager_HandleEvent(0x0042AD50, Ivk_CGameManager_HandleEvent, IVK_AUTO);
int __fastcall Ivk_CGameManager_HandleEvent(CGameManager* _this, void*, int key)
{
	if (key == 0x01)
		return FALSE;
	return pIvk_CGameManager_HandleEvent(_this, key);
}

// VOB visual fix
void __fastcall Invk_zCParticleFX(zCParticleFX* _this, void*);
CInvoke<void(__thiscall*)(zCParticleFX*)> pInvk_zCParticleFX(0x005ACF70, Invk_zCParticleFX);
void __fastcall Invk_zCParticleFX(zCParticleFX* _this, void*)
{
	pInvk_zCParticleFX(_this);
	_this->dontKillPFXWhenDone = TRUE;
}

//0x00643F20 private: int __thiscall zCRnd_D3D::XD3D_InitPerDX(long,int,int,int,int)
int __fastcall XD3D_InitPerDX(zCRnd_D3D*, void*, long, int, int, int, int);
CInvoke <int(__thiscall *) (zCRnd_D3D*, long, int, int, int, int)> pXD3D_InitPerDX(0x00643F20, XD3D_InitPerDX, IVK_AUTO);
int __fastcall XD3D_InitPerDX(zCRnd_D3D* _this, void*, long flags, int x, int y, int bpp, int id)
{
	int result = pXD3D_InitPerDX(_this, 0, x, y, bpp, id);
	return result;
}