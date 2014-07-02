// TcpInterface.h : main header file for the TCPINTERFACE application
//

#if !defined(AFX_TCPINTERFACE_H__3E519F8E_E2DB_4999_A432_11A17D05D144__INCLUDED_)
#define AFX_TCPINTERFACE_H__3E519F8E_E2DB_4999_A432_11A17D05D144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTcpInterfaceApp:
// See TcpInterface.cpp for the implementation of this class
//

class CTcpInterfaceApp : public CWinApp
{
public:
	CTcpInterfaceApp();
	int m_iIndex;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpInterfaceApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTcpInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTcpInterfaceApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPINTERFACE_H__3E519F8E_E2DB_4999_A432_11A17D05D144__INCLUDED_)
