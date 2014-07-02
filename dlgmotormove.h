#if !defined(AFX_DLGMOTORMOVE_H__68B08134_83F5_4D4B_B9EF_8320D82EBC3F__INCLUDED_)
#define AFX_DLGMOTORMOVE_H__68B08134_83F5_4D4B_B9EF_8320D82EBC3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMotorMove.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMove dialog

class CDlgMotorMove : public CDialog
{
// Construction
public:
	CDlgMotorMove(long now, CWnd* pParent = NULL);   // standard constructor

	
// Dialog Data
	//{{AFX_DATA(CDlgMotorMove)
	enum { IDD = IDD_MOVE };
	CEdit	m_wndMotorNew;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	long	m_New;
	long	m_Now;
	long	m_NewGo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMotorMove)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMotorMove)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOTORMOVE_H__68B08134_83F5_4D4B_B9EF_8320D82EBC3F__INCLUDED_)
