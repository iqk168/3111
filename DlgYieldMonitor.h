#if !defined(AFX_DLGYIELDMONITOR_H__D2A9FA40_F9D7_458B_9D75_4ABAFDEB3E9B__INCLUDED_)
#define AFX_DLGYIELDMONITOR_H__D2A9FA40_F9D7_458B_9D75_4ABAFDEB3E9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgYieldMonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldMonitor dialog

class CDlgYieldMonitor : public CDialog
{
// Construction
public:
	CDlgYieldMonitor(CWnd* pParent = NULL);   // standard constructor

	void YieldStatus();
	void InitTips();
	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgYieldMonitor)
	enum { IDD = IDD_DLG_YIELD_MONITOR };
	CStatic	m_wndTested;
	CStatic	m_wndFailRate;
	CStatic	m_wndContinueFailStatus;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYieldMonitor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgYieldMonitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGYIELDMONITOR_H__D2A9FA40_F9D7_458B_9D75_4ABAFDEB3E9B__INCLUDED_)
