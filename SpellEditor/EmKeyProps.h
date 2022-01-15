#pragma once

//oCEmitterKey defines

#define EmvisEmProps				0        
#define _EmvisName_S				0
#define _EmvisSizeScale				1
#define _EmscaleDuration			2

#define pfxEmProps					1        
#define _Empfx_ppsValue				0
#define _Empfx_ppsIsSmoothChg		1
#define _Empfx_ppsIsLoopingChg		2
#define _Empfx_scTime				3
#define _Empfx_flyGravity_S			4

#define shpEmProps					2        
#define _Empfx_shpDim_S				0
#define _Empfx_shpIsVolumeChg		1
#define _Empfx_shpScaleFPS			2
#define _Empfx_shpDistribWalkSpeed  3
#define _Empfx_shpOffsetVec_S		4
#define _Empfx_shpDistribType_S		5
#define _Empfx_dirMode_S			6
#define _Empfx_dirFOR_S				7
#define _Empfx_dirModeTargetFOR_S   8
#define _Empfx_dirModeTargetPos_S   9
#define _Empfx_velAvg				10
#define _Empfx_lspPartAvg			11
#define _Empfx_visAlphaStart		12

#define otherEmProps				3        
#define _EmlightPresetName			0
#define _EmlightRange				1
#define _EmsfxID					2
#define _EmsfxIsAmbient				3
#define _EmemCreateFXID				4

#define emEmProps					4        
#define _EmemFlyGravity				0
#define _EmemSelfRotVel_S			1
#define _EmemTrjMode_S				2
#define _EmemTrjEaseVel				3
#define _EmemCheckCollision			4
#define _EmemFXLifeSpan				5
// диалоговое окно CEmKeyProps

class CEmKeyProps : public CDialogEx
{
	DECLARE_DYNAMIC(CEmKeyProps)

public:
	CEmKeyProps(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CEmKeyProps();

public:
	CRect m_SaveRect;
	CRect Rect;
public:
	CMFCPropertyGridCtrl emitterKeyProps;
public:
	CMFCPropertyGridProperty * pKeyVis;
	CMFCPropertyGridProperty * pKeyPfx;
	CMFCPropertyGridProperty * pKeyShp;

	CMFCPropertyGridProperty * pKeyOther;
	CMFCPropertyGridProperty * pKeyEm;
public:
	void InitParams();
	void EditKey();
	BOOL KeyMess(CString key);
	char* GetString(COleVariant v);
	float GetFloat(COleVariant v);
	short GetBool(COleVariant v);
	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EMKEYPARAMS };
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