#if !defined(AFX_DLGCLEARCOUNT_H__278FB359_BA4F_40B1_8AE4_A3E37DA4472B__INCLUDED_)
#define AFX_DLGCLEARCOUNT_H__278FB359_BA4F_40B1_8AE4_A3E37DA4472B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgClearCount.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgClearCount dialog

class CDlgClearCount : public CDialog
{
// Construction
public:
	CDlgClearCount(CWnd* pParent = NULL);   // standard constructor

	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgClearCount)
	enum { IDD = IDD_DLG_CLEAR_COUNT };
	CButtonST	m_btnClear;
	CColorFontStatic	m_wndCount;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgClearCount)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgClearCount)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCLEARCOUNT_H__278FB359_BA4F_40B1_8AE4_A3E37DA4472B__INCLUDED_)
