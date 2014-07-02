#if !defined(AFX_DLGREPEATTRAYENABLE_H__8C57BA18_03A5_4C35_9D60_6308A2F6D5ED__INCLUDED_)
#define AFX_DLGREPEATTRAYENABLE_H__8C57BA18_03A5_4C35_9D60_6308A2F6D5ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatTrayEnable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayEnable dialog

class CDlgRepeatTrayEnable : public CDialog
{
// Construction
public:
	CDlgRepeatTrayEnable(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();

	tagEnableRepeatTray m_EnableRepeatTrayFun; 

// Dialog Data
	//{{AFX_DATA(CDlgRepeatTrayEnable)
	enum { IDD = IDD_DLG_REPEAT_TRAY_ENABLE };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	BOOL	m_bInputOutCtrl;
	BOOL	m_bBiningFunctionCtrl;
	BOOL	m_bNoneCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatTrayEnable)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatTrayEnable)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATTRAYENABLE_H__8C57BA18_03A5_4C35_9D60_6308A2F6D5ED__INCLUDED_)
