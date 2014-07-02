// Interface.h : main header file for the INTERFACE application
//

#if !defined(AFX_INTERFACE_H__EC6214C6_D0DF_4C54_A258_0110DA5B291B__INCLUDED_)
#define AFX_INTERFACE_H__EC6214C6_D0DF_4C54_A258_0110DA5B291B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp:
// See Interface.cpp for the implementation of this class
//

#include "BtnST.h"
#include "ColorBtn.h"
#include "Interface.h"
#include "Member.h"
#include "Parser3111.h"
class CInterfaceApp : public CWinApp
{
public:
	void Add(char *buff, int size);
	CInterfaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CInterfaceApp theApp;
extern CMember m;
extern UINT ReadThread(LPVOID p);

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACE_H__EC6214C6_D0DF_4C54_A258_0110DA5B291B__INCLUDED_)
