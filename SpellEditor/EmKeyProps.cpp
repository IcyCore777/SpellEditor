// EmKeyProps.cpp: файл реализации
//

#include "stdafx.h"
#include "SpellEditor.h"
#include "EmKeyProps.h"
#include "afxdialogex.h"


extern OleVar value;
extern zCVob	    *editVob;
extern zCVob		*targetVob;
IMPLEMENT_DYNAMIC(CEmKeyProps, CDialogEx)

CEmKeyProps::CEmKeyProps(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_EMKEYPARAMS, pParent)
{

}

CEmKeyProps::~CEmKeyProps()
{
}

void CEmKeyProps::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EMKEYPARAMS, emitterKeyProps);
}


BEGIN_MESSAGE_MAP(CEmKeyProps, CDialogEx)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)

	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

//get string value
char* CEmKeyProps::GetString(COleVariant v)
{
	zCDrvProperties_MSS val;
	return _com_util::ConvertBSTRToString(v.bstrVal);
}

//get float value
float CEmKeyProps::GetFloat(COleVariant v)
{
	return v.fltVal;
}

//get bool value
short CEmKeyProps::GetBool(COleVariant v)
{
	if (v.boolVal == -1)
		return 1;
	if (v.boolVal == 0)
		return 0;
}

//Error message func
BOOL CEmKeyProps::KeyMess(CString key)
{
	int result;
	CString ask = "Key " + key + " not found, create new?";
	result = AfxMessageBox(ask, MB_YESNO);
	if (result == IDYES)	return TRUE;
	else					return FALSE;
}

void CEmKeyProps::InitParams()
{

	//Set Window Pos
	RECT systemRect;
	SystemParametersInfo(SPI_GETWORKAREA, 0, &systemRect, 0);

	RECT wrect;
	int sysWidth = systemRect.right - systemRect.left;

	int frameRight = sysWidth;

	GetWindowRect(&wrect);

	int height;
	int width;

	height = (wrect.bottom - wrect.top);
	width = (wrect.right - wrect.left);
	frameRight = sysWidth - width;

	SetWindowPos(&wndTop, frameRight, 0, width, height, 0);


	//Init Values

	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	emitterKeyProps.EnableHeaderCtrl(TRUE, _T("Parameter"), _T("Value"));
	emitterKeyProps.SetVSDotNetLook(TRUE);

	OleVar    visName_S(CString(""));
	OleVar    visSizeScale((float)0);
	OleVar    scaleDuration((float)0);
	OleVar    pfx_ppsValue((float)0);
	OleVar    pfx_ppsIsSmoothChg((short)0, VT_BOOL);
	OleVar    pfx_ppsIsLoopingChg((short)0, VT_BOOL);
	OleVar    pfx_scTime((float)0);
	OleVar    pfx_flyGravity_S(CString(""));
	OleVar    pfx_shpDim_S(CString(""));
	OleVar    pfx_shpIsVolumeChg((short)0, VT_BOOL);
	OleVar    pfx_shpScaleFPS((float)0);
	OleVar    pfx_shpDistribWalkSpeed((float)0);
	OleVar    pfx_shpOffsetVec_S(CString(""));
	OleVar    pfx_shpDistribType_S(CString(""));
	OleVar    pfx_dirMode_S(CString(""));
	OleVar    pfx_dirFOR_S(CString(""));
	OleVar    pfx_dirModeTargetFOR_S(CString(""));
	OleVar    pfx_dirModeTargetPos_S(CString(""));
	OleVar    pfx_velAvg((float)0);
	OleVar    pfx_lspPartAvg((float)0);
	OleVar    pfx_visAlphaStart((float)0);
	OleVar    lightPresetName(CString(""));
	OleVar    lightRange((float)0);
	OleVar    sfxID(CString(""));
	OleVar    sfxIsAmbient((short)0, VT_BOOL);
	OleVar    emCreateFXID(CString(""));
	OleVar    emFlyGravity((float)0);
	OleVar    emSelfRotVel_S(CString(""));
	OleVar    emTrjMode_S(CString(""));
	OleVar    emTrjEaseVel((float)0);
	OleVar    emCheckCollision((short)0, VT_BOOL);
	OleVar    emFXLifeSpan((float)0);


	pKeyVis = NewProp(_T("Visual: name, size"));
	emitterKeyProps.AddProperty(pKeyVis);
	pKeyVis->AddSubItem(NewProp(_T("visName_S"), visName_S, _T("Visual name (Particle fx instance ,or *.tga, *.3ds, *.mds, *.trl, *.ltn, *.eqk, *.fov, *.scx, *.mms file name.)")));
	pKeyVis->AddSubItem(NewProp(_T("visSizeScale"), visSizeScale, _T("--")));
	pKeyVis->AddSubItem(NewProp(_T("scaleDuration"), scaleDuration, _T("--")));

	pKeyPfx = NewProp(_T("Particles: pps, smooth, loop"));
	emitterKeyProps.AddProperty(pKeyPfx);
	pKeyPfx->AddSubItem(NewProp(_T("pfx_ppsValue"), pfx_ppsValue, _T("Num particles per second")));
	pKeyPfx->AddSubItem(NewProp(_T("pfx_ppsIsSmoothChg"), pfx_ppsIsSmoothChg, _T("if True pfx has infinite life")));
	pKeyPfx->AddSubItem(NewProp(_T("pfx_ppsIsLoopingChg"), pfx_ppsIsLoopingChg, _T("Smooth transition in scale keys")));
	pKeyPfx->AddSubItem(NewProp(_T("pfx_scTime"), pfx_scTime, _T("--")));
	pKeyPfx->AddSubItem(NewProp(_T("pfx_flyGravity_S"), pfx_flyGravity_S, _T("flyGravity_S - XYZ vector")));

	pKeyShp = NewProp(_T("Particles: shape params"));
	emitterKeyProps.AddProperty(pKeyShp);
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpDim_S"), pfx_shpDim_S, _T("--")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpIsVolumeChg"), pfx_shpIsVolumeChg, _T("--")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpScaleFPS"), pfx_shpScaleFPS, _T("--")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpDistribWalkSpeed"), pfx_shpDistribWalkSpeed, _T("--")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpOffsetVec_S"), pfx_shpOffsetVec_S, _T("shape offset XYZ vector")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_shpDistribType_S"), pfx_shpDistribType_S, _T("Distrib type: RAND, UNIFORM, WALK")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_dirMode_S"), pfx_dirMode_S, _T("Direction mode: DIR,TARGET,MESH")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_dirFOR_S"), pfx_dirFOR_S, _T("Direction for: OBJECT, WORLD")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_dirModeTargetFOR_S"), pfx_dirModeTargetFOR_S, _T("Direction target for: OBJECT,WORLD")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_dirModeTargetPos_S"), pfx_dirModeTargetPos_S, _T("--")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_velAvg"), pfx_velAvg, _T("Avg velocity")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_lspPartAvg"), pfx_lspPartAvg, _T("Lifetime")));
	pKeyShp->AddSubItem(NewProp(_T("pfx_visAlphaStart"), pfx_visAlphaStart, _T("--")));

	pKeyOther = NewProp(_T("Other params"));
	emitterKeyProps.AddProperty(pKeyOther);
	pKeyOther->AddSubItem(NewProp(_T("lightPresetName"), lightPresetName, _T("Light preset name")));
	pKeyOther->AddSubItem(NewProp(_T("lightRange"), lightRange, _T("Light range")));
	pKeyOther->AddSubItem(NewProp(_T("sfxID"), sfxID, _T("Sound FX name")));
	pKeyOther->AddSubItem(NewProp(_T("sfxIsAmbient"), sfxIsAmbient, _T("TRUE - SFX is ambient")));
	pKeyOther->AddSubItem(NewProp(_T("emCreateFXID"), emCreateFXID, _T("Name of Visual FX inst")));

	pKeyEm = NewProp(_T("Emitter"));
	emitterKeyProps.AddProperty(pKeyEm);
	pKeyEm->AddSubItem(NewProp(_T("emFlyGravity"), emFlyGravity, _T("--")));
	pKeyEm->AddSubItem(NewProp(_T("emSelfRotVel_S"), emSelfRotVel_S, _T("Rotating velocity ZYX")));
	pKeyEm->AddSubItem(NewProp(_T("emTrjMode_S"), emTrjMode_S, _T("none, target, line, spline, random, follow, missile")));
	pKeyEm->AddSubItem(NewProp(_T("emTrjEaseVel"), emTrjEaseVel, _T("Fly velocity")));
	pKeyEm->AddSubItem(NewProp(_T("emCheckCollision"), emCheckCollision, _T("--")));
	pKeyEm->AddSubItem(NewProp(_T("emFXLifeSpan"), emFXLifeSpan, _T("--")));

	emitterKeyProps.SetCustomColors(RGB(228, 243, 254), RGB(46, 70, 165), RGB(200, 236, 209), RGB(33, 102, 49), RGB(255, 229, 216), RGB(128, 0, 0), RGB(159, 159, 255));

	emitterKeyProps.ShowScrollBar(SB_HORZ);
	emitterKeyProps.ShowScrollBar(SB_HORZ, FALSE);
}


//property change handler
LRESULT CEmKeyProps::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	if (!oCVisualFX::actFX)
		return 0;
	if (!oCVisualFX::actFX->actKey)
		return 0;
	CMFCPropertyGridProperty * pProp = (CMFCPropertyGridProperty*)lparam;
	CString param = pProp->GetName();
	value = pProp->GetValue();

	switch (wparam)
	{
	case(IDC_EMKEYPARAMS):

		if (param == "visName_S")					oCVisualFX::actFX->actKey->visName_S = GetString(value);
		if (param == "visSizeScale")				oCVisualFX::actFX->actKey->visSizeScale = GetFloat(value);
		if (param == "scaleDuration")				oCVisualFX::actFX->actKey->scaleDuration = GetFloat(value);
		if (param == "pfx_ppsValue")				oCVisualFX::actFX->actKey->pfx_ppsValue = GetFloat(value);
		if (param == "pfx_ppsIsSmoothChg")			oCVisualFX::actFX->actKey->pfx_ppsIsSmoothChg = GetBool(value);
		if (param == "pfx_ppsIsLoopingChg")			oCVisualFX::actFX->actKey->pfx_ppsIsLoopingChg = GetBool(value);
		if (param == "pfx_scTime")					oCVisualFX::actFX->actKey->pfx_scTime = GetFloat(value);
		if (param == "pfx_flyGravity_S")			oCVisualFX::actFX->actKey->pfx_flyGravity_S = GetString(value);
		if (param == "pfx_shpDim_S")				oCVisualFX::actFX->actKey->pfx_shpDim_S = GetString(value);
		if (param == "pfx_shpIsVolumeChg")			oCVisualFX::actFX->actKey->pfx_shpIsVolumeChg = GetBool(value);
		if (param == "pfx_shpScaleFPS")				oCVisualFX::actFX->actKey->pfx_shpScaleFPS = GetFloat(value);
		if (param == "pfx_shpDistribWalkSpeed")		oCVisualFX::actFX->actKey->pfx_shpDistribWalkSpeed = GetFloat(value);
		if (param == "pfx_shpOffsetVec_S")			oCVisualFX::actFX->actKey->pfx_shpOffsetVec_S = GetString(value);
		if (param == "pfx_shpDistribType_S")		oCVisualFX::actFX->actKey->pfx_shpDistribType_S = GetString(value);
		if (param == "pfx_dirMode_S")				oCVisualFX::actFX->actKey->pfx_dirMode_S = GetString(value);
		if (param == "pfx_dirFOR_S")				oCVisualFX::actFX->actKey->pfx_dirFOR_S = GetString(value);
		if (param == "pfx_dirModeTargetFOR_S")		oCVisualFX::actFX->actKey->pfx_dirModeTargetFOR_S = GetString(value);
		if (param == "pfx_dirModeTargetPos_S")		oCVisualFX::actFX->actKey->pfx_dirModeTargetPos_S = GetString(value);
		if (param == "pfx_velAvg")					oCVisualFX::actFX->actKey->pfx_velAvg = GetFloat(value);
		if (param == "pfx_lspPartAvg")				oCVisualFX::actFX->actKey->pfx_lspPartAvg = GetFloat(value);
		if (param == "pfx_visAlphaStart")			oCVisualFX::actFX->actKey->pfx_visAlphaStart = GetFloat(value);
		if (param == "lightPresetName")				oCVisualFX::actFX->actKey->lightPresetName = GetString(value);
		if (param == "lightRange")					oCVisualFX::actFX->actKey->lightRange = GetFloat(value);
		if (param == "sfxID")						oCVisualFX::actFX->actKey->sfxID = GetString(value);
		if (param == "sfxIsAmbient")				oCVisualFX::actFX->actKey->sfxIsAmbient = GetBool(value);
		if (param == "emCreateFXID")				oCVisualFX::actFX->actKey->emCreateFXID = GetString(value);
		if (param == "emFlyGravity")				oCVisualFX::actFX->actKey->emFlyGravity = GetFloat(value);
		if (param == "emSelfRotVel_S")				oCVisualFX::actFX->actKey->emSelfRotVel_S = GetString(value);
		if (param == "emTrjMode_S")					oCVisualFX::actFX->actKey->emTrjMode_S = GetString(value);
		if (param == "emTrjEaseVel")				oCVisualFX::actFX->actKey->emTrjEaseVel = GetFloat(value);
		if (param == "emCheckCollision")			oCVisualFX::actFX->actKey->emCheckCollision = GetBool(value);
		if (param == "emFXLifeSpan")				oCVisualFX::actFX->actKey->emFXLifeSpan = GetFloat(value);

		SetEditVob();
		oCVisualFX::actFX->actKey->ParseStrings();
		oCVisualFX::actFX->UpdateFXByEmitterKey(oCVisualFX::actFX->GetActKey());
		oCVisualFX::actFX->target = GetNearVob();

		if (!oCVisualFX::actFX->target) oCVisualFX::actFX->targetPos = editVob->GetPositionWorld() + 400 * editVob->GetAtVectorWorld();

		oCVisualFX::actFX->CalcTrajectory();
		break;
	}
	return 0;
}


//edit key
void CEmKeyProps::EditKey()
{
	if (!oCVisualFX::actFX->actKey) return;

	SetWindowText(oCVisualFX::actFX->actKey->name.ToChar());
	GetKeyVal(EmvisEmProps, _EmvisName_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->visName_S.ToChar()));
	GetKeyVal(EmvisEmProps, _EmvisSizeScale)->SetValue(OleVar(oCVisualFX::actFX->actKey->visSizeScale));
	GetKeyVal(EmvisEmProps, _EmscaleDuration)->SetValue(OleVar(oCVisualFX::actFX->actKey->scaleDuration));
	GetKeyVal(pfxEmProps, _Empfx_ppsValue)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_ppsValue));
	GetKeyVal(pfxEmProps, _Empfx_ppsIsSmoothChg)->SetValue((_variant_t)(bool)oCVisualFX::actFX->actKey->pfx_ppsIsSmoothChg);
	GetKeyVal(pfxEmProps, _Empfx_ppsIsLoopingChg)->SetValue((_variant_t)(bool)oCVisualFX::actFX->actKey->pfx_ppsIsLoopingChg);
	GetKeyVal(pfxEmProps, _Empfx_scTime)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_scTime));
	GetKeyVal(pfxEmProps, _Empfx_flyGravity_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_flyGravity_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_shpDim_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_shpDim_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_shpIsVolumeChg)->SetValue((_variant_t)(bool)oCVisualFX::actFX->actKey->pfx_shpIsVolumeChg);
	GetKeyVal(shpEmProps, _Empfx_shpScaleFPS)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_shpScaleFPS));
	GetKeyVal(shpEmProps, _Empfx_shpDistribWalkSpeed)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_shpDistribWalkSpeed));
	GetKeyVal(shpEmProps, _Empfx_shpOffsetVec_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_shpOffsetVec_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_shpDistribType_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_shpDistribType_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_dirMode_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_dirMode_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_dirFOR_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_dirFOR_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_dirModeTargetFOR_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_dirModeTargetFOR_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_dirModeTargetPos_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_dirModeTargetPos_S.ToChar()));
	GetKeyVal(shpEmProps, _Empfx_velAvg)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_velAvg));
	GetKeyVal(shpEmProps, _Empfx_lspPartAvg)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_lspPartAvg));
	GetKeyVal(shpEmProps, _Empfx_visAlphaStart)->SetValue(OleVar(oCVisualFX::actFX->actKey->pfx_visAlphaStart));
	GetKeyVal(otherEmProps, _EmlightPresetName)->SetValue(OleVar(oCVisualFX::actFX->actKey->lightPresetName.ToChar()));
	GetKeyVal(otherEmProps, _EmlightRange)->SetValue(OleVar(oCVisualFX::actFX->actKey->lightRange));
	GetKeyVal(otherEmProps, _EmsfxID)->SetValue(OleVar(oCVisualFX::actFX->actKey->sfxID.ToChar()));
	GetKeyVal(otherEmProps, _EmsfxIsAmbient)->SetValue((_variant_t)(bool)oCVisualFX::actFX->actKey->sfxIsAmbient);
	GetKeyVal(otherEmProps, _EmemCreateFXID)->SetValue(OleVar(oCVisualFX::actFX->actKey->emCreateFXID.ToChar()));
	GetKeyVal(emEmProps, _EmemFlyGravity)->SetValue(OleVar(oCVisualFX::actFX->actKey->emFlyGravity));
	GetKeyVal(emEmProps, _EmemSelfRotVel_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->emSelfRotVel_S.ToChar()));
	GetKeyVal(emEmProps, _EmemTrjMode_S)->SetValue(OleVar(oCVisualFX::actFX->actKey->emTrjMode_S.ToChar()));
	GetKeyVal(emEmProps, _EmemTrjEaseVel)->SetValue(OleVar(oCVisualFX::actFX->actKey->emTrjEaseVel));
	GetKeyVal(emEmProps, _EmemCheckCollision)->SetValue((_variant_t)(bool)oCVisualFX::actFX->actKey->emCheckCollision);
	GetKeyVal(emEmProps, _EmemFXLifeSpan)->SetValue(OleVar(oCVisualFX::actFX->actKey->emFXLifeSpan));
}

void CEmKeyProps::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!cx || !cy) return;

	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;

	OffsetChildWindow(GetDlgItem(IDC_EMKEYPARAMS), 0, 0, dx, dy);

	GetClientRect(&m_SaveRect);
}


void CEmKeyProps::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = Rect.Width();
	lpMMI->ptMinTrackSize.y = Rect.Height();
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CEmKeyProps::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(&m_SaveRect);

	GetWindowRect(&Rect);

	return TRUE; 
}
