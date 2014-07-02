#if !defined(AFX_DLGPASSWORD_H__F8ACABFA_E2F6_4D87_946E_4C3C5713C0B0__INCLUDED_)
#define AFX_DLGPASSWORD_H__F8ACABFA_E2F6_4D87_946E_4C3C5713C0B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPassword.h : header file
//

#include "Deer.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword dialog

class CDlgPassword : public CDialog
{
// Construction
public:
	CDlgPassword(bool bPassword = false, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPassword)
	enum { IDD = IDD_PASSWORD };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CButtonST	m_btnUser3;
	CButtonST	m_btnUser2;
	CButtonST	m_btnUser;
	CEdit	m_edtPassword;
	CButtonST	m_btnChangePassword;
	CStatic	m_wndNew2;
	CEdit	m_edtNewPassword2;
	CStatic	m_wndNew;
	CStatic	m_wndOld;
	CEdit	m_edtNewPassword;
	CString	m_csPassword;
	CString	m_csNewPassword;
	int		m_iUser;
	CString	m_csNewPassword2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPassword)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	bool m_bPassword;

	// Generated message map functions
	//{{AFX_MSG(CDlgPassword)
	afx_msg void OnUser();
	afx_msg void OnSetup();
	afx_msg void OnEngineer();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePassword();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSWORD_H__F8ACABFA_E2F6_4D87_946E_4C3C5713C0B0__INCLUDED_)
