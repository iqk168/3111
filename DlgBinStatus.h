#if !defined(AFX_DLGBINSTATUS_H__A00A8EBE_C234_4845_AA4D_6ACEC8B7A112__INCLUDED_)
#define AFX_DLGBINSTATUS_H__A00A8EBE_C234_4845_AA4D_6ACEC8B7A112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBinStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBinStatus dialog

class CDlgBinStatus : public CDialog
{
// Construction
public:
	CDlgBinStatus(CWnd* pParent = NULL);   // standard constructor

	void UpdateBinStatus();

// Dialog Data
	//{{AFX_DATA(CDlgBinStatus)
	enum { IDD = IDD_DLG_BIN_STATUS };
	CStatic	m_wndTesterBin;
	CStatic	m_wndArmBin;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBinStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBinStatus)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBINSTATUS_H__A00A8EBE_C234_4845_AA4D_6ACEC8B7A112__INCLUDED_)
