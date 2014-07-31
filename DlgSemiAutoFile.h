#if !defined(AFX_DLGSEMIAUTOFILE_H__F60C90FE_9A8B_448D_BA67_BC8981044AD3__INCLUDED_)
#define AFX_DLGSEMIAUTOFILE_H__F60C90FE_9A8B_448D_BA67_BC8981044AD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSemiAutoFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSemiAutoFile dialog

class CDlgSemiAutoFile : public CDialog
{
// Construction
public:
	CDlgSemiAutoFile(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSemiAutoFile)
	enum { IDD = IDD_DLG_SEMIAUTOFILE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSemiAutoFile)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSemiAutoFile)
	afx_msg void OnBSet();
	afx_msg void OnBAdd();
	afx_msg void OnBDelete();
	afx_msg void OnBUp();
	afx_msg void OnBDown();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSEMIAUTOFILE_H__F60C90FE_9A8B_448D_BA67_BC8981044AD3__INCLUDED_)
