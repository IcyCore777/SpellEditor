// PfxProps.cpp: файл реализации
//

#include "stdafx.h"
#include "SpellEditor.h"
#include "PfxProps.h"
#include "afxdialogex.h"
#include "Control.h"

float speed = 0.002f;

OleVar value;

IMPLEMENT_DYNAMIC(CPfxProps, CDialogEx)

CPfxProps::CPfxProps(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PFXPROPS, pParent)
{
	//World
	pfx				= NULL;
	emitter			= NULL;
	particleVob		= NULL;
	particleRotVob	= NULL;
	//Prop Grid
	pEmitterPpsTime	= NULL;
	pShape			= NULL;
	pSpeedDir		= NULL;
	pLifeTime		= NULL;
	pGravityColl	= NULL;

	pVisual			= NULL;
	pColor			= NULL;
	pSizeAni		= NULL;
	pAlpha			= NULL;

	pMiscParams		= NULL;
	pTrail			= NULL;
	pMarks			= NULL;
	pFlocking		= NULL;
	pOther			= NULL;
}

CPfxProps::~CPfxProps()
{
}

void CPfxProps::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PFXPROPS, PfxParams);
}


BEGIN_MESSAGE_MAP(CPfxProps, CDialogEx)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

void CPfxProps::InitParams()
{
	//Set window pos
	RECT wrect;
	GetWindowRect(&wrect);
	SetWindowPos(&wndTop, 0, 0, wrect.right - wrect.left, wrect.bottom - wrect.top, 0);

	//Init Values

	GetClientRect(&m_SaveRect);

	GetWindowRect(&Rect);
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));

	PfxParams.EnableHeaderCtrl(TRUE, _T("Parameter"), _T("Value"));
	PfxParams.SetVSDotNetLook(TRUE);


	//time pps flow
	OleVar	ppsValue = (float)0;
	OleVar	ppsScaleKeys_S = CString("");
	OleVar	ppsIsLooping((short)0, VT_BOOL);
	OleVar	ppsIsSmooth((short)0, VT_BOOL);
	OleVar	ppsFPS = (float)0;
	OleVar	ppsCreateEm_S = CString("");
	OleVar	ppsCreateEmDelay = (float)0;

	//space params
	OleVar	shpType_S = CString("POINT");
	OleVar	shpFOR_S = CString("OBJECT");
	OleVar	shpOffsetVec_S = CString("");
	OleVar	shpDistribType_S = CString("RAND");
	OleVar	shpDistribWalkSpeed = (float)0;
	OleVar	shpIsVolume((short)0, VT_BOOL);
	OleVar	shpDim_S = CString("");
	OleVar	shpMesh_S = CString("");
	OleVar	shpMeshRender_B((short)0, VT_BOOL);
	OleVar	shpScaleKeys_S = CString("");
	OleVar	shpScaleIsLooping((short)0, VT_BOOL);
	OleVar	shpScaleIsSmooth((short)0, VT_BOOL);
	OleVar	shpScaleFPS = (float)0;

	//speed, direction
	OleVar	dirMode_S = CString("DIR");
	OleVar	dirFOR_S = CString("OBJECT");
	OleVar	dirModeTargetFOR_S = CString("");
	OleVar	dirModeTargetPos_S = CString("");
	OleVar	dirAngleHead = (float)0;
	OleVar	dirAngleHeadVar = (float)0;
	OleVar	dirAngleElev = (float)0;
	OleVar	dirAngleElevVar = (float)0;
	OleVar	velAvg = (float)0;
	OleVar	velVar = (float)0;

	//particles Lifetime
	OleVar	lspPartAvg = (float)0;
	OleVar	lspPartVar = (float)0;
	//particles gravity, collision
	OleVar	flyGravity_S = CString("");
	OleVar	flyCollDet_B = (_variant_t)0;

	// 6) particles visualisation
	OleVar	visName_S = CString("");
	OleVar	visOrientation_S = CString("NONE");
	OleVar	visTexIsQuadPoly((short)0, VT_BOOL);
	OleVar	visTexAniFPS = (float)0;
	//OleVar	visTexAniIsLooping((short)0, VT_BOOL);
	OleVar	visTexAniIsLooping((long)0);


	// color		(nur Tex, lifeSpan-Sync)			
	OleVar	visTexColorStart_S = CString("");
	OleVar	visTexColorEnd_S = CString("");

	// size-ani		(nur Tex, lifeSpan-Sync)
	OleVar	visSizeStart_S = CString("");
	OleVar	visSizeEndScale = (float)0;

	// alpha		(lifeSpan-Sync)
	OleVar	visAlphaFunc_S = CString("");
	OleVar	visAlphaStart = (float)0;
	OleVar	visAlphaEnd = (float)0;

	// 7) misc effects

	// trail
	OleVar	trlFadeSpeed = (float)0;
	OleVar	trlTexture_S = CString("");
	OleVar	trlWidth = (float)0;

	// marks
	OleVar	mrkFadeSpeed = (float)0;
	OleVar	mrkTexture_S = CString("");
	OleVar	mrkSize = (float)0;

	// flocking
	OleVar	flockMode = CString("NONE");
	OleVar	flockStrength = (float)0;

	// other
	OleVar 	useEmittersFOR((short)0, VT_BOOL);
	OleVar	timeStartEnd_S = CString("");
	OleVar	m_bIsAmbientPFX((short)0, VT_BOOL);


	{
		pEmitterPpsTime = NewProp(_T("Emitter: time, flow, pps"));
		PfxParams.AddProperty(pEmitterPpsTime);

		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsValue"), ppsValue, _T("Num particles per second")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsScaleKeys_S"), ppsScaleKeys_S, _T("per second pps multiplier  \r\n\"1 2 0 0.5 1\" ")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsIsLooping"), ppsIsLooping, _T("if True pfx has infinite life")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsIsSmooth"), ppsIsSmooth, _T("Smooth transition in scale keys")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsFPS"), ppsFPS, _T("Scale keys fps")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsCreateEm_S"), ppsCreateEm_S, _T("Create child pfx \r\nchild pfx instance name")));
		pEmitterPpsTime->AddSubItem(NewProp(_T("ppsCreateEmDelay"), ppsCreateEmDelay, _T("Delay between creation child pfx")));
	}

	{
		pShape = NewProp(_T("Emitter: shape"));
		PfxParams.AddProperty(pShape);


		CMFCPropertyGridProperty* pShpType_S = NewProp(_T("shpType_S"), shpType_S, _T("Sets the type of radiating surface"));
		pShpType_S->AddOption(_T("POINT"));
		pShpType_S->AddOption(_T("LINE"));
		pShpType_S->AddOption(_T("BOX"));
		pShpType_S->AddOption(_T("CIRCLE"));
		pShpType_S->AddOption(_T("SPHERE"));
		pShpType_S->AddOption(_T("MESH"));
		pShpType_S->AllowEdit(FALSE);
		pShape->AddSubItem(pShpType_S);

		CMFCPropertyGridProperty* pShpFOR_S = NewProp(_T("shpFOR_S"), shpFOR_S, _T("should the particles follow the turns of the surface \r\nWORLD = no \r\nOBJECT = yes"));
		pShpFOR_S->AddOption(_T("OBJECT"));
		pShpFOR_S->AddOption(_T("WORLD"));
		pShpFOR_S->AllowEdit(FALSE);
		pShape->AddSubItem(pShpFOR_S);

		pShape->AddSubItem(NewProp(_T("shpOffsetVec_S"), shpOffsetVec_S, _T("Emitter point offset")));

		CMFCPropertyGridProperty* pShpDistribType_S = NewProp(_T("shpDistribType_S"), shpDistribType_S, _T("Sets the distribution of emitted particles over the surface."));
		pShpDistribType_S->AddOption(_T("RAND"));
		pShpDistribType_S->AddOption(_T("UNIFORM"));
		pShpDistribType_S->AddOption(_T("WALK"));
		pShpDistribType_S->AllowEdit(FALSE);
		pShape->AddSubItem(pShpDistribType_S);

		pShape->AddSubItem(NewProp(_T("shpDistribWalkSpeed"), shpDistribWalkSpeed, _T("Sets the speed of movement on the surface of the particles source.")));
		pShape->AddSubItem(NewProp(_T("shpIsVolume"), shpIsVolume, _T("shpIsVolume")));
		pShape->AddSubItem(NewProp(_T("shpDim_S"), shpDim_S, _T("shpDim_S")));
		pShape->AddSubItem(NewProp(_T("shpMesh_S"), shpMesh_S, _T("shpMesh_S")));
		pShape->AddSubItem(NewProp(_T("shpMeshRender_B"), shpMeshRender_B, _T("shpMeshRender_B")));
		pShape->AddSubItem(NewProp(_T("shpScaleKeys_S"), shpScaleKeys_S, _T("shpScaleKeys_S")));
		pShape->AddSubItem(NewProp(_T("shpScaleIsLooping"), shpScaleIsLooping, _T("shpScaleIsLooping")));
		pShape->AddSubItem(NewProp(_T("shpScaleIsSmooth"), shpScaleIsSmooth, _T("shpScaleIsSmooth")));
		pShape->AddSubItem(NewProp(_T("shpScaleFPS"), shpScaleFPS, _T("shpScaleFPS")));
	}

	{
		pSpeedDir = NewProp(_T("Particles: direction, speed"));
		PfxParams.AddProperty(pSpeedDir);

		CMFCPropertyGridProperty* pDirMode_S = NewProp(_T("dirMode_S"), dirMode_S, _T("dirMode_S"));
		pDirMode_S->AddOption(_T("DIR"));
		pDirMode_S->AddOption(_T("TARGET"));
		pDirMode_S->AddOption(_T("MESH_POLY"));
		pDirMode_S->AddOption(_T("NONE"));
		pDirMode_S->AllowEdit(FALSE);
		pSpeedDir->AddSubItem(pDirMode_S);

		CMFCPropertyGridProperty* pDirFOR_S = NewProp(_T("dirFOR_S"), dirFOR_S, _T("dirFOR_S"));
		pDirFOR_S->AddOption(_T("OBJECT"));
		pDirFOR_S->AddOption(_T("WORLD"));
		pDirFOR_S->AllowEdit(FALSE);
		pSpeedDir->AddSubItem(pDirFOR_S);

		pSpeedDir->AddSubItem(NewProp(_T("dirModeTargetFOR_S"), dirModeTargetFOR_S, _T("dirModeTargetFOR_S")));
		pSpeedDir->AddSubItem(NewProp(_T("dirModeTargetPos_S"), dirModeTargetPos_S, _T("dirModeTargetPos_S")));
		pSpeedDir->AddSubItem(NewProp(_T("dirAngleHead"), dirAngleHead, _T("dirAngleHead")));
		pSpeedDir->AddSubItem(NewProp(_T("dirAngleHeadVar"), dirAngleHeadVar, _T("dirAngleHeadVar")));
		pSpeedDir->AddSubItem(NewProp(_T("dirAngleElev"), dirAngleElev, _T("dirAngleElev")));
		pSpeedDir->AddSubItem(NewProp(_T("dirAngleElevVar"), dirAngleElevVar, _T("dirAngleElevVar")));
		pSpeedDir->AddSubItem(NewProp(_T("velAvg"), velAvg, _T("velAvg")));
		pSpeedDir->AddSubItem(NewProp(_T("velVar"), velVar, _T("velVar")));
	}

	{
		pLifeTime = NewProp(_T("Particles: lifetime"));
		PfxParams.AddProperty(pLifeTime);

		pLifeTime->AddSubItem(NewProp(_T("lspPartAvg"), lspPartAvg, _T("lspPartAvg")));
		pLifeTime->AddSubItem(NewProp(_T("lspPartVar"), lspPartVar, _T("lspPartVar")));
	}

	{
		pGravityColl = NewProp(_T("Particles: gravity, collision"));
		PfxParams.AddProperty(pGravityColl);

		pGravityColl->AddSubItem(NewProp(_T("flyGravity_S"), flyGravity_S, _T("flyGravity_S - XYZ vector"))); //
		pGravityColl->AddSubItem(NewProp(_T("flyCollDet_B"), flyCollDet_B, _T("0 - no collision detect \r\n1 - reflect, damp \r\n2 - reflect, accel \r\n3 - freeze \r\n4 - remove")));
	}

	{
		pVisual = NewProp(_T("Particles: visualisation"));
		PfxParams.AddProperty(pVisual);


		pVisual->AddSubItem(NewProp(_T("visName_S"), visName_S, _T("visName_S")));

		CMFCPropertyGridProperty* pVisOrientation_S = NewProp(_T("visOrientation_S"), visOrientation_S, _T("NONE, VELO"));
		pVisOrientation_S->AddOption(_T("NONE"));
		pVisOrientation_S->AddOption(_T("VELO3D"));
		pVisOrientation_S->AddOption(_T("VEL"));
		pVisOrientation_S->AddOption(_T("VOB"));
		pVisOrientation_S->AllowEdit(FALSE);
		pVisual->AddSubItem(pVisOrientation_S);

		pVisual->AddSubItem(NewProp(_T("visTexIsQuadPoly"), visTexIsQuadPoly, _T("FALSE = triMesh, TRUE = quadMesh")));
		pVisual->AddSubItem(NewProp(_T("visTexAniFPS"), visTexAniFPS, _T("visTexAniFPS")));
		pVisual->AddSubItem(NewProp(_T("visTexAniIsLooping"), visTexAniIsLooping, _T("visTexAniIsLooping")));

		{
			pColor = NewProp("Color");
			PfxParams.AddProperty(pColor);


			CMFCPropertyGridColorProperty * startColor = new CMFCPropertyGridColorProperty(_T("visTexColorStart_S"), RGB(0, 198, 250), NULL, _T("Set start color"));
			CMFCPropertyGridColorProperty * endColor = new CMFCPropertyGridColorProperty(_T("visTexColorEnd_S"), RGB(0, 198, 250), NULL, _T("Set end color"));
			startColor->EnableOtherButton(_T("Other..."));
			endColor->EnableOtherButton(_T("Other..."));

			pColor->AddSubItem(startColor);
			pColor->AddSubItem(endColor);
		}

		{
			pSizeAni = NewProp("Size, ani");
			PfxParams.AddProperty(pSizeAni);
			pSizeAni->AddSubItem(NewProp(_T("visSizeStart_S"), visSizeStart_S, _T("visSizeStart_S - XYZ")));//
			pSizeAni->AddSubItem(NewProp(_T("visSizeEndScale"), visSizeEndScale, _T("visSizeEndScale")));
		}

		{
			pAlpha = NewProp("Alpha");
			PfxParams.AddProperty(pAlpha);

			CMFCPropertyGridProperty* pAlphaFunc = NewProp(_T("visAlphaFunc_S"), visAlphaFunc_S, _T("visAlphaFunc_S"));
			pAlphaFunc->AddOption(_T("MAT_DEFAULT"));
			pAlphaFunc->AddOption(_T("NONE"));
			pAlphaFunc->AddOption(_T("BLEND"));
			pAlphaFunc->AddOption(_T("ADD"));
			pAlphaFunc->AddOption(_T("SUB"));
			pAlphaFunc->AddOption(_T("MUL"));
			pAlphaFunc->AddOption(_T("MUL2"));
			pAlphaFunc->AllowEdit(FALSE);
			pAlpha->AddSubItem(pAlphaFunc);

			pAlpha->AddSubItem(NewProp(_T("visAlphaStart"), visAlphaStart, _T("visAlphaStart")));
			pAlpha->AddSubItem(NewProp(_T("visAlphaEnd"), visAlphaEnd, _T("visAlphaEnd")));
		}
	}

	{
		pMiscParams = NewProp("Misc");
		PfxParams.AddProperty(pMiscParams);

		pTrail = NewProp("Trail");
		pMiscParams->AddSubItem(pTrail);

		pTrail->AddSubItem(NewProp(_T("trlFadeSpeed"), trlFadeSpeed, _T("trlFadeSpeed")));
		pTrail->AddSubItem(NewProp(_T("trlTexture_S"), trlTexture_S, _T("trlTexture_S")));
		pTrail->AddSubItem(NewProp(_T("trlWidth"), trlWidth, _T("trlWidth")));

		pMarks = NewProp("Marks");
		pMiscParams->AddSubItem(pMarks);

		pMarks->AddSubItem(NewProp(_T("mrkFadeSpeed"), mrkFadeSpeed, _T("mrkFadeSpeed")));
		pMarks->AddSubItem(NewProp(_T("mrkTexture_S"), mrkTexture_S, _T("mrkTexture_S")));
		pMarks->AddSubItem(NewProp(_T("mrkSize"), mrkSize, _T("mrkSize")));

		pFlocking = NewProp("Flocking");
		pMiscParams->AddSubItem(pFlocking);

		CMFCPropertyGridProperty* pFlockMode = NewProp(_T("flockMode"), flockMode, _T("flockMode"));
		pFlockMode->AddOption(_T("NONE"));
		pFlockMode->AddOption(_T("WIND"));
		pFlockMode->AddOption(_T("PLANTS"));
		pFlockMode->AllowEdit(FALSE);
		pFlocking->AddSubItem(pFlockMode);

		pFlocking->AddSubItem(NewProp(_T("flockStrength"), flockStrength, _T("flockStrength")));
	}

	{
		pOther = NewProp("Other");
		PfxParams.AddProperty(pOther);

		pOther->AddSubItem(NewProp(_T("useEmittersFOR"), useEmittersFOR, _T("useEmittersFOR")));
		pOther->AddSubItem(NewProp(_T("timeStartEnd_S"), timeStartEnd_S, _T("timeStartEnd_S")));
		pOther->AddSubItem(NewProp(_T("m_bIsAmbientPFX"), m_bIsAmbientPFX, _T("m_bIsAmbientPFX")));
	}


	PfxParams.MarkModifiedProperties();
	PfxParams.SetCustomColors(RGB(228, 243, 254), RGB(46, 70, 165), RGB(200, 236, 209), RGB(33, 102, 49), RGB(255, 229, 216), RGB(128, 0, 0), RGB(159, 159, 255));
	PfxParams.ShowScrollBar(SB_VERT);
	PfxParams.ShowScrollBar(SB_VERT, FALSE);
}

void CPfxProps::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = Rect.Width();
	lpMMI->ptMinTrackSize.y = Rect.Height();
	CDialogEx::OnGetMinMaxInfo(lpMMI);
}

void CPfxProps::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (!cx || !cy) return;

	int dx = cx - m_SaveRect.right;
	int dy = cy - m_SaveRect.bottom;

	OffsetChildWindow(GetDlgItem(IDC_PFXPROPS), 0, 0, dx, dy);

	GetClientRect(&m_SaveRect);
}

BOOL CPfxProps::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	GetClientRect(&m_SaveRect);
	GetWindowRect(&Rect);
	return TRUE; 
}

bool CPfxProps::GetEmitterBool(int b)
{
	if (b)
		return true;
	else
		return false;
}

char* CPfxProps::GetString(COleVariant v)
{
	return _com_util::ConvertBSTRToString(v.bstrVal);
}

float CPfxProps::GetFloat(COleVariant v)
{
	return v.fltVal;
}

short CPfxProps::GetBool(COleVariant v)
{
	if (v.boolVal == -1)
		return 1;
	if (v.boolVal == 0)
		return 0;
}



zVEC3 String2Vec3(const zSTRING& s) {
	zVEC3 v;
	v[0] = s.PickWord(1, " ", " ").ToFloat();
	v[1] = s.PickWord(2, " ", " ").ToFloat();
	v[2] = s.PickWord(3, " ", " ").ToFloat();
	return v;
};
//color
inline zVEC3 GetRgb(zSTRING color)
{
	zVEC3 clr; clr = String2Vec3(color);

	return clr;
}

COLORREF GetColorRef(zSTRING str)
{
	return RGB(GetRgb(str).n[0], GetRgb(str).n[1], GetRgb(str).n[2]);
}

void CPfxProps::EditFx()
{
	if (!emitter)
	{
		MessageBox("Emitter not found!", 0, 0);
		return;
	}
	//MessageBox(emitter->shpType_S.ToChar(), 0, 0);

	SetWindowText(emitter->particleFXName.ToChar());
	{
		//emitter tfp
		GetPfxProp(EmitterTFP, _ppsValue)->SetValue(OleVar(emitter->ppsValue));
		GetPfxProp(EmitterTFP, _ppsScaleKeys_S)->SetValue(OleVar(emitter->ppsScaleKeys_S.ToChar()));
		GetPfxProp(EmitterTFP, _ppsIsLooping)->SetValue((_variant_t)(bool)emitter->ppsIsLooping);
		GetPfxProp(EmitterTFP, _ppsIsSmooth)->SetValue((_variant_t)(bool)emitter->ppsIsSmooth);
		GetPfxProp(EmitterTFP, _ppsFPS)->SetValue(OleVar(emitter->ppsFPS));
		GetPfxProp(EmitterTFP, _ppsCreateEm_S)->SetValue(OleVar(emitter->ppsCreateEm_S.ToChar()));
		GetPfxProp(EmitterTFP, _ppsCreateEmDelay)->SetValue(OleVar(emitter->ppsCreateEmDelay));
	}

	{
		//emitter shape
		GetPfxProp(EmitterShape, _shpType_S)->SetValue(OleVar(emitter->shpType_S.ToChar()));
		GetPfxProp(EmitterShape, _shpFOR_S)->SetValue(OleVar(emitter->shpFOR_S.ToChar()));
		GetPfxProp(EmitterShape, _shpOffsetVec_S)->SetValue(OleVar(emitter->shpOffsetVec_S.ToChar()));
		GetPfxProp(EmitterShape, _shpDistribType_S)->SetValue(OleVar(emitter->shpDistribType_S.ToChar()));
		GetPfxProp(EmitterShape, _shpDistribWalkSpeed)->SetValue(OleVar(emitter->shpDistribWalkSpeed));
		GetPfxProp(EmitterShape, _shpIsVolume)->SetValue((_variant_t)(bool)emitter->shpIsVolume);
		GetPfxProp(EmitterShape, _shpDim_S)->SetValue(OleVar(emitter->shpDim_S.ToChar()));
		GetPfxProp(EmitterShape, _shpMesh_S)->SetValue(OleVar(emitter->shpMesh_S.ToChar()));
		GetPfxProp(EmitterShape, _shpMeshRender_B)->SetValue((_variant_t)(bool)emitter->shpMeshRender_B);
		GetPfxProp(EmitterShape, _shpScaleKeys_S)->SetValue(OleVar(emitter->shpScaleKeys_S.ToChar()));
		GetPfxProp(EmitterShape, _shpScaleIsLooping)->SetValue((_variant_t)(bool)emitter->shpScaleIsLooping);
		GetPfxProp(EmitterShape, _shpScaleIsSmooth)->SetValue((_variant_t)(bool)emitter->shpScaleIsSmooth);
		GetPfxProp(EmitterShape, _shpScaleFPS)->SetValue(OleVar(emitter->shpScaleFPS));
	}

	{
		//speed, direction
		GetPfxProp(ParticlesSpdDir, _dirMode_S)->SetValue(OleVar(emitter->dirMode_S.ToChar()));
		GetPfxProp(ParticlesSpdDir, _dirFOR_S)->SetValue(OleVar(emitter->dirFOR_S.ToChar()));
		GetPfxProp(ParticlesSpdDir, _dirModeTargetFOR_S)->SetValue(OleVar(emitter->dirModeTargetFOR_S.ToChar()));
		GetPfxProp(ParticlesSpdDir, _dirModeTargetPos_S)->SetValue(OleVar(emitter->dirModeTargetPos_S.ToChar()));
		GetPfxProp(ParticlesSpdDir, _dirAngleHead)->SetValue(OleVar(emitter->dirAngleHead));
		GetPfxProp(ParticlesSpdDir, _dirAngleHeadVar)->SetValue(OleVar(emitter->dirAngleHeadVar));
		GetPfxProp(ParticlesSpdDir, _dirAngleElev)->SetValue(OleVar(emitter->dirAngleElev));
		GetPfxProp(ParticlesSpdDir, _dirAngleElevVar)->SetValue(OleVar(emitter->dirAngleElevVar));
		GetPfxProp(ParticlesSpdDir, _velAvg)->SetValue(OleVar(emitter->velAvg));
		GetPfxProp(ParticlesSpdDir, _velVar)->SetValue(OleVar(emitter->velVar));
	}

	{
		//lifetime
		GetPfxProp(ParticlesLife, _lspPartAvg)->SetValue(OleVar(emitter->lspPartAvg));
		GetPfxProp(ParticlesLife, _lspPartVar)->SetValue(OleVar(emitter->lspPartVar));
	}

	{
		//gravity
		GetPfxProp(ParticlesGrav, _flyGravity_S)->SetValue(OleVar(emitter->flyGravity_S.ToChar()));
		GetPfxProp(ParticlesGrav, _flyCollDet_B)->SetValue((_variant_t)emitter->flyCollDet_B);
	}

	{
		//Visualisation
		GetPfxProp(ParticlesVis, _visName_S)->SetValue(OleVar(emitter->visName_S.ToChar()));
		GetPfxProp(ParticlesVis, _visOrientation_S)->SetValue(OleVar(emitter->visOrientation_S.ToChar()));
		GetPfxProp(ParticlesVis, _visTexIsQuadPoly)->SetValue((_variant_t)(bool)emitter->visTexIsQuadPoly);
		GetPfxProp(ParticlesVis, _visTexAniFPS)->SetValue(OleVar(emitter->visTexAniFPS));
		GetPfxProp(ParticlesVis, _visTexAniIsLooping)->SetValue((long)emitter->visTexAniIsLooping);
		//GetPfxProp(ParticlesVis, _visTexAniIsLooping)->SetValue((_variant_t)(bool)emitter->visTexAniIsLooping);

	}

	{
		CMFCPropertyGridColorProperty* startColor = (CMFCPropertyGridColorProperty*)GetPfxProp(Color, _visTexColorStart_S);
		startColor->SetColor(GetColorRef(emitter->visTexColorStart_S.ToChar()));
		CMFCPropertyGridColorProperty* endColor = (CMFCPropertyGridColorProperty*)GetPfxProp(Color, _visTexColorEnd_S);
		endColor->SetColor(GetColorRef(emitter->visTexColorEnd_S.ToChar()));
	}

	{
		//SizeAni
		GetPfxProp(SizeAni, _visSizeStart_S)->SetValue(OleVar(emitter->visSizeStart_S.ToChar()));
		GetPfxProp(SizeAni, _visSizeEndScale)->SetValue(OleVar(emitter->visSizeEndScale));
	}

	{
		//aplha
		GetPfxProp(Aplha, _visAlphaFunc_S)->SetValue(OleVar(emitter->visAlphaFunc_S.ToChar()));
		GetPfxProp(Aplha, _visAlphaStart)->SetValue(OleVar(emitter->visAlphaStart));
		GetPfxProp(Aplha, _visAlphaEnd)->SetValue(OleVar(emitter->visAlphaEnd));
	}

	{
		//Misk
		//trail
		GetPfxProp(Misk, MiskTrail)->GetSubItem(_trlFadeSpeed)->SetValue(emitter->trlFadeSpeed);
		GetPfxProp(Misk, MiskTrail)->GetSubItem(_trlTexture_S)->SetValue(emitter->trlTexture_S.ToChar());
		GetPfxProp(Misk, MiskTrail)->GetSubItem(_trlWidth)->SetValue(emitter->trlWidth);

		//marks
		GetPfxProp(Misk, MiskMarks)->GetSubItem(_mrkFadeSpeed)->SetValue(emitter->mrkFadeSpeed);
		GetPfxProp(Misk, MiskMarks)->GetSubItem(_mrkTexture_S)->SetValue(emitter->mrkTexture_S.ToChar());
		GetPfxProp(Misk, MiskMarks)->GetSubItem(_mrkSize)->SetValue(emitter->mrkSize);

		//flocking
		GetPfxProp(Misk, MiskFlocking)->GetSubItem(_flockMode)->SetValue(emitter->m_flockMode_S.ToChar());
		GetPfxProp(Misk, MiskFlocking)->GetSubItem(_flockStrength)->SetValue(emitter->m_fFlockWeight);
	}

	{
		//other
		GetPfxProp(Other, _useEmittersFOR)->SetValue((_variant_t)(bool)emitter->m_bSlowLocalFOR);
		GetPfxProp(Other, _timeStartEnd_S)->SetValue(emitter->m_timeStartEnd_S.ToChar());
		GetPfxProp(Other, _m_bIsAmbientPFX)->SetValue((_variant_t)(bool)emitter->m_bIsAmbientPFX);
	}
}

LRESULT CPfxProps::OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam)
{
	CMFCPropertyGridProperty * pProp = (CMFCPropertyGridProperty*)lparam;
	ccstr param = pProp->GetName();
	value = pProp->GetValue();
	if (!emitter) return (0);

	{
		if (param == "ppsValue")
			emitter->ppsValue = GetFloat(value);

		if (param == "ppsScaleKeys_S")
			emitter->ppsScaleKeys_S = GetString(value);

		if (param == "ppsIsLooping")
			emitter->ppsIsLooping = GetBool(value);

		if (param == "ppsIsSmooth")
			emitter->ppsIsSmooth = GetBool(value);

		if (param == "ppsFPS")
			emitter->ppsFPS = GetFloat(value);

		if (param == "ppsCreateEm_S")
			emitter->ppsCreateEm_S = GetString(value);

		if (param == "ppsCreateEmDelay")
			emitter->ppsCreateEmDelay = GetFloat(value);
	}
	{
		//Shape
		if (param == "shpType_S")
			emitter->shpType_S = GetString(value);

		if (param == "shpFOR_S")
			emitter->shpFOR_S = GetString(value);

		if (param == "shpOffsetVec_S")
			emitter->shpOffsetVec_S = GetString(value);

		if (param == "shpDistribType_S")
			emitter->shpDistribType_S = GetString(value);

		if (param == "shpDistribWalkSpeed")
			emitter->shpDistribWalkSpeed = GetFloat(value);

		if (param == "shpIsVolume")
			emitter->shpIsVolume = GetBool(value);

		if (param == "shpDim_S")
			emitter->shpDim_S = GetString(value);

		if (param == "shpMesh_S")
			emitter->shpMesh_S = GetString(value);

		if (param == "shpMeshRender_B")
			emitter->shpMeshRender_B = GetBool(value);

		if (param == "shpScaleKeys_S")
			emitter->shpScaleKeys_S = GetString(value);

		if (param == "shpScaleIsLooping")
			emitter->shpScaleIsLooping = GetBool(value);

		if (param == "shpScaleIsSmooth")
			emitter->shpScaleIsSmooth = GetBool(value);

		if (param == "shpScaleFPS")
			emitter->shpScaleFPS = GetFloat(value);
	}
	{
		//direction
		if (param == "dirMode_S")
			emitter->dirMode_S = GetString(value);

		if (param == "dirFOR_S")
			emitter->dirFOR_S = GetString(value);

		if (param == "dirModeTargetFOR_S")
			emitter->dirModeTargetFOR_S = GetString(value);

		if (param == "dirModeTargetPos_S")
			emitter->dirModeTargetPos_S = GetString(value);

		if (param == "dirAngleHead")
			emitter->dirAngleHead = GetFloat(value);

		if (param == "dirAngleHeadVar")
			emitter->dirAngleHeadVar = GetFloat(value);

		if (param == "dirAngleElev")
			emitter->dirAngleElev = GetFloat(value);

		if (param == "dirAngleElevVar")
			emitter->dirAngleElevVar = GetFloat(value);
	}
	{
		//
		if (param == "velAvg")
			emitter->velAvg = GetFloat(value);
		if (param == "velVar")
			emitter->velVar = GetFloat(value);

		if (param == "lspPartAvg")
			emitter->lspPartAvg = GetFloat(value);
		if (param == "lspPartVar")
			emitter->lspPartVar = GetFloat(value);

		if (param == "flyGravity_S")
			emitter->flyGravity_S = GetString(value);
		if (param == "flyCollDet_B")
			emitter->flyCollDet_B = value.intVal;
	}
	{
		if (param == "visName_S")
			emitter->visName_S = GetString(value);
		if (param == "visOrientation_S")
			emitter->visOrientation_S = GetString(value);
		if (param == "visTexIsQuadPoly")
			emitter->visTexIsQuadPoly = GetBool(value);
		if (param == "visTexAniFPS")
			emitter->visTexAniFPS = GetFloat(value);
		if (param == "visTexAniIsLooping")
			emitter->visTexAniIsLooping = value.llVal;
			//emitter->visTexAniIsLooping = GetBool(value);
	}
	{
		CMFCPropertyGridColorProperty* color = (CMFCPropertyGridColorProperty*)pProp;
		if (param == "visTexColorStart_S")
			emitter->visTexColorStart_S = zCOLOR(GetRValue(color->GetColor()), GetGValue(color->GetColor()), GetBValue(color->GetColor())).GetDescriptionRGB();

		if (param == "visTexColorEnd_S")
			emitter->visTexColorEnd_S = zCOLOR(GetRValue(color->GetColor()), GetGValue(color->GetColor()), GetBValue(color->GetColor())).GetDescriptionRGB();
	}
	{
		if (param == "visSizeStart_S")
			emitter->visSizeStart_S = GetString(value);
		if (param == "visSizeEndScale")
			emitter->visSizeEndScale = GetFloat(value);
		if (param == "visAlphaFunc_S")
			emitter->visAlphaFunc_S = GetString(value);
		if (param == "visAlphaStart")
			emitter->visAlphaStart = GetFloat(value);
		if (param == "visAlphaEnd")
			emitter->visAlphaEnd = GetFloat(value);
	}
	{
		if (param == "trlFadeSpeed")
			emitter->trlFadeSpeed = GetFloat(value);
		if (param == "trlTexture_S")
			emitter->trlTexture_S = GetString(value);
		if (param == "trlWidth")
			emitter->trlWidth = GetFloat(value);
		if (param == "mrkFadeSpeed")
			emitter->mrkFadeSpeed = GetFloat(value);
		if (param == "mrkTexture_S")
			emitter->mrkTexture_S = GetString(value);
		if (param == "mrkSize")
			emitter->mrkSize = GetFloat(value);

		if (param == "flockMode")
			emitter->m_flockMode_S = GetString(value);
		if (param == "flockStrength")
			emitter->m_fFlockWeight = GetFloat(value);
		if (param == "useEmittersFOR")
			emitter->m_bSlowLocalFOR = GetBool(value);
		if (param == "timeStartEnd_S")
			emitter->m_timeStartEnd_S = GetString(value);
		if (param == "m_bIsAmbientPFX")
			emitter->m_bIsAmbientPFX = GetBool(value);
	}
	emitter->UpdateInternals();
	return(0);
}

void CPfxProps::CreateParticleFxScript(zSTRING& pfx)
{
	// Rename ??
	pfx.Upper();
	zoptions->ChangeDir(DIR_SCRIPTS);

	zFILE *file = zfactory->CreateZFile("System\\Pfx\\PfxInstMagic.d");
	file->Open(true);
	file->Append();
	file->Write(zSTRING("\nINSTANCE " + pfx + "(C_PARTICLEFX)\n"));
	file->Write(zSTRING("{\n"));
	file->Write(zSTRING("};\n"));
	file->Close();
	delete (file);

	zCParticleFX::ParseParticleFXScript_union();
	
}


void CPfxProps::RotateVob()
{


	static zVEC3 pivot = particleVob->GetPositionWorld();
	static float rotater = 0.0;
	
	static const float range = 350.0f;

	rotater += speed * ztimer->frameTimeFloat;
	if (rotater >= PI * 2.0f)
		rotater = 0.0f;

	float x = sin(rotater) * range;
	float y = cos(rotater) * range;
	particleRotVob->SetPositionWorld(pivot + zVEC3(x, 0.0f, y));
}
