#if !defined(AFX_THTESTING_H__21C4CBCD_1843_4F7E_B436_C6397684C930__INCLUDED_)
#define AFX_THTESTING_H__21C4CBCD_1843_4F7E_B436_C6397684C930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThTesting.h : header file
//

#include "NetInterface.h"

/////////////////////////////////////////////////////////////////////////////
// CThTesting thread

class CThTesting : public CWinThread
{
	DECLARE_DYNCREATE(CThTesting)
public:
	CThTesting();           // protected constructor used by dynamic creation
	CThTesting(int iID); 
	virtual ~CThTesting();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThTesting)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	int m_iID;
	CNetInterface m_Interface;

	// Generated message map functions
	//{{AFX_MSG(CThTesting)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void ShowMessage(CString cs);
	 bool InitialConnect();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THTESTING_H__21C4CBCD_1843_4F7E_B436_C6397684C930__INCLUDED_)
