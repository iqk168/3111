#if !defined(AFX_DLGTIMERSETTING_H__E9AA1648_C0FA_469B_87A6_1A6808E4E5A4__INCLUDED_)
#define AFX_DLGTIMERSETTING_H__E9AA1648_C0FA_469B_87A6_1A6808E4E5A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTimerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTimerSetting dialog

class CDlgTimerSetting : public CDialog
{
// Construction
public:
	CDlgTimerSetting(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;
	void InitTips();

	// Dialog Data
	//{{AFX_DATA(CDlgTimerSetting)
	enum { IDD = IDD_TIMER_SETTING };
	CButtonST	m_btnModify;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	int			m_iInitialEachMotorWaitTime;
	int			m_iMotorRunlineTimeout;
	int			m_iMotorRunTimeout;
	int			m_iInitialZWaitTime;
	int			m_iInitialTimeout;
	int			m_iCommectionTimeout;
	int			m_iBinLogInsertTimeout;
	int			m_iScanTrayStatus;
	int			m_iArmZCheckTime;
	int			m_iRotatorTime;
	double		m_iRotatorTimeout;
	int			m_iShuttleHomeTimeout;
	int			m_iShuttlePickTimeout;
	int		m_iShuttleStableTime;
	//}}AFX_DATA
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTimerSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTimerSetting)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnModifyParameter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTIMERSETTING_H__E9AA1648_C0FA_469B_87A6_1A6808E4E5A4__INCLUDED_)
