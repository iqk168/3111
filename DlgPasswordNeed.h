#if !defined(AFX_DLGPASSWORDNEED_H__19D4C8FF_0BD6_446A_ABCE_BE5C870D78D7__INCLUDED_)
#define AFX_DLGPASSWORDNEED_H__19D4C8FF_0BD6_446A_ABCE_BE5C870D78D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPasswordNeed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordNeed dialog

class CDlgPasswordNeed : public CDialog
{
// Construction
public:
	CDlgPasswordNeed(bool bEngineer,bool bDebuger, CWnd* pParent = NULL);   // standard constructor

	bool m_bEngineer;

	// 
	bool m_bDebuger;


// Dialog Data
	//{{AFX_DATA(CDlgPasswordNeed)
	enum { IDD = IDD_DLG_NEED_PASSWORD };
	CStatic	m_wndMsg;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CString	m_csPassword;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPasswordNeed)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPasswordNeed)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSWORDNEED_H__19D4C8FF_0BD6_446A_ABCE_BE5C870D78D7__INCLUDED_)
