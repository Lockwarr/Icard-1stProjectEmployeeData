
// HumanResources.h : main header file for the HumanResources application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CHumanResourcesApp:
// See HumanResources.cpp for the implementation of this class
//

class CHumanResourcesApp : public CWinAppEx
{
public:
	CHumanResourcesApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation


	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();

	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	DECLARE_MESSAGE_MAP()
};

extern CHumanResourcesApp theApp;
