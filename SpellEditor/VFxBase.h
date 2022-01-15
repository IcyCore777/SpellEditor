#pragma once

//oCVisualFX defines

#define visProps					0

#define _visName_S					0
#define _visSize_S					1
#define _visAlpha					2
#define _visAlphaBlendFunc_S		3
#define _visTexAniFPS				4
#define _visTexAniIsLooping			5

#define emProps						1

#define _emTrjMode_S				0
#define _emTrjOriginNode			1
#define _emTrjTargetNode			2
#define _emTrjTargetRange			3
#define _emTrjTargetAzi				4
#define _emTrjTargetElev			5
#define _emTrjNumKeys				6
#define _emTrjNumKeysVar			7
#define _emTrjAngleElevVar			8
#define _emTrjAngleHeadVar			9
#define _emTrjKeyDistVar			10
#define _emTrjLoopMode_S			11
#define _emTrjEaseFunc_S			12
#define _emTrjEaseVel				13
#define _emTrjDynUpdateDelay		14
#define _emTrjDynUpdateTargetOnly   15
#define _emFXCreate_S				16
#define _emFXInvestOrigin_S			17
#define _emFXInvestTarget_S			18
#define _emFXTriggerDelay			19
#define _emFXCreatedOwnTrj			20
#define _emActionCollDyn_S			21
#define _emActionCollStat_S			22
#define _emFXCollStat_S				23
#define _emFXCollDyn_S				24
#define _emFXCollDynPerc_S			25
#define _emFXCollStatAlign_S		26
#define _emFXCollDynAlign_S			27
#define _emFXLifeSpan				28
#define _emCheckCollision			29
#define _emAdjustShpToOrigin		30
#define _emInvestNextKeyDuration    31
#define _emFlyGravity				32
#define _emSelfRotVel_S				33

#define otherProps					2

#define _userString0				0
#define _userString1				1
#define _userString2				2
#define _userString3				3
#define _userString4				4
#define _lightPresetName			5
#define _sfxID						6
#define _sfxIsAmbient				7
#define _sendAssessMagic			8
#define _secsPerDamage				9

// диалоговое окно CVFxBase

class CVFxBase : public CDialogEx
{
	DECLARE_DYNAMIC(CVFxBase)

public:
	CVFxBase(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CVFxBase();
public:
	CRect m_SaveRect;
	CRect Rect;
public:
	CMFCPropertyGridCtrl visualFxParams;
public:
	CMFCPropertyGridProperty * pVis;
	CMFCPropertyGridProperty * pEm;
	CMFCPropertyGridProperty * pOther;
public:
	void InitParams();
	void  EditFx();
	char* GetString(COleVariant v);
	float GetFloat(COleVariant v);
	short GetBool(COleVariant v);
	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VFXPARAMS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnPropertyChanged(__in WPARAM wparam, __in LPARAM lparam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL OnInitDialog();
};
