#if !defined(AFX_DLGCUSTOMMCFUNCTION_H__3C7E542E_9351_4E95_A241_4C4D7EA527A7__INCLUDED_)
#define AFX_DLGCUSTOMMCFUNCTION_H__3C7E542E_9351_4E95_A241_4C4D7EA527A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCustomMCFunction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomMCFunction dialog

class CDlgCustomMCFunction : public CDialog
{
// Construction
public:
	CDlgCustomMCFunction(CWnd* pParent = NULL);   // standard constructor

	void InitOption();
	void SaveData();

public:
	tagManualContactEnable m_MCFunction;

// Dialog Data
	//{{AFX_DATA(CDlgCustomMCFunction)
	enum { IDD = IDD_DLG_CUSTOM_MC_FUN };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	BOOL	m_bManualTorque;
	BOOL	m_bManualTemp;
	BOOL	m_bManualOffset;
	BOOL	m_bManualIFTesting;
	BOOL	m_bManualTsDirectContact;
	BOOL	m_bManualTestSieVacc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCustomMCFunction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCustomMCFunction)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCUSTOMMCFUNCTION_H__3C7E542E_9351_4E95_A241_4C4D7EA527A7__INCLUDED_)
