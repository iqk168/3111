#if !defined(AFX_DLGRELOADFILE_H__E104D636_ACC9_44A2_BB9A_0C031BB64B46__INCLUDED_)
#define AFX_DLGRELOADFILE_H__E104D636_ACC9_44A2_BB9A_0C031BB64B46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgReLoadFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgReLoadFile dialog

class CDlgReLoadFile : public CDialog
{
// Construction
public:
	CDlgReLoadFile(CWnd* pParent = NULL);   // standard constructor

	void DisableUI(bool bEnable);

// Dialog Data
	//{{AFX_DATA(CDlgReLoadFile)
	enum { IDD = IDD_DLG_RELOAD_FILE };
	CButton		m_btnErrorCode;
	CButton		m_btnLanguage;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgReLoadFile)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgReLoadFile)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLoadLanguage();
	afx_msg void OnLoadErrorcode();
	afx_msg void OnLoadSystem();
	afx_msg void OnAlignment();
	afx_msg void OnRepeatTrayConfim();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGRELOADFILE_H__E104D636_ACC9_44A2_BB9A_0C031BB64B46__INCLUDED_)
