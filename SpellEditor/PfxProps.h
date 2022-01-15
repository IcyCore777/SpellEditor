#pragma once


#define EmitterTFP				0

#define _ppsValue				0
#define _ppsScaleKeys_S			1
#define _ppsIsLooping			2
#define _ppsIsSmooth			3
#define _ppsFPS					4
#define _ppsCreateEm_S			5
#define _ppsCreateEmDelay		6

#define EmitterShape			1

//space params
#define _shpType_S				0
#define _shpFOR_S				1
#define _shpOffsetVec_S			2
#define _shpDistribType_S		3
#define _shpDistribWalkSpeed	4
#define _shpIsVolume			5
#define _shpDim_S				6
#define _shpMesh_S				7
#define _shpMeshRender_B		8
#define _shpScaleKeys_S			9
#define _shpScaleIsLooping		10
#define _shpScaleIsSmooth		11
#define _shpScaleFPS			12

//speed, direction
#define ParticlesSpdDir			2

#define _dirMode_S				0
#define _dirFOR_S				1
#define _dirModeTargetFOR_S		2
#define _dirModeTargetPos_S		3
#define _dirAngleHead			4
#define _dirAngleHeadVar		5
#define _dirAngleElev			6
#define _dirAngleElevVar		7
#define _velAvg					8
#define _velVar					9

#define ParticlesLife			3

//particles Lifetime
#define _lspPartAvg				0
#define _lspPartVar				1

#define ParticlesGrav			4

//particles gravity, collision
#define _flyGravity_S			0
#define _flyCollDet_B			1


#define ParticlesVis			5

// 6) particles visualisation
#define _visName_S				0
#define _visOrientation_S		1
#define _visTexIsQuadPoly		2
#define _visTexAniFPS			3
#define _visTexAniIsLooping		4

#define Color					6
// color		(nur Tex, lifeSpan-Sync)			
#define _visTexColorStart_S		0
#define _visTexColorEnd_S		1

#define SizeAni					7
// size-ani		(nur Tex, lifeSpan-Sync)
#define _visSizeStart_S			0
#define _visSizeEndScale		1

#define	Aplha					8
// alpha		(lifeSpan-Sync)
#define _visAlphaFunc_S			0
#define _visAlphaStart			1
#define _visAlphaEnd			2


#define Misk					9

#define	MiskTrail				0
#define	MiskMarks				1
#define	MiskFlocking			2

// trail
#define _trlFadeSpeed			0
#define _trlTexture_S			1
#define _trlWidth				2

// marks
#define _mrkFadeSpeed			0
#define _mrkTexture_S			1
#define _mrkSize				2

// flocking
#define _flockMode				0
#define _flockStrength			1

#define Other					10
// other
#define _useEmittersFOR			0
#define _timeStartEnd_S			1
#define _m_bIsAmbientPFX		2




// диалоговое окно CPfxProps

class CPfxProps : public CDialogEx
{
	DECLARE_DYNAMIC(CPfxProps)

public:
	CRect m_SaveRect;
	CRect Rect;

	CMFCPropertyGridCtrl PfxParams;
	zCParticleFX			 *  pfx;
	zCParticleEmitter		 *	emitter;
	zCVob					 *  particleVob;
	zCVob					 *  particleRotVob;

public:
	CMFCPropertyGridProperty *	pEmitterPpsTime;
	CMFCPropertyGridProperty *	pShape;
	CMFCPropertyGridProperty *	pSpeedDir;
	CMFCPropertyGridProperty *	pLifeTime;
	CMFCPropertyGridProperty *	pGravityColl;

	CMFCPropertyGridProperty *	pVisual;
	CMFCPropertyGridProperty*	pColor;
	CMFCPropertyGridProperty*	pSizeAni;
	CMFCPropertyGridProperty*	pAlpha;

	CMFCPropertyGridProperty *	pMiscParams;
	CMFCPropertyGridProperty *	pTrail;
	CMFCPropertyGridProperty *	pMarks;
	CMFCPropertyGridProperty *	pFlocking;
	CMFCPropertyGridProperty *	pOther;
public:
	CPfxProps(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CPfxProps();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PFXPROPS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:

	void InitParams();


	char* GetString(COleVariant v);
	float GetFloat(COleVariant v);
	short GetBool(COleVariant v);
	void EditFx();
	bool GetEmitterBool(int);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam);
	virtual BOOL OnInitDialog();
	void CreateParticleFxScript(zSTRING& pfx);
	void RotateVob();
};
