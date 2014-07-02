#if !defined(AFX_DLGATCMODULEMODIFY_H__687032F9_D521_4871_9F06_5B516EE9B887__INCLUDED_)
#define AFX_DLGATCMODULEMODIFY_H__687032F9_D521_4871_9F06_5B516EE9B887__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCModuleModify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleModify dialog
#include "ComboListCtrl.h"

class CDlgATCModuleModify : public CDialog
{
// Construction
public:
	CDlgATCModuleModify(CString csFile = _T(""), CWnd* pParent = NULL);   // standard constructor
	CString m_csFile;
	void Style();
	void InitValue();
	void InitGrid();

// Dialog Data
	//{{AFX_DATA(CDlgATCModuleModify)
	enum { IDD = IDD_DLG_ATC_MODULE_MODIFY };
	CComboListCtrl	m_listData;
	CColorFontStatic	m_wndFile;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCModuleModify)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCModuleModify)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMODULEMODIFY_H__687032F9_D521_4871_9F06_5B516EE9B887__INCLUDED_)
