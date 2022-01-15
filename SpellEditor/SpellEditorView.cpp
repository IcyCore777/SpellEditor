
// SpellEditorView.cpp : ���������� ������ CSpellView
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "SpellEditor.h"
#endif
#include "zWE_Controller.h"
#include "SpellEditorDoc.h"
#include "SpellEditorView.h"

CSpellView*	CSpellView::view = 0;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSpellView

IMPLEMENT_DYNCREATE(CSpellView, CView)

BEGIN_MESSAGE_MAP(CSpellView, CView)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// ��������/����������� CSpellView

CSpellView::CSpellView()
{
	// TODO: �������� ��� ��������
	view = this;
}

CSpellView::~CSpellView()
{
}

BOOL CSpellView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �������� ����� Window ��� ����� ����������� ���������
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// ��������� CSpellView

void CSpellView::OnDraw(CDC* /*pDC*/)
{
	CSpellDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �������� ����� ��� ��������� ��� ����������� ������
}


// ����������� CSpellView

#ifdef _DEBUG
void CSpellView::AssertValid() const
{
	CView::AssertValid();
}

void CSpellView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpellDoc* CSpellView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpellDoc)));
	return (CSpellDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CSpellView


void CSpellView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	switch (nChar)
	{
	case 114:
		if (ControllerEvents.CameraMoving == zCM_DISABLED)
			ControllerEvents.CameraMoving = zCM_ENABLED;
		else
			ControllerEvents.CameraMoving = zCM_DISABLED;
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
