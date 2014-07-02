#if !defined(AFX_DLGBINNEW_H__1B16F7F9_61AB_4081_BF34_846F3B6DB1EA__INCLUDED_)
#define AFX_DLGBINNEW_H__1B16F7F9_61AB_4081_BF34_846F3B6DB1EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBinNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBinNew dialog

class CDlgBinNew : public CDialog
{
// Construction
public:
	CDlgBinNew(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBinNew)
	enum { IDD = IDD_DLG_BIN_NEW };
	CStatic	m_wndMappingBase;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CString	m_csNewFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBinNew)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBinNew)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBINNEW_H__1B16F7F9_61AB_4081_BF34_846F3B6DB1EA__INCLUDED_)
