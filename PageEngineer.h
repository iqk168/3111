#if !defined(AFX_PAGEENGINEER_H__9EF233BA_0FAE_4114_A9E3_6D8384564E62__INCLUDED_)
#define AFX_PAGEENGINEER_H__9EF233BA_0FAE_4114_A9E3_6D8384564E62__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageEngineer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageEngineer dialog

class CPageEngineer : public CDialog
{
// Construction
public:
	CPageEngineer(CWnd* pParent = NULL);   // standard constructor
	
	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);
	void ReDrawUI();

	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CPageEngineer)
	enum { IDD = IDD_PAGE_ENGINEER };
	CButtonST	m_btnAlarmMail;
	CButtonST	m_btnLoopTest;
	CButtonST	m_btnSocketCCDSetup;
	CButtonST	m_btnContactCounter;
	CButtonST	m_btnEventLog;
	CButtonST	m_btnMotorMonitor;
	CButtonST	m_btnSpeed;
	CButtonST	m_btnChangeFile;
	CButtonST	m_btnIOMonitor;
	CButtonST	m_btnAlignment;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageEngineer)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageEngineer)
	virtual BOOL OnInitDialog();
	afx_msg void OnSpeed();
	afx_msg void OnChangeFile();
	afx_msg void OnMotorMontior();
	afx_msg void OnIoMontior();
	afx_msg void OnAlignmentSetup();
	afx_msg void OnEventLog();
	afx_msg void OnContactCounter2();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnCcdDoubleDetect();
	afx_msg void OnLoopTest();
	afx_msg void OnAlarmMail();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEENGINEER_H__9EF233BA_0FAE_4114_A9E3_6D8384564E62__INCLUDED_)
