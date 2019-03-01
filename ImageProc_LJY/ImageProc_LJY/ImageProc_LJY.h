
// ImageProc_LJY.h : main header file for the ImageProc_LJY application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CImageProc_LJYApp:
// See ImageProc_LJY.cpp for the implementation of this class
//

class CImageProc_LJYApp : public CWinApp
{
public:
	CImageProc_LJYApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CImageProc_LJYApp theApp;
