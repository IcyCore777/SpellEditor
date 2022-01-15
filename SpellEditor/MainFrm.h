
// MainFrm.h : интерфейс класса CMainFrame
//

#pragma once

class CControl;

class CMainFrame : public CFrameWndEx
{
	
protected: // создать только из сериализации

	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)
public: 
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	int					size_x, size_y;
// Атрибуты
public:
	static CMainFrame*		mainframe;
	CControl* wndControl;
// Операции
public:

// Переопределение
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // встроенные члены панели элементов управления
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// Созданные функции схемы сообщений
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


