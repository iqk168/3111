#if !defined(AFX_DLGSITESETTING_H__0089D695_03D3_4F57_850B_26BD81F6A91F__INCLUDED_)
#define AFX_DLGSITESETTING_H__0089D695_03D3_4F57_850B_26BD81F6A91F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSiteSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteSetting dialog

class CDlgSiteSetting : public CDialog
{
// Construction
public:
	CDlgSiteSetting(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;
	void InitTips();
public:
	void CheckUIForRunMode(int mode);
// Dialog Data
	//{{AFX_DATA(CDlgSiteSetting)
	enum { IDD = IDD_DLG_SITE_SETTING };
	CEdit	m_edtDemoDummyForCatorgy2;
	CEdit	m_edtDemoDummyForCatorgy;
	CButtonST	m_btnSave;
	CEdit	m_edtDemoTestTime;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	long	m_iSiteDummyBin;
	long	m_iSiteDummyBinForCatorgy;
	//}}AFX_DATA
	CButtonST	m_btnRunMode[theApp.enRunModeEnd];

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSiteSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void UpdateRunModeStatus(int iMode);
	tagSite m_Site;

	// Generated message map functions
	//{{AFX_MSG(CDlgSiteSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnRunMode1();
	afx_msg void OnRunMode2();
	afx_msg void OnRunMode3();
	afx_msg void OnRunMode4();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSITESETTING_H__0089D695_03D3_4F57_850B_26BD81F6A91F__INCLUDED_)
