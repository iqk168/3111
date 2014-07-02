#if !defined(AFX_DLGAUTORETRYSETTING_H__23D0B3AA_EFC4_4B26_AE7D_ED3006DE10C0__INCLUDED_)
#define AFX_DLGAUTORETRYSETTING_H__23D0B3AA_EFC4_4B26_AE7D_ED3006DE10C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAutoRetrySetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetrySetting dialog

class CDlgAutoRetrySetting : public CDialog
{
// Construction
public:
	CDlgAutoRetrySetting(CWnd* pParent = NULL);   // standard constructor

	//
	void DisplayEnableStatus();
	void InitValue();
	bool SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgAutoRetrySetting)
	enum { IDD = IDD_DLG_AUTO_RETRY_SET };
	CLed	m_ledEnableAutoRetry;
	CButton	m_btnAlwaysAdjust;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	double	m_dAdjustValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAutoRetrySetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAutoRetrySetting)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnELedEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAUTORETRYSETTING_H__23D0B3AA_EFC4_4B26_AE7D_ED3006DE10C0__INCLUDED_)
