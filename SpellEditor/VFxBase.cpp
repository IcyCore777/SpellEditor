// VFxBase.cpp: файл реализации
//

#include "stdafx.h"
#include "SpellEditor.h"
#include "VFxBase.h"
#include "afxdialogex.h"
#include "Control.h"
#include "EmKeyProps.h"

// диалоговое окно CVFxBase

extern OleVar value;

extern zCVob	    *editVob;
extern zCVob		*targetVob;


zBOOL		npc_initialised = FALSE;



IMPLEMENT_DYNAMIC(CVFxBase, CDialogEx)

CVFxBase::CVFxBase(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VFXPARAMS, pParent)
{

}

CVFxBase::~CVFxBase()
{
}

void CVFxBase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VFXPROPS, visualFxParams);
}


BEGIN_MESSAGE_MAP(CVFxBase, CDialogEx)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()


//get string value
char* CVFxBase::GetString(COleVariant v)
{
	return _com_util::ConvertBSTRToString(v.bstrVal);
}

//get float value
float CVFxBase::GetFloat(COleVariant v)
{
	return v.fltVal;
}

//get bool value
short CVFxBase::GetBool(COleVariant v)
{
	if (v.boolVal == -1)
		return 1;
	if (v.boolVal == 0)
		return 0;
}


void CVFxBase::InitParams()
{
	//Set window pos
	RECT wrect;
	GetWindowRect(&wrect);
	SetWindowPos(&wndTop, 0, 0, wrect.right - wrect.left, wrect.bottom - wrect.top, 0);

	//Init Values

	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	visualFxParams.EnableHeaderCtrl(TRUE, _T("Parameter"), _T("Value"));
	visualFxParams.SetVSDotNetLook(TRUE);



	OleVar visName_S(CString(""));
	OleVar visSize_S(CString(""));
	OleVar visAlpha((float)0);
	OleVar visAlphaBlendFunc_S(CString(""));
	OleVar visTexAniFPS((float)0);
	OleVar visTexAniIsLooping((short)0, VT_BOOL);
	OleVar emTrjMode_S(CString(""));
	OleVar emTrjOriginNode_S(CString(""));
	OleVar emTrjTargetNode_S(CString(""));
	OleVar emTrjTargetRange((float)0);
	OleVar emTrjTargetAzi((float)0);
	OleVar emTrjTargetElev((float)0);
	OleVar emTrjNumKeys((long)0);
	OleVar emTrjNumKeysVar((long)0);
	OleVar emTrjAngleElevVar((float)0);
	OleVar emTrjAngleHeadVar((float)0);
	OleVar emTrjKeyDistVar((float)0);
	OleVar emTrjLoopMode_S(CString(""));
	OleVar emTrjEaseFunc_S(CString(""));
	OleVar emTrjEaseVel((float)0);
	OleVar emTrjDynUpdateDelay((float)0);
	OleVar emTrjDynUpdateTargetOnly((short)0, VT_BOOL);
	OleVar emFXCreate_S(CString(""));
	OleVar emFXInvestOrigin_S(CString(""));
	OleVar emFXInvestTarget_S(CString(""));
	OleVar emFXTriggerDelay((float)0);
	OleVar emFXCreatedOwnTrj((short)0, VT_BOOL);
	OleVar emActionCollDyn_S(CString(""));
	OleVar emActionCollStat_S(CString(""));
	OleVar emFXCollStat_S(CString(""));
	OleVar emFXCollDyn_S(CString(""));
	OleVar emFXCollDynPerc_S(CString(""));
	OleVar emFXCollStatAlign_S(CString(""));
	OleVar emFXCollDynAlign_S(CString(""));
	OleVar emFXLifeSpan((float)0);
	OleVar emCheckCollision((short)0, VT_BOOL);
	OleVar emAdjustShpToOrigin((short)0, VT_BOOL);
	OleVar emInvestNextKeyDuration((float)0);
	OleVar emFlyGravity((float)0);
	OleVar emSelfRotVel_S(CString(""));
	OleVar userString0 = (CString(""));
	OleVar userString1 = (CString(""));
	OleVar userString2 = (CString(""));
	OleVar userString3 = (CString(""));
	OleVar userString4 = (CString(""));
	OleVar lightPresetName = (CString(""));
	OleVar sfxID = (CString(""));
	OleVar sfxIsAmbient((short)0, VT_BOOL);
	OleVar sendAssessMagic((short)0, VT_BOOL);
	OleVar secsPerDamage = ((float)0);


	pVis = NewProp(_T("Visual: name, alpha, size"));
	visualFxParams.AddProperty(pVis);

	pVis->AddSubItem(NewProp(_T("visName_S"), visName_S, _T("Visual name (Particle fx instance ,or *.tga, *.3ds, *.mds, *.trl, *.ltn, *.eqk, *.fov, *.scx, *.mms file name.)")));
	pVis->AddSubItem(NewProp(_T("visSize_S"), visSize_S, _T("Visual size 2d dim  ex. 22 22")));
	pVis->AddSubItem(NewProp(_T("visAlpha"), visAlpha, _T("--")));

	CMFCPropertyGridProperty* pAlphaFunc = NewProp(_T("visAlphaBlendFunc_S"), visAlphaBlendFunc_S, _T("Alpha blending function"));
	pAlphaFunc->AddOption(_T("MAT_DEFAULT"));
	pAlphaFunc->AddOption(_T("NONE"));
	pAlphaFunc->AddOption(_T("BLEND"));
	pAlphaFunc->AddOption(_T("ADD"));
	pAlphaFunc->AddOption(_T("SUB"));
	pAlphaFunc->AddOption(_T("MUL"));
	pAlphaFunc->AddOption(_T("MUL2"));
	pAlphaFunc->AllowEdit(FALSE);
	pVis->AddSubItem(pAlphaFunc);

	pVis->AddSubItem(NewProp(_T("visTexAniFPS"), visTexAniFPS, _T("--")));
	pVis->AddSubItem(NewProp(_T("visTexAniIsLooping"), visTexAniIsLooping, _T("--")));

	pEm = NewProp(_T("Emitter"));
	visualFxParams.AddProperty(pEm);
	pEm->AddSubItem(NewProp(_T("emTrjMode_S"), emTrjMode_S, _T("none, target, line, spline, random, follow, missile")));
	pEm->AddSubItem(NewProp(_T("emTrjOriginNode_S"), emTrjOriginNode_S, _T("Origin node any bone or zs_node ex. ZS_RIGHTHAND")));
	pEm->AddSubItem(NewProp(_T("emTrjTargetNode_S"), emTrjTargetNode_S, _T("Target node any bone or zs_node ex. BIP01 HEAD")));
	pEm->AddSubItem(NewProp(_T("emTrjTargetRange"), emTrjTargetRange, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjTargetAzi"), emTrjTargetAzi, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjTargetElev"), emTrjTargetElev, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjNumKeys"), emTrjNumKeys, _T("Minimal count of trj keys")));
	pEm->AddSubItem(NewProp(_T("emTrjNumKeysVar"), emTrjNumKeysVar, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjAngleElevVar"), emTrjAngleElevVar, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjAngleHeadVar"), emTrjAngleHeadVar, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjKeyDistVar"), emTrjKeyDistVar, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjLoopMode_S"), emTrjLoopMode_S, _T("Loop mode, variants: RESTART, PINGPONG_ONCE, PINGPONG, HALT")));
	pEm->AddSubItem(NewProp(_T("emTrjEaseFunc_S"), emTrjEaseFunc_S, _T("Eas speed function: LINEAR, SINE, EXP")));
	pEm->AddSubItem(NewProp(_T("emTrjEaseVel"), emTrjEaseVel, _T("Fly velocity")));
	pEm->AddSubItem(NewProp(_T("emTrjDynUpdateDelay"), emTrjDynUpdateDelay, _T("--")));
	pEm->AddSubItem(NewProp(_T("emTrjDynUpdateTargetOnly"), emTrjDynUpdateTargetOnly, _T("--")));
	pEm->AddSubItem(NewProp(_T("emFXCreate_S"), emFXCreate_S, _T("Create child FX with name")));
	pEm->AddSubItem(NewProp(_T("emFXInvestOrigin_S"), emFXInvestOrigin_S, _T("Origin invest FX name")));
	pEm->AddSubItem(NewProp(_T("emFXInvestTarget_S"), emFXInvestTarget_S, _T("Target invest FX name")));
	pEm->AddSubItem(NewProp(_T("emFXTriggerDelay"), emFXTriggerDelay, _T("--")));
	pEm->AddSubItem(NewProp(_T("emFXCreatedOwnTrj"), emFXCreatedOwnTrj, _T("If TRUE child fx has own trj")));
	pEm->AddSubItem(NewProp(_T("emActionCollDyn_S"), emActionCollDyn_S, _T("CREATE, BOUNCE, CREATEONCE, NORESP, COLLIDE")));
	pEm->AddSubItem(NewProp(_T("emActionCollStat_S"), emActionCollStat_S, _T("CREATE, BOUNCE, CREATEONCE, NORESP, COLLIDE, CREATEQUAD")));
	pEm->AddSubItem(NewProp(_T("emFXCollStat_S"), emFXCollStat_S, _T("Static collision FX name")));
	pEm->AddSubItem(NewProp(_T("emFXCollDyn_S"), emFXCollDyn_S, _T("Dynamic collision FX name")));
	pEm->AddSubItem(NewProp(_T("emFXCollDynPerc_S"), emFXCollDynPerc_S, _T("--")));
	pEm->AddSubItem(NewProp(_T("emFXCollStatAlign_S"), emFXCollStatAlign_S, _T("TRAJECTORY, COLLISIONNORMAL")));
	pEm->AddSubItem(NewProp(_T("emFXCollDynAlign_S"), emFXCollDynAlign_S, _T("--")));
	pEm->AddSubItem(NewProp(_T("emFXLifeSpan"), emFXLifeSpan, _T("--")));
	pEm->AddSubItem(NewProp(_T("emCheckCollision"), emCheckCollision, _T("--")));
	pEm->AddSubItem(NewProp(_T("emAdjustShpToOrigin"), emAdjustShpToOrigin, _T("--")));
	pEm->AddSubItem(NewProp(_T("emInvestNextKeyDuration"), emInvestNextKeyDuration, _T("--")));
	pEm->AddSubItem(NewProp(_T("emFlyGravity"), emFlyGravity, _T("--")));
	pEm->AddSubItem(NewProp(_T("emSelfRotVel_S"), emSelfRotVel_S, _T("Rotating velocity ZYX vector")));


	pOther = NewProp(_T("Other"));
	visualFxParams.AddProperty(pOther);

	pOther->AddSubItem(NewProp(_T("userString[0]"), userString0, _T("--")));
	pOther->AddSubItem(NewProp(_T("userString[1]"), userString1, _T("--")));
	pOther->AddSubItem(NewProp(_T("userString[2]"), userString2, _T("--")));
	pOther->AddSubItem(NewProp(_T("userString[3]"), userString3, _T("--")));
	pOther->AddSubItem(NewProp(_T("userString[4]"), userString4, _T("--")));
	pOther->AddSubItem(NewProp(_T("lightPresetName"), lightPresetName, _T("--")));
	pOther->AddSubItem(NewProp(_T("sfxID"), sfxID, _T("--")));
	pOther->AddSubItem(NewProp(_T("sfxIsAmbient"), sfxIsAmbient, _T("--")));
	pOther->AddSubItem(NewProp(_T("sendAssessMagic"), sendAssessMagic, _T("If true, FX send Assess magic perception")));
	pOther->AddSubItem(NewProp(_T("secsPerDamage"), secsPerDamage, _T("--")));


	visualFxParams.SetCustomColors(RGB(228, 243, 254), RGB(46, 70, 165), RGB(200, 236, 209), RGB(33, 102, 49), RGB(255, 229, 216), RGB(128, 0, 0), RGB(159, 159, 255));

	visualFxParams.ShowScrollBar(SB_HORZ);
	visualFxParams.ShowScrollBar(SB_HORZ, FALSE);
}


LRESULT CVFxBase::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	CMFCPropertyGridProperty * pProp = (CMFCPropertyGridProperty*)lparam;
	CString param = pProp->GetName();
	value = pProp->GetValue();

	if (!oCVisualFX::actFX)
		return 0;

	switch (wparam)
	{
	case(IDC_VFXPROPS):
		if (param == "visName_S")					oCVisualFX::actFX->visName_S = GetString(value);
		if (param == "visSize_S")					oCVisualFX::actFX->visSize_S = GetString(value);
		if (param == "visAlpha")					oCVisualFX::actFX->visAlpha = GetFloat(value);
		if (param == "visAlphaBlendFunc_S")			oCVisualFX::actFX->visAlphaBlendFunc_S = GetString(value);
		if (param == "visTexAniFPS")				oCVisualFX::actFX->visTexAniFPS = GetFloat(value);
		if (param == "visTexAniIsLooping")			oCVisualFX::actFX->visTexAniIsLooping = GetBool(value);
		if (param == "emTrjMode_S")					oCVisualFX::actFX->emTrjMode_S = GetString(value);
		if (param == "emTrjOriginNode_S")			oCVisualFX::actFX->emTrjOriginNode_S = GetString(value);
		if (param == "emTrjTargetNode_S")			oCVisualFX::actFX->emTrjTargetNode_S = GetString(value);
		if (param == "emTrjTargetRange")			oCVisualFX::actFX->emTrjTargetRange = GetFloat(value);
		if (param == "emTrjTargetAzi")				oCVisualFX::actFX->emTrjTargetAzi = GetFloat(value);
		if (param == "emTrjTargetElev")				oCVisualFX::actFX->emTrjTargetElev = GetFloat(value);
		if (param == "emTrjNumKeys")				oCVisualFX::actFX->emTrjNumKeys = value.llVal;
		if (param == "emTrjNumKeysVar")				oCVisualFX::actFX->emTrjNumKeysVar = value.llVal;
		if (param == "emTrjAngleElevVar")			oCVisualFX::actFX->emTrjAngleElevVar = GetFloat(value);
		if (param == "emTrjAngleHeadVar")			oCVisualFX::actFX->emTrjAngleHeadVar = GetFloat(value);
		if (param == "emTrjKeyDistVar")				oCVisualFX::actFX->emTrjKeyDistVar = GetFloat(value);
		if (param == "emTrjLoopMode_S")				oCVisualFX::actFX->emTrjLoopMode_S = GetString(value);
		if (param == "emTrjEaseFunc_S")				oCVisualFX::actFX->emTrjEaseFunc_S = GetString(value);
		if (param == "emTrjEaseVel")				oCVisualFX::actFX->emTrjEaseVel = GetFloat(value);
		if (param == "emTrjDynUpdateDelay")			oCVisualFX::actFX->emTrjDynUpdateDelay = GetFloat(value);
		if (param == "emTrjDynUpdateTargetOnly")	oCVisualFX::actFX->emTrjDynUpdateTargetOnly = GetBool(value);
		if (param == "emFXCreate_S")				oCVisualFX::actFX->emFXCreate_S = GetString(value);
		if (param == "emFXInvestOrigin_S")			oCVisualFX::actFX->emFXInvestOrigin_S = GetString(value);
		if (param == "emFXInvestTarget_S")			oCVisualFX::actFX->emFXInvestTarget_S = GetString(value);
		if (param == "emFXTriggerDelay")			oCVisualFX::actFX->emFXTriggerDelay = GetFloat(value);
		if (param == "emFXCreatedOwnTrj")			oCVisualFX::actFX->emFXCreatedOwnTrj = GetBool(value);
		if (param == "emActionCollDyn_S")			oCVisualFX::actFX->emActionCollDyn_S = GetString(value);
		if (param == "emActionCollStat_S")			oCVisualFX::actFX->emActionCollStat_S = GetString(value);
		if (param == "emFXCollStat_S")				oCVisualFX::actFX->emFXCollStat_S = GetString(value);
		if (param == "emFXCollDyn_S")				oCVisualFX::actFX->emFXCollDyn_S = GetString(value);
		if (param == "emFXCollDynPerc_S")			oCVisualFX::actFX->emFXCollDynPerc_S = GetString(value);
		if (param == "emFXCollStatAlign_S")			oCVisualFX::actFX->emFXCollStatAlign_S = GetString(value);
		if (param == "emFXCollDynAlign_S")			oCVisualFX::actFX->emFXCollDynAlign_S = GetString(value);
		if (param == "emFXLifeSpan")				oCVisualFX::actFX->emFXLifeSpan = GetFloat(value);
		if (param == "emCheckCollision")			oCVisualFX::actFX->emCheckCollision = GetBool(value);
		if (param == "emAdjustShpToOrigin")			oCVisualFX::actFX->emAdjustShpToOrigin = GetBool(value);
		if (param == "emInvestNextKeyDuration")		oCVisualFX::actFX->emInvestNextKeyDuration = GetFloat(value);
		if (param == "emFlyGravity")				oCVisualFX::actFX->emFlyGravity = GetFloat(value);
		if (param == "emSelfRotVel_S")				oCVisualFX::actFX->emSelfRotVel_S = GetString(value);
		if (param == "userString[0]")				oCVisualFX::actFX->userString[0] = GetString(value);
		if (param == "userString[1]")				oCVisualFX::actFX->userString[1] = GetString(value);
		if (param == "userString[2]")				oCVisualFX::actFX->userString[2] = GetString(value);
		if (param == "userString[3]")				oCVisualFX::actFX->userString[3] = GetString(value);
		if (param == "userString[4]")				oCVisualFX::actFX->userString[4] = GetString(value);
		if (param == "lightPresetName")				oCVisualFX::actFX->lightPresetName = GetString(value);
		if (param == "sfxID")						oCVisualFX::actFX->sfxID = GetString(value);
		if (param == "sfxIsAmbient")				oCVisualFX::actFX->sfxIsAmbient = GetBool(value);
		if (param == "sendAssessMagic")				oCVisualFX::actFX->sendAssessMagic = GetBool(value);
		if (param == "secsPerDamage")				oCVisualFX::actFX->secsPerDamage = GetFloat(value);


		oCVisualFX::actFX->ParseStrings();
		oCVisualFX::actFX->target = GetNearVob();
		if (!oCVisualFX::actFX->target) oCVisualFX::actFX->targetPos = editVob->GetPositionWorld() + 400 * editVob->GetAtVectorWorld();
		oCVisualFX::actFX->CalcTrajectory();
		break;
	}
	return 0;
}



//edit fx
void  CVFxBase::EditFx()
{
	SetWindowText(oCVisualFX::actFX->GetName().ToChar());
	GetCFx_BaseVal(visProps, _visName_S)->SetValue(OleVar(oCVisualFX::actFX->visName_S.ToChar()));
	GetCFx_BaseVal(visProps, _visSize_S)->SetValue(OleVar(oCVisualFX::actFX->visSize_S.ToChar()));
	GetCFx_BaseVal(visProps, _visAlpha)->SetValue(OleVar(oCVisualFX::actFX->visAlpha));
	GetCFx_BaseVal(visProps, _visAlphaBlendFunc_S)->SetValue(OleVar(oCVisualFX::actFX->visAlphaBlendFunc_S.ToChar()));
	GetCFx_BaseVal(visProps, _visTexAniFPS)->SetValue(OleVar(oCVisualFX::actFX->visTexAniFPS));
	GetCFx_BaseVal(visProps, _visTexAniIsLooping)->SetValue((_variant_t)(bool)oCVisualFX::actFX->visTexAniIsLooping);
	GetCFx_BaseVal(emProps, _emTrjMode_S)->SetValue(OleVar(oCVisualFX::actFX->emTrjMode_S.ToChar()));
	GetCFx_BaseVal(emProps, _emTrjOriginNode)->SetValue(oCVisualFX::actFX->emTrjOriginNode_S.ToChar());
	GetCFx_BaseVal(emProps, _emTrjTargetNode)->SetValue(OleVar(oCVisualFX::actFX->emTrjTargetNode_S.ToChar()));
	GetCFx_BaseVal(emProps, _emTrjTargetRange)->SetValue(OleVar(oCVisualFX::actFX->emTrjTargetRange));
	GetCFx_BaseVal(emProps, _emTrjTargetAzi)->SetValue(OleVar(oCVisualFX::actFX->emTrjTargetAzi));
	GetCFx_BaseVal(emProps, _emTrjTargetElev)->SetValue(OleVar(oCVisualFX::actFX->emTrjTargetElev));
	GetCFx_BaseVal(emProps, _emTrjNumKeys)->SetValue((long)oCVisualFX::actFX->emTrjNumKeys);
	GetCFx_BaseVal(emProps, _emTrjNumKeysVar)->SetValue((long)oCVisualFX::actFX->emTrjNumKeysVar);
	GetCFx_BaseVal(emProps, _emTrjAngleElevVar)->SetValue(OleVar(oCVisualFX::actFX->emTrjAngleElevVar));
	GetCFx_BaseVal(emProps, _emTrjAngleHeadVar)->SetValue(OleVar(oCVisualFX::actFX->emTrjAngleHeadVar));
	GetCFx_BaseVal(emProps, _emTrjKeyDistVar)->SetValue(OleVar(oCVisualFX::actFX->emTrjKeyDistVar));
	GetCFx_BaseVal(emProps, _emTrjLoopMode_S)->SetValue(OleVar(oCVisualFX::actFX->emTrjLoopMode_S.ToChar()));
	GetCFx_BaseVal(emProps, _emTrjEaseFunc_S)->SetValue(OleVar(oCVisualFX::actFX->emTrjEaseFunc_S.ToChar()));
	GetCFx_BaseVal(emProps, _emTrjEaseVel)->SetValue(OleVar(oCVisualFX::actFX->emTrjEaseVel));
	GetCFx_BaseVal(emProps, _emTrjDynUpdateDelay)->SetValue(OleVar(oCVisualFX::actFX->emTrjDynUpdateDelay));
	GetCFx_BaseVal(emProps, _emTrjDynUpdateTargetOnly)->SetValue((_variant_t)(bool)oCVisualFX::actFX->emTrjDynUpdateTargetOnly);
	GetCFx_BaseVal(emProps, _emFXCreate_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCreate_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXInvestOrigin_S)->SetValue(OleVar(oCVisualFX::actFX->emFXInvestOrigin_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXInvestTarget_S)->SetValue(OleVar(oCVisualFX::actFX->emFXInvestTarget_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXTriggerDelay)->SetValue(OleVar(oCVisualFX::actFX->emFXTriggerDelay));
	GetCFx_BaseVal(emProps, _emFXCreatedOwnTrj)->SetValue((_variant_t)(bool)oCVisualFX::actFX->emFXCreatedOwnTrj);
	GetCFx_BaseVal(emProps, _emActionCollDyn_S)->SetValue(OleVar(oCVisualFX::actFX->emActionCollDyn_S.ToChar()));
	GetCFx_BaseVal(emProps, _emActionCollStat_S)->SetValue(OleVar(oCVisualFX::actFX->emActionCollStat_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXCollStat_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCollStat_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXCollDyn_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCollDyn_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXCollDynPerc_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCollDynPerc_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXCollStatAlign_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCollStatAlign_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXCollDynAlign_S)->SetValue(OleVar(oCVisualFX::actFX->emFXCollDynAlign_S.ToChar()));
	GetCFx_BaseVal(emProps, _emFXLifeSpan)->SetValue(OleVar(oCVisualFX::actFX->emFXLifeSpan));
	GetCFx_BaseVal(emProps, _emCheckCollision)->SetValue((_variant_t)(bool)oCVisualFX::actFX->emCheckCollision);
	GetCFx_BaseVal(emProps, _emAdjustShpToOrigin)->SetValue((_variant_t)(bool)oCVisualFX::actFX->emAdjustShpToOrigin);
	GetCFx_BaseVal(emProps, _emInvestNextKeyDuration)->SetValue(OleVar(oCVisualFX::actFX->emInvestNextKeyDuration));
	GetCFx_BaseVal(emProps, _emFlyGravity)->SetValue(OleVar(oCVisualFX::actFX->emFlyGravity));
	GetCFx_BaseVal(emProps, _emSelfRotVel_S)->SetValue(OleVar(oCVisualFX::actFX->emSelfRotVel_S.ToChar()));
	//
	GetCFx_BaseVal(otherProps, _userString0)->SetValue(OleVar(oCVisualFX::actFX->userString[0].ToChar()));
	GetCFx_BaseVal(otherProps, _userString1)->SetValue(OleVar(oCVisualFX::actFX->userString[1].ToChar()));
	GetCFx_BaseVal(otherProps, _userString2)->SetValue(OleVar(oCVisualFX::actFX->userString[2].ToChar()));
	GetCFx_BaseVal(otherProps, _userString3)->SetValue(OleVar(oCVisualFX::actFX->userString[3].ToChar()));
	GetCFx_BaseVal(otherProps, _userString4)->SetValue(OleVar(oCVisualFX::actFX->userString[4].ToChar()));
	//
	GetCFx_BaseVal(otherProps, _lightPresetName)->SetValue(OleVar(oCVisualFX::actFX->lightPresetName.ToChar()));
	GetCFx_BaseVal(otherProps, _sfxID)->SetValue(OleVar(oCVisualFX::actFX->sfxID.ToChar()));
	GetCFx_BaseVal(otherProps, _sfxIsAmbient)->SetValue((_variant_t)(bool)oCVisualFX::actFX->sfxIsAmbient);
	GetCFx_BaseVal(otherProps, _sendAssessMagic)->SetValue((_variant_t)(bool)oCVisualFX::actFX->sendAssessMagic);
	GetCFx_BaseVal(otherProps, _secsPerDamage)->SetValue(OleVar(oCVisualFX::actFX->secsPerDamage));

	CMainFrame::mainframe->wndControl->wndEmKeyProps->EditKey();
}



void CVFxBase::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!cx || !cy) return;

	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;

	OffsetChildWindow(GetDlgItem(IDC_VFXPROPS), 0, 0, dx, dy);

	GetClientRect(&m_SaveRect);
}


void CVFxBase::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = Rect.Width();
	lpMMI->ptMinTrackSize.y = Rect.Height();
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}


BOOL CVFxBase::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(&m_SaveRect);

	GetWindowRect(&Rect);

	return TRUE;
}
