#if !defined(AFX_DLGMAIL_H__CBE7021E_6EC3_4E8E_A5F5_A3C12365C009__INCLUDED_)
#define AFX_DLGMAIL_H__CBE7021E_6EC3_4E8E_A5F5_A3C12365C009__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMail dialog

class CDlgMail : public CDialog
{
// Construction
public:
	CDlgMail(CWnd* pParent = NULL);   // standard constructor

	bool m_fChange;

	tagMailSetting	m_MailSetting;
	void InitValue();

public:
	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgMail)
	enum { IDD = IDD_DLG_MAIL };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CString	m_csSmtpContent1;
	CString	m_csSmtpContent2;
	CString	m_csSmtpFrom;
	CString	m_csSmtpLoginName;
	CString	m_csSmtpLoginPwd;
	int		m_iSmtpPort;
	CString	m_csSmtpServer;
	CString	m_csSmtpSubject;
	CString	m_csSmtpTo1;
	CString	m_csSmtpTo2;
	CString	m_csSmtpName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMail)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeESmtpContent1();
	afx_msg void OnChangeESmtpContent2();
	afx_msg void OnChangeESmtpFrom();
	afx_msg void OnChangeESmtpLoginName();
	afx_msg void OnChangeESmtpLoginPwd();
	afx_msg void OnChangeESmtpPort();
	afx_msg void OnChangeESmtpServer();
	afx_msg void OnChangeESmtpSubject();
	afx_msg void OnChangeESmtpTo1();
	afx_msg void OnChangeESmtpTo2();
	afx_msg void OnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMAIL_H__CBE7021E_6EC3_4E8E_A5F5_A3C12365C009__INCLUDED_)
