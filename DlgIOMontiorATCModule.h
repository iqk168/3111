#if !defined(AFX_DLGIOMONTIORATCMODULE_H__C2A681A0_19DB_4FD8_BA77_7107A928B6FE__INCLUDED_)
#define AFX_DLGIOMONTIORATCMODULE_H__C2A681A0_19DB_4FD8_BA77_7107A928B6FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOMontiorATCModule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorATCModule dialog

class CDlgIOMontiorATCModule : public CDialog
{
// Construction
public:
	CDlgIOMontiorATCModule(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitLed();
	void InitTips();
	void IOQuery();

	//
	void ReDrawUI();

	//
	bool m_bOnlyShow;
	void SetOnlyShow(bool bOnlyShow);

// Dialog Data
	//{{AFX_DATA(CDlgIOMontiorATCModule)
	enum { IDD = IDD_DLG_IOMONITOR_ATC_MODULE };
	CLed	m_ledATCFan2;
	CLed	m_ledATCFan1;
	CLed	m_ledATCWaterFlow;
	CLed	m_ledATCWaterPump;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOMontiorATCModule)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOMontiorATCModule)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLedAtcWaterPump();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMONTIORATCMODULE_H__C2A681A0_19DB_4FD8_BA77_7107A928B6FE__INCLUDED_)
