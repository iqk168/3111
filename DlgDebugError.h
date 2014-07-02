#if !defined(AFX_DLGDEBUGERROR_H__A8FB0510_4186_40CB_BCA2_42BE9E737EC7__INCLUDED_)
#define AFX_DLGDEBUGERROR_H__A8FB0510_4186_40CB_BCA2_42BE9E737EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDebugError.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugError dialog

class CDlgDebugError : public CDialog
{
// Construction
public:
	CDlgDebugError(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDebugError)
	enum { IDD = IDD_DLG_DEBUG_ERR };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;

	int		m_iError;
	

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDebugError)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDebugError)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnOpenError();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEBUGERROR_H__A8FB0510_4186_40CB_BCA2_42BE9E737EC7__INCLUDED_)
