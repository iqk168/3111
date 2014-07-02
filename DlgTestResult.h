#if !defined(AFX_DLGTESTRESULT_H__FCCE835A_D55B_47D1_8CEA_EDFFA9C3C787__INCLUDED_)
#define AFX_DLGTESTRESULT_H__FCCE835A_D55B_47D1_8CEA_EDFFA9C3C787__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTestResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTestResult dialog

class CDlgTestResult : public CDialog
{
// Construction
public:
	CDlgTestResult(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTestResult)
	enum { IDD = IDD_DLG_TEST_RESULT };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestResult)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTestResult)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTRESULT_H__FCCE835A_D55B_47D1_8CEA_EDFFA9C3C787__INCLUDED_)
