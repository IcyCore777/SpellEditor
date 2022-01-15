
// SpellEditorView.h : ��������� ������ CSpellView
//

#pragma once


class CSpellView : public CView
{
protected: // ������� ������ �� ������������
	CSpellView();
	DECLARE_DYNCREATE(CSpellView)

// ��������
public:
	CSpellDoc* GetDocument() const;
	static CSpellView* view;
// ��������
public:

// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ����������
public:
	virtual ~CSpellView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // ���������� ������ � SpellEditorView.cpp
inline CSpellDoc* CSpellView::GetDocument() const
   { return reinterpret_cast<CSpellDoc*>(m_pDocument); }
#endif

