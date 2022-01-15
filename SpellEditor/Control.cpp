// Control.cpp: файл реализации
//

#include "stdafx.h"
#include "SpellEditor.h"
#include "Control.h"
#include "afxdialogex.h"
#include "EmKeyProps.h"
#include "PfxProps.h"
#include "VFxBase.h"

extern zCVob			*editVob;
extern zCVob			*targetVob;
extern zBOOL			npc_initialised;
extern BOOL				bRotVob;
extern float			speed;
zCArraySort<zSTRING>	s_VfxList;

int& _drawBBox		= *(int*)0x008CE7E0;
int& _drawTrj		= *(int*)0x008CE7E4;
int& _showTarget	= *(int*)0x008CE7E8;



//Инициализация тестовых нпс
void InitNpcs()
{
	if (npc_initialised) return;
	//Отключаем показ вспомогательных визуалов
	zCVob::SetShowHelperVisuals(FALSE);

	//Включаем АИ для нпс
	oCNpc::SetNpcAIDisabled(FALSE);

	//Активируем менеджер вставки нпс
	ogame->GetSpawnManager()->SetSpawningEnabled(TRUE);

	//Инициализация нпс
	ogame->NpcInit();

	//Инициализация отношений
	ogame->InitNpcAttitudes();

	//Получаем указатель на нпс "Цель"
	oCNpc*  npc = (oCNpc*)ogame->GetGameWorld()->SearchVobByName("FX_112_TARGET");

	//Находим вейпоинт на которой стоит цель
	zCWaypoint* wp = npc->GetHomeWorld()->GetWayNet()->GetNearestWaypoint(npc->GetPositionWorld());

	//Если найден, передаем конмманду на выравнивание по вейпоинту
	if (wp) npc->GetEM()->OnMessage(zNEW(oCMsgMovement)(oCMsgMovement::EV_TURNTOPOS, npc->GetPositionWorld() + wp->dir * 200), npc);

	//Находим указатель на нпс "Кастер"
	npc = (oCNpc*)ogame->GetGameWorld()->SearchVobByName("FX_111_CASTER");

	//Переводим нпс в режим боя магией
	npc->SetWeaponMode(NPC_WEAPON_MAG);

	//Инициализация нпс завершена
	npc_initialised = TRUE;
}


IMPLEMENT_DYNAMIC(CControl, CDialogEx)

CControl::CControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CONTROL, pParent)
	, PfxName(_T(""))
	, VfxName(_T(""))
	, InvestNum(_T(""))
{
	wndVfxProps = 0;
	wndPfxProps = 0;
	wndEmKeyProps = 0;
}

CControl::~CControl()
{
}

void CControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_VFXINPUT, VfxName);
	DDX_Control(pDX, IDC_VFXINPUT, vfxName);

	DDX_Text(pDX, IDC_PFXINPUT, PfxName);
	DDX_Control(pDX, IDC_PFXINPUT, pfxName);

	DDX_Control(pDX, IDC_VFXLIST, VfxList);
	DDX_Control(pDX, IDC_PFXLIST, PfxList);

	DDX_Control(pDX, IDC_TRJ, drawTrj);
	DDX_Control(pDX, IDC_BBOX, drawBbox);
	DDX_Control(pDX, IDC_TARGET, showTarget);
	DDX_Control(pDX, IDC_INVESTNUM, investNum);

	DDX_Text(pDX, IDC_INVESTNUM, InvestNum);

	DDX_Control(pDX, IDC_SPEED, Speed);
}


BEGIN_MESSAGE_MAP(CControl, CDialogEx)
	ON_BN_CLICKED(IDC_DYN, &CControl::OnBnClickedDyn)
	ON_BN_CLICKED(IDC_STAT, &CControl::OnBnClickedStat)
	ON_BN_CLICKED(IDC_PFXPLAY, &CControl::OnBnClickedPfxplay)
	ON_BN_CLICKED(IDC_SAVEPFX, &CControl::OnBnClickedSavepfx)
	ON_BN_CLICKED(IDC_LOAD, &CControl::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_VFXPLAY, &CControl::OnBnClickedVfxplay)
	ON_BN_CLICKED(IDC_VFXSAVE, &CControl::OnBnClickedVfxsave)
	ON_BN_CLICKED(IDC_LOADVFX, &CControl::OnBnClickedLoadvfx)
	ON_BN_CLICKED(IDC_PFXEDIT, &CControl::OnBnClickedPfxedit)
	ON_BN_CLICKED(IDC_VFXEDIT, &CControl::OnBnClickedVfxedit)
	ON_BN_CLICKED(IDC_TRJ, &CControl::OnBnClickedTrj)
	ON_BN_CLICKED(IDC_BBOX, &CControl::OnBnClickedBbox)
	ON_BN_CLICKED(IDC_TARGET, &CControl::OnBnClickedTarget)
	ON_LBN_SELCHANGE(IDC_VFXLIST, &CControl::OnVfxList)
	ON_BN_CLICKED(IDC_KEYINIT, &CControl::OnBnClickedKeyinit)
	ON_BN_CLICKED(IDC_KEYOPEN, &CControl::OnBnClickedKeyopen)
	ON_BN_CLICKED(IDC_KEYCAST, &CControl::OnBnClickedKeycast)
	ON_BN_CLICKED(IDC_KEYINVEST, &CControl::OnBnClickedKeyinvest)
	ON_BN_CLICKED(IDC_KEYSTOP, &CControl::OnBnClickedKeystop)
	ON_BN_CLICKED(IDC_KEYCOLLIDE, &CControl::OnBnClickedKeycollide)
	ON_LBN_SELCHANGE(IDC_PFXLIST, &CControl::OnLbnSelchangePfxlist)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SPEED, &CControl::OnNMCustomdrawSpeed)


	ON_BN_CLICKED(IDC_CLEAR, &CControl::OnBnClickedClear)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
END_MESSAGE_MAP()



//-------------------------------------
// PARTICLE FX SECTION
//+++++++++++++++++++++++++++++++++++++

void CControl::OnBnClickedDyn()
{
	bRotVob = TRUE;
	this->wndPfxProps->particleVob->SetVisual(NULL);
	this->wndPfxProps->particleRotVob->SetVisual(this->wndPfxProps->pfx);
}


void CControl::OnBnClickedStat()
{
	bRotVob = FALSE;
	this->wndPfxProps->particleRotVob->SetVisual(NULL);
	this->wndPfxProps->particleVob->SetVisual(this->wndPfxProps->pfx);
}


void CControl::OnBnClickedPfxplay()
{
	this->wndPfxProps->particleVob->SetShowVisual(TRUE);
	this->wndPfxProps->particleRotVob->SetShowVisual(TRUE);
	if (!this->wndPfxProps->pfx)
	{
		this->wndPfxProps->pfx = zNEW(zCParticleFX);
		this->wndPfxProps->particleVob->SetVisual(this->wndPfxProps->pfx);

	}
	if (!this->wndPfxProps->emitter)
	{
		MessageBox("Load emitter first!", 0, 0);
		return;
	}
	else this->wndPfxProps->pfx->SetAndStartEmitter(this->wndPfxProps->emitter);
}

void CControl::OnBnClickedSavepfx()
{ 
	if (!this->wndPfxProps->emitter) return;
	this->wndPfxProps->particleRotVob->SetShowVisual(FALSE);
	this->wndPfxProps->particleVob->SetShowVisual(FALSE);
	OnBnClickedClear();
	zCParser* p = zCParticleFX::s_pfxParser;

	p->SaveInstance(p->GetIndex(this->wndPfxProps->emitter->particleFXName), this->wndPfxProps->emitter);

	zCParticleFX::ParseParticleFXScript_union();
}

void CControl::OnBnClickedLoad()
{
	CString ID;
	pfxName.GetWindowText(ID);
	ID.MakeUpper();
	
	if (ID.GetLength() > 2)
	{
		if (!zCParticleFX::SearchParticleEmitter(zSTRING(ID)))
			this->wndPfxProps->CreateParticleFxScript(zSTRING(ID));
	}
	if (zCParticleFX::SearchParticleEmitter(zSTRING(ID)))
		this->wndPfxProps->emitter = zCParticleFX::SearchParticleEmitter(zSTRING(ID));
	this->wndPfxProps->EditFx();
}

//-------------------------------------
// VISUAL FX SECTION
//+++++++++++++++++++++++++++++++++++++

void CControl::OnBnClickedVfxplay()
{

	if (!oCVisualFX::actFX) return;
	InitNpcs();
	zCVob *nearVob = GetNearVob();


	if (nearVob) oCVisualFX::actFX->Init(editVob, nearVob);
	else		 oCVisualFX::actFX->Init(editVob, editVob->GetPositionWorld() + 400 * editVob->GetAtVectorWorld());

	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedVfxsave()
{
	zCParser* p = oCVisualFX::fxParser;
	if (!oCVisualFX::actFX) {
		AfxMessageBox("VFX not found!!!", 0); return;
	}

	p->SaveInstance(p->GetIndex(oCVisualFX::actFX->GetName()), (zBYTE*)&oCVisualFX::actFX->visName_S);
	UpdateVfx();
	if (!oCVisualFX::actFX->actKey)
		return;

	p->SaveInstance(p->GetIndex(oCVisualFX::actFX->actKey->name), oCVisualFX::actFX->actKey);

	oCVisualFX::InitParser();
}

void CControl::OnBnClickedLoadvfx()
{
	CString ID;
	vfxName.GetWindowText(ID);

	//Load From Text Input
	if (ID.GetLength() > 2)
	{
		oCVisualFX::InitParser();
		if (oCVisualFX::actFX)
		{
			oCVisualFX::actFX->RemoveVobFromWorld();
			zRELEASE(oCVisualFX::actFX);
		}

		zSTRING id = ID;
		int idx = oCVisualFX::fxParser->GetIndex(id);
		if (id.Length() < 2) return;
		if (idx == -1) {
			oCVisualFX::actFX = zNEW(oCVisualFX());

			oCVisualFX::actFX->fxName = id;
			oCVisualFX::CreateNewScriptFX(id);
			oCVisualFX::InitParser();
			oCVisualFX::actFX->SetByScript(id);
			UpdateVfx();
			SetEditVob();
			zCVob *nearVob = GetNearVob();

			oCVisualFX::actFX->Open();

			if (nearVob) oCVisualFX::actFX->Init(editVob, nearVob);
			else		 oCVisualFX::actFX->Init(editVob, editVob->GetPositionWorld() + 400 * editVob->GetAtVectorWorld());

			wndVfxProps->EditFx();

			return;
		};

		oCVisualFX::actFX = zNEW(oCVisualFX());
		oCVisualFX::actFX->SetByScript(id);

		SetEditVob();

		oCVisualFX::actFX->Open();

		wndVfxProps->EditFx();
		if (oCVisualFX::actFX->emKeyList.GetNumInList() >= 1) {
			oCVisualFX::actFX->actKey = oCVisualFX::actFX->emKeyList[0];
		}
		
	}
	else
	//Load From FX list
	{
		zSTRING name = VfxName;
		if (name.Length() < 1)
			return;

		oCVisualFX::InitParser();
		if (oCVisualFX::actFX)
		{
			oCVisualFX::actFX->RemoveVobFromWorld();
			zRELEASE(oCVisualFX::actFX);
		}

		oCVisualFX::actFX = zNEW(oCVisualFX());
		oCVisualFX::actFX->SetByScript(name);

		SetEditVob();

		oCVisualFX::actFX->Open();

		wndVfxProps->EditFx();
		if (oCVisualFX::actFX->emKeyList.GetNumInList() >= 1) {
			oCVisualFX::actFX->actKey = oCVisualFX::actFX->emKeyList[0];
		}
	}
}

void CControl::OnBnClickedPfxedit()
{
	if (!wndVfxProps) return;
	if (!wndEmKeyProps) return;
	if (!wndVfxProps) return;

	if (wndVfxProps->IsWindowVisible()) wndVfxProps->ShowWindow(SW_HIDE);
	if (wndEmKeyProps->IsWindowVisible()) wndEmKeyProps->ShowWindow(SW_HIDE);

	if (!wndPfxProps->IsWindowVisible()) wndPfxProps->ShowWindow(SW_SHOW);
	else wndPfxProps->ShowWindow(SW_HIDE);
}

void CControl::OnBnClickedVfxedit()
{
	if (wndPfxProps->IsWindowVisible())  wndPfxProps->ShowWindow(SW_HIDE);

	if (!wndVfxProps->IsWindowVisible()) wndVfxProps->ShowWindow(SW_SHOW);
	else wndVfxProps->ShowWindow(SW_HIDE);

	if (!wndEmKeyProps->IsWindowVisible()) wndEmKeyProps->ShowWindow(SW_SHOW);
	else wndEmKeyProps->ShowWindow(SW_HIDE);
}

void CControl::OnBnClickedTrj()
{
	if (!_drawTrj)		_drawTrj = TRUE;
	else				_drawTrj = FALSE;
}

void CControl::OnBnClickedBbox()
{
	if (!_drawBBox)		_drawBBox = TRUE;
	else				_drawBBox = FALSE;
}

void CControl::OnBnClickedTarget()
{
	if (!_showTarget)	_showTarget = TRUE;
	else				_showTarget = FALSE;
}

BOOL CControl::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(&m_SaveRect);
	GetWindowRect(&Rect);


	RECT systemRect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &systemRect, 0);

	RECT wrect;
	int sysHeight = systemRect.bottom - systemRect.top;
	int sysWidth = systemRect.right - systemRect.left;

	int frameRight = sysWidth;
	int frameBottom = sysHeight;

	GetWindowRect(&wrect);

	int height;
	int width;
	height = (wrect.bottom - wrect.top);
	width = (wrect.right - wrect.left);
	SetWindowPos(&wndTop, sysWidth - width, sysHeight - height, width, height, 0);

	if (!wndVfxProps)
	{
		wndVfxProps = new CVFxBase();
		wndVfxProps->Create(IDD_VFXPARAMS, 0);
		wndVfxProps->ShowWindow(SW_HIDE);
		wndVfxProps->InitParams();
	}

	if (!wndEmKeyProps)
	{
		wndEmKeyProps = new CEmKeyProps();
		wndEmKeyProps->Create(IDD_EMKEYPARAMS, 0);
		wndEmKeyProps->ShowWindow(SW_HIDE);
		wndEmKeyProps->InitParams();
	}

	if (!wndPfxProps)
	{
		wndPfxProps = new CPfxProps();
		wndPfxProps->Create(IDD_PFXPROPS, 0);
		wndPfxProps->ShowWindow(SW_HIDE);
		wndPfxProps->InitParams();
	}

	Speed.SetRangeMax(10);
	Speed.SetRangeMin(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}

void CControl::OnVfxList()
{
	UpdateData(TRUE);

	int index = VfxList.GetCurSel();
	if (index == LB_ERR) return;
	VfxList.GetText(index, VfxName);

	UpdateData(FALSE);
}

void CControl::UpdateVfx()
{
	s_VfxList.DeleteList();
	s_VfxList.EmptyList();
	VfxList.ResetContent();

	zSTRING instanceName;
	int		cindex = oCVisualFX::fxParser->GetIndex(zSTRING("CFX_BASE"));
	int		pos = 0;
	while (pos >= 0) {
		pos = oCVisualFX::fxParser->GetInstance(cindex, pos + 1);
		zCPar_Symbol *sym = oCVisualFX::fxParser->GetSymbol(pos);
		if (sym) {
			instanceName = sym->name;

			s_VfxList.Insert(instanceName);
			zerr->Message("D: VFX: " + instanceName);
		};
	};
	s_VfxList.QuickSort();

	if (VfxList.GetCount() < s_VfxList.GetNumInList())
		for (int i = 0; i<s_VfxList.GetNumInList(); i++)
			VfxList.AddString(s_VfxList.GetSafe(i).ToChar());
}

void CControl::UpdatePfx()
{
	PfxList.ResetContent();
	if (PfxList.GetCount() < zCParticleFX::s_emitterPresetList.GetNumInList())
		for (int i = 0; i<zCParticleFX::s_emitterPresetList.GetNumInList(); i++)
			PfxList.AddString(zCParticleFX::s_emitterPresetList.GetSafe(i)->GetParticleFXName().ToChar());
}

void CControl::OnBnClickedKeyinit()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;
	int index = oCVisualFX::actFX->FindKey("INIT");

	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_INIT");
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	}

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_INIT;
	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedKeyopen()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;
	int index = oCVisualFX::actFX->FindKey("OPEN");

	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_OPEN");
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	};

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_OPEN;
	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedKeycast()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;
	int index = oCVisualFX::actFX->FindKey("CAST");

	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_CAST");
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	};

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_CAST;

	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedKeyinvest()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;

	CString keyNum;
	investNum.GetWindowText(keyNum);

	int index = oCVisualFX::actFX->FindKey("INVEST_" + zSTRING(keyNum));
	
	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_INVEST_" + zSTRING(keyNum));
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	};

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_INVESTNEXT;
	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedKeystop()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;
	int index = oCVisualFX::actFX->FindKey("STOP");

	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_STOP");
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	};

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_STOP;
	this->wndEmKeyProps->EditKey();
}

void CControl::OnBnClickedKeycollide()
{
	if (!oCVisualFX::actFX) return;

	oCEmitterKey *actEmKey;
	int index = oCVisualFX::actFX->FindKey("COLLIDE");

	if (index == -1)
	{
		actEmKey = zNEW(oCEmitterKey);
		actEmKey->SetName(oCVisualFX::actFX->GetName() + "_KEY_COLLIDE");
		oCVisualFX::actFX->InsertKey(actEmKey);

	}
	else actEmKey = oCVisualFX::actFX->GetKey(index);

	if (!oCVisualFX::fxParser->GetSymbol(actEmKey->GetName()))
	{
		if (!this->wndEmKeyProps->KeyMess(actEmKey->GetName().ToChar())) return;
		//ctrl_inf = "Created new key";
		UpdateData(FALSE);
		oCEmitterKey::CreateNewScriptKey(actEmKey->GetName());
		actEmKey->SetDefaultByFX(oCVisualFX::actFX);
		oCVisualFX::InitParser();
	};

	oCVisualFX::actFX->actKey = actEmKey;
	oCVisualFX::actFX->UpdateFXByEmitterKey(actEmKey);
	oCVisualFX::actFX->fxState = zVFXSTATE_COLLIDE;
	this->wndEmKeyProps->EditKey();
}

void CControl::OnLbnSelchangePfxlist()
{
	UpdateData(TRUE);

	int index = PfxList.GetCurSel();
	if (index == LB_ERR) return;
	PfxList.GetText(index, PfxName);

	UpdateData(FALSE);
}

void CControl::OnNMCustomdrawSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	speed = Speed.GetPos() * 0.001;
	*pResult = 0;

}




void CControl::OnBnClickedClear()
{
	zCArray<zCVob*> PfxList;
	zCArray<zCVob*> VfxList;
	ogame->GetWorld()->SearchVobListByClass(zCVob::classDef, PfxList);
	ogame->GetWorld()->SearchVobListByClass(oCVisualFX::classDef, VfxList);

	for (size_t i = 0; i < PfxList.GetNumInList(); i++)
		if (dynamic_cast<zCParticleFX*>(PfxList[i]->visual))
			PfxList[i]->SetShowVisual(FALSE);

	for (size_t i = 0; i < VfxList.GetNumInList(); i++)
		ogame->GetWorld()->RemoveVobSubtree(VfxList[i]);
}


void CControl::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = Rect.Width();
	lpMMI->ptMinTrackSize.y = Rect.Height();
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


void CControl::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!cx || !cy) return;

	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;

	return;
	//PFX
	OffsetChildWindow(GetDlgItem(IDC_PFXLIST), 0, 0, dx, dy);
	OffsetChildWindow(GetDlgItem(IDC_STATIC1), 0, 0, dx, dy);
	OffsetChildWindow(GetDlgItem(IDC_PFXINPUT), 0, 0, dx, 0);
	OffsetChildWindow(GetDlgItem(IDC_SPEED), 0, 0, dx, 0);
	OffsetChildWindow(GetDlgItem(IDC_SAVEPFX), dx, 0, 0, 0);
	OffsetChildWindow(GetDlgItem(IDC_LOAD), dx, 0, 0, 0);

	//VFX
	OffsetChildWindow(GetDlgItem(IDC_VFXLIST), dx, 0, 0, dy);
	OffsetChildWindow(GetDlgItem(IDC_STATIC2), dx, 0, 0, dy);
	OffsetChildWindow(GetDlgItem(IDC_VFXINPUT), dx, 0, 0, 0);

	OffsetChildWindow(GetDlgItem(IDC_VFXINPUT), 0, 0, dx, 0);
	OffsetChildWindow(GetDlgItem(IDC_VFXPLAY), dx, 0, 0, 0);
	//IDC_LOADVFX
		//IDC_VFXSAVE
		//
	GetClientRect(&m_SaveRect);
}
