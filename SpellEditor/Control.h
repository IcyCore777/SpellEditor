#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// диалоговое окно CControl

// диалоговое окно CControl
class CPfxProps;
class CVFxBase;
class CEmKeyProps;

class CControl : public CDialogEx
{
	DECLARE_DYNAMIC(CControl)
public:
	//pfx
	CString PfxName;
	CListBox PfxList;

	//vfx
	CString VfxName;
	CListBox VfxList;
	CString InvestNum;

	//options
	CButton drawTrj;
	CButton drawBbox;
	CButton showTarget;

	CVFxBase	* wndVfxProps;
	CPfxProps	* wndPfxProps;
	CEmKeyProps * wndEmKeyProps;


	CRect m_SaveRect;
	CRect Rect;
public:
	CControl(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CControl();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedDyn();
	afx_msg void OnBnClickedStat();
	afx_msg void OnBnClickedPfxplay();
	afx_msg void OnBnClickedSavepfx();
	afx_msg void OnBnClickedLoad();

	afx_msg void OnBnClickedVfxplay();
	afx_msg void OnBnClickedVfxsave();
	afx_msg void OnBnClickedLoadvfx();

	afx_msg void OnBnClickedPfxedit();
	afx_msg void OnBnClickedVfxedit();
	afx_msg void OnBnClickedTrj();
	afx_msg void OnBnClickedBbox();
	afx_msg void OnBnClickedTarget();

	virtual BOOL OnInitDialog();
	afx_msg void OnVfxList();
	void UpdateVfx();
	void UpdatePfx();
	CEdit vfxName;
	afx_msg void OnBnClickedKeyinit();
	afx_msg void OnBnClickedKeyopen();
	afx_msg void OnBnClickedKeycast();
	afx_msg void OnBnClickedKeyinvest();
	CEdit investNum;
	afx_msg void OnBnClickedKeystop();
	afx_msg void OnBnClickedKeycollide();
	CEdit pfxName;
	afx_msg void OnLbnSelchangePfxlist();
	CSliderCtrl Speed;
	afx_msg void OnNMCustomdrawSpeed(NMHDR *pNMHDR, LRESULT *pResult);

	afx_msg void OnBnClickedClear();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
