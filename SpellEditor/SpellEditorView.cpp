
// SpellEditorView.cpp : реализация класса CSpellView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
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

// создание/уничтожение CSpellView

CSpellView::CSpellView()
{
	// TODO: добавьте код создания
	view = this;
}

CSpellView::~CSpellView()
{
}

BOOL CSpellView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// рисование CSpellView

void CSpellView::OnDraw(CDC* /*pDC*/)
{
	CSpellDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}


// диагностика CSpellView

#ifdef _DEBUG
void CSpellView::AssertValid() const
{
	CView::AssertValid();
}

void CSpellView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSpellDoc* CSpellView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSpellDoc)));
	return (CSpellDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CSpellView


void CSpellView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

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
