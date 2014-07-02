#if !defined(AFX_DLGATCMODULENEW_H__BB6EA4C9_0692_407A_9B61_67B48954FD0F__INCLUDED_)
#define AFX_DLGATCMODULENEW_H__BB6EA4C9_0692_407A_9B61_67B48954FD0F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCModuleNew.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleNew dialog

class CDlgATCModuleNew : public CDialog
{
// Construction
public:
	CDlgATCModuleNew(CString csFile = _T(""), CWnd* pParent = NULL);   // standard constructor
	CString m_csFile;
	void InitValue();
	bool CreateNewFile(); // success return true
	bool IsFileExist(CString csFile);
		
// Dialog Data
	//{{AFX_DATA(CDlgATCModuleNew)
	enum { IDD = IDD_DLG_ATC_MODULE_NEW };
	CEdit	m_wndNewFile;
	CColorFontStatic	m_wndBaseFile;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCModuleNew)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCModuleNew)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMODULENEW_H__BB6EA4C9_0692_407A_9B61_67B48954FD0F__INCLUDED_)
