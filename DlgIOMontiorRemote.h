#if !defined(AFX_DLGIOMONTIORREMOTE_H__3E3A2940_BC58_42DA_8B7C_64826658A851__INCLUDED_)
#define AFX_DLGIOMONTIORREMOTE_H__3E3A2940_BC58_42DA_8B7C_64826658A851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOMontiorRemote.h : header file
//
// GroupBox
#include "GroupControl.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorRemote dialog

class CDlgIOMontiorRemote : public CDialog
{
// Construction
public:
	CDlgIOMontiorRemote(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitLed();
	void InitTips();
	void IOQuery();

	void IODebug();

	//
	void ReDrawUI();

	//
	bool m_bOnlyShow;
	void SetOnlyShow(bool bOnlyShow);

	BOOL m_bShowEnable;

// Dialog Data
	//{{AFX_DATA(CDlgIOMontiorRemote)
	enum { IDD = IDD_DLG_IOMONITOR_REMOTE };
	CStatic	m_wndDebugAvg;
	CStatic	m_wndDebugCount;
	CStatic	m_wndDebugError;
	CGroupControl	m_wndDebugGroup;
	CLed	m_ledOutStop;
	CLed	m_ledOutStart;
	CLed	m_ledOutSkip;
	CLed	m_ledOutRetry;
	CLed	m_ledOutReset;
	CLed	m_ledOutOneCycle;
	CLed	m_ledOutInitial;
	CLed	m_ledPInStop;
	CLed	m_ledPInStart;
	CLed	m_ledPInSkip;
	CLed	m_ledPInRetry;
	CLed	m_ledPInReset;
	CLed	m_ledPInOneCycle;
	CLed	m_ledPInInitial;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOMontiorRemote)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOMontiorRemote)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLedPOutStart();
	afx_msg void OnLedPOutOnecycle();
	afx_msg void OnLedPOutStop();
	afx_msg void OnLedPOutReset();
	afx_msg void OnLedPOutSkip();
	afx_msg void OnLedPOutRetry();
	afx_msg void OnLedPOutInitial();
	afx_msg void OnStaticDebug();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMONTIORREMOTE_H__3E3A2940_BC58_42DA_8B7C_64826658A851__INCLUDED_)
