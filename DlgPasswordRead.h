#if !defined(AFX_DLGPASSWORDREAD_H__98333350_FA4E_495B_AE74_AB446C2444C3__INCLUDED_)
#define AFX_DLGPASSWORDREAD_H__98333350_FA4E_495B_AE74_AB446C2444C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPasswordRead.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordRead dialog

class CDlgPasswordRead : public CDialog
{
// Construction
public:
	CDlgPasswordRead(CWnd* pParent = NULL);   // standard constructor

	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgPasswordRead)
	enum { IDD = IDD_PASSWORD_READ };
	CStatic	m_wndEngineerPw;
	CStatic	m_wndSetupPw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPasswordRead)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPasswordRead)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPASSWORDREAD_H__98333350_FA4E_495B_AE74_AB446C2444C3__INCLUDED_)
