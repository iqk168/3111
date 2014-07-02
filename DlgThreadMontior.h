#if !defined(AFX_DLGTHREADMONTIOR_H__CB9732A7_6BBF_4501_A3F1_B2F5496FB24D__INCLUDED_)
#define AFX_DLGTHREADMONTIOR_H__CB9732A7_6BBF_4501_A3F1_B2F5496FB24D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgThreadMontior.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgThreadMontior dialog

class CDlgThreadMontior : public CDialog
{
// Construction
public:
	CDlgThreadMontior(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgThreadMontior)
	enum { IDD = IDD_DLG_THREAD_MONITOR };
	CStatic	m_wndManual;
	CStatic	m_wndTesterCtrl;	
	CStatic	m_wndInspectCtrl;
	CStatic	m_wndInserterCtrl;
	CStatic	m_wndArmCtrl;
	CStatic	m_wndSystemStatus;
	CStatic	m_wndIO;
	CStatic	m_wndErrCtrl;
	CStatic	m_wndThreadCounter;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgThreadMontior)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString GetText(tagThreadCode value, long code = 0);
	CString GetSystemText(int SystemStatus);
	void UpdateStatus();

	// Generated message map functions
	//{{AFX_MSG(CDlgThreadMontior)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTHREADMONTIOR_H__CB9732A7_6BBF_4501_A3F1_B2F5496FB24D__INCLUDED_)
