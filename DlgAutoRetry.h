#if !defined(AFX_DLGAUTORETRY_H__0AD1EF67_C124_4883_8A32_599EBD76651E__INCLUDED_)
#define AFX_DLGAUTORETRY_H__0AD1EF67_C124_4883_8A32_599EBD76651E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoRetry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetry dialog

class CDlgAutoRetry : public CDialog
{
// Construction
public:
	CDlgAutoRetry(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;
	void InitTips();
	void InitValue();
	bool CheckValue();
	
	bool m_fChange;

// Dialog Data
	//{{AFX_DATA(CDlgAutoRetry)
	enum { IDD = IDD_DLG_AUTO_RETRY };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	int		m_iArmZRetry;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAutoRetry)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAutoRetry)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeAmrzRetry();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTORETRY_H__0AD1EF67_C124_4883_8A32_599EBD76651E__INCLUDED_)
