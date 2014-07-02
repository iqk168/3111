#if !defined(AFX_DLGATCMONITOR_H__C7706554_441A_472C_B6D9_CC4EC248F1D9__INCLUDED_)
#define AFX_DLGATCMONITOR_H__C7706554_441A_472C_B6D9_CC4EC248F1D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCMonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCMonitor dialog

class CDlgATCMonitor : public CDialog
{
// Construction
public:
	CDlgATCMonitor(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitLed();
	void InitTips();

	//
	void UpdateATCStatus();

// Dialog Data
	//{{AFX_DATA(CDlgATCMonitor)
	enum { IDD = IDD_DLG_ATC_MONITOR };
	CStatic	m_wndPV;
	CEdit	m_wndSV;
	CLed	m_ledEnable;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCMonitor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCMonitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMONITOR_H__C7706554_441A_472C_B6D9_CC4EC248F1D9__INCLUDED_)
