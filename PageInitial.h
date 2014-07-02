#if !defined(AFX_PAGEINITIAL_H__A7AEDAC7_FDC2_4A26_B7BE_F9E8FEF47F47__INCLUDED_)
#define AFX_PAGEINITIAL_H__A7AEDAC7_FDC2_4A26_B7BE_F9E8FEF47F47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageInitial.h : header file
//

#include "led.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CPageInitial dialog

class CPageInitial : public CDialog
{
// Construction
public:
	CPageInitial(CWnd* pParent = NULL);   // standard constructor

	void InitLed();
	void UpdateInitialStatus();

	void SetTimeClock(); // We set a timer for updata initial complete or not.!

	CString csLmt;

// Dialog Data
	//{{AFX_DATA(CPageInitial)
	enum { IDD = IDD_PAGE_INITIAL };
	CStatic	m_wndInserter;
	CStatic	m_wndArmZ;
	CStatic	m_wndArmY;
	CStatic	m_wndArmX;
	CStatic	m_wndArmXMotor;
	CStatic	m_wndArmYMotor;
	CStatic	m_wndArmZMotor;
	CStatic	m_wndTestSiteMotor;
	CLed	m_ledInserter;
	CLed	m_ledArmZ;
	CLed	m_ledArmY;
	CLed	m_ledArmX;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageInitial)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageInitial)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEINITIAL_H__A7AEDAC7_FDC2_4A26_B7BE_F9E8FEF47F47__INCLUDED_)
