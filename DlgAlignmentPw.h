#if !defined(AFX_DLGALIGNMENTPW_H__8C52BA57_AD18_4749_81B2_DAE84B310AA8__INCLUDED_)
#define AFX_DLGALIGNMENTPW_H__8C52BA57_AD18_4749_81B2_DAE84B310AA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlignmentPw.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentPw dialog

class CDlgAlignmentPw : public CDialog
{
// Construction
public:
	CDlgAlignmentPw(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlignmentPw)
	enum { IDD = IDD_DLG_ALIGNMENT_PW };
	CString	m_csPw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlignmentPw)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlignmentPw)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALIGNMENTPW_H__8C52BA57_AD18_4749_81B2_DAE84B310AA8__INCLUDED_)
