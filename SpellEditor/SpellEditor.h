
// SpellEditor.h : главный файл заголовка для приложения SpellEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CSpellApp:
// О реализации данного класса см. SpellEditor.cpp
//

class CSpellApp : public CWinAppEx
{
public:
	CSpellApp();

	UINT  m_nAppLook;
// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSpellApp theApp;
