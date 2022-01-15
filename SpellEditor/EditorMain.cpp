#include "stdafx.h"
#include "zWin32.h"
#include "Control.h"
#include "zWE_Controller.h"
#include "PfxProps.h"
BOOL	bReady = FALSE;



CInvoke <void(__thiscall*) (CGameManager*)> pRun(0x00425830, &CGameManager::Run_AST, IVK_PROTECTED);
CInvoke<void(__thiscall*)(CGameManager*, HWND&)> Ivk_CGameManager_Init(0x00424C70, &CGameManager::Init_AST, IVK_AUTO);
DllExport zTWE_ControllerEvents ControllerEvents;

BOOL bRotVob = FALSE;


//�������� ��������� ����
void LoadWorld()
{
	//�������� �� ������� �������� ���������� ����������, ������, ������� ����, �������
	if (!gameMan->gameSession)	return;
	if (!CMainFrame::mainframe) return;
	if (!CSpellView::view)		return;

	//������� � ����� �����
	zoptions->ChangeDir(DIR_WORLD);
	//��������� ����� �������������
	gameMan->InitScreen_Close();
	//��������� ����� ��������
	ogame->OpenLoadscreen(TRUE, "");
	//��������� ��� � ������ �������������
	ogame->LoadWorld("ParticleScene\\ParticleScene.zen", zCWorld::zWLD_LOAD_EDITOR_COMPILED);
	//�� ��������� �������� ��������� ����-�����
	ogame->CloseLoadscreen();

	//���������� ��� ������ (�� �����, �������� �� ��������)
	if (ogame->GetCamera() && ogame->GetCamera()->GetVob())
		ogame->GetWorld()->RemoveVob(ogame->GetCamera()->GetVob());

	//�������������� ������
	ogame->CamInit();

	//������ ��� ���� ������
	ogame->GetCamera()->GetVob()->SetVobName("PIDOR_CAMERA_VOB");
	ogame->GetCamera()->GetVob()->SetAI(0);

	//������������� ����������� ���������
	ogame->EnvironmentInit();

	
	//������������� ��������� ���������� ������
	ogame->GetCamera()->GetVob()->SetPositionWorld(zVEC3(30029.9512, 5411.15039, -16529.3555));
	//������������� ����������� ������
	ogame->GetCamera()->GetVob()->SetHeadingAtWorld(zVEC3(-0.133660987, -0.40354538, 0.905148625));

	//������� ���� ��� �������� ������, ��������� � ������������.
	if (!CMainFrame::mainframe->wndControl->wndPfxProps->particleVob)
		CMainFrame::mainframe->wndControl->wndPfxProps->particleVob = ogame->GetWorld()->SearchVobByName("PARTICLE_VOB");
	if (!CMainFrame::mainframe->wndControl->wndPfxProps->particleRotVob)
		CMainFrame::mainframe->wndControl->wndPfxProps->particleRotVob = ogame->GetWorld()->SearchVobByName("PARTICLE_VOB_ROTATE");
}

CInvoke <void(__thiscall*) (oCVisualFX*)> pCollide_union(0x00493A00, &oCVisualFX::Collide_union, IVK_PROTECTED);

void oCVisualFX::Collide_union(const zBOOL killAfterDone)
{
	
	for (int j = 0; j < childList.GetNumInList(); j++)
	{
		int numChilds = childList.GetNumInList();
		childList[j]->Collide(killAfterDone);
		if (childList.GetNumInList() != numChilds) j = -1;  // Evtl. Restart n�tig, da ein Stop() die FX/Child Liste des Parents �ndert
	};
	
	int index = FindKey("COLLIDE");
	
	if (index != -1)
	{
		
		actKey = emKeyList[index];
		UpdateFXByEmitterKey(actKey);
		
	}

	fxState = zVFXSTATE_COLLIDE;

	EndEffect(killAfterDone);
};



__declspec(noinline) void CGameManager::Init_AST(HWND& hwnd) {

	CMainFrame::mainframe->OnApplicationLook(205);
	CMainFrame::mainframe->RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	CMainFrame::mainframe->m_wndRibbonBar.Create(CMainFrame::mainframe);
	CMainFrame::mainframe->m_wndRibbonBar.LoadFromResource(IDR_RIBBON1);
	//CMainFrame::mainframe->m_wndRibbonBar.Create(CMainFrame::mainframe);
	//CMainFrame::mainframe->m_wndRibbonBar.LoadFromResource(IDR_RIBBON1);
	//CMainFrame::mainframe->RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	//��������� ������� ���� ����
	DestroyWindow(hwnd);
	
	

	Ivk_CGameManager_Init(this, CSpellView::view->m_hWnd);

	//���������� ������� � ��� ��� �������� ������ �������
	bReady = TRUE;

	//���������� ������� ����
	CMainFrame::mainframe->ShowWindow(SW_SHOW);

	//�������������� �������
	CSpellView::view->RedrawWindow();

	//������ ������������� �����
	ogame->GetWorldTimer()->SetTime(12, 00);


	//������������� ����������� ������
	ControllerEvents.mainframe = CMainFrame::mainframe->m_hWnd;		//�������� ����������� ��������� �� ������� ����
	ControllerEvents.PickMode = zPM_DISABLED;						//��������� ����� �����
	ControllerEvents.GizmoScale = 0;								

	//���������� ���
	ogame->game_frameinfo = TRUE;

	//������ ������ VFX & PFX ���������
	CMainFrame::mainframe->wndControl->UpdateVfx();
	CMainFrame::mainframe->wndControl->UpdatePfx();

	//��������� ���
	LoadWorld();
	//������� ��� ��� ������� PFX
	if (!CMainFrame::mainframe->wndControl->wndPfxProps->particleVob)
		CMainFrame::mainframe->wndControl->wndPfxProps->particleVob = ogame->GetWorld()->SearchVobByName("PARTICLE_VOB");

	//���� �� �����, ����� ����
	if (!CMainFrame::mainframe->wndControl->wndPfxProps->particleVob)
		this->Done();
	
	//������������ ������� �������� ������ � VFX
	zCParticleFX::ParseParticleFXScript_union();
	oCVisualFX::InitParser();

}



void CGameManager::Run_AST()
{
	if (dontStartGame) return;

	gameSession->game_testmode = TRUE;

	exitGame = FALSE;
	zSTRING inivalue = zoptions->ParmValue("ini");
	if (inivalue.IsEmpty())
		inivalue = "Gothic.ini";
	zoptions->Save(inivalue);

	ShowCursor(TRUE);

	if (!exitGame)
	{
		// Ingame-Rendering
		do
		{
			if (::GetActiveWindow() == CMainFrame::mainframe->m_hWnd)
				zCView::GetInput();
			sysEvent();
			//----------------------
			//Window selection fix
			//----------------------
			POINT   mPos;
			GetCursorPos(&mPos);


			//Base render
			if (GetGame() && gameSession)
			{

				gameSession->Render();

				//���� ����� �������� ������������� ���� �������, ������� ��� ������ �����.
				if(bRotVob)
					CMainFrame::mainframe->wndControl->wndPfxProps->RotateVob();
				gameSession->RenderBlit();
				//HACK Update cmd ui for ToolBar
				//CMainFrame::mainframe->m_wndObjectToolbar.SendMessage(WM_IDLEUPDATECMDUI);
				//CMainFrame::mainframe->m_wndActionToolbar.SendMessage(WM_IDLEUPDATECMDUI);
			}
		} while (!exitGame);
	}
}