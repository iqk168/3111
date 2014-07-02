#if !defined(AFX_DLGVISUALBUTTON_H__F4D201FA_78B2_499F_BED7_FF80D03897E4__INCLUDED_)
#define AFX_DLGVISUALBUTTON_H__F4D201FA_78B2_499F_BED7_FF80D03897E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVisualButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVisualButton dialog

class CDlgVisualButton : public CDialog
{
// Construction
public:
	CDlgVisualButton(CWnd* pParent = NULL);   // standard constructor

	void UpdateDisplay();		// We read IO/OUT setting. and use timer to refreash it.

	bool CheckSafe();

// Dialog Data
	//{{AFX_DATA(CDlgVisualButton)
	enum { IDD = IDD_DLG_VISUAL_PANEL };
	//
	CColorFontStatic	m_wndMainMsg;
	CButtonST			m_btnOK;
	CButtonST			m_btnCancel;
	//
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
	//{{AFX_VIRTUAL(CDlgVisualButton)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVisualButton)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnRetry();
	afx_msg void OnSkip();
	afx_msg void OnInitial();
	afx_msg void OnFlush();
	afx_msg void OnReset();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVISUALBUTTON_H__F4D201FA_78B2_499F_BED7_FF80D03897E4__INCLUDED_)
