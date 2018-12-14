
// Rota.h : main header file for the Rota application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CRotaApp:
// See Rota.cpp for the implementation of this class
//
class CWorkspace;
class CRotaApp : public CWinAppEx
{
private:
	CWorkspace* mp_workserver;
public:
	CRotaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CWorkspace* GetWorkspaceServer();
// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CRotaApp theApp;
