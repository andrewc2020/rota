// ScenarioLib.h : main header file for the ScenarioLib DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CScenarioLibApp
// See ScenarioLib.cpp for the implementation of this class
//

class CScenarioLibApp : public CWinApp
{
public:
	CScenarioLibApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
