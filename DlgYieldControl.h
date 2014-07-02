#if !defined(AFX_DLGYIELDCONTROL_H__1AB2747B_3E90_42B2_8FE2_6D52D1014F89__INCLUDED_)
#define AFX_DLGYIELDCONTROL_H__1AB2747B_3E90_42B2_8FE2_6D52D1014F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgYieldControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldControl dialog

class CDlgYieldControl : public CDialog
{
// Construction
public:
	CDlgYieldControl(bool Mode = false , CWnd* pParent = NULL);   // standard constructor

	bool m_fChange;
	bool m_Mode; // if true. it mean setup level. setup level can modify yield setting
	void LevelControl();

public:
	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgYieldControl)
	enum { IDD = IDD_YIELD_SETTING };

	CEdit	m_edtContineFail;
	CEdit	m_edtYieldWindow;
	CEdit	m_edtYieldLimit;
	CEdit	m_edtRetestCount;
	CButtonST	m_btnSave;
	CButtonST	m_btnContinueFail;
	CButtonST	m_btnYieldControl;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CButtonST	m_btnDropMode;
	CEdit		m_edtDropTime;
	CEdit		m_edtDropHigh;
	double		m_dDropHigh;
	double		m_dDropTime;
	int			iRetestCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgYieldControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateStatus();
	tagYieldSetting m_YieldSetting;

	// Generated message map functions
	//{{AFX_MSG(CDlgYieldControl)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnSave();
	afx_msg void OnEnableYieldControl();
	afx_msg void OnEnableContinueFail();
	afx_msg void OnChangeYieldLimit();
	afx_msg void OnChangeContinueFail();
	afx_msg void OnChangeYieldWindows();
	afx_msg void OnChangeReset();
	afx_msg void OnDropMode();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGYIELDCONTROL_H__1AB2747B_3E90_42B2_8FE2_6D52D1014F89__INCLUDED_)
