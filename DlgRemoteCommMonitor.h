#if !defined(AFX_DLGREMOTECOMMMONITOR_H__CC27811C_F79B_43BB_9FAD_490BE9777C62__INCLUDED_)
#define AFX_DLGREMOTECOMMMONITOR_H__CC27811C_F79B_43BB_9FAD_490BE9777C62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteCommMonitor.h : header file
//

#define _R_REV		"R:"
#define _R_SEND		"S:"

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMonitor dialog

class CDlgRemoteCommMonitor : public CDialog
{
// Construction
public:
	CDlgRemoteCommMonitor(CWnd* pParent = NULL);   // standard constructor

public:

	void InsertLogRaw(CString csLog);
	void InsertLogCmd(CString csLog);
	void DeleteLog(CString csFileName );

	long m_lMonitorDataCount;

// Dialog Data
	//{{AFX_DATA(CDlgRemoteCommMonitor)
	enum { IDD = IDD_DLG_REMOTE_COMMUNICATION_MONITOR };
	CListBox	m_wndLogRaw;
	CListBox	m_wndLogCmd;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteCommMonitor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteCommMonitor)
	virtual BOOL OnInitDialog();
	afx_msg void OnEClearRawLog();
	afx_msg void OnEClearLog();
	afx_msg void OnEDelRawLog();
	afx_msg void OnEDelLog();
	afx_msg void OnSelchangeListLogCmd();
	afx_msg void OnDblclkListLogCmd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECOMMMONITOR_H__CC27811C_F79B_43BB_9FAD_490BE9777C62__INCLUDED_)
