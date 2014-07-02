#if !defined(AFX_DLGOFFSETTS_H__66F4795A_659A_46CC_B4CE_EFDA9DEC6D40__INCLUDED_)
#define AFX_DLGOFFSETTS_H__66F4795A_659A_46CC_B4CE_EFDA9DEC6D40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOffsetTS.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOffsetTS dialog

class CDlgOffsetTS : public CDialog
{
// Construction
public:
	CDlgOffsetTS(CWnd* pParent = NULL);   // standard constructor
	
	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();

	bool m_fChange;

	tagOffset m_Offset;

	bool SaveData();
	bool CheckValue();

// Dialog Data
	//{{AFX_DATA(CDlgOffsetTS)
	enum { IDD = IDD_DLG_OFFSET_TS };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	double	m_dOffsetTSPick;
	double	m_dOffsetTSPlace;
	double	m_dOffsetTSContact;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOffsetTS)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOffsetTS)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeOffsetTsPick();
	afx_msg void OnChangeOffsetTsPlace();
	afx_msg void OnChangeOffsetTsContact();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOFFSETTS_H__66F4795A_659A_46CC_B4CE_EFDA9DEC6D40__INCLUDED_)
