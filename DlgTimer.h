#if !defined(AFX_DLGTIMER_H__8DDCB6F0_3B06_409A_A960_44EF94309914__INCLUDED_)
#define AFX_DLGTIMER_H__8DDCB6F0_3B06_409A_A960_44EF94309914__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer dialog

class CDlgTimer : public CDialog
{
// Construction
public:
	CDlgTimer(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	bool CheckValue();

	CToolTipCtrl m_ToolTip;

	void InitTips();

	bool m_fChange;

// Dialog Data
	//{{AFX_DATA(CDlgTimer)
	enum { IDD = IDD_TIMER };
	CButtonST	m_btnModify;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;

	// Arm
	double	m_dInsertPuff;
	double	m_dInsertPick;
	double	m_dPickPuff;
	double	m_dPickPick;

	// Tray transfer
	double	m_dTrayDown;
	double	m_dTrayPuff;
	double	m_dTrayVacc;

	// Cooling
	double m_dCoolingWaitTime;

	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTimer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTimer)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnModifyParameter();
	afx_msg void OnChangePickVac();
	afx_msg void OnChangePickPuff();
	afx_msg void OnChangeInserterPickVac();
	afx_msg void OnChangeInserterPickPuff();
	afx_msg void OnChangeCoolingWaitTime();
	afx_msg void OnChangeTrayVacc();
	afx_msg void OnChangeTrayPuff();
	afx_msg void OnChangeTrayDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMER_H__8DDCB6F0_3B06_409A_A960_44EF94309914__INCLUDED_)
