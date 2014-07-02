#if !defined(AFX_DLGSETTING_H__F76A6385_CF77_449D_86DA_7002C2DB5485__INCLUDED_)
#define AFX_DLGSETTING_H__F76A6385_CF77_449D_86DA_7002C2DB5485__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog

class CDlgSetting : public CDialog
{
// Construction
public:
	CDlgSetting(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetting)
	enum { IDD = IDD_DLG_SETTING };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;

	CString		m_csMachine;
	//}}AFX_DATA
public:
	void SetHandlerInfo();
	void SetMachineInfo();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSetting)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTING_H__F76A6385_CF77_449D_86DA_7002C2DB5485__INCLUDED_)
