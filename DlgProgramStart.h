#if !defined(AFX_DLGPROGRAMSTART_H__876D9D8C_225E_467C_933E_7CC540B0618B__INCLUDED_)
#define AFX_DLGPROGRAMSTART_H__876D9D8C_225E_467C_933E_7CC540B0618B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgProgramStart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgProgramStart dialog

class CDlgProgramStart : public CDialog
{
// Construction
public:
	CDlgProgramStart(CWnd* pParent = NULL);   // standard constructor

	void Style();
	bool m_bPass;

public:
	CString GetFilePath();
// Dialog Data
	//{{AFX_DATA(CDlgProgramStart)
	enum { IDD = IDD_PROGRAM_START };
	CColorListCtrl	m_listShowCtrl;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgProgramStart)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgProgramStart)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROGRAMSTART_H__876D9D8C_225E_467C_933E_7CC540B0618B__INCLUDED_)
