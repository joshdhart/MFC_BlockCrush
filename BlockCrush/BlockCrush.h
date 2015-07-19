
// BlockCrush.h : main header file for the BlockCrush application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBlockCrushApp:
// See BlockCrush.cpp for the implementation of this class
//

class CBlockCrushApp : public CWinApp
{
public:
	CBlockCrushApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBlockCrushApp theApp;
