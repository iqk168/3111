#if !defined(AFX_DLGATCMODULESETTING_H__E75E8695_79CF_423D_BB26_BDDDF14ADD83__INCLUDED_)
#define AFX_DLGATCMODULESETTING_H__E75E8695_79CF_423D_BB26_BDDDF14ADD83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCModuleSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleSetting dialog

class CDlgATCModuleSetting : public CDialog
{
// Construction
public:
	CDlgATCModuleSetting(CString csFile = _T(""), CWnd* pParent = NULL);   // standard constructor

	CString m_csFile;
	bool m_fChange;
	void InitValue();
	bool SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgATCModuleSetting)
	enum { IDD = IDD_DLG_ATC_MODULE_SETTING };
	CStatic	m_wndFileName;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	double	m_dChangeStableTime;
	double	m_dTemperatureRange;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCModuleSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCModuleSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangePTempRange();
	afx_msg void OnChangePChangeStableTime();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMODULESETTING_H__E75E8695_79CF_423D_BB26_BDDDF14ADD83__INCLUDED_)
