#if !defined(AFX_DLGCONTACTCOUNTER_H__7D786F33_5DE1_4EF9_A014_69D141F73455__INCLUDED_)
#define AFX_DLGCONTACTCOUNTER_H__7D786F33_5DE1_4EF9_A014_69D141F73455__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgContactCounter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgContactCounter dialog

class CDlgContactCounter : public CDialog
{
// Construction
public:
	CDlgContactCounter(bool bClear = true, CWnd* pParent = NULL);   // standard constructor

	// 
	bool m_bClear;

// Dialog Data
	//{{AFX_DATA(CDlgContactCounter)
	enum { IDD = IDD_DLG_CONTACT_COUNTER };
	CButtonST	m_btnClear;
	CStatic	m_wndContactCounter;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgContactCounter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgContactCounter)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCONTACTCOUNTER_H__7D786F33_5DE1_4EF9_A014_69D141F73455__INCLUDED_)
