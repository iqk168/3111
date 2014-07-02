#if !defined(AFX_DLGBUTTON_H__296AD179_C5C6_47D8_B1F9_02FD48D29F18__INCLUDED_)
#define AFX_DLGBUTTON_H__296AD179_C5C6_47D8_B1F9_02FD48D29F18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgButton dialog

class CDlgButton : public CDialog
{
// Construction
public:
	CDlgButton(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();

	//
	void ButtonQuery();

	//
	void SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgButton)
	enum { IDD = IDD_DLG_BUTTON };
	CButtonST	m_btnDLWest;
	CButtonST			m_btnDManual;
	CButtonST			m_btnDLTester;
	CButtonST			m_btnDLInspect;
	CButtonST			m_btnDLTestSite;
	CButtonST			m_btnDLArm;
	CListBox			m_list;
	CButtonST			m_btnOK;
	CButtonST			m_btnCancel;
	CColorFontStatic	m_wndStop;
	CColorFontStatic	m_wndStart;
	CColorFontStatic	m_wndSkip;
	CColorFontStatic	m_wndRetry;
	CColorFontStatic	m_wndOneCycle;
	CColorFontStatic	m_wndInitial;
	CColorFontStatic	m_wndReset;
	CColorFontStatic	m_wndTownerRed;
	CColorFontStatic	m_wndTownerYellow;
	CColorFontStatic	m_wndTownerGreen;
	CColorFontStatic	m_wndTownerBuzzer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgButton)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStart();
	afx_msg void OnFlush();
	afx_msg void OnStop();
	afx_msg void OnReset();
	afx_msg void OnRetry();
	afx_msg void OnSkip();
	afx_msg void OnInitial();
	afx_msg void OnSet();
	afx_msg void OnClear();
	afx_msg void OnDblclkM();
	//}}AFX_MSG

	afx_msg LRESULT OnShowMessage(WPARAM p, LPARAM l);

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBUTTON_H__296AD179_C5C6_47D8_B1F9_02FD48D29F18__INCLUDED_)
