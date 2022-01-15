
// SpellEditorView.h : интерфейс класса CSpellView
//

#pragma once


class CSpellView : public CView
{
protected: // создать только из сериализации
	CSpellView();
	DECLARE_DYNCREATE(CSpellView)

// Атрибуты
public:
	CSpellDoc* GetDocument() const;
	static CSpellView* view;
// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	virtual ~CSpellView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // отладочная версия в SpellEditorView.cpp
inline CSpellDoc* CSpellView::GetDocument() const
   { return reinterpret_cast<CSpellDoc*>(m_pDocument); }
#endif

