#if !defined(AFX_DLGLOGENABLE_H__57F49E9C_BA9F_4F58_B5CB_59CBA56C87C0__INCLUDED_)
#define AFX_DLGLOGENABLE_H__57F49E9C_BA9F_4F58_B5CB_59CBA56C87C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogEnable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogEnable dialog

class CDlgLogEnable : public CDialog
{
// Construction
public:
	CDlgLogEnable(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgLogEnable)
	enum { IDD = IDD_DLG_LOG_ENABLE };
	CButton	m_btnShuttleJamLog;
	CButton	m_btnEnableUPHDataLog;
	CButton	m_btnEnableJamReport;
	CButton	m_btnEnableCCDSocketLog;
	CButton	m_btnStatusReportLog;
	CButton	m_btnMotorLog;
	CButton	m_btnDualMotorLog;
	CButton	m_btnSingleMotorLog;
	CButton	m_btnEnableCommLog;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLogEnable)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLogEnable)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOGENABLE_H__57F49E9C_BA9F_4F58_B5CB_59CBA56C87C0__INCLUDED_)
