#if !defined(AFX_DLGCOMMUNICATION_H__58D23D2D_01A7_4EC6_B856_24A2167FF6D4__INCLUDED_)
#define AFX_DLGCOMMUNICATION_H__58D23D2D_01A7_4EC6_B856_24A2167FF6D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCommunication.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCommunication dialog

class CDlgCommunication : public CDialog
{
// Construction
public:
	CDlgCommunication(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCommunication)
	enum { IDD = IDD_DLG_COMMUNICATION };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCommunication)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCommunication)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMMUNICATION_H__58D23D2D_01A7_4EC6_B856_24A2167FF6D4__INCLUDED_)
