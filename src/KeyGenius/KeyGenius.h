// KeyGenius.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CKeyGeniusApp:
// See KeyGenius.cpp for the implementation of this class
//

class CKeyGeniusApp : public CWinApp
{
public:
	CKeyGeniusApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CKeyGeniusApp theApp;