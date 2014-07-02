#if !defined(AFX_DLGREMOTECONTROL_H__A8D7DE9E_64C4_46AD_B994_853CA823A0B8__INCLUDED_)
#define AFX_DLGREMOTECONTROL_H__A8D7DE9E_64C4_46AD_B994_853CA823A0B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControl dialog

class CDlgRemoteControl : public CDialog
{
// Construction
public:
	CDlgRemoteControl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControl)
	enum { IDD = IDD_DLG_REMOTE_CONTROL };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControl)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROL_H__A8D7DE9E_64C4_46AD_B994_853CA823A0B8__INCLUDED_)
