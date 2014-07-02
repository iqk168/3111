#if !defined(AFX_DLGSLTPROTOCOLHELP_H__E3B4332B_FDBD_4838_858C_7FDC5C89C053__INCLUDED_)
#define AFX_DLGSLTPROTOCOLHELP_H__E3B4332B_FDBD_4838_858C_7FDC5C89C053__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSLTProtocolHelp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolHelp dialog

class CDlgSLTProtocolHelp : public CDialog
{
// Construction
public:
	CDlgSLTProtocolHelp(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void InitUI();

// Dialog Data
	//{{AFX_DATA(CDlgSLTProtocolHelp)
	enum { IDD = IDD_DLG_SLT_PROTOCOL_HELP };
	CRichEditCtrl	m_wndSLTHelp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSLTProtocolHelp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSLTProtocolHelp)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLTPROTOCOLHELP_H__E3B4332B_FDBD_4838_858C_7FDC5C89C053__INCLUDED_)
