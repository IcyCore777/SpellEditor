
// SpellEditor.h : ������� ���� ��������� ��� ���������� SpellEditor
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������


// CSpellApp:
// � ���������� ������� ������ ��. SpellEditor.cpp
//

class CSpellApp : public CWinAppEx
{
public:
	CSpellApp();

	UINT  m_nAppLook;
// ���������������
public:
	virtual BOOL InitInstance();

// ����������
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSpellApp theApp;
