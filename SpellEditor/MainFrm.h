
// MainFrm.h : ��������� ������ CMainFrame
//

#pragma once

class CControl;

class CMainFrame : public CFrameWndEx
{
	
protected: // ������� ������ �� ������������

	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
public: 
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	int					size_x, size_y;
// ��������
public:
	static CMainFrame*		mainframe;
	CControl* wndControl;
// ��������
public:

// ���������������
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����������
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ���������� ����� ������ ��������� ����������
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ��������� ������� ����� ���������
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

public:
	void InitWindows();
	afx_msg void OnClear();
	afx_msg void OnAppExit();
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
};


