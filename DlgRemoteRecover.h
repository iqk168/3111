#if !defined(AFX_DLGREMOTERECOVER_H__6F066FAB_AB33_48DC_9026_90EA939B45C1__INCLUDED_)
#define AFX_DLGREMOTERECOVER_H__6F066FAB_AB33_48DC_9026_90EA939B45C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteRecover.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteRecover dialog

class CDlgRemoteRecover : public CDialog
{
// Construction
public:
	CDlgRemoteRecover(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteRecover)
	enum { IDD = IDD_DLG_REMOTE_RECOVER };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteRecover)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteRecover)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTERECOVER_H__6F066FAB_AB33_48DC_9026_90EA939B45C1__INCLUDED_)
