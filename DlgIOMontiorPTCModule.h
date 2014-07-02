#if !defined(AFX_DLGIOMONTIORPTCMODULE_H__57E581A5_73DE_415A_AF8F_2C0B878E7A01__INCLUDED_)
#define AFX_DLGIOMONTIORPTCMODULE_H__57E581A5_73DE_415A_AF8F_2C0B878E7A01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOMontiorPTCModule.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorPTCModule dialog

class CDlgIOMontiorPTCModule : public CDialog
{
// Construction
public:
	CDlgIOMontiorPTCModule(CWnd* pParent = NULL);   // standard constructor

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
	//{{AFX_DATA(CDlgIOMontiorPTCModule)
	enum { IDD = IDD_DLG_IOMONITOR_PTC_MODULE };
	CLed	m_ledPTCFan2;
	CLed	m_ledPTCFan1;
	CLed	m_ledPTCWaterFlow;
	CLed	m_ledPTCWaterPump;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOMontiorPTCModule)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOMontiorPTCModule)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLedPtcWaterPump();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMONTIORPTCMODULE_H__57E581A5_73DE_415A_AF8F_2C0B878E7A01__INCLUDED_)
